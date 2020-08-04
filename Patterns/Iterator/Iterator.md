#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Iterator { // 迭代器抽象类
public:
    virtual string First() = 0;
    virtual string Next() = 0;
    virtual bool IsDone() = 0;
    virtual string CurrentItem() = 0;
    virtual ~Iterator(){}
};

class Aggregate { // 聚集抽象类
public:
    virtual Iterator* CreateIterator() = 0;
    virtual void Push(string s) = 0;
    virtual string Pop(int index) = 0;
    virtual int Count() = 0;
};

class ConcreteIterator : public Iterator { // 具体迭代器类
private:
    Aggregate* aggregate;
    int index;
public:
    ConcreteIterator(Aggregate* a) {
        index = 0;
        aggregate = a;
    }
    string First() { return aggregate->Pop(0); }
    string Next() { 
        string str;
        index++;
        if (index < aggregate->Count()) str = aggregate->Pop(index);
        return str;
    }

    bool IsDone() { return (index >= aggregate->Count()); }
    string CurrentItem() { return aggregate->Pop(index); }
};

class ConcreteAggregate : public Aggregate {
private:
    vector<string> items;
    Iterator* iterator;
public:
    ConcreteAggregate() {
        iterator = NULL;
        items.clear();
    }
    ~ConcreteAggregate() {
        if (iterator){
            delete iterator;
            iterator = NULL;
        }
    }
    Iterator* CreateIterator() {
        if (iterator == NULL) iterator = new ConcreteIterator(this);
        return iterator;
    }
    int Count() { return items.size(); }
    void Push(string s) { items.push_back(s); }
    string Pop(int index) {
        string str;
        if (index < Count()) str = items[index];
        return str;
    }
};

int main() {
    ConcreteAggregate* ca = new ConcreteAggregate();
    ca->Push("Hello");
    ca->Push("World");

    Iterator* it = new ConcreteIterator(ca);
    while(!it->IsDone()) {
        cout << it->CurrentItem() << endl; 
        it->Next();
    }

    delete it;
    delete ca;
    return 0;
}