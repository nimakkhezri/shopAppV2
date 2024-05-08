#ifndef SALESHISTORY_H
#define SALESHISTORY_H
#include <iostream>
#include <vector>
#include "Order.h"

class SalesHistory {
public : 
    std::vector <Order> orders;

    void add_order(Order order);
    void display_orders();
    void display_orders_list();
    void veiw_order_detials(int choice);
    int get_total_sales(std::string start_date, std::string end_date);
    void print_sales_report (std::string start_date, std::string end_date);
    
    std::vector<Order> get_orders();
};

#endif