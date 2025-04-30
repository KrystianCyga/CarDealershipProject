// test/car_manager_test.cpp

#include "doctest.h" 
#include "../include/CarManager.hpp"  
#include <string> 
#include <vector> 
#include <memory> 


TEST_SUITE("CarManager Simple Tests") {

    TEST_CASE("CarManager starts empty") {
        CarManager manager; 
        CHECK(manager.GetCarCount() == 0);
        CHECK(manager.GetNextCarId() == 1); 
    }

    TEST_CASE("AddCar increases car count and sets status") {
        CarManager manager;
        manager.AddCar("ModelA", 2023, 10000.0);
        CHECK(manager.GetCarCount() == 1);

        CHECK(manager.IsCarSold(1) == false);

        manager.AddCar("ModelB", 2022, 20000.0);
        CHECK(manager.GetCarCount() == 2);
        CHECK(manager.IsCarSold(2) == false);
    }

    TEST_CASE("SellCar sells an available car") {
        CarManager manager;
        manager.AddCar("SellMe", 2020, 30000.0);

        CHECK(manager.IsCarSold(1) == false);

        // Sell
        bool result = manager.SellCar(1);

        CHECK(result == true); 
        CHECK(manager.IsCarSold(1) == true); 
        CHECK(manager.GetCarCount() == 1); 
    }

     TEST_CASE("SellCar returns false for selling already sold car") {
        CarManager manager;
        manager.AddCar("SellTwice", 2019, 40000.0); 

        manager.SellCar(1);
        CHECK(manager.IsCarSold(1) == true);

        bool result = manager.SellCar(1);

        CHECK(result == false); 
        CHECK(manager.IsCarSold(1) == true); 
        CHECK(manager.GetCarCount() == 1); 
    }

    TEST_CASE("SellCar returns false for non-existent car ID") {
        CarManager manager;
        manager.AddCar("OnlyOne", 2021, 50000.0); 

        bool result = manager.SellCar(999); 

        CHECK(result == false); 
        CHECK(manager.GetCarCount() == 1); 
        CHECK(manager.IsCarSold(1) == false); 
    }


    TEST_CASE("LoadFromFile handles non-existent file") {
        CarManager manager; 
        manager.LoadFromFile("i_do_not_exist.csv");
        CHECK(manager.GetCarCount() == 0);
    }


} 