#include "SalesHistory.h"
#include <iomanip>

void SalesHistory::add_order(Order order) {
    orders.push_back(order);
}

void SalesHistory::display_orders(){
    if(orders.empty()){
        std::cout << "\n\n\n\t                          ** ORDERS LIST **" << '\n' << '\n';
        std::cout << "\n\n\tThere is no Orders here! Go back and add a new order! " << '\n';
        std::cout << "\n\n\t-----------------------------------------------------------------" << '\n';
    }else{
        int choice;
        do{
            system("CLS");
            // Showing orders
            display_orders_list();

            std::cout << "\n\n\tEnter order number to view or edit order details (0 for returning back): ";
            std::cin >> choice;
            if (choice != 0){
                Order& order = orders[choice - 1];

                // View order details
                system("CLS");
                veiw_order_detials(choice);

                //int orderEditChoice;
                //do{
                //    std::cout << "To edit invoice information, choose the following options: " << '\n';
                //    //std::cout << "1. Edit the number of a product." << '\n';
                //    std::cout << "1. Edit discount." << '\n';
                //    std::cout << "0. returning back." << '\n';
                //    std::cout << "Your choice: ";
                //    std::cin >> orderEditChoice;
                //    switch (orderEditChoice)
                //    {
                //    //case 1:
                //    //    order.edit_order_product_quantity();
                //    //    break;
                //    case 1:
                //        std::cout << "Enter a new discount percent: ";
                //        int newDiscount;
                //        std::cin >> newDiscount;
                //        order.apply_discount(newDiscount);
                //        break;
                //    case 0: 
                //        std::cout << "Done! your changes applied! " << '\n';
                //        break;
                //    default:
                //        std::cout << "You enterd an unvalid number!! Please try again! ";
                //        break;
                //    }
                //}while (orderEditChoice != 0);
                system("pause");
                system("CLS");
            }
        }while(choice != 0);
    }
}

void SalesHistory::display_orders_list(){
    std::cout << "\n\n\n\t                          ** ORDERS LIST **" << '\n' << '\n';
    int i = 1;
        for (Order order : orders){
            std::cout << "\n\t" << i++ << ". Date: " << order.get_date() << ", Customer name: " << order.get_customer_info().get_full_name() << ", Total price: " << order.get_offer_price() << "Toman. \n";
        }
    std::cout << "\n\n\t-----------------------------------------------------------------" << '\n';
}

void SalesHistory::veiw_order_detials(int choice){
    Order& order = orders[choice - 1];

    std::cout << "\n\n\n\t                         *** ORDER DETAILS ***" << '\n' << '\n';
    std::cout << "\n\n\t                         ** CUSTOMER INFO **" << '\n' << '\n';
    std::cout << "\n\tCustomer Name: " << order.get_customer_info().get_full_name() << '\n';
    std::cout << "\n\tCustomer Phone number: " << order.get_customer_info().get_phone_number() << '\n';
    std::cout << "\n\tDate: " << order.get_date() << "\n\n";
    std::cout << "\n\n\t                         ** ORDER PRODUCTS **" << '\n' << '\n';
    int i = 1;
    for(Product product : order.products){
        std::cout << "\n\t" << i++ <<". " << product.get_name() << '\t' << "Numbers: " << product.get_stock() << '\t' << "base Price: " << product.get_price() << '\t' << "Total Price: " << product.get_price() * product.get_stock() << " Toman" << '\n';
    }
    std::cout << '\n';
    std::cout << "\n\n\t                         ** TOTAL PRICE **" << '\n' << '\n';
    std::cout << "\n\tTotal Price without discount: " << order.get_total_price() << '\n';
    std::cout << "\n\tdiscount Percent: " << order.get_discount() <<"% \n";
    std::cout << "\n\tTotal payment: " << order.get_offer_price() << '\n';
    std::cout << "\n\n\t-----------------------------------------------------------------" << '\n';
}

