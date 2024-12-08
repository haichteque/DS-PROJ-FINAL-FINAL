# Restaurant Management System - DSA Project Phase 1

## Authors
- **Huzaifa Tahir** (23i-0088)
- **Abdul Basit** (23i-3018)  
**Section:** SE-B  

---

## Project Overview
This project is a restaurant management system built for managing restaurants, customers, employees, and orders. It provides features for an admin, customers, and employees to interact with the system, including adding restaurants, placing orders, reviewing dishes/restaurants, and more.

---

## Project Structure
### Files
- **`main.cpp`**: The main driver program.
- **`RestaurantHub.h`**: Contains the class definitions and functionality related to the overall restaurant hub.
- **`Orders.h`**: Contains the class definitions for handling orders.
- **`Customer.h`**: Class definition for customer
- **`Dish.h`**: Class definition for Dish, and dishlist and dishnode
- **`Employee`**: Class definition for employee
- **`Graph.h`**: Contains the graph which stores vertices in the form of adjacency list for reduced space complexity
- **`HashMap.h`**: HashMap for employees and customers
- **`MyBinaryTree.h`**: Regular binary tree to store dishes
- **`MyLinkedList.h`**: Regular linked list to store Restaurants
- **`ordersPriorQ.h`**: Contains the priority queue for orders being processed on the basis of type, and on the basis of weight
- **`Promotion.h`**: Contains the promotion stack, and promotion logic
- **`Restaurant.h`**: Contains the class for Restaurant, and everything relevant to restaurant
- **`RestaurantHub.h`**: The singleton class that stores a linked list of restaurants, and the hashmap for customers and employees. Note that graph was stored separately.
- **`Reviews.h`**: definition of review class, and the  reviewnode and reviewlist.



---

### Features 


### Main Menu
On running the program, you will be greeted with the following main menu:
**Admin:** Access admin functionalities after logging in.
**Customer:** Register or log in as a customer to place orders or leave reviews.
**Employee:** Log in as an employee to manage restaurant menus or perform other duties.
**Exit:** Exit the application.

### Admin Guide
**To log in as an admin:**

Username: admin
Password: admin
Admin Features
Add a new restaurant.
Print all available restaurants.
Delete a restaurant by ID.
Edit an existing restaurant.

___

### Customer Guide
Registering
New users can register their accounts by selecting the Customer option in the main menu.
___

### Features for Customers
Change account details.
Place orders at restaurants by selecting dishes from their menu.
View order history.
View the current order and its status.
View, leave, edit, or delete reviews for restaurants or dishes.
___

### Employee Guide
Employees log in using their assigned credentials.

### Roles
**Manager:**
1. Add, remove, or edit dishes in the menu.
2. Print the menu.
3. Create accounts for other employees.
4. Edit account details.

**Regular Employee:**
1.View orders and their statuses.
2. Assist in order processing.


### Notes
**Error Handling:** The program includes prompts and checks to ensure valid inputs (e.g., IDs, ratings, and menu options).
**Data Persistence:** All data is maintained in memory during runtime; no database or file storage is used.
**Testing:** Debugging outputs are included for easier validation of the program flow.

___

### NEW FEATURES AND UPDATES AFTER PHASE 2
- Customer can now enter location of where they want to receive their order
- Restuarants now have their own location
- A new type of employee **driver** has been introduced, this employee will deliver the order, it will also have the ability to do everything else a regular employee can do
- Shortest path algorithm that's applied is Dijkstra's algorithm, and it's a greedy algorithm
- Added the abiltiy to add drivers through admin
- Added the ability to login as driver, and driver can process, and also deliver, which is exclusive **only** to the driver.
- New delivery fees have been added to the Order
- The different statuses of Orders are now "Not Processed", "Processed", and "Delivered".
- The locations are all stored in an adjacency list, which is taken input through a comma separated file

