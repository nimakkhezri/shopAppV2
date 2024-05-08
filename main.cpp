#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include "Product.h"
#include "Order.h"
#include "Customer.h"
#include "SalesHistory.h"

std::vector<Product> readProductsFromFile(const std::string& filename);
void saveProductsToFile(const std::string& filename, const std::vector<Product>& products);
void saveOrdersToFiles(const std::vector<Order>& orders);
std::vector<Order> readOrdersFromFile();

void display_products(const std::vector<Product>& products);
void display_cart(const std::vector<Product>& products);
void edit_cart(std::vector<Product>& order_products, std::vector<Product>& products);
void edit_product(std::vector<Product>& products);
void add_product(std::vector<Product>& products);
bool has_product(std::string productName, const std::vector<Product>& products);
Order create_new_order(std::vector<Product>& products);
void showSalesHistory(SalesHistory);

int main (){
    std::vector <Product> products = readProductsFromFile("Data/products.dat");
    SalesHistory sales_history;
    sales_history.set_orders(readOrdersFromFile());

    int choice;
    do {
        std::cout << "\n\n\n\t                           ** AGHCHE SHOP **" << '\n';
        std::cout << "\n\n\t01. NEW PRODUCT                   ---              AFZOODAN-E MAHSOOL .01" << '\n';
        std::cout << "\n\n\t02. PRODUCTS                      ---              MAHSOOLAT .02" << '\n';
        std::cout << "\n\n\t03. ADD A NEW ORDER               ---              EJAD-E SEFARESH-E JADID .03" << '\n';
        std::cout << "\n\n\t04. ORDERS                        ---              SEFARESHAT .04" << '\n';
        std::cout << "\n\n\t05. TURNOVER                      ---              MODIRIAT-E MALI .05" << '\n';
        std::cout << "\n\n\t00. EXIT                          ---              KHOROOJ .00" << '\n';
        std::cout << "\n\n\n\tSelect Your Option (0-5): ";
        std::cin >> choice;
        std::cout << '\n';

        switch (choice) {
            case 1:
                system("CLS");
                add_product(products);
                system("CLS");
                break;
            case 2:
                system("CLS");
                int new_choice;
                display_products(products);
                std::cout << "\n\n\t*For editing products, please enter 1 \n";
                std::cout << "\n\t*For returning back please enter 0 \n";
                std::cout << "\n\n\tYour choise: ";
                std::cin >> new_choice;
                std::cout << '\n';
                if (new_choice == 1)
                    edit_product(products);
                system("CLS");
                break;
            case 3:
                system("CLS");
                sales_history.add_order(create_new_order(products));
                system("CLS");
                break;
            case 4:
                system("CLS");
                sales_history.display_orders();
                system("CLS");
                break;
            case 5:
                system("CLS");
                showSalesHistory(sales_history);
                system("CLS");
                break;
            default:
                break;
        }
    }while (choice != 0);

    saveProductsToFile("Data/products.dat", products);
    saveOrdersToFiles(sales_history.get_orders());
}

void display_products(const std::vector<Product>& products) {
    std::cout << "\n\n\n\t                          ** PRODUCTS LIST **" << '\n';
    std::cout << "\n\n\t-----------------------------------------------------------------" << "\n\n";
    if (products.empty()) {
        std::cout << "\n\tThere is no product here !!" << std::endl;
    } else {
        int i = 1;
        for (Product product : products) {
            std::cout << "\n\t" << i++ << ". " << std::setw(20) << std::left << product.get_name() << " (Stock: " << std::setw(5) << product.get_stock() << ", Price: " << std::setw(10) << product.get_price() << "Toman)" << std::endl;
        }
    }
    std::cout << "\n\n\t-----------------------------------------------------------------" << '\n';
}