int SalesHistory::get_total_sales(std::string start_date, std::string end_date) {
    int total_sales = 0;
    for (Order order : orders) {
        if (order.get_date() >= start_date && order.get_date() <= end_date) {
            total_sales += order.get_offer_price();
        }
    }
    return total_sales;
}

void SalesHistory::print_sales_report(std::string start_date, std::string end_date) {
    double total_sales = get_total_sales(start_date, end_date);
    std::cout << "\n\n\tDate: \t" << start_date << " \tto\t" << end_date << std::endl;
    std::cout << "\n\n\tSales number: \t" << get_sales_number(start_date, end_date) << std::endl;
    std::cout << "\n\n\tTotal sales: \t" << get_total_sales(start_date, end_date) << "\t Toman" << std::endl;
    std::cout << std::endl;
}

std::vector<Order> SalesHistory::get_orders(){
    return orders;
}

void SalesHistory::set_orders(std::vector<Order> saved_orders){
    this->orders = saved_orders;
}

void SalesHistory::print_last_month(){
    // Current time 
    time_t now = time(NULL);
    tm* timeptr = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeptr);
    std::string current_date(buffer);

    std::string last_month_date = current_date;

    if (last_month_date.substr(5, 2) == "00"){
        last_month_date = last_month_date.replace(5, 2, "12");
        last_month_date = last_month_date.replace(3, 1, std::to_string(std::stoi(last_month_date.substr(0, 4)) - 1));
    } else if (std::stoi(last_month_date.substr(5, 2)) <= 10){
        last_month_date = last_month_date.replace(5, 2, "0" + std::to_string(std::stoi(last_month_date.substr(5, 2)) - 1));
    } else {
        last_month_date = last_month_date.replace(5, 2, std::to_string(std::stoi(last_month_date.substr(5, 2)) - 1));

    }
    std::cout << "\n\n\n\t                          ** LAST MONTH'S SALES **" << '\n';

    print_sales_report(last_month_date, current_date);
}

void SalesHistory::print_last_year(){
    // Current time 
    time_t now = time(NULL);
    tm* timeptr = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeptr);
    std::string current_date(buffer);

    std::string last_year_date = current_date;

    int this_year = std::stoi(current_date.substr(0, 4));
    last_year_date = last_year_date.replace(0, 4, std::to_string(std::stoi(current_date.substr(0, 4)) - 1));

    print_sales_report(last_year_date, current_date);
}

void SalesHistory::print_last_week(){
    // Current time 
    time_t now = time(NULL);
    tm* timeptr = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeptr);
    std::string current_date(buffer);

    std::string last_week_date = current_date;
    int today = std::stoi(current_date.substr(8, 2));
    int this_month = std::stoi(current_date.substr(5, 2));
    int this_year = std::stoi(current_date.substr(0, 4));

    if (today <= 10){
        if (today < 7){
            if (this_month == 0){
                last_week_date = last_week_date.replace(5, 2, "12");
                last_week_date = last_week_date.replace(3, 1, std::to_string(this_year - 1));
            }
            else if (this_month <= 10){
                last_week_date = last_week_date.replace(5, 2, "0" + std::to_string(this_month - 1));
            } else if (this_month > 10){
                last_week_date = last_week_date.replace(5, 2, std::to_string(this_month - 1));
            }
            last_week_date = last_week_date.replace(8, 2, std::to_string(30 + today - 7));
        } else {
            last_week_date = last_week_date.replace(8, 2, "0" + std::to_string(today - 7));
        }
    }
    std::cout << "\n\n\n\t                          ** LAST WEEK'S SALES **" << '\n';

    print_sales_report(last_week_date, current_date);
}

int SalesHistory::get_sales_number(std::string start_date, std::string end_date){
    int quantity = 0;
    for (Order order : orders) {
        if (order.get_date() >= start_date && order.get_date() <= end_date) {
            quantity++;
        }
    }
    return quantity;
}