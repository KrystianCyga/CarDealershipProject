# Car Dealership Console System

A small C++ console application for managing a used car dealership inventory.

## Features

*   Add new cars to the inventory with model, registration year, and initial price.
*   Calculate current car price with simulated time-based depreciation (0.1% after 30s, then additional 0.1% every 10s, max 20% total).
*   Sell available cars at their current calculated price.
*   Maintain sale status; sold cars are not available for purchase.
*   Generate daily reports showing both available and sold cars.
*   Load and save inventory data to/from a simple text file (`CarsDB.csv`).
*   Simple command-line interface menu.

## Project Requirements Fulfilled

This project demonstrates key C++ concepts including:

*   Object-Oriented Programming (OOP) principles: Classes (`Car`, `CarManager`), encapsulation, methods.
*   Smart Pointers (`std::unique_ptr`): For automatic dynamic memory management (RAII).
*   Standard Library Containers (`std::vector`): For managing car collection.
*   Standard Library Algorithms (`std::find_if`): For searching.
*   File I/O (`fstream`, `sstream`): For data persistence.
*   Time Handling (`std::chrono`): For depreciation calculation (based on session time).
*   Basic unit testing using Doctest.

## Building and Running

### Prerequisites

*   A C++17 compliant compiler (e.g., GCC, Clang, MSVC).
*   CMake (version 3.14 or higher recommended).

### Steps

1.  **Clone the repository:** If hosted on GitHub, use the provided URL.
    ```bash
    git clone [<repository-url>](https://github.com/KrystianCyga/CarDealershipProject.git)
    cd CarDealershipProject 
    ```
2.  **Create the data resources directory:** The application expects a `resources` directory for the data file.
    ```bash
    mkdir resources
    ```
    *(Note: You may want to place the example `CarsDB.csv` file in this directory after cloning/creating it).*
3.  **Generate build files with CMake:** Navigate to the root project directory and run CMake to configure the build.
    ```bash
    cmake -S . -B build
    ```
    *(This will create a `build` directory where the build files will be generated).*
4.  **Build the project:** Compile the source code.
    ```bash
    cmake --build build --config Debug # Use --config Release for Release build
    ```
    *(This compiles both the main application and the test executable).*
5.  **Run the application:** Navigate to the build output directory and execute the main application.
    ```bash
    cd build/Debug # or build/Release
    ./car_app # On Windows: car_app.exe
    ```
    *(The application should start, attempt to load `CarsDB.csv`, and display the main menu).*
6.  **Run the tests:** Navigate to the build directory and run CTest.
    ```bash
    cd build # Go back to the build root directory
    ctest -C Debug # Use -C Release for Release tests
    ```

## Example Usage

Once the application is running, use the menu options (A, R, L, W, S, D, X) to interact with the car inventory.

## Documentation

This project's code is documented using [Doxygen](https://www.doxygen.nl/).

To generate the HTML documentation:

1.  Make sure Doxygen is installed on your system.
2.  Navigate to the root project directory (where the main `CMakeLists.txt` is located).
3.  Run the command:    doxygen Doxyfile
4.  Open the generated `html/index.html` file in your web browser.
