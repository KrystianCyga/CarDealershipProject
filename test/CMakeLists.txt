

add_executable(runTests 
    main_test.cpp           
    test_car.cpp            
    car_manager_test.cpp    
    ../src/car.cpp          
    ../src/CarManager.cpp   
)


target_include_directories(runTests PRIVATE
    ../include 
    .         
)

add_test(NAME UnitTests COMMAND runTests) 
