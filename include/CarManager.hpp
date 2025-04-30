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

    /**
     * @brief Adds a new car to the inventory.
     *
     * Creates a new Car object with a unique ID, based on the provided details,
     * and adds it to the manager's list. The car is initially not sold.
     *
     * @param model The car's model, like "Opel Astra".
     * @param registerYear The year the car was first registered.
     * @param initialPrice The price the car is listed at when added.
     */
    void AddCar(const std::string& model, unsigned int registerYear, double initialPrice);

    /**
     * @brief Attempts to sell a car by its unique ID.
     *
     * Finds the car with the matching ID. If found and not already sold,
     * it marks the car as sold, calculates its final sale price based on current time,
     * and records that price. Prints messages about success or failure.
     *
     * @param id The unique ID of the car to sell.
     * @return true if a car with the given ID was found and successfully marked as sold, false otherwise
     */
    bool SellCar(unsigned int id);

    /**
     * @brief Checks if a specific car is currently marked as sold.
     *
     * Searches for a car with the given ID and returns its sold status.
     *
     * @param id The unique ID of the car to check.
     * @return true if a car with the given ID exists in the inventory and is marked as sold, false otherwise.
     */
    bool IsCarSold(unsigned int id) const ;

    /**
     * @brief Gets the total number of cars (both sold and available) in the inventory.
     * @return The count of all cars held by the manager.
     */
    int GetCarCount() const;

     /**
     * @brief Gets the next available unique ID that will be assigned to a newly added car.
     *
     * Useful for knowing what ID the next added car will receive.
     *
     * @return The value of the counter for the next car ID.
     */
    int GetNextCarId() const; // Assuming you added this getter based on your tests


    /**
     * @brief Loads car data from a specified file.
     *
     * Cleans the current list of cars and attempts to read car details
     * from the file, adding them to the inventory.
     * Handles cases where the file doesn't exist or has errors.
     *
     * @param filename The path to the file to load data from.
     */
    void LoadFromFile(const std::string& filename);

    /**
     * @brief Saves the current inventory data to a specified file.
     *
     * Writes details of all cars (sold and available) to the file
     * in a simple text format. Overwrites the file if it exists.
     * Handles errors if the file cannot be created or written to.
     *
     * @param filename The path to the file to save data to.
     */
    void SaveToFile(const std::string& filename) const;

    /**
     * @brief Displays basic information for all cars currently available for sale.
     *
     * Iterates through the inventory and calls ShowCarInfo for any car
     * that is not marked as sold. Includes calculated price with depreciation.
     */
    void ShowAvailableCars() const;

    /**
     * @brief Prints a report showing the status of all cars.
     *
     * Lists all cars, typically divided into sections for sold and available.
     * Provides counts for each category.
     * Includes sale price for sold cars and current price for available ones.
     */
    void ShowDailyReport() const;
};