void edit_product(std::vector<Product>& products) {
    std::cout << "\n\n\n\t                        **** EDIT PRODUCTS ****" << '\n';

    display_products(products);

    int product_index;
    if (products.empty()){
        system("Pause");
    }else{
        do {
            std::cout << "\n\n\tPlease enter your product number:  ";
            std::cin >> product_index;
        } while (product_index < 1 || product_index > products.size());

        int choice;
        do {
            std::cout << "\n\n\t*What do you want to do ?" << std::endl;
            std::cout << "\n\t1. Edit stock" << std::endl;
            std::cout << "\n\t2. Edit price" << std::endl;
            std::cout << "\n\t3. Return" << std::endl;
            std::cout << "\n\tChoose: ";
            std::cin >> choice;
            std::cout << '\n';
        } while (choice < 1 || choice > 3);

        Product& product = products[product_index - 1];

        switch (choice) {
            case 1: {
            int new_stock;
            do {
                std::cout << "\n\n\tPlease enter new stock: ";
                std::cin >> new_stock;
            } while (new_stock < 0);
            product.set_stock(new_stock);
            std::cout<< "\n\n\t" << product.get_name() << "'s stock changed to " << new_stock << ", Successfully !!" << std::endl;
            break;
            }
            case 2: {
            double new_price;
            do {
                std::cout << "\n\n\tPlease enter new price: ";
                std::cin >> new_price;
            } while (new_price < 0);
            product.set_price(new_price);
            std::cout << "\n\n\t" << product.get_name() << "'s price changed to " << new_price << " , Successfully !!" << std::endl;
            break;
            }
            case 3:
            break;
        }
        std::cout << "\n\n";
        system("Pause");
    }
}

void add_product(std::vector<Product> &products){
    std::cout << "\n\n\n\t                          ** ADD A NEW PRODUCT **" << '\n';
    std::string product_name;
    int product_price, product_inventory;
    std::cout << "\n\n\tPlease enter the name of your product: ";
    std::cin.ignore();
    std::getline(std::cin, product_name);
    std::cout << "\n\n\tPlease enter the price of your product: ";
    std::cin >> product_price;
    std::cout << "\n\n\tPlease enter your product inventory: ";
    std::cin >> product_inventory;
    products.push_back(Product(product_name, product_inventory, product_price));
    std::cout << "\n\n\tDone! ... Your product has been added succesfully!!\n\n" << '\n';
    system("pause");
}

