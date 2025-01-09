#include<iostream>
#include<string>

#ifdef _WIN32
#include <cstdlib>
#else
#include <unistd.h>
#endif
using namespace std;
void clearScreen() {
#ifdef _WIN32
	std::system("cls"); // For Windows
#else
	std::system("clear"); // For Linux
#endif
}
void waitForEnter() {
	std::cout << "\nPress Enter to continue...";
	std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
	std::cin.get();
}
struct OrderNode {
	string orderID;
	char priority;
	OrderNode* next;

	OrderNode() : next(nullptr), orderID(""), priority('\0') {}
};
class OrderQueue {
private:
	OrderNode* head;
	OrderNode* tail;
	int totalOrders;
	int completedOrders;

public:
	OrderQueue() : head(nullptr), tail(nullptr), totalOrders(0), completedOrders(0) {}

	void enqueue(string orderID, char priority) {
		OrderNode* newNode = new OrderNode;
		newNode->orderID = orderID;
		newNode->priority = priority;

		if (!head) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}

		totalOrders++;
	}
	void dequeue() {
		OrderNode* current = head;
		if (!head) {
			cout << "\n===========================\n";
			cout << "No order available";
			cout << "\n===========================\n";

			return;

		}

		cout << "Order ID: " << head->orderID << endl;
		cout << "Priority: " << head->priority << endl;

		head = head->next;
		delete current;

		totalOrders--;
		completedOrders++;

	}
	void dequeue(string orderID) {
		OrderNode* current = head;
		OrderNode* prev = nullptr;

		while (current) {
			if (current->orderID == orderID) {
				if (current == head) {
					head = current->next;
				}
				else {
					prev->next = current->next;
				}

				cout << "Order ID: " << current->orderID << endl;
				cout << "Priority: " << current->priority << endl;

				delete current;
				totalOrders--;
				completedOrders++;

				return;
			}

			prev = current;
			current = current->next;
		}

		// If the loop completes, the orderID was not found
		cout << "Order ID " << orderID << " not found." << endl;
	}

	void dequeueAll() {
		while (head) {
			dequeue();
		}

		tail = nullptr;
		completedOrders += totalOrders;
		totalOrders = 0;
	}


	void displayOrders() {
		OrderNode* current = head;
		while (current) {
			switch (current->priority) {
			case '1':
			case '2':
			case '3':
				cout << "=========================================\n";
				cout << "Order Id: " << current->orderID << endl;
				cout << "Priority: " << current->priority << endl;
				cout << "=========================================\n";
				break;
			default:
				// Handle unexpected priority value
				break;
			}
			current = current->next;
		}
	}

	void displaySingleOrder(string orderID) {
		OrderNode* current = head;
		while (current) {
			if (current->orderID == orderID) {
				cout << "=========================================\n";
				cout << "Order Id: " << current->orderID << endl;
				cout << "Priority: " << current->priority << endl;
				cout << "=========================================\n";
			}
			current = current->next;
		}
	}

	void getOrderStatistics() {
		if (!head)
		{
			totalOrders = completedOrders = 0;
		}
		cout << "Total number of orders pending: " << totalOrders << endl;
		cout << "Total number of orders completed: " << completedOrders << endl;
	}
	bool check()
	{
		if (!head) {
			return true;
		}
		else
		{
			return false;
		}
	}
	~OrderQueue() {
		while (head) {
			OrderNode* current = head;
			head = head->next;
			delete current;
		}
		tail = nullptr;
	}
};
struct OrderDetails {
	string name;
	string orderId;
	string deliveryTime;
	string terms;
	string productName;
	string* raw;  // Changed to string type to avoid memory leaks
	int productionCost;
	int rawCost;
	int totalAmount;
	int rawQ;
	OrderDetails* next;

	OrderDetails() : next(nullptr), name(""), orderId(""), deliveryTime(""), terms(""), productionCost(0), rawCost(0), totalAmount(0), raw(nullptr), rawQ(0) {}
};
class OrderDetailsList {
private:
	OrderDetails* head;
	OrderDetails* tail;

public:
	OrderDetailsList() : head(nullptr), tail(nullptr) {}

