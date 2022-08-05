cmake_minimum_required(VERSION 3.5)
project(topological_bayes_filter)

## Use C++11
add_definitions(-std=c++14)
## By adding -Wall and -Werror, the compiler does not ignore warnings anymore,
## enforcing cleaner code.
#add_definitions(-std=c++11 -Wall -Werror)

set(PACKAGE_DEPENDENCIES
        #ur3_model
        )

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS ${PACKAGE_DEPENDENCIES})

## Find system libraries
find_package(Eigen3 REQUIRED)

catkin_package(
        INCLUDE_DIRS include
        LIBRARIES ${PROJECT_NAME}
        CATKIN_DEPENDS ${PACKAGE_DEPENDENCIES}
        DEPENDS Eigen3
)

###########
## Build ##
###########

include_directories(include)
include_directories(${Eigen3_INCLUDE_DIR})
include_directories(${catkin_INCLUDE_DIRS})

## Declare a C++ library
add_library(${PROJECT_NAME}
        src/topological_bayes_filter.cpp
        )

## Add dependencies to exported targets, like ROS msgs or srvs
#add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link executable targets against
target_link_libraries(${PROJECT_NAME}
        ${catkin_LIBRARIES}
        Eigen3::Eigen
        )
