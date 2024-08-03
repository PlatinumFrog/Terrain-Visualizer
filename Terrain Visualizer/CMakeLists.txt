# CMakeList.txt : CMake project for Terrain Visualizer, include source and define
# project specific logic here.

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
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2-Windows/include/SDL2
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2_image-Windows/include/SDL2
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/${GLAD_NAME}/include
    )
    add_executable (
	    CMakeTarget
	    src/Main.cpp
        src/Input.cpp
        libraries/${GLAD_NAME}/src/glad.c
    )
    target_link_libraries(
        CMakeTarget
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2-Windows/lib/SDL2.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2-Windows/lib/SDL2main.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2_image-Windows/lib/SDL2_image.lib
    )
else()
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2-Linux/lib/cmake/SDL2")
    find_package(SDL2 REQUIRED)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2_image-Linux/lib/cmake/SDL2_image")
    find_package(SDL2_image REQUIRED)
    set(GLAD_NAME "$<IF:$<CONFIG:Debug>,gladDebug,gladRelease>")
    include_directories(
        SYSTEM 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2_image-Linux/include/SDL2_image
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2-Linux/include/SDL2
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
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2-Linux/lib/libSDL2.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2-Linux/lib/libSDL2main.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libraries/SDL2_image-Linux/lib/libSDL2_image-2.0.so.0.800.2
    )
endif()

# Add source to this project's executable.

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

