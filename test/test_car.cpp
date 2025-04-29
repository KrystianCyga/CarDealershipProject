#include "doctest.h"
#include "car.hpp"

#include <chrono>
#include <cmath>

using namespace std::chrono;

TEST_SUITE("Car Tests")
{

    TEST_CASE("CalculateCurrentPrice no discount in first 30s")
    {
        Car c(1, "TestModel", 2020, 10000.0);
        auto addTime = c.GetAddTime();

        auto currentTime_29s = addTime + seconds(29);
        double expected = 10000.0;
        double actual = c.CalculateCurrentPrice(currentTime_29s);

        CHECK_MESSAGE(actual == doctest::Approx(expected),
                      "Price should not change in first 30 seconds");
    }

    TEST_CASE("CalculateCurrentPrice discount over time")
    {
        Car c(5, "SmallPriceCar", 2022, 100.0);
        auto addTime = c.GetAddTime();

        SUBCASE("after 40s 0.2% discount")
        {
            auto currentTime = addTime + seconds(40);
            double expected = 100.0 * (1.0 - 0.002); // 99.8
            double actual = c.CalculateCurrentPrice(currentTime);
            CHECK_MESSAGE(actual == doctest::Approx(expected),
                          "Expected ~99.8 after 40s, got " << actual);
        }

        SUBCASE("after 3000s 20% discount")
        {
            auto currentTime = addTime + seconds(3000);
            double expected = 100.0 * (1.0 - 0.20); // 80.0
            double actual = c.CalculateCurrentPrice(currentTime);
            CHECK_MESSAGE(actual == doctest::Approx(expected),
                          "Expected 80.0 after 3000, got " << actual);
        }
    }

    TEST_CASE("CalculateCurrentPrice exact 30s boundary") {
        Car c(2, "BoundaryCar", 2021, 1000.0);
        auto addTime = c.GetAddTime();
    
        auto currentTime_30s = addTime + seconds(30);
        double expected = 1000.0; 
        double actual = c.CalculateCurrentPrice(currentTime_30s);
    
        CHECK_MESSAGE(actual == doctest::Approx(expected),
                      "Price should start decreasing after 30s");
    }

    TEST_CASE("CalculateCurrentPrice negative time") {
        Car c(4, "FutureCar", 2025, 3000.0);
        auto addTime = c.GetAddTime();
    
        auto currentTime = addTime - seconds(10); 
        double actual = c.CalculateCurrentPrice(currentTime);
    
        CHECK_MESSAGE(actual == doctest::Approx(3000.0),
                      "Price should stay the same if currentTime is before addTime");
    }
    
}