	void addOrderDetails(string name, string orderId, string deliveryTime, string terms) {
		OrderDetails* newNode = new OrderDetails;
		newNode->name = name;
		newNode->orderId = orderId;
		newNode->deliveryTime = deliveryTime;
		newNode->terms = terms;

		if (!head) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
	}

	void rawMaterial(int amount) {
		OrderDetails* current = tail;  // Update to the last node

		if (!current) {
			cout << "\n===========================\n";
			cout << "   No order available";
			cout << "\n===========================\n";
			return;
		}

		current->raw = new string[amount];
		current->rawQ = amount;
		int cost = 0, quantity = 0;

		for (int i = 0; i < amount; i++) {
			cout << "Enter material name" << endl;
			cin.ignore();
			getline(cin, current->raw[i]);
			cout << "Enter quantity of product" << endl;
			cin >> quantity;
			cout << "Enter cost of material" << endl;
			cin >> cost;

			current->rawCost += (cost * quantity);

			current->totalAmount = current->rawCost + current->productionCost;

			cout << "===============================\n";
		}
	}
	void production()
	{
		OrderDetails* current = tail;
		int p = 0;
		cout << "Enter product name" << endl;
		cin.ignore();
		getline(cin, current->productName);
		cout << "enter production fee: ";
		cin >> p;
		current->productionCost = p;
		current->totalAmount = current->rawCost + current->productionCost;

	}
	void displayRaw() {
		OrderDetails* current = head;

		if (!current) {
			cout << "\n===========================\n";
			cout << "No order available";
			cout << "\n===========================\n";
			return;
		}

		while (current) {
			cout << "=== material for order ID:" << current->orderId << " ===" << endl;
			cout << "---------------------------------------------------\n";
			cout << "Material used " << endl;
			for (int i = 0; i < current->rawQ; i++) {
				cout << endl;
				cout << current->raw[i];
				cout << "\n=================\n";
			}
			cout << "---------------------------------------------------\n";

			current = current->next;  // Move to the next node
		}
	}

