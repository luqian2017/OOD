/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
using namespace std;

class Person
{
public:
	virtual void CreateHead() = 0;
	virtual void CreateHand() = 0;
	virtual void CreateBody() = 0;
	virtual void CreateFoot() = 0;
};

class ThinPerson : public Person
{
public:
	virtual void CreateHead()
	{
		cout << "thin head" << endl;
	}
	virtual void CreateHand()
	{
		cout << "thin hand" << endl;
	}
	virtual void CreateBody()
	{
		cout << "thin body" << endl;
	}
	virtual void CreateFoot()
	{
		cout << "thin foot" << endl;
	}
};

class ThickPerson : public Person
{
public:
	virtual void CreateHead()
	{
		cout << "ThickPerson head" << endl;
	}
	virtual void CreateHand()
	{
		cout << "ThickPerson hand" << endl;
	}
	virtual void CreateBody()
	{
		cout << "ThickPerson body" << endl;
	}
	virtual void CreateFoot()
	{
		cout<< "ThickPerson foot" <<endl;
	}
};

//指挥者类
class Direct
{
public:
	Direct(Person* temp) { p = temp;}
	void Create()
	{
		p->CreateHead();
		p->CreateBody();
		p->CreateHand();
		p->CreateFoot();
	}
private:
	Person* p;
};

//客户端代码：
int main()
{
    Person *p = new ThickPerson();
	Direct *d = new Direct(p);
	d->Create();
	delete d;
	delete p;
	return 0;
}