cmake_minimum_required(VERSION 3.6)
project(mission2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -lpthread")
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES main.cpp Point.cpp Point.h BfsSearch.cpp BfsSearch.h PointNode.cpp PointNode.h Node.cpp Node.h
        Map.cpp Map.h Passanger.cpp Passanger.h Trip.cpp Trip.h Cab.cpp Cab.h LuxuryCab.cpp LuxuryCab.h Driver.cpp
        Driver.h MainFlow.cpp MainFlow.h Statistics.cpp Statistics.h TaxiCenter.cpp TaxiCenter.h
        Clock.cpp Clock.h Socket.cpp Socket.h Tcp.cpp Tcp.h DriverConect.cpp DriverConect.h DriveThread.cpp DriveThread.h TripThread.cpp TripThread.h ThreadPool.cpp ThreadPool.h Task.cpp Task.h Parser.cpp Parser.h)

set(SOURCE_FILES1 Driver.h Driver.cpp ClientMain.cpp Cab.cpp Cab.h LuxuryCab.cpp LuxuryCab.h Point.cpp Point.h
        Clock.cpp Clock.h DriversCenter.cpp DriversCenter.h PointNode.cpp PointNode.h
        Point.h Point.cpp Node.h Node.cpp Socket.cpp Socket.h Tcp.cpp Tcp.h ClientParser.cpp ClientParser.h)
set(SOURCE_FILES2 check.cpp Point.cpp Point.h BfsSearch.cpp BfsSearch.h PointNode.cpp PointNode.h Node.cpp Node.h
        Map.cpp Map.h Passanger.cpp Passanger.h Trip.cpp Trip.h Cab.cpp Cab.h LuxuryCab.cpp LuxuryCab.h Driver.cpp
        Driver.h MainFlow.cpp MainFlow.h Statistics.cpp Statistics.h TaxiCenter.cpp TaxiCenter.h
         Parser.cpp Parser.h DriverConect.cpp DriverConect.h)

add_executable(server.out ${SOURCE_FILES})
add_executable(client.out ${SOURCE_FILES1})
add_executable(check.out ${SOURCE_FILES2})

target_link_libraries(server.out gtest gtest_main)

target_link_libraries(check.out ${Boost_LIBRARIES})
target_link_libraries(server.out ${Boost_LIBRARIES})
target_link_libraries(client.out ${Boost_LIBRARIES})