Order create_new_order(std::vector <Product>& products){
    std::vector<Product> order_products;

    std::cout << "\n\n\n\t                      **** CREAT A NEW ORDER ****" << '\n';

    int choice;
    do{
        system("CLS");
        display_cart(order_products);
        display_products(products);
        
        std::cout << "\n\n\tPlease enter the product number you want(0 for finish choosing and -1 for editing cart) : ";
        std::cin >> choice;

        if(choice == -1)
            edit_cart(order_products, products);

        if(choice > 0 && choice <= products.size()){
            Product& product = products[choice - 1];

            if(product.get_stock() > 0) {

                int quantity;
                do{
                    std::cout << "\n\n\t*You have chose " << product.get_name() << "\t stock = " << product.get_stock() << '\n';
                    std::cout << "\n\n\tEnter numbers of it : ";
                    std::cin >> quantity;
                    if(quantity > product.get_stock() || quantity < 0){
                        std::cout << "\n\t*Sorry! Please enter a valid number. \n";
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
                
                std::cout << "\n\n\t" << quantity << " number(s) of " << product.get_name() << " have been added to the shopping cart! \n";

            }else{
                std::cout << "\n\t*There is not enough stock to place an order ... Please try again!" << '\n';
            }
        }
        if(choice == 0 && order_products.empty()){
            std::cout << "\n\tYour shopping cart is empty please add some products to you cart and then try again!" << '\n';
        }
    }while(choice != 0 || order_products.empty());

    int no_offer_total_price = 0;

    for(Product product : order_products){
        no_offer_total_price += product.get_price() * product.get_stock();
    }

    double discount_percent; 
    std::cout << "\n\n\tPlease enter the discount amount based on percentage (0 for No-Offer): ";
    std::cin >> discount_percent;

    // Current time 
    time_t now = time(NULL);
    tm* timeptr = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeptr);
    std::string current_date(buffer);

    // Customer details
    std::string first_name, last_name, phone_number;
    std::cout << "\n\n\tFist name: ";
    std::cin >> first_name;
    std::cout << "\n\tLast name: ";
    std::cin >> last_name;
    std::cout << "\n\tPhone number: ";
    std::cin >> phone_number;
    //std::cout << "Address: ";
    //std::cin.ignore();
    //std::getline(std::cin, address);

  Customer customer(first_name, last_name, phone_number/*, address*/);

    Order order(order_products, discount_percent, no_offer_total_price, customer, current_date);
    std::cout << "\n\n\tDone!\n";
    std::cout << "\n\tYour Order has been added successfully!\n\n";
    system("Pause");
    return order;
}

void display_cart(const std::vector <Product>& products){
    std::cout << "\n\n\n\t                          ** YOUR CART **" << "\n\n";
    if(products.empty())
        std::cout << "\n\tYour cart is empty!! " << '\n';
    else{
        int i = 1;
        for(Product product : products){
            std::cout << "\n\t" << i << ". " << std::left << std::setw(20) << product.get_name() << " Quantitiy: " << std::setw(5) << product.get_stock() << '\n';
            i++;
        }
    }
    std::cout << "\n\n\t-----------------------------------------------------------------" << '\n' << '\n';
}

void edit_cart(std::vector <Product>& order_products, std::vector <Product>& products){
    std::cout << "\n\n\n\t                           ** YOUR CART **" << "\n\n";
    int i = 1;
    if(order_products.empty()){
        std::cout << "\n\tYour cart is empty!! " << '\n';
    }else{
        for (Product product : order_products){
            std::cout << "\n\t" << i++ << ". " << std::left << std::setw(20) << product.get_name() << " Quantity: " << std::setw(5) << product.get_stock() << '\n';
        }
        std::cout << "\n\n\t-----------------------------------------------------------------" << '\n' << '\n';

        std::cout << "\n\n\t*Please enter a product number to edit (0 for returning back): ";
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
                std::cout << "\n\n\t*You have chosen " << std::left << std::setw(20) << order_product.get_name() << " Quantity: " << std::setw(5) << order_product.get_stock() << '\n';
                std::cout << "\n\n\tPlease enter a new quantity: ";
                std::cin >> new_quantity;
                if(new_quantity < 0 || new_quantity > product_total_stock)
                    std::cout << "\n\n\tPlease enter a valid value! " << '\n';
            }while(new_quantity < 0 || new_quantity > product_total_stock);

            order_product.set_stock(new_quantity);

            for(Product& product : products){
                if(order_product.get_name() == product.get_name())
                    product.set_stock(product_total_stock - new_quantity);
            }
        std::cout << "\n\n\tDone!" << '\n';
        }
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

std::vector<Product> readProductsFromFile(const std::string& filename){
    std::vector<Product> products;

    std::ifstream file(filename);
    if(file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            std::stringstream ss(line);

            std::string productName, productStock, productPrice;

            std::getline(ss, productName, ',');
            std::getline(ss, productStock, ',');
            std::getline(ss, productPrice, ',');

            products.push_back(Product(productName, std::stoi(productStock), std::stoi(productPrice)));
        }
        file.close();
    } else {
        std::cout << "\n\n\tError: Unable to open file " << filename << std::endl;
    }

    return products;

}

