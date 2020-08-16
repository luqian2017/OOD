#include <iostream>
using namespace std;
enum SOAPTYPE {SFJ,XSL,NAS};
enum TOOTHTYPE {HR,ZH};
 
class SoapBase
{
	public:
	virtual ~SoapBase(){};
	virtual void show() = 0;
};
 
class SFJSoap:public SoapBase
{
	public:
	void show() {cout<<"SFJ Soap!"<<endl;}
};
 
class NASSoap:public SoapBase
{
	public:
	void show() {cout<<"NAS Soap!"<<endl;}
};
 
class ToothBase
{
	public:
	virtual ~ToothBase(){};
	virtual void show() = 0;
};
 
class HRTooth:public ToothBase
{
	public:
	void show() {cout<<"Hei ren Toothpaste!"<<endl;}
};
 
class ChinaTooth:public ToothBase
{
	public:
	void show() {cout<<"China Toothpaste!"<<endl;}
};
 
class FactoryBase
{
	public:
	virtual SoapBase * creatSoap() = 0;
	virtual ToothBase * creatToothpaste() = 0;
};
 
class FactoryA :public FactoryBase
{
	public:
	SoapBase * creatSoap()
	{
		return new SFJSoap();
	}
	
	ToothBase * creatToothpaste()
	{
		return new HRTooth();
	}
};
 
class FactoryB :public FactoryBase
{
	public:
	SoapBase * creatSoap()
	{
		return new NASSoap();
	}
	
	ToothBase * creatToothpaste()
	{
		return new ChinaTooth();
	}
};
 
 
int main()
{
	FactoryA factory1;
	FactoryB factory2;
	SoapBase *pSoap1 = NULL;
	ToothBase *pToothpaste1 = NULL;
	pSoap1 = factory1.creatSoap();
	pToothpaste1 = factory1.creatToothpaste();
	pSoap1->show();
	pToothpaste1->show();
	
	SoapBase *pSoap2 = NULL;
	ToothBase *pToothpaste2 = NULL;
	pSoap2 = factory2.creatSoap();
	pToothpaste2 = factory2.creatToothpaste();
	pSoap2->show();
	pToothpaste2->show();
	
	delete pSoap1;
	delete pSoap2;
	delete pToothpaste1;
	delete pToothpaste2;
	
	return 0;
}