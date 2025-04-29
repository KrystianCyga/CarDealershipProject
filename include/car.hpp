
#pragma once

#include <string>
#include <chrono>

/**
* @brief Holds all the details for a single used car.
*
* This class keeps track of basic info like the model, year it was made,
* its starting price, and if it's been sold. It also figures out
* the car's current price, since that price drops over time.
*/
class Car
{

private:
    std::string _model;
    unsigned int _registerYear;
    std::chrono::system_clock::time_point _addTime;
    double _initialPrice;
    unsigned int _id;
    bool _isSold;

public:
    // Constructor

    /**
    * @brief Creates a new record for a car.
    *
    * Sets up all the basic car info you give it.
    * Automatically notes the exact time THIS car was added to the system
    * and sets its status to "not sold".
    *
    * @param id A unique number so we know which car is which.
    * @param model The car's model name (like "Ford Focus").
    * @param registerYear The year it was first registered.
    * @param initialPrice The price we first listed the car at.
    */
    Car(unsigned int id, const std::string &model, unsigned int year, double initialPrice)
        : _id(id), _model(model), _registerYear(year), _initialPrice(initialPrice), _isSold(false)
    {
        _addTime = std::chrono::system_clock::now();
    }

    // Getters
    unsigned int GetId() const { return _id; }
    const std::string &GetModel() const { return _model; }
    unsigned int GetRegisterYear() const { return _registerYear; }
    double GetInitialPrice() const { return _initialPrice; }
    const std::chrono::system_clock::time_point &GetAddTime() const { return _addTime; }
    bool IsSold() const { return _isSold; }

    // Setters
    void SetSold(bool sold) { _isSold = sold; }

    // Other methods

    /**
    * @brief Calculates the current price of the car considering depreciation.
    *
    * The price depreciates by 0.1% after the first 30 seconds, and then
    * by an additional 0.1% every 10 seconds, up to a maximum 20% depreciation.
    *
    * @param currentTime The current system time point used to calculate elapsed time since added.
    * @return The current calculated price of the car.
    */
    double CalculateCurrentPrice(std::chrono::system_clock::time_point currentTime) const;

    /**
    * @brief Displays detailed information about the car to the console.
    *
    * Includes ID, model, year, initial price, current price, and sale status.
    */
    void ShowCarInfo(std::chrono::system_clock::time_point currentTime) const;
};