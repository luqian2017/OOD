#include <string>
#include <iostream>
using namespace std;
#include <list>

//pure virtual class, like JAVA's interface
class Observer  
{
public:
	Observer() {}
	virtual ~Observer() {}
	virtual void Update() {} 
};

class Blog  
{
public:
	Blog() {}
	virtual ~Blog() {}
	void Attach(Observer *observer) { m_observers.push_back(observer); }
	void Remove(Observer *observer) { m_observers.remove(observer); }
	void Notify()
	{
		list<Observer*>::iterator iter = m_observers.begin();
		for(; iter != m_observers.end(); iter++)
			(*iter)->Update();
	}
	virtual void SetStatus(string s) { m_status = s; }
	virtual string GetStatus() { return m_status; }
private:
	list<Observer* > m_observers;
protected:
	string m_status;
};


class BlogCSDN : public Blog
{
private:
	string m_name;
public:
	BlogCSDN(string name): m_name(name) {}
	~BlogCSDN() {}
	void SetStatus(string s) { m_status = "CSDN Notice : " + m_name + s; }
	string GetStatus() { return m_status; }
};

class ObserverBlog : public Observer   
{
private:
	string m_name;
	Blog *m_blog;
public: 
	ObserverBlog(string name,Blog *blog): m_name(name), m_blog(blog) {}
	~ObserverBlog() {}
	void Update()
	{ 
		string status = m_blog->GetStatus();
		cout<<m_name<<"-------"<<status<<endl;
	}
};

int main()
{
	Blog *blog = new BlogCSDN("roufoo");
	Observer *observer1 = new ObserverBlog("Tom", blog);
	Observer *observer2 = new ObserverBlog("Jerry", blog);
	blog->Attach(observer1);
	blog->Attach(observer2);
	blog->SetStatus("roufoo's new post published"");
	blog->Notify();
	delete blog; 
	delete observer1;
	delete observer2;
	return 0;
}
