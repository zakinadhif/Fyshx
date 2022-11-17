#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>
#include <unordered_map>
#include <cassert>
#include <optional>

#include "fmt/printf.h"

struct Body {
	sf::Vector2f position;
	float rotation;
	float radius;

	Body(const sf::Vector2f& position, float rotation, float radius)
		: position(position), rotation(rotation), radius(radius) {}
};

class ShaderManager {
	private:
		struct Shader {
			sf::Shader innerSfmlShader;
			std::string vertexShaderPath;
			std::string fragmentShaderPath;
		};

	public:
		sf::Shader& load(
				const std::string& name,
				const std::string& vsPath,
				const std::string& fsPath
				) {
			auto [shaderPairIter, isEmplaceSuccessful] = m_shaders.try_emplace(name);
			assert(isEmplaceSuccessful);
			
			auto& [key, shader] = *shaderPairIter;
			shader.vertexShaderPath = vsPath;
			shader.fragmentShaderPath = fsPath;

			// SFML should print errors when shader fails to load or compile
			auto& innerSfmlShader = shader.innerSfmlShader;
			innerSfmlShader.loadFromFile(shader.vertexShaderPath, shader.fragmentShaderPath);

			return innerSfmlShader;
		}

		sf::Shader* get(const std::string& name) {
			if (m_shaders.contains(name)) {
				return &m_shaders[name].innerSfmlShader;
			} else {
				return nullptr;
			}
		}

		void refresh() {
			for (auto& [key, shader] : m_shaders) {
				// SFML should print errors when shader fails to load or compile
				auto& innerSfmlShader = shader.innerSfmlShader;
				innerSfmlShader.loadFromFile(shader.vertexShaderPath, shader.fragmentShaderPath);
			}
		}

	private:
		std::unordered_map<std::string, Shader> m_shaders;
};

void renderBodies(sf::RenderTarget& target, const std::vector<Body>& bodies)
{
	sf::CircleShape circle;

	for (const auto& body : bodies) {
		circle.setPosition(body.position);
		circle.setRotation(body.rotation);
		circle.setRadius(body.radius);

		target.draw(circle);
	}
}

int main()
{
	auto window = sf::RenderWindow{ { 400u, 400u }, "Physics Simulation" };
	window.setFramerateLimit(144);

	ShaderManager shaderManager;
	auto& gridShader = shaderManager.load("grid", "assets/grid.vertex.glsl", "assets/grid.fragment.glsl");

	std::vector<Body> bodies;
	bodies.emplace_back(sf::Vector2f{200.f, 200.f}, 0.0f, 9.0f);

	sf::RectangleShape gridLayer({400.f, 400.f});
	gridLayer.setPosition({0.f, 0.f});

	while (window.isOpen())
	{
		for (auto event = sf::Event{}; window.pollEvent(event);)
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::S) {
					shaderManager.refresh();
				}
			}
		}

		window.clear();
		window.draw(gridLayer, &gridShader);
		renderBodies(window, bodies);
		window.display();
	}
}
