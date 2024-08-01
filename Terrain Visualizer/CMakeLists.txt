# CMakeList.txt : CMake project for Terrain Visualizer, include source and define
# project specific logic here.
#
add_compile_options(-Wall)

if(WIN32)
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2-Windows/cmake")
find_package(SDL2 REQUIRED)
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2_image-Windows/cmake")
find_package(SDL2_image REQUIRED)
set(GLAD_NAME "$<IF:$<CONFIG:Debug>,gladDebug,gladRelease>")
include_directories(
    SYSTEM 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2-Windows/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2_image-Windows/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/${GLAD_NAME}/include
)
add_executable (
	CMakeTarget
	src/Main.cpp
    src/Input.cpp
    src/Shader.cpp
    libraries/${GLAD_NAME}/src/glad.c
)
target_link_libraries(
    CMakeTarget
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2-Windows/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2_image-Windows/lib
)
else()
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2-Linux/cmake")
find_package(SDL2 REQUIRED)
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2_image/cmake")
find_package(SDL2_image REQUIRED)
set(GLAD_NAME "$<IF:$<CONFIG:Debug>,gladDebug,gladRelease>")
include_directories(
    SYSTEM 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2_image/include/SDL2
    ${SDL2_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/${GLAD_NAME}/include
)
add_executable (
	CMakeTarget
	src/Main.cpp
    src/Input.cpp
    src/Shader.cpp
    libraries/${GLAD_NAME}/src/glad.c
)
target_link_libraries(
    CMakeTarget
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2-Linux/lib/libSDL2.a
    ${SDL2_IMAGE_LIBS}
)
endif()

# Add source to this project's executable.

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

