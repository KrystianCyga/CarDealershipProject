
add_executable(car_tests
    main_test.cpp
    test_car.cpp
    ../src/car.cpp  
)


target_include_directories(car_tests PRIVATE
    ../include
    .
)

add_test(NAME CarTests COMMAND car_tests)
