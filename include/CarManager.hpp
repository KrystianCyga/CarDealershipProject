#pragma once

#include "car.hpp"
#include <vector>
#include <memory>

class CarManager
{

private:
    std::vector<std::unique_ptr<Car>> _cars;
    unsigned int _nextCarId;

public:

    void AddCar(const std::string& model, unsigned int registerYear, double initialPrice);
    bool SellCar(unsigned int id);


    void LoadFromFile(const std::string& filename);
    void SaveToFile(const std::string& filename) const;

    void ShowAvaliableCars() const;
    void ShowDaylyReport() const;
};