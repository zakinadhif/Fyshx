#include <SFML/Graphics.hpp>

struct Body {
  sf::Vector2f position;
  float rotation;
  float radius;
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

  std::vector<Body> bodies;
  bodies.emplace_back(Body {
    .position = {200.f, 200.f},
    .rotation = 0.0f,
    .radius = 9.0f,
  });

  while (window.isOpen())
  {
    for (auto event = sf::Event{}; window.pollEvent(event);)
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    window.clear();
    renderBodies(window, bodies);
    window.display();
  }
}
