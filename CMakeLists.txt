cmake_minimum_required(VERSION 3.5.0)
project(SpaceShooter VERSION 0.2.0 LANGUAGES C CXX)

include_directories(SDL2-2.28.5/include)
link_directories(SDL2-2.28.5/lib/x64)
include_directories(SDL_image)
link_directories(SDL_image/lib/x64)

add_executable(${PROJECT_NAME} main.cpp
    class/utility/graphics/screen.cpp
    class/utility/graphics/sprite.cpp
    class/utility/graphics/sprite_renderer.cpp
    
    class/utility/math/vector2.cpp
    class/utility/math/vector3.cpp
)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image)
add_compile_options(-Wall)