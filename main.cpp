/*
DSA Project Phase 1
By Huzaifa Tahir 23i-0088 & Abdul Basit 23i-
SE-B
   */
#define liner "===============" << endl
#define ender 5 // Ends the program when taken as input
#include "RestaurantHub.h"
#include "Orders.h"
using namespace std;
bool authenticatedAdmin() {
	int count = 0;
	bool flag = true;
	string username, password;
	while (count < 3) {
		cout << "Enter the username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
		if (username == "admin" && password == "admin") {
			return true;
		}
		else {
			cout << "Invalid username or password" << endl;
			count++;
		}
	}
	return false;
}

int main() {

	// Variables
	int adminChoice;
	PromotionStack ps;

	// Instantiating RestaurantHub, and populating
	RestaurantHub restauranthub;
	Restaurant r("Ranchers", "Fast Food");
	r.menu = Menu(&r.name, 0);
	Dish burger("Butcher", "Burger", 850);
	burger.ID = burger.IDcount++;
	r.menu.dishes.insert(burger);
	Dish burger2("TexasJack", "Burger", 850);
	burger2.ID = burger2.IDcount++;
	r.menu.dishes.insert(burger2);

	// Assign employee to restaurant
	Employee e("huz", "huz@gmail.com", "Za!nkhau");
	e.workplace = &r;
	e.ID = Employee::IDcounter++;
	r.manager = &e;
	restauranthub.addRestaurant(r);
	e.type = 1; // As employee is a manager

	// Assign employee to hashmap
	restauranthub.hash.insertEmployee(e);


	// DEBUGGING
	int authenticationChoice;
	// MAIN MENU
	do {
		cout << "Welcome to RestaurantHub" << endl;
		cout << liner;
		cout << "What would you like to view this as?" << endl;
		cout << "1. Admin" << endl;
		cout << "2. Customer" << endl;
		cout << "3. Employee" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice: ";

		cin >> authenticationChoice;


		// View as Admin
		if (authenticationChoice == 1) {

			// Login to admin
			if (authenticatedAdmin()) {
				cout << "Welcome admin!" << endl;

				do {
					cout << liner;
					cout << "What would you like to do " << endl;
					cout << "1. Add a restaurant" << endl;
					cout << "2. Print all restaurants" << endl;
					cout << "3. Delete a restaurant" << endl;
					cout << "4. Edit a restaurant" << endl;

					cout << ender << "." << " Exit" << endl;

					cin >> adminChoice;
					switch (adminChoice) {
					case 1: {
						restauranthub.initializeRestaurant();
						break;

					}
					case 2: {
						restauranthub.printRestaurants();
						break;
					}
					case 3: {
						restauranthub.printRestaurants();
						cout << "Enter the ID of the restaurant that you want to delete: ";
						int resID;
						cin >> resID;
						resID -= 10000; // To get the index
						restauranthub.removeRestaurant(resID);

						break;
					}
					case 4: {
						restauranthub.printRestaurants();
						cout << "Enter the ID of the restaurant that you want to edit: ";
						int resID;
						cin >> resID;
						resID -= 10000; // To get the index
						restauranthub.editRestaurant(resID);
					}

					} // Switch ends here

				} while (adminChoice != ender);
			}




		}

		// View as User
		else if (authenticationChoice == 2) {
			cout << liner;
			cout << "What would you like to do: " << endl;
			cout << "1. Login" << endl;
			cout << "2. Register" << endl;
			cout << "Enter your choice: ";
			int loginChoice;
			do {
				cin >> loginChoice;
			} while (loginChoice < 1 || loginChoice > 2);

			if (loginChoice == 1) { // If logging in
				int tokenID = restauranthub.authenticatedCustomer();
				Customer* current = NULL;

				if (tokenID == 0) {
					cout << "Sorry, the username or password is incorrect or does not exist!" << endl;
				}
				else { // If authenticated
					current = restauranthub.hash.retrieveCustomer(tokenID);
					cout << liner;
					cout << "Welcome, " << current->name << endl;
					cout << endl;
					// Customer Menu
					int customerMenuChoice;
					do {
						cout << liner;
						cout << "What would you like to do : " << endl;
						cout << "1. Change account details" << endl;
						cout << "2. Place your order" << endl;
						cout << "3. View order history" << endl;
						cout << "4. View current order & order status" << endl;
						cout << "5. View all your reviews" << endl;
						cout << "6. Leave a review" << endl;
						cout << "7. Read a review" << endl;
						cout << "8. Exit" << endl;
						cout << "Enter your choice: ";
						cin >> customerMenuChoice;

						switch (customerMenuChoice) {
						case 1: {
							current->EditAccountDetails();
							break;
						}
						case 2: {
							restauranthub.printRestaurants();
							cout << "Enter the restaurantID at which you wish to order: ";
							int resID;
							cin >> resID;
							Restaurant* tempR = restauranthub.restaurants.retrieveAtIndex(resID - 10000);
							if (!tempR) {
								cout << "Sorry, no exist" << endl;
							}
							else {
								tempR->menu.printMenu();
								DishList dl;
								bool flag = true;
								while (flag) {
									cout << "Enter the ID of the dish that you wish to add to order: ";
									int dishID;
									cin >> dishID;
									Dish* tempDish = tempR->menu.dishes.retrieveDishById(dishID);

									if (tempDish) {
										cout << "Enter the quantity: ";
										int quantity;
										cin >> quantity;
										dl.addDish(tempDish, quantity);
										cout << "Do you wish to add more dishes (y/n): ";
										char sentinelChoice;
										cin >> sentinelChoice;
										if (sentinelChoice == 'n') {
											flag = false;
											break;

										}

									}
								}
								cout << "Enter type of Order (Premium/Express/Normal): ";
								string type;
								cin >> type;
								Orders* order1 = new Orders(dl, current, type, tempR->name);

								applyOrderPromotion(ps, *order1);
								float floatTemp = order1->getProcessingCost();
								cout << "Processing charge additional of : " << floatTemp << endl;
								order1->total += floatTemp;

								tempR->orderQueue.enqueue(order1);

								cout << "Order was placed" << endl;
								// Add order to customer history && current order to order1
								current->currentOD = order1;
								current->orderHistory.addOrders(order1);





							}
							break;
						}
						case 3: {
							if (!current->orderHistory.head) {
								cout << "No orders yet!" << endl;
							}
							else {
								current->orderHistory.print();
							}
							break;
						}

						case 4: {
							cout << liner;
							cout << "Current order is" << endl;
							current->currentOD->displayOrder();
							break;
						}
						
						case 5: {

							break;
						}
						case 6: {
							restauranthub.printRestaurants();
							cout << "Select the ID of the restaurant that you wish to leave a review for";
							int resID;
							do {
								cin >> resID;
								if (resID < 10000) cout << "Try again: ";
							} while (resID < 10000);
							Restaurant* revres = restauranthub.restaurants.retrieveAtIndex(resID-10000);
							if (!revres) {
								cout << "Sorry, not exist" << endl;
							}
							else {
								cout << "Would you like to leave a review for the restaurant or the dish from the restaurant" << endl;
								cout << "1. Restaurant" << endl;
								cout << "2. Dish" << endl;
								int revChoice;
								do {
									cin >> revChoice;
								} while (revChoice < 1 || revChoice > 2);
								float rating1;
								string description;

								if (revChoice == 1) { // If review for restaurant
									cout << "Enter a rating for the restaurant (from 0.0 to 5.0): ";
									
									do{
										cin >> rating1;
									} while (rating1 < 0 || rating1 > 5);

									cout << "Enter the description of your review: ";
									cin.ignore();
									getline(cin, description);
									review* r1 = new review(rating1, description, current, revres);
									r1->displayReview();
									revres->posReviews.insert(*r1);
									revres->negReviews.insert(*r1);
									current->reviewHistory.addReview(r1);
								}
								else { // If review for dish
									revres->menu.printMenu();
									cout << "Enter the ID of the dish that you want to leave a review for: ";
									int dishID;
									cin >> dishID;
									Dish* revDish = revres->menu.dishes.retrieveDishById(dishID);
									if (!revDish) {
										cout << "Sorry, dish does not exist" << endl;
										break;
									}

									cout << "Enter a rating for the dish (from 0.0 to 5.0): ";

									do {
										cin >> rating1;
									} while (rating1 < 0 || rating1 > 5);

									cout << "Enter the description of your review: ";
									cin.ignore();
									getline(cin, description);
									review* r1 = new review(rating1, description, current, revDish);
									revDish->negReviews.insert(*r1);
									revDish->posReviews.insert(*r1);
									current->reviewHistory.addReview(r1);
									
								}
							}
							

							break;
						}
						case 7: {
							restauranthub.printRestaurants();
							cout << "Select the ID of the restaurant that you wish to leave a review for";
							int resID;
							do {
								cin >> resID;
								if (resID < 10000) cout << "Try again: ";
							} while (resID < 10000);
							Restaurant* revres = restauranthub.restaurants.retrieveAtIndex(resID - 10000);
							if (!revres) {
								cout << "Sorry, not exist" << endl;
								break;
							}
							cout << "Would you like to leave a review for the restaurant or the dish from the restaurant" << endl;
							cout << "1. Restaurant" << endl;
							cout << "2. Dish" << endl;
							int revChoice;
							do {
								cin >> revChoice;
							} while (revChoice < 1 || revChoice > 2);
							break;

							if (revChoice == 1) { // View reviews for the restaurant
								cout << "Would you like to view the top five reviews ,or the bottom five reviews" << endl;
								cout << "1. Top 5" << endl;
								cout << "2. Bottom 5" << endl;
								int topChoice;
								do {
									cin >> topChoice;

								} while (topChoice < 1 || topChoice > 2);

								if (topChoice == 1) { // Print top 5
									revres->posReviews.displayTop5();
								}
								else { // Print bottom 5
									revres->negReviews.displayTop5();
								}

							}
							else { // View reviews for the Dish
								revres->menu.printMenu();
								cout << "Enter the dishID  that you wish to check the top or bottom reviews for :";
								int dishID;
								cin >> dishID;
								Dish* revDish = revres->menu.dishes.retrieveDishById(dishID);
								if (!revDish) {
									cout << "Sorry, dish does not exist" << endl;
									break;
								}
								cout << "Would you like to view the top five reviews ,or the bottom five reviews" << endl;
								cout << "1. Top 5" << endl;
								cout << "2. Bottom 5" << endl;
								int topChoice;
								do {
									cin >> topChoice;

								} while (topChoice < 1 || topChoice > 2);

								if (topChoice == 1) { // Print top 5
									revDish->posReviews.displayTop5();
								}
								else { // Print bottom 5
									revDish->negReviews.displayTop5();
								}
							}

						}
						} // Switch ending brace

					} while (customerMenuChoice != 8);
				}
			}
			else { // Registering as a user
				restauranthub.registerCustomer();
			}

		}

		// View as Employee
		else if (authenticationChoice == 3) {
			int tokenID = restauranthub.authenticatedEmployee();
			Employee* current = NULL;
			bool isManager = 0;
			if (tokenID == 0) { // If not authenticated
				cout << "Sorry, the username or password is incorrect or does not exist!" << endl;
			}
			else { // If authenticated
				current = restauranthub.hash.retrieveEmployee(tokenID); // Retrieve the current employee through ID
				cout << liner;
				cout << "Welcome, " << current->name << endl;

				if (current->type == 1) { // Prints Manager if employee is manager
					isManager = true;
					cout << "Role: Manager" << endl;

				}
				else { // Otherwise prints employee
					cout << "Role: Employee" << endl;

				}
				cout << "Working at: " << current->workplace->name << " Restaurant" << endl;
				int dishchoice;
				// Two different menus, one for manager, one for regular employee
				if (isManager) {
					do {
						cout << liner;
						cout << "1. Add a dish to the menu" << endl;
						cout << "2. Remove a dish from the menu" << endl;
						cout << "3. Edit a dish in the menu" << endl;
						cout << "4. Print menu" << endl;
						cout << "5. Create an employee's account" << endl;
						cout << "6. Edit your account details" << endl;
						cout << "10. Exit" << endl;

						cin >> dishchoice;
						switch (dishchoice) {
						case 1: {
							cin.ignore();
							current->workplace->menu.initializeMenu();

							break;
						}
						case 2: {
							current->workplace->menu.printMenu();
							cout << "Enter the ID of the dish that you wish to remove: ";
							int dishID;
							cin >> dishID;
							current->workplace->menu.dishes.deleteDishById(dishID);

							break;
						}
						case 3: {
							current->workplace->menu.printMenu();
							cout << "Enter the ID of the dish that you wish to edit: ";
							int dishID;
							cin >> dishID;
							current->workplace->menu.editDish(dishID);
							break;
						}

						case 4: {
							current->workplace->menu.printMenu();
							break;
						}

						case 5: {
							restauranthub.initializeEmployeeNotManager(*current->workplace);

							break;
						}
						case 6: {
							current->EditAccountDetails();


							break;
						}
						} // Switch ending bracket

					} while (dishchoice != 10);
				}
				else { // For regular  employee
					cout << liner;
					do {
						cout << liner;

						cout << "1. Edit your account details" << endl;
						cout << "2. Process Order" << endl;
						cout << "2. Exit" << endl;

						cin >> dishchoice;
						switch (dishchoice) {

						case 1: {
							current->EditAccountDetails();


							break;
						}
						case 2: {
							Orders* temp = current->workplace->orderQueue.dequeue();
							temp->setWaiter(current);
							temp->displayOrder();
							cout << "Was processed successfully!" << endl;
							break;
						}
						} // Switch ending bracket

					} while (dishchoice != 3);

				}



			}




		}

	} while (authenticationChoice != 4);

	return 0;
}




