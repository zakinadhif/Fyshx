cmake_minimum_required(VERSION 3.21)
project(
  Fyshx
  VERSION 0.1.0
  DESCRIPTION "Foo"
  LANGUAGES CXX C)

include(FetchContent)
FetchContent_Declare(SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.x
	)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
	GIT_TAG 9.1.0
	)
FetchContent_MakeAvailable(fmt)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(Fyshx ${SOURCES})

target_compile_features(
	Fyshx PUBLIC
	cxx_std_17
	)

target_link_libraries(Fyshx
	PRIVATE
	sfml-graphics
	fmt
	)

if (WIN32 AND BUILD_SHARED_LIBS)
	add_custom_command(TARGET Fyshx POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Fyshx> $<TARGET_FILE_DIR:Fyshx> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Fyshx)
