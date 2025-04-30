#include "car.hpp"
#include <iostream>
#include <algorithm>

double Car::CalculateCurrentPrice(std::chrono::system_clock::time_point currentTime) const{

    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - _addTime).count();
    double discount=0;

    if(elapsed_seconds>30&&elapsed_seconds<40){
        discount=0.001;
    }
    else if (elapsed_seconds>=40)
    {
        int times=(elapsed_seconds-30)/10;
        discount=0.001+0.001*times;
    }
    else return _initialPrice;

    discount=std::min(discount,0.20);
    return _initialPrice*(1.0-discount);
}


void Car::ShowCarInfo(std::chrono::system_clock::time_point currentTime) const{

    std::cout<<"ID: "<<_id<<"\n";
    std::cout<<"Model: "<<_model<<"\n";
    std::cout<<"Register Year: "<<_registerYear<<"\n";
    std::cout<<"Actual Price: "<<CalculateCurrentPrice(currentTime)<<"\n";
    std::cout << "Status: " << (_isSold ? "Sold" : "Available") << "\n";
}

void Car::ShowCarInfo() const{

    std::cout<<"ID: "<<_id<<"\n";
    std::cout<<"Model: "<<_model<<"\n";
    std::cout<<"Register Year: "<<_registerYear<<"\n";
    std::cout<<"Sell Price: "<<_initialPrice<<"\n";
    std::cout << "Status: " << (_isSold ? "Sold" : "Available") << "\n";
}

void Car::SetSold(){
    _isSold=true;
}

void Car::SetSalePrice(double price){
    _salePrice = price;
}