	void displayRaw(string orderId) {
		OrderDetails* current = head;

		if (!current) {
			cout << "\n===========================\n";
			cout << "No order available";
			cout << "\n===========================\n";
			return;
		}

		while (current) {
			if (current->orderId == orderId) {
				cout << "Finished product: " << current->productName << endl;
				cout << "=== material for order ID:" << current->orderId << " ===" << endl;
				cout << "---------------------------------------------------\n";
				cout << "Material used " << endl;
				for (int i = 0; i < current->rawQ; i++) {
					cout << endl;
					cout << current->raw[i];
					cout << "\n=================\n";
				}
				cout << "---------------------------------------------------\n";
			}
			current = current->next;
		}
	}
	void removeOrderDetails(string name, string orderId) {
		OrderDetails* current = head;
		OrderDetails* prev = nullptr;

		while (current) {
			if (current->name == name && current->orderId == orderId) {
				if (current == head) {
					head = current->next;
				}
				else {
					prev->next = current->next;
				}

				delete current;
				return;
			}

			prev = current;
			current = current->next;
		}
	}
	void removeAll()
	{
		while (head) {
			OrderDetails* current = head;
			head = head->next;
			delete[] current->raw;  // Delete the allocated array
			delete current;
		}
		tail = nullptr;
	}
	void displayOrderDetails() {
		OrderDetails* current = head;
		while (current != nullptr) {
			cout << "===============================================================================\n";
			cout << "------------------------------------------------\n";
			cout << "Customer Name: " << current->name << endl;
			cout << "Order ID: " << current->orderId << endl;
			cout << "Delivery Time: " << current->deliveryTime << endl;
			cout << "------------------------------------------------\n";
			cout << "------------------------------------------------\n";
			cout << "Conditional Terms: " << current->terms << endl;
			cout << "------------------------------------------------\n";
			cout << "------------------------------------------------\n";
			cout << "product Name: " << current->productName << endl;
			cout << "Production Cost: " << current->productionCost << endl;
			cout << "Raw Material Cost: " << current->rawCost << endl;
			cout << "Total Amount: " << current->totalAmount << endl;
			cout << "------------------------------------------------\n";
			cout << "================================================================================\n";

			current = current->next;
		}
	}
	void displayOrderDetails(string name, string orderId) {
		OrderDetails* current = head;
		while (current) {
			if (current->name == name && current->orderId == orderId) {
				cout << "------------------------------------------------\n";
				cout << "Customer Name: " << current->name << endl;
				cout << "Order ID: " << current->orderId << endl;
				cout << "Delivery Time: " << current->deliveryTime << endl;
				cout << "Conditional Terms: " << current->terms << endl;
				cout << "Production Cost: " << current->productionCost << endl;
				cout << "Raw Material Cost: " << current->rawCost << endl;
				cout << "Total Amount: " << current->totalAmount << endl;
				cout << "------------------------------------------------\n";
			}
			else
			{
				cout << "no order avaliable for this entry" << endl;
				waitForEnter();
			}
			current = current->next;
		}
	}
	bool check()
	{
		if (!head) {
			return true;
		}
		else
		{
			return false;
		}
	}
	OrderDetails getOrderDetailsFromList(string name, string orderId) {
		OrderDetails* current = head;
		while (current) {
			if (current->name == name && current->orderId == orderId) {
				return *current;
			}
			current = current->next;
		}
		// Return a default-constructed OrderDetails if not found
		return OrderDetails();
	}
	~OrderDetailsList() {
		while (head) {
			OrderDetails* current = head;
			head = head->next;
			delete[] current->raw;  // Delete the allocated array
			delete current;
		}
		tail = nullptr;
	}
};
struct HistoryNode {
	string name;
	string orderId;
	string deliveryTime;
	string terms;
	string productName;
	int productionCost;
	int rawCost;
	int totalAmount;
	string* raw;
	int rawQ;
	HistoryNode* next;

	HistoryNode() : next(nullptr), name(""), orderId(""), deliveryTime(""), terms(""), productionCost(0), rawCost(0), totalAmount(0), raw(nullptr), rawQ(0) {}

	// Copy constructor to copy data from OrderDetails to HistoryNode
	HistoryNode(const OrderDetails& orderDetails) {
		name = orderDetails.name;
		orderId = orderDetails.orderId;
		deliveryTime = orderDetails.deliveryTime;
		terms = orderDetails.terms;
		productName = orderDetails.productName;
		productionCost = orderDetails.productionCost;
		rawCost = orderDetails.rawCost;
		totalAmount = orderDetails.totalAmount;

		// Copy raw materials
		if (orderDetails.rawQ > 0) {
			raw = new string[orderDetails.rawQ];
			for (int i = 0; i < orderDetails.rawQ; i++) {
				raw[i] = orderDetails.raw[i];
			}
		}
		rawQ = orderDetails.rawQ;
	}
};
class OrderHistoryStack {
private:
	HistoryNode* top;

public:
	OrderHistoryStack() : top(nullptr) {}

	void push(const OrderDetails& orderDetails) {
		HistoryNode* newNode = new HistoryNode(orderDetails);
		newNode->next = top;
		top = newNode;
	}

	void pop() {
		if (isEmpty()) {
			cout << "History is empty." << endl;
			return;
		}

		HistoryNode* current = top;
		top = top->next;
		delete current;
	}

	bool isEmpty() const {
		return top == nullptr;
	}

