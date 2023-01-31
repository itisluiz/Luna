cmake_minimum_required (VERSION 3.15)
project("luna" VERSION 0.3 LANGUAGES CXX)

## interface
set(PROJECT_INTERFACE ${PROJECT_NAME}_interface)
add_library(${PROJECT_INTERFACE} INTERFACE)

# depencencies
find_package(minhook REQUIRED)

# settings
target_compile_features(${PROJECT_INTERFACE} INTERFACE cxx_std_17)

# sources
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp" "src/*.cc")
target_sources(${PROJECT_INTERFACE} INTERFACE ${PROJECT_SOURCES})

# includes
target_include_directories(${PROJECT_INTERFACE} INTERFACE "include")

# linking
target_link_libraries(${PROJECT_INTERFACE} INTERFACE minhook::minhook)

## output
set(PROJECT_TARGET ${PROJECT_NAME})
add_library(${PROJECT_TARGET} SHARED)

# linking
target_link_libraries(${PROJECT_TARGET} ${PROJECT_INTERFACE})
