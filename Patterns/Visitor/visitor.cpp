#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Cat;
class Dog;
class Mouse;

class Animal
{
    public:
    class IVisitor 
    {
    public:
        virtual ~IVisitor()
        {
        }
        
        virtual void Visit(Cat* animal) = 0; 
        virtual void Visit(Dog* animal) = 0; 
        virtual void Visit(Mouse* animal) = 0;
    };
    private:
        string name;
    public:
        Animal(const string& theName)
            :name{theName}
    {
    }

    virtual ~Animal()
    {
    }

    const string& GetName()const
    {
        return name;
    }

    virtual string Introduce()const = 0;
    virtual void Accept(IVisitor* visitor) = 0;
};

class Cat : public Animal
{
    public:
        Cat(const string& theName)
            :Animal{theName}
    {
    }

    string Introduce()const override
    {
        return "我是一只猫，我的名字叫\"" + GetName() + "\"。";
    }
        
    void Accept(IVisitor* visitor) override
    {
        visitor->Visit(this);
    }
};

class Dog : public Animal
{
    public:
        Dog(const string& theName)
            :Animal{theName}
    {
    }

    string Introduce()const override
    {
        return "我是一只狗，我的名字叫\"" + GetName() + "\"。";
    }
        
    void Accept(IVisitor* visitor) override
    {
        visitor->Visit(this);
    }
};

class Mouse : public Animal
{
public:
    Mouse(const string& theName)
        :Animal{theName}
    {
    }

    string Introduce()const override
    {
        return "我是一只老鼠，我的名字叫\"" + GetName() + "\"。";
    }
        
    void Accept(IVisitor* visitor) override
    {
        visitor->Visit(this);
    }
};

class OutputVisitor : public Animal::IVisitor {
public:
    void Visit(class Cat *obj) override {
        cout << obj->Introduce() << endl;
    }
 
    void Visit(class Dog *obj) override {
        cout << obj->Introduce() << endl;
    }

    void Visit(class Mouse *obj) override {
        cout << obj->Introduce() << endl;
    }
};

int main()
{
    auto tom = make_shared<Cat>("Tom");
    auto jerry = make_shared<Mouse>("Jerry");
    auto spike = make_shared<Dog>("Spike");
    auto butch = make_shared<Cat>("Butch");
    auto lightning = make_shared<Cat>("Lightning");
    vector<shared_ptr<Animal>> friends{ tom, jerry, spike, butch, lightning };

    OutputVisitor visitor;
    for (auto animal : friends)
    {
        animal->Accept(&visitor);
//        cout << animal->Introduce() << endl;
    }
    
    return 0;
}
