# CMakeList.txt : CMake project for SimpleSharedPointer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("SimpleSharedPointer")

# Add source to this project's executable.
add_executable (SimpleSharedPointer "SimpleSharedPointer.cpp" "SimpleSharedPointer.h")


# TODO: Add tests and install targets if needed.
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17 
	CXX_STANDARD_REQUIRED ON
)