class CoffeePack
{
private:
    int neededMilk;
	int neededSugar;

public:

	CoffeePack(int neededMilk, int neededSugar)
	{
		this->neededMilk = neededMilk;
		this->neededSugar = neededSugar;
	}

	int getNeededMilk()
	{
		return neededMilk;
	}

	int getNeededSugar()
	{
		return neededSugar;
	}
};

class Coffee
{
public:
	virtual double getCost() = 0;
	virtual string getIngredients() = 0;
};

class SimpleCoffee :public Coffee
{
public:

	double getCost()
	{
		return 2;
	}

	string getIngredients()
	{
		return "Plain Coffee";
	}
};

class CoffeeDecorator :public Coffee
{
protected:
	Coffee *decoratedCoffee;

public:

	CoffeeDecorator(Coffee *coffee)
	{
		this->decoratedCoffee = coffee;
	}

	double getCost()
	{
		return decoratedCoffee->getCost();
	}

	string getIngredients()
	{
		return decoratedCoffee->getIngredients();
	}
};

class WithMilk :public CoffeeDecorator
{
public:

	WithMilk(Coffee *coffee):CoffeeDecorator(coffee){}

	double getCost()
	{
		return CoffeeDecorator::getCost() + 0.5;
	}

	string getIngredients()
	{
		return CoffeeDecorator::getIngredients() + ", Milk";
	}
};

class WithSugar :public CoffeeDecorator
{
public:

	WithSugar(Coffee *coffee):CoffeeDecorator(coffee){}

	double getCost()
	{
		return CoffeeDecorator::getCost() + 0.5;
	}

	string getIngredients()
	{
		return CoffeeDecorator::getIngredients() + ", Sugar";
	}
};

class CoffeeMaker
{
public:
	Coffee *makeCoffee(CoffeePack *pack)
	{
		Coffee *coffee = new SimpleCoffee();

		for (int i = 0; i < pack->getNeededMilk(); i++)
		{
			coffee = new WithMilk(coffee);
		}

		for (int i = 0; i < pack->getNeededSugar(); i++)
		{
			coffee = new WithSugar(coffee);
		}
		return coffee;
	}
};