#include "CarManager.hpp"
#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <sstream>

void CarManager::AddCar(const std::string &model, unsigned int registerYear, double initialPrice)
{
    unsigned int newCarId = _nextCarId;
    auto newCarPtr = std::make_unique<Car>(newCarId, model, registerYear, initialPrice);

    std::cout << "Car added: ID " << newCarId << " (" << model << " " << registerYear << ") Initial Price: " << initialPrice << "\n";

    _cars.push_back(std::move(newCarPtr));
    _nextCarId++;
}

bool CarManager::SellCar(unsigned int id)
{
    auto currentTime = std::chrono::system_clock::now();
    auto it = std::find_if(_cars.begin(), _cars.end(), [&](const std::unique_ptr<Car> &car)
                           { return car->GetId() == id; });

    if (it != _cars.end())
    {
        if ((*it)->IsSold())
        {
            std::cout << "Car already sold!!\n";
            return false;
        }

        (*it)->SetSold();

        double actualSalePrice = (*it)->CalculateCurrentPrice(currentTime);
        (*it)->SetSalePrice(actualSalePrice);

        std::cout << "Success: Car with ID " << id << " (" << (*it)->GetModel()
                  << ") sold for " << std::fixed << std::setprecision(2) << actualSalePrice << "." << std::endl;

        return true;
    }

    return false;
}

void CarManager::LoadFromFile(const std::string &filename) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cout << "Warning: Could not open file for loading: " << filename << "." << std::endl;
        _cars.clear();
        _nextCarId = 1;
        return;
    }

    _cars.clear();
    _nextCarId = 1;

    std::string line;
    unsigned int maxId = 0;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string segment;

        unsigned int id;
        std::string model;
        unsigned int registerYear;
        double initialPrice;
        bool isSold;
        double salePrice = 0.0;

        try {
            if (!std::getline(ss, segment, ';')) throw std::runtime_error("Missing ID");
            id = std::stoul(segment);
            if (!std::getline(ss, segment, ';')) throw std::runtime_error("Missing Model");
            model = segment;
            if (!std::getline(ss, segment, ';')) throw std::runtime_error("Missing Register Year");
            registerYear = std::stoul(segment);
            if (!std::getline(ss, segment, ';')) throw std::runtime_error("Missing Initial Price");
            initialPrice = std::stod(segment);
            if (!std::getline(ss, segment, ';')) throw std::runtime_error("Missing IsSold status");
            isSold = (std::stoi(segment) != 0);
             if (std::getline(ss, segment) && !segment.empty()) { 
                 try { salePrice = std::stod(segment); }
                 catch (const std::exception& e) {  }
             }


            auto car_ptr = std::make_unique<Car>(id, model, registerYear, initialPrice);

            
            if (isSold) {
                 car_ptr->SetSold();
                 car_ptr->SetSalePrice(salePrice);
            }

            _cars.push_back(std::move(car_ptr));

            if (id >= maxId) {
                maxId = id;
            }

        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: '" << line << "'. Error: " << e.what() << ". Skipping line." << std::endl;
        }
    }

    if (maxId > 0) {
        _nextCarId = maxId + 1;
    } else {
        _nextCarId = 1;
    }

    std::cout << "Cars successfully loaded from " << filename << ". Total cars: " << _cars.size() << std::endl;
}

void CarManager::SaveToFile(const std::string &filename) const {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for saving: " << filename << std::endl;
        return;
    }

    outFile << std::fixed << std::setprecision(2);

    for (const auto& car_ptr : _cars) {
        const Car* car = car_ptr.get();

        outFile << car->GetId() << ";";
        outFile << car->GetModel() << ";";
        outFile << car->GetRegisterYear() << ";";
        outFile << car->GetInitialPrice() << ";";
        outFile << car->IsSold() << ";";
        outFile << car->GetSalePrice() << "\n"; 
    }

    std::cout << "Inventory successfully saved to " << filename << std::endl;
}

void CarManager::ShowAvailableCars() const
{
    std::cout << "--- Available Cars ---\n";
    auto currentTime = std::chrono::system_clock::now();
    bool foundAvailable = false;

    for (auto &&car_ptr : _cars)
    {
        if (!car_ptr->IsSold())
        {
            car_ptr->ShowCarInfo(currentTime);
            std::cout << "----------------------\n";
            foundAvailable = true;
        }
    }

    if (!foundAvailable)
    {
        std::cout << "No cars currently available for sale.\n";
    }
}

void CarManager::ShowDailyReport() const
{
    int soldCounter = 0;
    int notSoldCounter = 0;

    std::cout << "----------- Day Report ---------\n";
    std::cout << "----------- Sold Cars ---------\n";

    for (auto &&car_ptr : _cars)
    {
        if (car_ptr->IsSold())
        {
            car_ptr->ShowCarInfo();
            std::cout << "----------------------\n";
            soldCounter++;
        }
    }

    std::cout << "----------- Not Sold Cars ---------\n";
    for (auto &&car_ptr : _cars)
    {
        if (!car_ptr->IsSold())
        {
            car_ptr->ShowCarInfo();
            std::cout << "----------------------\n";
            notSoldCounter++;
        }
    }

    std::cout << "Summary: Sold - " << soldCounter << ", Available - " << notSoldCounter << "\n"; // Ulepszone formatowanie i literówka
    std::cout << "----------------------------------\n";
}

bool CarManager::IsCarSold(unsigned int id) const {
    auto it = std::find_if(_cars.begin(), _cars.end(), [&](const std::unique_ptr<Car>& car_ptr){
        return car_ptr->GetId() == id;
    });

    if (it != _cars.end()) {
        return (*it)->IsSold();
    }

    return false; 
}

int CarManager::GetCarCount() const{
    return _cars.size();
}

int CarManager::GetNextCarId() const{
    return _nextCarId;
}