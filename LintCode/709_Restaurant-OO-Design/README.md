709. Restaurant OO Design
中文English
No food delivery.

No table reservation

The table has different size

The restaurant will choose the smallest table which fit the numbers of people(For example, if the party has 3 people, the restaurant would assign a 4-people table instead of a 10-people table)

Implement Restaurant Class

Everytime after calling findTable, takeOrder, checkOut, we will userestaurantDescription to test the program.

Example
Example 1

Input:
meal(10.0)
meal(13.0)
meal(17.0)
table(4)
table(4)
table(10)
party(3)
party(7)
party(4)
party(6)
party(1)
order(1)
order(2, 3)
findTable(1)
findTable(3)
findTable(4)
takeOrder(1, 1)
takeOrder(3, 2)
checkOut(3)
findTable(4)

Output:
Table: 0, table size: 4, isAvailable: false. No current order for this table.
Table: 1, table size: 4, isAvailable: true. No current order for this table.
Table: 2, table size: 10, isAvailable: true. No current order for this table.
*****************************************

Table: 0, table size: 4, isAvailable: false. No current order for this table.
Table: 1, table size: 4, isAvailable: false. No current order for this table.
Table: 2, table size: 10, isAvailable: true. No current order for this table.
*****************************************

Table: 0, table size: 4, isAvailable: false. No current order for this table.
Table: 1, table size: 4, isAvailable: false. No current order for this table.
Table: 2, table size: 10, isAvailable: false. No current order for this table.
*****************************************

Table: 0, table size: 4, isAvailable: false. Order price: 10.0.
Table: 1, table size: 4, isAvailable: false. No current order for this table.
Table: 2, table size: 10, isAvailable: false. No current order for this table.
*****************************************

Table: 0, table size: 4, isAvailable: false. Order price: 10.0.
Table: 1, table size: 4, isAvailable: false. No current order for this table.
Table: 2, table size: 10, isAvailable: false. Order price: 30.0.
*****************************************

Table: 0, table size: 4, isAvailable: false. Order price: 10.0.
Table: 1, table size: 4, isAvailable: false. No current order for this table.
Table: 2, table size: 10, isAvailable: true. No current order for this table.
*****************************************

Table: 0, table size: 4, isAvailable: false. Order price: 10.0.
Table: 1, table size: 4, isAvailable: false. No current order for this table.
Table: 2, table size: 10, isAvailable: false. No current order for this table.
*****************************************

Explanation:
meal(x) means we create a meal, whose price is x
Example 2

Input:
meal(12.0)
table(4)
table(4)
table(10)
party(13)
findTable(1)

Output:
Table: 0, table size: 4, isAvailable: true. No current order for this table.
Table: 1, table size: 4, isAvailable: true. No current order for this table.
Table: 2, table size: 10, isAvailable: true. No current order for this table.
*****************************************
在线评测地址: http://www.lintcode.com/problem/restaurant-oo-design/


class Meal {
private:
	float price;
	
public:
	Meal(float price) {
		this->price = price;
	}
	
	float getPrice() {
		return this->price;
	}
};

class Order {
private:
	vector<Meal*> *meals;
	
public:
	Order() {
		meals =new vector<Meal*>;
	}
	
	vector<Meal*>* getMeals() {
		return meals;
	}
	
	Order* mergeOrder(Order *order) {
		Order* ans = new Order;
		for(Meal* &meal : *(this->getMeals())) {
			ans->meals->push_back(meal);
		}
		if(order != NULL) {
			for(Meal* &meal : *(order->getMeals())) {
				ans->meals->push_back(meal);
			}
		}
		return ans;
	}
	
	float getBill() {
		float bill = 0;
		for(int i = 0; i < meals->size(); i++) {
			bill += (*meals)[i]->getPrice();
		}
		return bill;
	}
};

class Party {
private:
		int size;
	
public:
	Party(int size) {
		this->size = size;
	}
	
	int getSize() {
		return this->size;
	}
};

class Table {
private:
	int capacity;
	bool available;
	Order *order;
	
public:
	
	Table(int capacity) {
		this->capacity = capacity;
		available =true;
		order = NULL;
	}
	
	int getCapacity() {
		return this->capacity;
	}
	
	bool isAvailable() {
		return this->available;
	}
	
	void markAvailable() {
		this->available = true;
	}
	
	void markUnavailable() {
		this->available = false;
	}
	
	Order * getCurrentOrder() {
		return this->order;
	}
	
	void setOrder(Order *o) {
		if(order == NULL) {
			this->order = o;
		}
		else {
			if( o != NULL) {
				this->order = this->order->mergeOrder(o);
			}
			else {
				this->order = o;
			}
		}
	}
};

class Restaurant {
private:
	vector<Table *> *tables;
	vector<Meal *> *menu;
	
public:
	Restaurant() {
		// Write your code here
	}
	
	void findTable(Party *p) {
		// Write your code here
	}
	
	void takeOrder(Table *t,Order *o) {
		// Write your code here
	}
	
	float checkOut(Table *t) {
		// Write your code here
	}
	
	vector<Meal *>* getMenu() {
		return menu;
	}
	
	void addTable(Table *t) {
		// Write your code here
	}
	
	string to_string(int x) {
		string ans;
		stringstream st;
		st << x;
		st >> ans;
		return ans;
	}
	
	string restaurantDescription() {
        // Keep them, don't modify.
		string description = "";
		for(int i = 0; i < tables->size(); i++) {
			Table* table = (*tables)[i];
			description += "Table: " + to_string(i) + ", table size: " 
			+ to_string(table->getCapacity()) + ", isAvailable: " +(table->isAvailable()?"true":"false") + ".";
			if(table->getCurrentOrder() == NULL)
				description += " No current order for this table";
			else 
			{
				description +=  " Order price: " + to_string(table->getCurrentOrder()->getBill())+".0";
			}
			description += ".\n";
		}
		description += "*****************************************\n";
		return description;
	}
	
};