	void displayHistory() const {
		if (isEmpty()) {
			cout << "History is empty." << endl;
			return;
		}

		HistoryNode* current = top;
		while (current) {
			cout << "================================================\n";
			// Display history details as needed
			cout << "Customer Name: " << current->name << endl;
			cout << "Order ID: " << current->orderId << endl;
			cout << "Delivery Time: " << current->deliveryTime << endl;
			cout << "Terms: " << current->terms << endl;
			cout << "Product Name: " << current->productName << endl;
			cout << "Production Cost: " << current->productionCost << endl;
			cout << "Raw Material Cost: " << current->rawCost << endl;
			cout << "Total Amount: " << current->totalAmount << endl;
			cout << "------------------------------------------------\n";
			// Display raw materials if available
			if (current->rawQ > 0) {
				cout << "Raw Materials:\n";
				for (int i = 0; i < current->rawQ; i++) {
					cout << current->raw[i] << endl;
				}
			}
			cout << "================================================\n";

			current = current->next;
		}
	}

	void clearHistory() {
		while (!isEmpty()) {
			pop();
		}
		cout << "History cleared." << endl;
	}
};

int main() {

	cout << "*********************************************" << endl;
	cout << "***************  Welcome to  ****************" << endl;
	cout << "********** Supply Chain Simulator ***********" << endl;
	cout << "*********************************************\n\n\n" << endl;
	cout << "*********************************************" << endl;
	cout << "********* Press any enter to start **********" << endl;
	cout << "*********************************************" << endl;
	waitForEnter();
	OrderQueue orderQueue;
	OrderDetailsList orderDetailsList;

	if (1) {
		string name, orderID, deliveryTime, terms;
		char priority;
		int entry = 0, n = 0, h = 0;
		OrderHistoryStack orderHistory;
		while (entry != 9) {
			clearScreen();
			cout << "******************** Hello ******************" << endl;
			cout << "Please choose from the options below " << endl;
			cout << "*********************************************" << endl;
			cout << "01 To Enter Order" << endl;
			cout << "02 Display Order" << endl;
			cout << "03 Display Detailed Order" << endl;
			cout << "04 Display raw Material" << endl;
			cout << "05 Display Order of given Order ID" << endl;
			cout << "06 Mark Order Complete" << endl;
			cout << "07 History" << endl;
			cout << "08 Clear Order List" << endl;
			cout << "Press 9 to exit" << endl;
			cout << "*********************************************" << endl;

			cin >> entry;

			switch (entry) {
			case 1:
			{
				clearScreen();
				while (n != 9)
				{
					clearScreen();
					cout << "----------------------------------\n";
					cout << "01 add profile details" << endl;
					cout << "02 add product name and raw materials" << endl;
					cout << "09 Exit" << endl;
					cout << "----------------------------------\n";

					cin >> n;
					switch (n) {
					case 1:
					{
						clearScreen();
						cout << "Enter Name" << endl;
						cin.ignore();  // Ignore any newline character in the buffer
						getline(cin, name);  // Use getline to read the entire line
						cout << "Enter OrderID" << endl;
						getline(cin, orderID);  // Use getline to read the entire line
						cout << "Enter Delivery Time" << endl;
						getline(cin, deliveryTime);  // Use getline to read the entire line
						cout << "Enter priority of order (1-3)" << endl;
						cin >> priority;
						cout << "Enter terms and conditions" << endl;
						cin.ignore();  // Ignore any newline character in the buffer
						getline(cin, terms);  // Use getline to read the entire line
						clearScreen();
						orderDetailsList.addOrderDetails(name, orderID, deliveryTime, terms);
						orderQueue.enqueue(orderID, priority);

						break;
					}
					case 2:
					{
						clearScreen();
						orderDetailsList.production();
						cout << "enter amount of raw materials" << endl;
						int amount = 0;
						cin >> amount;
						orderDetailsList.rawMaterial(amount);
						break;
					}
					case 9:
						break;
					default:
						clearScreen();
						cout << "wrong entry" << endl;
						break;
					}
				}
				n = 0;
				waitForEnter();
				break;
			}
			case 2:
			{
				clearScreen();
				if (orderQueue.check() && orderDetailsList.check())
				{
					orderQueue.getOrderStatistics();
					cout << "--------------------------------" << endl;
					cout << "No Order Available" << endl;
					cout << "--------------------------------" << endl;
					waitForEnter();
					break;
				}
				orderQueue.getOrderStatistics();
				cout << "Priority-based order list" << endl;
				orderQueue.displayOrders();
				waitForEnter();
				break;
			}
			case 3:
			{
				clearScreen();
				if (orderQueue.check() && orderDetailsList.check())
				{
					orderQueue.getOrderStatistics();
					cout << "--------------------------------" << endl;
					cout << "No Order Available" << endl;
					cout << "--------------------------------" << endl;
					waitForEnter();
					break;
				}
				cout << "Order detail" << endl;
				orderDetailsList.displayOrderDetails();
				waitForEnter();
				break;
			}
			case 4:
			{
				clearScreen();
				if (orderQueue.check() && orderDetailsList.check())
				{
					orderQueue.getOrderStatistics();
					cout << "--------------------------------" << endl;
					cout << "No Order Available" << endl;
					cout << "--------------------------------" << endl;
					waitForEnter();
					break;
				}
				orderDetailsList.displayRaw();
				waitForEnter();
				break;
			}
			case 5:
			{
				clearScreen();
				if (orderQueue.check() && orderDetailsList.check())
				{
					orderQueue.getOrderStatistics();
					cout << "--------------------------------" << endl;
					cout << "No Order Available" << endl;
					cout << "--------------------------------" << endl;
					waitForEnter();
					break;
				}				cout << "Enter Name" << endl;
				cin >> name;
				cout << "Enter Order ID" << endl;
				cin >> orderID;
				clearScreen();
				orderQueue.displaySingleOrder(orderID);
				orderDetailsList.displayOrderDetails(name, orderID);
				orderDetailsList.displayRaw(orderID);
				waitForEnter();
				break;
			}
			case 6:
			{
				clearScreen();
				if (orderQueue.check() && orderDetailsList.check())
				{
					orderQueue.getOrderStatistics();
					cout << "--------------------------------" << endl;
					cout << "No Order Available" << endl;
					cout << "--------------------------------" << endl;
					waitForEnter();
					break;
				}
				cout << "Enter Name" << endl;
				cin >> name;
				cout << "Enter Order ID" << endl;
				cin >> orderID;

				// Add the completed order details to the history
				OrderDetails completedOrder = orderDetailsList.getOrderDetailsFromList(name, orderID);
				orderHistory.push(completedOrder);

				orderQueue.dequeue(orderID);
				orderDetailsList.removeOrderDetails(name, orderID);
				waitForEnter();
				break;
			}
			case 7:
				clearScreen();
				while (h != 9)
				{
					clearScreen();

					cout << "------------------------------------\n";
					cout << "01 Display history" << endl;
					cout << "02 clear history" << endl;
					cout << "09 Exit" << endl;
					cout << "------------------------------------\n";
					cin >> h;
					clearScreen();
					switch (h)
					{
					case 1:
						if (orderHistory.isEmpty()) {
							cout << "History is empty." << endl;
							waitForEnter();
						}
						else {
							cout << "Order History:\n";
							orderHistory.displayHistory();
							waitForEnter();

						}
						break;
					case 2:
						orderHistory.clearHistory();
						break;
					default:
						break;
					}

				}h = 0;
				waitForEnter();
				break;
			case 8:
			{
				clearScreen();
				if (orderQueue.check() && orderDetailsList.check())
				{
					cout << "------------------------------------\n";
					cout << "No Order Available" << endl;
					cout << "------------------------------------\n";
					waitForEnter();
					break;
				}
				cout << "------------------------------------\n";
				cout << "List Reset successfully" << endl;
				cout << "------------------------------------\n";
				waitForEnter();
				orderDetailsList.removeAll();
				orderQueue.dequeueAll();
				break;
			}
			case 9:
				break;
			default:
				clearScreen();
				cout << "Wrong entry. Try again." << endl;
				break;
			}

		}
	}

	system("pause");
	return 0;
}
