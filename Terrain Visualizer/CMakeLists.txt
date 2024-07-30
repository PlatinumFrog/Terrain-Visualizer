# CMakeList.txt : CMake project for Terrain Visualizer, include source and define
# project specific logic here.
#

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/cmake")
find_package(SDL2 REQUIRED)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL2_image/cmake")
find_package(SDL2_image REQUIRED)

file(GLOB_RECURSE SOURCES source/*.cpp)
file(GLOB_RECURSE HEADERS source/*.hpp)

# Add source to this project's executable.

set(GLAD_NAME "$<IF:$<CONFIG:Debug>,gladDebug,gladRelease>")

include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/${GLAD_NAME}/include" "include")

add_executable (
	CMakeTarget
	"src/Main.cpp"
    "src/Input.cpp"
    "src/Shader.cpp"
    "${GLAD_NAME}/src/glad.c"
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(
    CMakeTarget
    PUBLIC
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
