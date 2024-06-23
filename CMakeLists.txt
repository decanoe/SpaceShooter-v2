cmake_minimum_required(VERSION 3.5.0)
project(SpaceShooter VERSION 0.2.0 LANGUAGES C CXX)

include_directories(SDL2-2.28.5/include)
link_directories(SDL2-2.28.5/lib/x64)
include_directories(SDL_image)
link_directories(SDL_image/lib/x64)

# add_compile_definitions(_DEBUG_PRINTS)

add_executable(${PROJECT_NAME} main.cpp
    class/utility/graphics/screen.cpp
    class/utility/graphics/sprite.cpp
    class/utility/graphics/sprite_renderer.cpp
    
    class/utility/math/vector2.cpp
    class/utility/math/vector3.cpp
    class/utility/math/rect.cpp
    class/utility/math/random_generator.cpp

    class/utility/component/transform.cpp
    class/utility/component/component.cpp

    class/utility/physics/rigid_object.cpp
    class/utility/physics/rect_collider.cpp

    
    class/gameplay/general/world.cpp
    class/gameplay/general/graphics.cpp
    
    class/gameplay/ship/test_ship.cpp
    class/gameplay/objects/asteroid.cpp

    class/gameplay/effect/stars_renderer.cpp
)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image)
add_compile_options(-Wall)