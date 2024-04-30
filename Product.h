#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>

class Product {
public : 
    std::string name;
    int stock, price;

    Product(std::string name, int stock, int price) {
        this->name = name;
        this->stock = stock;
        this->price = price;
    }

    std::string get_name();
    int get_stock();
    void set_stock(int new_stock);
    int get_price();
    void set_price(int new_price);
};

#endif