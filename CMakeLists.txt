cmake_minimum_required(VERSION 3.21)
project(Fyshx LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(Fyshx ${SOURCES})

target_link_libraries(Fyshx
    PRIVATE
    sfml-graphics
)

target_compile_features(Fyshx
    PRIVATE
    cxx_std_17
)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Fyshx POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Fyshx> $<TARGET_FILE_DIR:Fyshx> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Fyshx)
