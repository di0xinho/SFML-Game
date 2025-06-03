cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Dodanie wsparcia dla OpenGL
find_package(OpenGL REQUIRED)

add_executable(main "src/main.cpp" "src/StateMachine.cpp" "src/MenuState.cpp" "src/InputManager.cpp" "src/AssetManager.cpp" "src/SoundManager.cpp" "src/PauseState.cpp" "src/GameOverState.cpp" "src/GameState.cpp" "src/Animation.cpp" "src/Player.cpp" "src/HUD.cpp" "src/Coin.cpp" "src/Trophy.cpp" "src/Enemy.cpp" "src/Weapon.cpp" "src/MoveLeftCommand.cpp" "src/MoveRightCommand.cpp" "src/JumpCommand.cpp" "src/AttackCommand.cpp")
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-audio sfml-system OpenGL)
target_include_directories(main PRIVATE include)