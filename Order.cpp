#include "Order.h"

void Order::add_product (Product product, int quantity){
    if (quantity > 0){
        products.push_back(product);
        total_price += product.get_price() * quantity;
    }
}

int Order::get_total_price(){
    return total_price;
}

void Order::apply_discount(double discount_percent){
    if (discount_percent >= 0 && discount_percent <= 100){
        discount = discount_percent / 100;
        total_price *= (1 - discount);
    }
}

Customer Order::get_customer_info(){
    return customer;
}

std::string Order::get_date(){
    return date;
}

double Order::get_discount(){
    return discount;
}

void Order::edit_order_product_quantity(){
    int choice;
    std::cout << "Enter the number of the product you want to edit: ";
    std::cin >> choice;
    int& number = this->numbers[choice - 1];
    std::cout << "Enter a new quantity: ";
    int new_quantity;
    std::cin >> new_quantity;
    number = new_quantity;
}

//euoro vital