cmake_minimum_required(VERSION 3.16.0)
project(socket-communication)

if (WIN32) # NOTE: Needs testing for optional AntTweakBar

  find_library(GLEW NAMES glew32s PATHS external/lib/x64)
  find_library(GLFW NAMES glfw3 PATHS external/lib)

  set(INCLUDE_DIRS
     libsrc
     external/include)

  set(LIBRARY_DIRS libsrc)

  set(CMAKE_CXX_STANDARD 11) 
  set(CMAKE_CXX_FLAGS 
     "/wd4018 /wd4244 /wd4305 
     /D_CRT_SECURE_NO_WARNINGS 
     /D_CRT_NONSTDC_NO_DEPRECATE 
     /D NOMINMAX /DGLEW_STATIC
     /EHsc")

  set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:\"MSVCRT\" /NODEFAULTLIB:\"LIBCMT\"")

  set(CORE atkui atk agl ${GLEW} ${GLFW} opengl32.lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

elseif (APPLE)

  set(CMAKE_MACOSX_RPATH 1)
  set(CMAKE_CXX_FLAGS "-Wall -Wno-unused-function -Wno-deprecated-declarations -Wno-reorder-ctor -Wno-unused-variable -g -stdlib=libc++ -std=c++14")
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
  find_library(GL_LIB OpenGL)
  find_library(GLEW glew)
  find_library(GLFW glfw)
  add_definitions(-DAPPLE)

  set(INCLUDE_DIRS
    .
    /System/Library/Frameworks
    /usr/local/include
    external/include
    libsrc/
    )

  set(LIBRARY_DIRS libsrc/)
  set(CORE atkui atk agl ${GL_LIB} ${GLEW} ${GLFW})

elseif (UNIX)

  set(CMAKE_CXX_FLAGS "-Wall -g -std=c++17 -Wno-unused-function -Wno-comment -Wno-sign-compare -Wno-reorder") 
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

  FIND_PACKAGE(OpenGL REQUIRED) 
  FIND_PACKAGE(GLEW REQUIRED)
  set(INCLUDE_DIRS
    external/include
    libsrc/
    )

  set(LIBRARY_DIRS
    /usr/X11R6/lib
    /usr/local/lib
    external/lib
    lib
    )

  add_definitions(-DUNIX)
  set(LIBS atkui agl GLEW glfw GL GLU X11 dl)

endif()

include_directories(${INCLUDE_DIRS})
link_directories(${LIBRARY_DIRS})
add_subdirectory(libsrc)

file (GLOB_RECURSE EXAMPLES CONFIGURE_DEPENDS demos/*.cpp)
foreach (example ${EXAMPLES})
  get_filename_component(example_name ${example} NAME_WLE)
  add_executable(${example_name} ${example})
  target_link_libraries(${example_name} ${LIBS})
endforeach()
