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
            // Showing orders
            display_orders_list();

            std::cout << "\n\n\tEnter order number to view or edit order details (0 for returning back): ";
            std::cin >> choice;
            if (choice != 0){
                Order& order = orders[choice - 1];

                // View order details
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
            std::cout << "\n\t" << i++ << ". Date: " << order.get_date() << ", Customer name: " << order.get_customer_info().get_full_name() << ", Total price: " << order.get_total_price() << "Toman. \n";
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
    std::cout << "\n\tTotal Price without discount: " << order.get_total_price() / (1 - order.get_discount()) << '\n';
    std::cout << "\n\tdiscount Percent: " << order.get_discount() * 100 <<"% \n";
    std::cout << "\n\tTotal payment: " << order.get_total_price() << '\n';
    std::cout << "\n\n\t-----------------------------------------------------------------" << '\n';
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

std::vector<Order> SalesHistory::get_orders(){
    return orders;
}