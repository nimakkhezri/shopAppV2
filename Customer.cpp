#include "Customer.h"

std::string Customer::get_full_name() {
    return first_name + " " + last_name;
}

std::string Customer::get_address(){
    return address;
}

int Customer::get_phone_number() {
    return phone_number;
}