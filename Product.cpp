#include "Product.h"

std::string Product::get_name() {
    return name;
}

int Product::get_stock () {
    return stock;
}

void Product::set_stock (int new_stock) {
    if (new_stock >= 0){
        stock = new_stock;
    }
}

int Product::get_price () {
    return price;
}

void Product::set_price (int new_price) {
    if (new_price >= 0) {
        price = new_price;
    }
}

