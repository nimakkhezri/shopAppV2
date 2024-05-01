#ifndef ORDER_H
#define ORDER_H
#include <iostream>
#include <vector>
#include "Product.h"
#include "Customer.h"

class Order {
public:
    std::vector<Product> products;
    std::vector<int> numbers;
    double discount;
    double total_price;
    Customer customer;
    std::string date;

    Order(std::vector<Product> products, std::vector<int> numbers, double discount, double total_price, const Customer customer, std::string date){
        this->products = products;
        this->discount = discount;
        this->total_price = total_price;
        this->customer = customer;
        this->date = date;
        this->numbers = numbers;
    }

    void add_product (Product product, int quantity);
    int get_total_price();
    void apply_discount(double discount_percent);
    Customer get_customer_info();
    std::string get_date();

};

#endif