std::vector<Order> readOrdersFromFile(){
    std::vector<Order> orders;

    if (!std::filesystem::exists("Data/Orders")) {
        std::filesystem::create_directories("Data/Orders");
    }

    int i = 1;
    while(true){
        std::vector<Product> order_products;

        std::string order_filename = "order" + std::to_string(i) + ".dat";
        std::string order_filepath = "Data/Orders/" + order_filename;
        std::string products_filename = "products" + std::to_string(i) + ".dat";
        std::string products_filepath = "Data/Orders/" + products_filename;

        std::ifstream orderfile (order_filepath);
        std::ifstream productsfile (products_filepath);

        if (!std::filesystem::exists(order_filepath)) {
            break;
        }
        
        std::string customer_firstname, customer_lastname, customer_phonenumber, discount, total_price, date;

        if (orderfile.is_open()){
            std::string line;
            std::getline(orderfile, line);

            std::stringstream customer_ss(line);
            

            std::getline(customer_ss, customer_firstname, ',');
            std::getline(customer_ss, customer_lastname, ',');
            std::getline(customer_ss, customer_phonenumber, ',');
            std::getline(customer_ss, discount, ',');
            std::getline(customer_ss, total_price, ',');
            std::getline(customer_ss, date, ',');

        } else {
            break;
        }

        Customer customer(customer_firstname, customer_lastname, customer_phonenumber);

        if (productsfile.is_open()){
            std::string line;
            while(std::getline(productsfile, line)){
                std::stringstream ss(line);

                std::string productName, productStock, productPrice;

                std::getline(ss, productName, ',');
                std::getline(ss, productStock, ',');
                std::getline(ss, productPrice, ',');

                order_products.push_back(Product(productName, std::stoi(productStock), std::stoi(productPrice)));
            }
        } else {
            break;
        }
        orders.push_back(Order(order_products, std::stod(discount), std::stod(total_price), customer, date));
        i++;
    }
    return orders;
}

void saveProductsToFile(const std::string& filename, const std::vector<Product>& products) { 
    std::ofstream file(filename, std::ios::out | std::ios::trunc); 

    if (file.is_open()) { 
        for (const Product& product : products) { 
        file << product.name << "," << product.stock << "," << product.price << std::endl; 
        } 
 
        file.close(); 
    } else { 
        std::cout << "\n\n\tError: Unable to open file " << filename << std::endl;
    } 
}

void saveOrdersToFiles(const std::vector<Order>& orders){
    std::filesystem::remove_all("Data/Orders");

    if (!std::filesystem::exists("Data/Orders")) {
        std::filesystem::create_directories("Data/Orders");
    }

    for (int i = 0; i < orders.size(); i++){
        const Order& order = orders[i];

        std::string order_filename = "order" + std::to_string(i + 1) + ".dat";
        std::string order_filepath = "Data/Orders/" + order_filename;
        std::string products_filename = "products" + std::to_string(i + 1) + ".dat";
        std::string products_filepath = "Data/Orders/" + products_filename;

        std::ofstream orderfile (order_filepath, std::ios::out);
        if (orderfile.is_open()){
            orderfile << order.customer.first_name << "," << order.customer.last_name << "," << order.customer.phone_number << "," << order.discount << "," << order.total_price << "," << order.date << std::endl;
        }else { 
            std::cout << "\n\n\tError: Unable to open file " << order_filename << std::endl;
        } 

        std::ofstream productsfile (products_filepath, std::ios::out);
        if (productsfile.is_open()){
            for (const Product& product : order.products){
                    productsfile << product.name << "," << product.stock << "," << product.price << std::endl;
                }
        }else { 
            std::cout << "\n\n\tError: Unable to open file " << products_filename << std::endl;
        }
    }
}

void showSalesHistory(SalesHistory sale_history){
    int choice;
    do {
        system("CLS");
        std::cout << "\n\n\n\t                           ** SALES HISTORY TAB **" << '\n';
        std::cout << "\n\n\t*Select your date range" << std::endl;
        std::cout << "\n\t1. Last week" << std::endl;
        std::cout << "\n\t2. Last month" << std::endl;
        std::cout << "\n\t3. Last year" << std::endl;
        std::cout << "\n\tChoose (0 for returning back): ";
        std::cin >> choice;
        std::cout << '\n';
        if (choice > 3){
            std::cout << "\n\n\t Please enter a valid number! \n";
        }
        
        switch (choice)
        {
        case 1:
            system("CLS");
            sale_history.print_last_week();
            system("Pause");
            break;
        case 2:
            system("CLS");
            sale_history.print_last_month();
            system("Pause");
            break;
        case 3:
            system("CLS");
            sale_history.print_last_year();
            system("Pause");
            break;
        }
    } while (choice != 0);
}