/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//reference
//https://blog.csdn.net/My_heart_/article/details/62237613
//组合模式Composite Pattern
 
//抽象的部件类描述将来所有部件共有的行为
class Component 
{
protected:
	string m_strComponent;
public :
	Component(string _name)
		:m_strComponent(_name)
	{}
	virtual ~Component()
	{}
	virtual void Operation() = 0;
	virtual void Add(Component* com) = 0;
	virtual void Remove(Component* com) = 0;
	virtual Component* Getchild(int index) = 0;
	virtual  string  getName()
	{
		return m_strComponent;
	}
	virtual void Print() = 0;
};
 
class Leaf : public Component //树叶结构
{
public:
	Leaf(string name)
		:Component(name)
	{}
	void Operation()
	{
		cout <<"name : " << m_strComponent << endl;
	}
 
	void Add(Component* com)
	{}
	void Remove(Component* com)
	{}
	Component *GetChild(int index)
	{
		return NULL;
	}
	void Print()
	{}
};
 
class Composite : public Component  //树枝结构
{
private:
	vector<Component *>  m_vecComp;
public:
	Composite(string name)
		:Component(name)
	{}
	~Composite()
	{
		vector<Component*>::iterator it = m_vecComp.begin();
		while (it != m_vecComp.end())
		{
			if (*it != NULL)
			{
				cout << "---delete" << (*it)->getName() + "---" << endl;
				delete *it;
				*it = NULL;
			}
			m_vecComp.erase(it);
			it = m_vecComp.begin();
		}
	}
	void Operation()
	{
		cout << "我是 " << m_strComponent << endl;
	}
	void Add(Component* com)
	{
		m_vecComp.push_back(com);
	}
 
	void Remove(Component* com)
	{
		for (vector<Component*>::iterator it = m_vecComp.begin(); it != m_vecComp.end();++it)
		{
			if ((*it)->getName() == com->getName())
			{
				if (*it != NULL)
				{
					delete *it;
					*it = NULL;
				}
				m_vecComp.erase(it);
				break;
			}
		}
	}
	Component*  Getchild(int index)
	{
		if ((size_t)index > m_vecComp.size())
			return NULL;
		return m_vecComp[index -1];
	}
 
	void Print()
	{
		for (vector<Component*>::iterator it = m_vecComp.begin(); it != m_vecComp.end(); ++it)
		{
			cout <<(*it)->getName() << endl;
		}
	}
};


//客户端
int test_Composite() //组合模式
{
	Component* pNode = new Composite("北京总部 ");
	Component * pNodeHr = new Composite("北京人事部");
	Component * pNode1 = new Composite("上海分公司");
	Component * pNode2 = new Composite("西安分公司");
	Component * pNode3 = new Composite("成都分公司");
	pNode->Add(pNodeHr);
	pNode->Add(pNode1);
	pNode->Add(pNode2);
	pNode->Add(pNode3);
	pNode->Print();
 
	Component* pNode1_Hr = new Composite("上海人事部 ");
	Component* pNode1_zj = new Composite("上海质检部 ");
	Component* pNode1_kf = new Composite("上海开发部 ");
	Component* pNode1_xs = new Composite("上海销售部 ");
	pNode1->Add(pNode1_Hr);
	pNode1->Add(pNode1_kf);
	pNode1->Add(pNode1_xs);
	pNode1->Add(pNode1_zj);
	pNode1->Print();
	//关闭上海质检部
	pNode1->Remove(pNode1_zj);
	if (pNode != NULL)
	{
		delete pNode;
		pNode = NULL;
	}

	return 0;
}

int main()
{
    test_Composite();

    return 0;
}
