cmake_minimum_required(VERSION 3.28)
project(VoidLevelLoader LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    )
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(nlohmann_json)

add_library(VoidLevelLoader STATIC
    "src/VoidLevelLoader.cpp"
 )

target_include_directories(VoidLevelLoader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(VoidLevelLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(VoidLevelLoader PRIVATE cxx_std_17)
target_link_libraries(VoidLevelLoader PRIVATE SFML::Graphics nlohmann_json::nlohmann_json)