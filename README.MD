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

---

### Features 


### Main Menu
On running the program, you will be greeted with the following main menu:
Admin: Access admin functionalities after logging in.
Customer: Register or log in as a customer to place orders or leave reviews.
Employee: Log in as an employee to manage restaurant menus or perform other duties.
Exit: Exit the application.
Admin Guide
To log in as an admin:

Username: admin
Password: admin
Admin Features
Add a new restaurant.
Print all available restaurants.
Delete a restaurant by ID.
Edit an existing restaurant.
Customer Guide
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

Roles
Manager:
Add, remove, or edit dishes in the menu.
Print the menu.
Create accounts for other employees.
Edit account details.
Regular Employee:
View orders and their statuses.
Assist in order processing.
Notes
Error Handling: The program includes prompts and checks to ensure valid inputs (e.g., IDs, ratings, and menu options).
Data Persistence: All data is maintained in memory during runtime; no database or file storage is used.
Testing: Debugging outputs are included for easier validation of the program flow.
Future Enhancements
Implement persistent data storage.
Add support for online payment systems.
Integrate additional features for promotions and discounts.
markdown
Copy code
