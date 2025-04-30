#include "CarManager.hpp" // Include the header for CarManager
#include <iostream>       // For input/output streams
#include <limits>         // For std::numeric_limits
#include <cctype>         // For std::toupper
#include <cstddef>        // For size_t
#include <string>
#include <sstream>
#include <cstdlib>         // system()


void clear_console() {
#ifdef _WIN32
    // Windows
    system("cls");
#elif defined(__APPLE__) || defined(__linux__) || defined(__unix__)
    // UNIX (Linux, macOS, BSD, itp.)
    system("clear");
#else
    for (int i = 0; i < 100; ++i) {
        std::cout << "\n";
    }
#endif
}

void print_menu()
{
    std::cout << "\n--- Car Dealership System Menu ---\n";
    std::cout << "----------------------------------\n";
    std::cout << " A - Show Available Cars\n";
    std::cout << " R - Show Daily Report\n";
    std::cout << " L - Load Cars from File\n";
    std::cout << " W - Save Cars to File\n";
    std::cout << " S - Sell a Car\n";
    std::cout << " D - Add a New Car\n";
    std::cout << " X - Exit\n";
    std::cout << "----------------------------------\n";
}

int main()
{
    CarManager MainCarManager;
    char option = ' ';

    // Define the path to the data file
    const std::string data_filename = "../resources/CarsDB.csv";

    // Attempt to load data automatically on startup
    MainCarManager.LoadFromFile(data_filename);

    while (true) // Loop until user chooses to exit
    {
        clear_console();
        print_menu();

        std::cout << "Enter your choice: ";
        std::string userInput;
        // Read the whole line, discarding leading whitespace and the newline character
        std::getline(std::cin >> std::ws, userInput);

        if (userInput.empty())
        {
            option = ' ';
        }
        else
        {
            option = std::toupper(userInput[0]);
        }

        switch (option)
        {
        case 'A': // Show Available Cars
            if (MainCarManager.GetCarCount() > 0)
            {
                MainCarManager.ShowAvailableCars();
            }
            else
            {
                std::cout << "Car inventory is currently empty." << std::endl;
            }
            break;

        case 'R': // Show Daily Report
            if (MainCarManager.GetCarCount() > 0)
            {
                MainCarManager.ShowDailyReport();
            }
            else
            {
                std::cout << "Car inventory is currently empty." << std::endl;
            }
            break;

        case 'L': // Load Cars from File
            MainCarManager.LoadFromFile(data_filename);
            break;

        case 'W': // Save Cars to File
            MainCarManager.SaveToFile(data_filename);
            break;

        case 'S': // Sell a Car
        {
            if (MainCarManager.GetCarCount() > 0)
            {
                MainCarManager.ShowAvailableCars();
            }
            else
            {
                std::cout << "Car inventory is currently empty." << std::endl;
            }
            std::cout << "Enter the ID of the car you want to sell:" << std::endl;
            std::cout << "ID -> ";
            std::string idInput;
            std::getline(std::cin >> std::ws, idInput);

            unsigned int carID_uint;

            try
            {
                size_t processed_chars;
                carID_uint = std::stoul(idInput, &processed_chars);

                if (processed_chars != idInput.length() || carID_uint == 0)
                {
                    throw std::invalid_argument("Invalid ID format or value.");
                }

                // Attempt to sell the car
                if (MainCarManager.SellCar(carID_uint))
                {
                    // Success or Already Sold messages are printed by SellCar method
                }
                else
                {
                    break;
                }
            }
            catch (const std::invalid_argument &e)
            {
                // Catch errors from std::stoul
                std::cerr << "Input Error: Invalid car ID format. Please enter a positive integer ID." << std::endl;
            }
            catch (const std::out_of_range &e)
            {
                // Catch errors if the number is too large for unsigned int
                std::cerr << "Input Error: Car ID value is out of acceptable range." << std::endl;
            }
        }
        break;

        case 'D': // Add a New Car
        {
            std::cout << "Enter car details...\n";

            std::string model;
            std::cout << "Model: ";
            std::getline(std::cin >> std::ws, model);

            unsigned int year;
            std::cout << "Register Year: ";
            std::string yearInput;
            std::getline(std::cin >> std::ws, yearInput);

            double price;
            std::cout << "Initial Price: ";
            std::string priceInput;
            std::getline(std::cin >> std::ws, priceInput);

            // Input validation for Year and Price
            try
            {
                size_t processed_chars_year;
                year = std::stoul(yearInput, &processed_chars_year);
                if (processed_chars_year != yearInput.length() || year == 0)
                {
                    throw std::invalid_argument("Invalid year format or value.");
                }

                size_t processed_chars_price;
                price = std::stod(priceInput, &processed_chars_price);
                if (processed_chars_price != priceInput.length() || price <= 0)
                {
                    throw std::invalid_argument("Invalid price format or value (must be positive).");
                }

                MainCarManager.AddCar(model, year, price);
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Input Error: Could not parse year or price. " << e.what() << std::endl;
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << "Input Error: Year or price value out of range. " << std::endl;
            }
        }
        break;

        case 'X': // Exit

            break;

        default: // Invalid input
            std::cout << "Invalid choice. Please select a valid option from the menu." << std::endl;
            break;
        }

        if (option != 'X') {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();

       }

        // Exit the loop if the user chose 'X'
        if (option == 'X')
        {
            std::cout << "Saving inventory before exiting..." << std::endl;
            MainCarManager.SaveToFile(data_filename);
            std::cout << "Exiting Car Dealership System. Goodbye!" << std::endl;
            break;
        }
    }

    return 0;
}