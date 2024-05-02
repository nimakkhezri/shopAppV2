#ifndef SALESHISTORY_H
#define SALESHISTORY_H
#include <iostream>
#include <vector>
#include "Order.h"

class SalesHistory {
public : 
    std::vector <Order> orders;

    void add_order(Order order);
    int get_total_sales(std::string start_date, std::string end_date);
    void print_sales_report (std::string start_date, std::string end_date);
    
};

#endif