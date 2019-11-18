# Version Setup
cmake_minimum_required(VERSION 3.1...3.14.3)

if (${CMAKE_VERSION} VERSION_LESS 3.14)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.14)
endif()

# OS
if(UNIX AND NOT APPLE)
        set(LINUX TRUE)
endif()

# Project Creation
project (BulletHell)
set (CMAKE_CXX_STANDARD 17)
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
set (WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/assets)
option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)

# Conan
if(EXISTS ${CMAKE_SOURCE_DIR}/conan/conanbuildinfo_multi.cmake)
	if( WIN32 )
		include(${CMAKE_SOURCE_DIR}/conan/conanbuildinfo_multi.cmake)
		conan_basic_setup()
	else()
		include($ENV{HOME}/conanCache/conanbuildinfo.cmake)
		conan_basic_setup()
	endif()
elseif(EXISTS ${CMAKE_SOURCE_DIR}/conan/conanbuildinfo.cmake)
    include(${CMAKE_SOURCE_DIR}/conan/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    if(EXISTS ${CMAKE_SOURCE_DIR}/conanfile.txt)
        message( FATAL_ERROR
" A conanfile.txt file exists in the source directory\n"
" indicating Conan is used for dependences but a conanbuildinfo.cmake\n"
" file does not exist. Make sure to execute:\n\n"
" Conan install ${CMAKE_SOURCE_DIR} --build=missing -if ${CMAKE_BINARY_DIR}" )
    endif()
endif()

find_package(nlohmann_json 3.2.0 REQUIRED)
#if (UNIX)
#	set(SFML_STATIC_LIBRARIES TRUE)
#	find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)
#endif()

# Progam Resource Management
file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY ${PROJECT_SOURCE_DIR}/playerData DESTINATION ${CMAKE_BINARY_DIR}/bin)

# .exe, Append all src files to an env. var.
FILE(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp
	${PROJECT_SOURCE_DIR}/src/Entities/*.cpp
	${PROJECT_SOURCE_DIR}/src/States/*.cpp
)

add_executable(BulletHell ${sources}) # Create executable
set_target_properties(BulletHell PROPERTIES 
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	CXX_STANDARD 17 # Force c++17 standard
)

# Include Directories
target_include_directories(BulletHell PUBLIC ${PROJECT_SOURCE_DIR}/src)

# Unix System Fixes
if(UNIX)
	target_link_libraries(BulletHell m)
#	target_link_libraries(BulletHell sfml-graphics)
endif()

# Link all Libraries
conan_target_link_libraries(BulletHell)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_link_libraries(BulletHell debug nlohmann_json::nlohmann_json)
else ()
	target_link_libraries(BulletHell optimized nlohmann_json::nlohmann_json)
endif()
