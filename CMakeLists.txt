CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(synthesize_image CXX)
#set(CMAKE_VERBOSE_MAKEFILE 1)
#set(CMAKE_INSTALL_PREFIX "./ex")

#BUILD mode
# set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE RelWithDebInfo)
# set(CMAKE_BUILD_TYPE MinSizeRel)
####################
#### C++ options
####################
SET(CMAKE_CXX_STANDARD 17) #11, 17
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

# Libraries
find_package(OpenGL)
find_package(glfw3)
find_package(OpenCV)

if (MSVC) #Visual Studio
    set(CMAKE_CXX_FLAGS "/W4")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT") #todo
    set(CMAKE_CXX_FLAGS_MINSIZEREL "/MT") #todo
elseif (CMAKE_COMPILER_IS_GNUCXX) #UNIX
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wend -Wold-non-virtual-dtorif-labels -Wfloat-equal -Winit-self -Winline -Wmissing-include-dirs -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-promo -Wswitch-default -Wswitch-enum -Wvariadic-macros -Wwrite-strings  -Wold-non-virtual-dtor -Wold-style-cast")
    set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=native")
ELSEIF (APPLE)
    set(CMAKE_MACOSX_RPATH 1)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wnon-virtual-dtor -Wfloat-equal -Winit-self -Winline -Wmissing-include-dirs -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-promo -Wswitch-default -Wswitch-enum -Wvariadic-macros -Wwrite-strings  -Wnon-virtual-dtor -Wold-style-cast")
    set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
    #set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=native")
endif ()
#INCLUDE_DIRECTORIES(${glfw3_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(/opt/homebrew/include/ ${OpenCV_INCLUDE_DIRS})
LINK_DIRECTORIES(/opt/homebrew/lib/)
ADD_EXECUTABLE(texture texture.cpp)
TARGET_LINK_LIBRARIES(texture glfw OpenGL::GL ${OpenCV_LIBS})

