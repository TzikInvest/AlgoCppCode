cmake_minimum_required(VERSION 3.29)
project(TzikInvest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the path to the IBAPI headers
include_directories(${CMAKE_SOURCE_DIR}/twsapi_macunix/include)

# Add the path to the IBAPI libraries
link_directories(${CMAKE_SOURCE_DIR}/twsapi_macunix/lib)

# Link against the IBAPI libraries
add_executable(TzikInvest main.cpp)
target_link_libraries(IBAPIProject
        twsapi
        pthread
)

if(APPLE)
    target_link_libraries(IBAPIProject "-framework CoreFoundation")
endif()