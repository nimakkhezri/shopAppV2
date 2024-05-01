#include <iostream>
#include <vector>
#include <time.h>
#include "Product.h"
#include "Order.h"
#include "Customer.h"
#include "SalesHistory.h"

void display_products(const std::vector<Product>& products);
void edit_product(std::vector<Product>& products);
void add_product(std::vector<Product>& products);
Order create_new_order(std::vector<Product>& products);

int main (){
    std::vector <Product> products;
    SalesHistory sales_history;

    int choice;
    do {
        std::cout << "---------------------- Aghche Shop ------------------------" << '\n';
        std::cout << "1. Add a product " << '\n';
        std::cout << "2. Products " << '\n';
        std::cout << "3. Add a new order" << '\n';
        std::cout << "4. Orders" << '\n';
        std::cout << "5. Turnover" << '\n';
        std::cout << "0. Exit" << '\n';
        std::cout << "---------------------- Aghche Shop ------------------------" << '\n';
        std::cout << "Enter your choice : ";
        std::cin >> choice;
        std::cout << '\n';

        switch (choice) {
            case 1:
                add_product(products);
                break;
            case 2:
                int new_choice;
                display_products(products);
                std::cout << "For editing products, please enter 1 \n";
                std::cout << "For returning back please enter 0 \n";
                std::cout << "Your choise: ";
                std::cin >> new_choice;
                std::cout << '\n';
                if (choice == 1)
                    edit_product(products);
                break;
            case 3:
                sales_history.add_order(create_new_order(products));
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                break;
        }
    }while (choice != 0);
}

void display_products(const std::vector<Product>& products) {
    if (products.empty()) {
        std::cout << "There is no product here !!" << std::endl;
    } else {
        std::cout << "-------------------- **Products --------------------**" << std::endl;
        for (Product product : products) {
            std::cout << "- " << product.get_name() << " (Stock: " << product.get_stock() << ", Price: " << product.get_price() << " Toman)" << std::endl;
        }
    }
}

void edit_product(std::vector<Product>& products) {
    if (products.empty()) {
        std::cout << "There is no product here !!" << std::endl;
        return;
    }

    std::cout << "-------------------- **Edit Product** --------------------" << std::endl;
    display_products(products);

    int product_index;
    do {
        std::cout << "Please enter your product number:  ";
        std::cin >> product_index;
    } while (product_index < 1 || product_index > products.size());

    int choice;
    do {
        std::cout << "What do you want to do ?" << std::endl;
        std::cout << "1. Edit stock" << std::endl;
        std::cout << "2. Edit price" << std::endl;
        std::cout << "3. Return" << std::endl;
        std::cout << "Choose: ";
        std::cin >> choice;
        std::cout << '\n';
    } while (choice < 1 || choice > 3);

    Product& product = products[product_index - 1];

    switch (choice) {
        case 1: {
        int new_stock;
        do {
            std::cout << "Please enter new stock: ";
            std::cin >> new_stock;
        } while (new_stock < 0);
        product.set_stock(new_stock);
        std::cout /*<< "موجودی محصول " */<< product.get_name() << "'s stock changed to" << new_stock << ", Succesfully !!" << std::endl;
        break;
        }
        case 2: {
        double new_price;
        do {
            std::cout << "Please enter new price: ";
            std::cin >> new_price;
        } while (new_price < 0);
        product.set_price(new_price);
        std::cout /*<< "قیمت محصول " */<< product.get_name() << "'s price changed to" << new_price << " , Succesfully !!" << std::endl;
        break;
        }
        case 3:
        break;
    }
}

void add_product(std::vector<Product> &products){
    std::string product_name;
    int product_price, product_inventory;
    std::cout << "Please enter the name of your product: ";
    std::cin >> product_name;
    std::cout << "Please enter the price of your product: ";
    std::cin >> product_price;
    std::cout << "Please enter your product inventory: ";
    std::cin >> product_inventory;
    products.push_back(Product(product_name, product_inventory, product_price));
    std::cout << "Your product has been added succesfully!! " << '\n';
}

Order create_new_order(std::vector <Product>& products){
    std::vector<Product> order_products;
    std::vector<int> order_numbers;

    int choice;
    do{
        display_products(products);
        
        std::cout << "Please enter the product number you want(0 for finish choosing) : ";
        std::cin >> choice;

        if(choice > 0 && choice <= products.size()){
            Product& product = products[choice - 1];

            int quantity;
            do{
                std::cout << "You have chose " << product.get_name() << ".... stock = " << product.get_stock() << '\n';
                std::cout << "Enter numbers of it : ";
                std::cin >> quantity;
                if(quantity > product.get_stock() || quantity < 0){
                    std::cout << "Sorry! Please enter a valid number. \n";
                }
            }while(quantity < 0 || quantity > product.get_stock());
            
            order_numbers.push_back(quantity);
            order_products.push_back(product);
            product.set_stock(product.get_stock() - quantity);

            std::cout << quantity << " number(s) of " << product.get_name() << " have been added to the shopping cart! \n";
        }
    }while(choice != 0);

    int total_price = 0;

    for(int i = 0; i < order_products.size(); i++){
        total_price += order_products[i].get_price() * order_numbers[i];
    }

    double discount_percent; 
    std::cout << "Please enter the discount amount based on percentage (0 for No-Offer): ";
    std::cin >> discount_percent;

    // Current time 
    time_t now = time(NULL);
    tm* timeptr = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeptr);
    std::string current_date(buffer);

    // Customer details
    std::string first_name, last_name, address;
    int phone_number;
    std::cout << "Fist name: ";
    std::cin >> first_name;
    std::cout << "Last name: ";
    std::cin >> last_name;
    std::cout << "Phone number: ";
    std::cin >> phone_number;
    std::cout << "Address: ";
    //std::cin.ignore();
    std::getline(std::cin, address);

  Customer customer(first_name, last_name, phone_number, address);

    Order order(order_products, order_numbers, discount_percent, total_price, customer, current_date);
    return order;
}
    