#include "Order.h"

void Order::add_product (Product product, int quantity){
    if (quantity > 0){
        products.push_back(product);
        total_price += product.get_price() * quantity;
    }
}

int Order::get_offer_price(){
    return offer_price;
}

int Order::get_total_price(){
    return total_price;
}

void Order::apply_discount(double discount_percent){
    offer_price = total_price;
    if (discount_percent >= 0 && discount_percent <= 100){
        offer_price *= (1 - (discount_percent / 100));
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

//void Order::edit_order_product_quantity(){
//    int choice;
//    std::cout << "Enter the number of the product you want to edit: ";
//    std::cin >> choice;
//    Product& product = this->products[choice - 1];
//    std::cout << "Enter a new quantity: ";
//    int new_quantity;
//    std::cin >> new_quantity;
//    product.set_stock(new_quantity);
//}

//euoro vital

std::vector<Product> Order::get_products(){
    return products;
}


void Order::set_customer(const Customer& customer){
    this->customer = customer;
}

void Order::set_products(const std::vector<Product>& productslist) {
    products = productslist;
}