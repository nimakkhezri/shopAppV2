#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
#include "Product.h"
#include "Order.h"
#include "Customer.h"
#include "SalesHistory.h"

void display_products(const std::vector<Product>& products);
void display_cart(const std::vector<Product>& products);
void edit_cart(std::vector<Product>& order_products, std::vector<Product>& products);
void edit_product(std::vector<Product>& products);
void add_product(std::vector<Product>& products);
bool has_product(std::string productName, const std::vector<Product>& products);
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
                if (new_choice == 1)
                    edit_product(products);
                break;
            case 3:
                sales_history.add_order(create_new_order(products));
                break;
            case 4:
                sales_history.display_orders();
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
        std::cout << "-------------------- **Products** --------------------" << std::endl;
        int i = 1;
        for (Product product : products) {
            std::cout << i << ". " << std::setw(20) << std::left << product.get_name() << " (Stock: " << std::setw(5) << product.get_stock() << ", Price: " << std::setw(10) << product.get_price() << "Toman)" << std::endl;
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
        std::cout << product.get_name() << "'s stock changed to" << new_stock << ", Succesfully !!" << std::endl;
        break;
        }
        case 2: {
        double new_price;
        do {
            std::cout << "Please enter new price: ";
            std::cin >> new_price;
        } while (new_price < 0);
        product.set_price(new_price);
        std::cout << product.get_name() << "'s price changed to" << new_price << " , Succesfully !!" << std::endl;
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
    std::cin.ignore();
    std::getline(std::cin, product_name);
    std::cout << "Please enter the price of your product: ";
    std::cin >> product_price;
    std::cout << "Please enter your product inventory: ";
    std::cin >> product_inventory;
    products.push_back(Product(product_name, product_inventory, product_price));
    std::cout << "Your product has been added succesfully!! " << '\n';
}

Order create_new_order(std::vector <Product>& products){
    std::vector<Product> order_products;

    int choice;
    do{
        display_cart(order_products);
        display_products(products);
        
        std::cout << "Please enter the product number you want(0 for finish choosing and -1 for editing cart) : ";
        std::cin >> choice;

        if(choice == -1)
            edit_cart(order_products, products);

        if(choice > 0 && choice <= products.size()){
            Product& product = products[choice - 1];

            if(product.get_stock() > 0) {

                int quantity;
                do{
                    std::cout << "You have chose " << product.get_name() << ".... stock = " << product.get_stock() << '\n';
                    std::cout << "Enter numbers of it : ";
                    std::cin >> quantity;
                    if(quantity > product.get_stock() || quantity < 0){
                        std::cout << "Sorry! Please enter a valid number. \n";
                    }
                }while(quantity < 0 || quantity > product.get_stock());

                if(has_product(product.get_name(), order_products)){
                    for(Product& new_order_product : order_products){
                        if(product.get_name() == new_order_product.get_name()){
                            new_order_product.set_stock(new_order_product.get_stock() + quantity);
                            product.set_stock(product.get_stock() - quantity);
                        }
                    }
                }else{
                    Product new_order_product = product;
                    new_order_product.set_stock(quantity);
                    order_products.push_back(new_order_product);
                    product.set_stock(product.get_stock() - quantity);
                }
                
                std::cout << quantity << " number(s) of " << product.get_name() << " have been added to the shopping cart! \n";

            }else{
                std::cout << "There is not enough stock to place an order ... Please try again!" << '\n';
            }
        }
        if(choice == 0 && order_products.empty()){
            std::cout << "Your shopping cart is empty please add some products to you cart and then try again!" << '\n';
        }
    }while(choice != 0 || order_products.empty());

    int total_price = 0;

    for(Product product : order_products){
        total_price += product.get_price() * product.get_stock();
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
    std::string first_name, last_name, phone_number;
    std::cout << "Fist name: ";
    std::cin >> first_name;
    std::cout << "Last name: ";
    std::cin >> last_name;
    std::cout << "Phone number: ";
    std::cin >> phone_number;
    //std::cout << "Address: ";
    //std::cin.ignore();
    //std::getline(std::cin, address);

  Customer customer(first_name, last_name, phone_number/*, address*/);

    Order order(order_products, discount_percent, total_price, customer, current_date);
    return order;
}

void display_cart(const std::vector <Product>& products){
    std::cout << "-------------------- ** CART ** --------------------" << '\n';
    if(products.empty())
        std::cout << "Your cart is empty!! " << '\n';
    else{
        int i = 1;
        for(Product product : products){
            std::cout << i << ". " << std::left << std::setw(120) << product.get_name() << " Quantitiy: " << std::setw(5) << product.get_stock() << '\n';
            i++;
        }
    }
    std::cout << "-------------------- ** CART ** --------------------" << '\n' << '\n';
}

void edit_cart(std::vector <Product>& order_products, std::vector <Product>& products){
    std::cout << "-------------------- ** EDIT CART ** --------------------" << '\n' << '\n';
    int i = 1;
    for (Product product : order_products){
        std::cout << i << ". " << std::left << std::setw(20) << product.get_name() << " Quantity: " << std::setw(5) << product.get_stock() << '\n';
    }
    std::cout << '\n';
    std::cout << "Please enter a product number to edit (0 for returning back): ";
    int choice; 
    std::cin >> choice;
    int product_total_stock;

    if (choice > 0 && choice <= order_products.size()){
        Product& order_product = order_products[choice - 1];

        for(Product& product : products){
            if(order_product.get_name() == product.get_name())
                product_total_stock = product.get_stock() + order_product.get_stock();
        }
        int new_quantity;

        do{
            std::cout << "You have chosen " << std::left << std::setw(20) << order_product.get_name() << " Quantity: " << std::setw(5) << order_product.get_stock() << '\n';
            std::cout << "Please enter a new quantity: ";
            std::cin >> new_quantity;
            if(new_quantity < 0 || new_quantity > product_total_stock)
                std::cout << "Please enter a valid value! " << '\n';
        }while(new_quantity < 0 || new_quantity > product_total_stock);

        order_product.set_stock(new_quantity);

        for(Product& product : products){
            if(order_product.get_name() == product.get_name())
                product.set_stock(product_total_stock - new_quantity);
        }
    std::cout << "Done!" << '\n';
    }
}

bool has_product(std::string productName, const std::vector<Product>& products){
    for(Product product : products){
        if (product.get_name() == productName){
            return true;
        }
    }
    return false;
}