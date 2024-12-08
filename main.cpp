/*
DSA Project Phase 1
By Huzaifa Tahir 23i-0088 & Abdul Basit 23i-3018
SE-B
 */
#define liner "===============" << endl
#define ender 5 // Ends the program when taken as input
#include"RestaurantHub.h"
#include "Orders.h"
#include "Graph.h"
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

	// Initialize everything into a graph
	ifstream file("Graph_of_Islamabad.csv");
	if (!file.is_open()) {
		cout << "Error: Could not open the file.\n";
		return 1;
	}

	Graph graph;

	string line;
	while (getline(file, line)) {
		istringstream ss(line);
		string vertex1, vertex2, weightStr;

		if (getline(ss, vertex1, ',') &&
			getline(ss, vertex2, ',') &&
			getline(ss, weightStr)) {
			int weight = stoi(weightStr);

			// Get indices for the vertices
			int index1 = graph.getVertexIndex(vertex1);
			int index2 = graph.getVertexIndex(vertex2);

			// Add edges to the adjacency list
			if (index1 != -1 && index2 != -1) {
				graph.addEdge(index1, index2, weight);
			}
		}
	}
	file.close();


	graph.printAdjacencyList();




	// Variables
	int adminChoice;
	PromotionStack ps;
	Promotion* p1 = new Promotion("10OFF", 10, 2);
	Promotion* p2 = new Promotion("20OFF", 20, 5);
	Promotion* p3 = new Promotion("30OFF", 30, 5);
	ps.push(p1);
	ps.push(p2);
	ps.push(p3);

	// Instantiating RestaurantHub, and populating
	RestaurantHub restauranthub;
	Restaurant r1("Ranchers", "Fast Food");
	r1.menu = Menu(&r1.name, 0);
	Dish burger1("Butcher", "Burger", 850);
	burger1.ID = burger1.IDcount++;
	r1.menu.dishes.insert(burger1);
	Dish burger2("TexasJack", "Burger", 850);
	burger2.ID = burger2.IDcount++;
	r1.menu.dishes.insert(burger2);
	r1.location = graph.vertices[0]; // sets location


	Employee e1("Huz", "huz@gmail.com", "Za!nkhau1");
	e1.workplace = &r1;
	e1.ID = Employee::IDcounter++;
	e1.type = 1;  // Manager
	r1.manager = &e1;

	// Restaurant 1 driver
	Employee e6("inam", "inamullah@gmail.com", "Inamullah!23");
	e6.workplace = &r1;
	e6.ID = Employee::IDcounter++;
	e6.type = 3;  // Driver
	restauranthub.hash.insertEmployee(e6);

	restauranthub.hash.insertEmployee(e1);

	// Restaurant 2: Ocean Grill
	Restaurant r2("Ocean Grill", "Seafood");
	r2.menu = Menu(&r2.name, 0);
	Dish fishTaco("ChefNet", "Fish Taco", 1200);
	fishTaco.ID = fishTaco.IDcount++;
	r2.menu.dishes.insert(fishTaco);
	Dish lobsterRoll("CaptainSea", "Lobster Roll", 2500);
	lobsterRoll.ID = lobsterRoll.IDcount++;
	r2.menu.dishes.insert(lobsterRoll);

	r2.location = graph.vertices[1]; // sets location as G-6

	Employee e2("Sara", "sara@ocean.com", "SeaPass123");
	e2.workplace = &r2;
	e2.ID = Employee::IDcounter++;
	e2.type = 1;  // Manager
	r2.manager = &e2;

	Employee e4("Inam", "inam@ocean.com", "inam!23");
	e4.workplace = &r2;
	e4.ID = Employee::IDcounter++;
	e4.type = 0;  // Not Manager
	restauranthub.hash.insertEmployee(e4);

	// Restaurant 2 Driver
	Employee e5("Driver", "driver@gmail.com", "driver!23");
	e5.workplace = &r2;
	e5.ID = Employee::IDcounter++;
	e5.type = 3;  // Driver
	restauranthub.hash.insertEmployee(e5);
	


	restauranthub.hash.insertEmployee(e2);

	// Restaurant 3: Bella Italia
	Restaurant r3("Bella Italia", "Italian");
	r3.menu = Menu(&r3.name, 0);
	Dish pasta("ChefMamma", "Spaghetti Carbonara", 1400);
	pasta.ID = pasta.IDcount++;
	r3.menu.dishes.insert(pasta);
	Dish pizza("NapoliChef", "Margherita Pizza", 1800);
	pizza.ID = pizza.IDcount++;
	r3.menu.dishes.insert(pizza);

	Employee e3("Marco", "marco@bella.com", "ItaliaP@ss1");
	e3.workplace = &r3;
	e3.ID = Employee::IDcounter++;
	e3.type = 1;  // Manager
	r3.manager = &e3;

	// Restaurant 3 Driver
	Employee e7("qazi", "qazi@gmail.com", "Qazihuz!23");
	e7.workplace = &r3;
	e7.ID = Employee::IDcounter++;
	e7.type = 3;  // Driver
	restauranthub.hash.insertEmployee(e7);


	// Customers populated here
	Customer* c1 = new Customer("Huzaifa", "huzaifa@gmail.com", "P@ss1234");
	c1->ID = c1->IDcounter++;
	restauranthub.hash.insertCustomer(c1);

	// Do the same for one more customer
	Customer* c2 = new Customer("Abdul", "abdulbasit@gmail.com", "Abdul!23");
	c2->ID = c2->IDcounter++;
	restauranthub.hash.insertCustomer(c2);

	DishList list1;
	list1.addDish(&lobsterRoll, 2);

	Orders* o1 = new Orders(list1, c2,"Premium", "Ocean Grill");
	o1->location = graph.vertices[4]; // sets location
	applyOrderPromotion(ps, *o1);
	float tmp = o1->getDeliveryCost();
	o1->total += tmp;
	tmp = o1->getProcessingCost();
	o1->total += tmp;
	r2.orderQueue.enqueue(o1);;
	c2->orderHistory.addOrders(o1);

	Orders* o2 = new Orders(list1, c2, "Premium", "Ocean Grill");
	o2->location = graph.vertices[5]; // sets location
	applyOrderPromotion(ps, *o2);
	tmp = o2->getDeliveryCost();
	o2->total += tmp;
	 tmp = o2->getProcessingCost();
	o2->total += tmp;
	r2.orderQueue.enqueue(o2);;
	c2->orderHistory.addOrders(o2);

	Orders* o3 = new Orders(list1, c2, "Premium", "Ocean Grill");
	o3->location = graph.vertices[6]; // sets location
	applyOrderPromotion(ps, *o3);
	tmp = o3->getDeliveryCost();
	o3->total += tmp;
	 tmp = o3->getProcessingCost();
	o3->total += tmp;
	r2.orderQueue.enqueue(o3);;
	c2->orderHistory.addOrders(o3);

	Orders* o4 = new Orders(list1, c2, "Premium", "Ocean Grill");
	o4->location = graph.vertices[7]; // sets location
	applyOrderPromotion(ps, *o4);
	tmp = o4->getDeliveryCost();
	o4->total += tmp;
	tmp = o4->getProcessingCost();
	o4->total += tmp;
	r2.orderQueue.enqueue(o4);;
	c2->orderHistory.addOrders(o4);

	Orders* o5 = new Orders(list1, c2, "Premium", "Ocean Grill");
	o5->location = graph.vertices[8]; // sets location
	applyOrderPromotion(ps, *o5);
	tmp = o5->getDeliveryCost();
	o5->total += tmp;
	 tmp = o5->getProcessingCost();
	o5->total += tmp;
	r2.orderQueue.enqueue(o5);;
	c2->orderHistory.addOrders(o5);
	c2->currentOD = o5;

	r3.location = graph.vertices[2]; // sets location

	restauranthub.hash.insertEmployee(e3);

	// Add 2 reviews for restaurant, 2 reviews for dish
	review* rev1 = new review(4.5, "Great food, great service", c1, &r1);
	review* rev2 = new review(3.7, "Great food, okay service", c2, &r1);
	
	review* di1 = new review(4.2, "Great burger, great service", c1, &burger1);
	review* di2 = new review(3.3, "Great burger, okay service", c2, &burger1);

	c1->reviewHistory.addReview(di1);
	c2->reviewHistory.addReview(di2);
	c1->reviewHistory.addReview(rev1);
	c2->reviewHistory.addReview(rev2);

	r1.posReviews.insert(rev1);
	r1.negReviews.insert(rev1);
	r1.posReviews.insert(rev2);
	r1.negReviews.insert(rev2);
	
	burger1.posReviews.insert(di1);
	burger1.negReviews.insert(di1);
	burger1.posReviews.insert(di2);
	burger1.negReviews.insert(di2);

	restauranthub.addRestaurant(&r1);
	restauranthub.addRestaurant(&r2);
	restauranthub.addRestaurant(&r3);

	system("pause");
	system("cls");

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
						restauranthub.initializeRestaurant(graph);
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
			//r2.orderQueue.displayQueue();
			cout << endl;
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
						cout << "8. Edit a review" << endl;
						cout << "9. Delete a review" << endl;
						cout << "10. Exit" << endl;
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
								int locationID;
								// Ask customer for their location
								graph.printVertices();
								cout << liner;
								cout << "Choose your location: ";
								do {
									cin >> locationID;
									locationID--; // So that its 0-based
								} while (locationID < 0 || locationID > graph.vertexCount-1);
								
								string customerLocation = graph.vertices[locationID];
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
								order1->location = customerLocation; // Add location to order
								applyOrderPromotion(ps, *order1);
								float floatTemp = order1->getDeliveryCost();
								order1->total += floatTemp;
								floatTemp = order1->getProcessingCost();
								cout << "Processing charge additional of : " << floatTemp << endl;
								order1->total += floatTemp;
								tempR->orderQueue.enqueue(order1);
								cout << "Order was placed" << endl;
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
							current->reviewHistory.displayReviews();
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
									
									revres->posReviews.insert(r1);
									revres->negReviews.insert(r1);

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
									revDish->negReviews.insert(r1);
									revDish->posReviews.insert(r1);
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
							cout << "Would you like to  view reviews for the restaurant or a dish from the restaurant" << endl;
							cout << "1. Restaurant" << endl;
							cout << "2. Dish" << endl;
							int revChoice;
							do {
								cin >> revChoice;
							} while (revChoice < 1 || revChoice > 2);
							
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
							break;
						}
						case 8: {
							current->reviewHistory.displayReviews();
							cout << "Enter the ID of the review that you wish to edit: ";
							int revID;
							cin >> revID;
							review* editRev = current->reviewHistory.retrieveReviewByID(revID);
							if (!editRev) {
								cout << "Review not found" << endl;
								break;
							}
							cout << "What would you like to edit about this review? " << endl;
							cout << "1. Rating" << endl;
							cout << "2. Description" << endl;
							int editChoice;
							do {
								cin >> editChoice;
							} while (editChoice < 1 || editChoice > 2);
							
							if (editChoice == 1) { // If rating
								float rating;
								cout << "Enter your new rating from 0 to 5" << endl;
								do {
									cin >> rating;
								} while (rating < 0 || rating > 5);

								editRev->rating = rating;

							}
							else { // If descriptiom
								string description;
								cout << "Enter your new description" << endl;
								cin.ignore();
								getline(cin, description);
								editRev->description = description;
							}

						

							break;
						}

						case 9: {
							if (!current->reviewHistory.head) {
								cout << "Empty!" << endl;
								break;
							}

							current->reviewHistory.displayReviews();
							cout << "Enter the ID of the review that you wish to delete: ";
							int reviewID;
							cin >> reviewID;
							review* tempRev = current->reviewHistory.retrieveReviewByID(reviewID);
							Restaurant* tempRes = tempRev->restaurant;
							// Delete the review from the restaurant
							

							current->reviewHistory.removeReview(reviewID);

							break;
						}

						} // Switch ending brace

					} while (customerMenuChoice != 10);
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
			int type = 0;
			if (tokenID == 0) { // If not authenticated
				cout << "Sorry, the username or password is incorrect or does not exist!" << endl;
			}
			else { // If authenticated
				current = restauranthub.hash.retrieveEmployee(tokenID); // Retrieve the current employee through ID
				cout << liner;
				cout << "Welcome, " << current->name << endl;

				if (current->type == 1) { // Prints Manager if employee is manager
					type = 1;
					cout << "Role: Manager" << endl;

				}
				else if (current->type == 0) { // Otherwise prints employee
					cout << "Role: Employee" << endl;

				}
				else {
					cout << "Role: Driver" << endl;
				}
				if (!current->workplace) {
					cout << "Sorry, you're unemployed!" << endl;
					
				}
				else {
					cout << "Working at: " << current->workplace->name << " Restaurant" << endl;
					int dishchoice;
					// Two different menus, one for manager, one for regular employee
					if (current->type == 1) {
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
					else if (current->type == 0) { // For regular  employee
						cout << liner;
						do {
							cout << liner;

							cout << "1. Edit your account details" << endl;
							cout << "2. Process Order" << endl;
							cout << "3. View order history" << endl;
							cout << "4. Exit" << endl;

							cin >> dishchoice;
							switch (dishchoice) {

							case 1: {
								current->EditAccountDetails();


								break;
							}
							case 2: {
								Orders* temp = current->workplace->orderQueue.dequeue();
								if (!temp) {
									cout << "No order currently in the queue!" << endl;
									break;
								}
								temp->setWaiter(current);
								temp->status = "Processed"; // The order has been processed

								// Now, find weight between start and end, and add it to orderpriorq after processed
								int startIndex = graph.getLocationIndex(current->workplace->location);
								int endIndex = graph.getLocationIndex(temp->location);
								int weight = graph.dijkstra(startIndex, endIndex);

								// Set order weight
								temp->weight = weight;

								// Add it to the post-process order queue
								current->workplace->processedOrders.enqueueByWeight(temp);



								cout << weight << endl;

								temp->displayOrder();
								cout << "Was processed successfully!" << endl;
								break;
							}

							case 3: {
								current->workplace->orderHistory.displayQueue();

								break;
							}

							} // Switch ending bracket

						} while (dishchoice != 4);

					}

					else { // For delivery driver
						cout << liner;
						do {
							cout << liner;

							cout << "1. Edit your account details" << endl;
							cout << "2. Process Order" << endl;
							cout << "3. Deliver Order" << endl;
							cout << "4. View order history" << endl;
							cout << "5. Exit" << endl;

							cin >> dishchoice;
							switch (dishchoice) {

							case 1: {
								current->EditAccountDetails();


								break;
							}
							case 2: {
								Orders* temp = current->workplace->orderQueue.dequeue();
								if (!temp) {
									cout << "No order currently in the queue!" << endl;
									break;
								}
								temp->setWaiter(current);
								temp->status = "Processed"; // The order has been processed

								// Now, find weight between start and end, and add it to orderpriorq after processed
								int startIndex = graph.getLocationIndex(current->workplace->location);
								int endIndex = graph.getLocationIndex(temp->location);
								int weight = graph.dijkstra(startIndex, endIndex);

								// Set order weight
								temp->weight = weight;

								// Add it to the post-process order queue
								current->workplace->processedOrders.enqueueByWeight(temp);
								
								

								cout << weight << endl;

								temp->displayOrder();
								cout << "Was processed successfully!" << endl;
								break;
							}
							case 3: {
								if (current->workplace->processedOrders.isEmpty()) { // if processed queue is empty
									cout << "Sorry, no order has been processed yet that needs to be delivered" << endl;
									break;
								}

								string deliveryPath = ""; // To store the complete delivery path
								int currentLocation = graph.getLocationIndex(current->workplace->location); // Starting location of the delivery driver
								int totalWeight = 0; // To keep track of the total distance covered

								// Begin delivery process
								while (!current->workplace->processedOrders.isEmpty()) {
									Orders* nextOrder = current->workplace->processedOrders.dequeue(); // Dequeue the next order
									int nextLocation = graph.getLocationIndex(nextOrder->location); // Get the delivery location for the order

									// Find the shortest path from the current location to the order's location
									string pathSegment = graph.dijkstraPath(currentLocation, nextLocation); // Returns path as a string
									int segmentWeight = graph.dijkstra(currentLocation, nextLocation); // Get the distance weight

									// Append the path segment to the full delivery path
									if (!deliveryPath.empty()) {
										deliveryPath += " -> ";
									}
									deliveryPath += pathSegment;

									totalWeight += segmentWeight; // Add the weight of this segment
									currentLocation = nextLocation; // Update current location to the new destination

									// Mark the order as delivered
									nextOrder->status = "Delivered";
									cout << "Order delivered to: " << graph.vertices[nextLocation] << endl;

									// Set its driver as well as adding it to orderhistory
									nextOrder->driver = current;
									nextOrder->driver->workplace->orderHistory.enqueueByWeight(nextOrder);
								}

								// Print the final delivery path and total weight
								cout << "Final Delivery Path: " << deliveryPath << endl;
								cout << "Total Distance Covered: " << totalWeight << " units" << endl;

								break;
							}
							case 4: {
								current->workplace->orderHistory.displayQueue();

								break;
							}
							} // Switch ending bracket

						} while (dishchoice != 5);
					}

				}


			}




		}

	} while (authenticationChoice != 4);

	return 0;
}




