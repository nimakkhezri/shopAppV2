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

//euoro vital