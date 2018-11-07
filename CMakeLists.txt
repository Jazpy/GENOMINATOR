cmake_minimum_required (VERSION 2.6)
project (genominator)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)

add_executable(genominator
	    src/genominator.cpp
	    src/shader.cpp
	    src/plane.cpp
	    src/camera.cpp
	    src/time.cpp
	    src/tower.cpp
	    )

target_link_libraries(genominator glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
