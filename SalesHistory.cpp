#include "SalesHistory.h"

void SalesHistory::add_order(Order order) {
    orders.push_back(order);
}

int SalesHistory::get_total_sales(std::string start_date, std::string end_date) {
    double total_sales = 0;
    for (Order order : orders) {
        if (order.get_date() >= start_date && order.get_date() <= end_date) {
            total_sales += order.get_total_price();
        }
    }
    return total_sales;
}

void SalesHistory::print_sales_report(std::string start_date, std::string end_date) {
    double total_sales = get_total_sales(start_date, end_date);
    std::cout << "**Turn Over**" << std::endl;
    std::cout << "Date: " << start_date << " to" << end_date << std::endl;
    std::cout << "Total sales: " << total_sales << " Toman" << std::endl;
    std::cout << std::endl;
}