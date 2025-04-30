#pragma once

#include "car.hpp"
#include <vector>
#include <memory>


/**
 * @brief Manages the collection of cars available in the dealership.
 *
 * This class handles adding new cars, selling existing ones, showing lists
 * of cars, and generating reports. It keeps all the car data organized.
 */
class CarManager
{

private:
    std::vector<std::unique_ptr<Car>> _cars;
    unsigned int _nextCarId;

public:

    CarManager() : _nextCarId(1){};

    void AddCar(const std::string& model, unsigned int registerYear, double initialPrice);
    bool SellCar(unsigned int id);
    bool IsCarSold(unsigned int id) const ;
    int GetCarCount() const;
    int GetNextCarId() const;


    void LoadFromFile(const std::string& filename);
    void SaveToFile(const std::string& filename) const;

    void ShowAvailableCars() const;
    void ShowDailyReport() const;
};