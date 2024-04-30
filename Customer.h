#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>

class Customer {
public:
    std::string first_name;
    std::string last_name;
    int phone_number;
    std::string address;

    Customer () {
        first_name = "";
        last_name = "";
        address = "";
        phone_number = 0;
    }
    Customer(std::string first_name, std::string last_name, int phone_number, std::string address) {
        this->first_name = first_name;
        this->last_name = last_name;
        this->phone_number = phone_number;
        this->address = address;
    }
    
    std::string get_full_name();
    int get_phone_number();
    std::string get_address();
};

#endif