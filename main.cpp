#include "graph.h"
#include "restaurant.h"
#include <iostream>
#include <vector>
using namespace std;


int main() {
    
    Graph g = buildGraph("graph.txt");
    vector<Restaurant> restaurants = Restaurant::loadRestaurants("restaurants.txt");

    cout << "Debug: Number of restaurants: " << restaurants.size() << endl;

    cout << "Select a restaurant:\n";
    for (size_t i = 0; i < restaurants.size(); ++i) {
        cout << (i + 1) << ". " << restaurants[i].getName() << '\n';
    }

    int restaurantIdx;
    cin >> restaurantIdx;
    restaurantIdx--;

    cout << "Debug: Selected restaurant index: " << restaurantIdx << endl;

    cout << "Select the food items:\n";
    const auto &menu = restaurants[restaurantIdx].getMenu();
    for (const auto &menuItem : menu) {
        cout << menuItem.first << " - $" << menuItem.second << '\n';
    }
    map<string, int> orderedItems;
    for (const auto &menuItem : menu) {
        cout << "Enter the quantity for " << menuItem.first << ": ";
        int quantity;
        cin >> quantity;
        if (quantity > 0) {
            orderedItems[menuItem.first] = quantity;
        }
    }

    double totalPrice = 0;
    for (const auto &item : orderedItems) {
        totalPrice += menu.at(item.first) * item.second;
    }

    int src = 0;
    int dest = restaurants[restaurantIdx].getNodeId();
    int deliveryTime = dijkstra(g, src)[dest];

    cout << "\n--- Receipt ---\n";
    cout << "Restaurant: " << restaurants[restaurantIdx].getName() << '\n';
    cout << "Ordered items:\n";
    for (const auto &item : orderedItems) {
        cout << item.first << " x" << item.second << " = $" << menu.at(item.first) * item.second << '\n';
    }
    cout << "Total Price: $" << totalPrice << '\n';
    cout << "Delivery Time: " << deliveryTime << " minutes\n";

    return 0;
}



