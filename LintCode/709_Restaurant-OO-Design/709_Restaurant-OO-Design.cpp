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
		tables = new vector<Table *>;
		menu = new vector<Meal *>;
	}
	
	void findTable(Party *p) {
		for(Table* &t: *tables) {
			if(t->isAvailable()) {
				if(t->getCapacity() >= p->getSize()) {
					t->markUnavailable();
					return;
				}
			}
		}
	}
	
	void takeOrder(Table *t,Order *o) {
		t->setOrder(o);
	}
	
	float checkOut(Table *t) {
		float bill = 0;
		if(t->getCurrentOrder() != NULL) {
			bill = t->getCurrentOrder()->getBill();
		}
		t->markAvailable();
		t->setOrder(NULL);
		return bill;
	}
	
	vector<Meal *>* getMenu() {
		return menu;
	}
	
	void addTable(Table *t) {
		vector<Table *>::iterator it;
		for(it = tables->begin(); it!=tables->end(); it++) {
			if((*it)->getCapacity() > t->getCapacity()) {
				tables->insert(it,t);
				return;
			}
		}
		tables->push_back(t);
	}
	
	string to_string(int x) {
		string ans;
		stringstream st;
		st << x;
		st >> ans;
		return ans;
	}
	
	string restaurantDescription() {
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