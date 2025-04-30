cmake_minimum_required(VERSION 3.14)
project(CarDealershipProject) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

add_executable(car_app 
    src/main.cpp     
    src/car.cpp      
    src/CarManager.cpp

)

target_include_directories(car_app PRIVATE include) 

enable_testing()
add_subdirectory(test) 