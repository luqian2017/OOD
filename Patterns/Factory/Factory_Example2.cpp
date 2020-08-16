#include <iostream>
using namespace std;
enum SOAPTYPE {SFJ,XSL,NAS};
 
class soapBase
{
	public:
	virtual ~soapBase(){};
	virtual void show() = 0;
};
 
class SFJSoap:public soapBase
{
	public:
	void show() {cout<<"SFJ Soap!"<<endl;}
};
 
class XSLSoap:public soapBase
{
	public:
	void show() {cout<<"XSL Soap!"<<endl;}
};
 
class NASSoap:public soapBase
{
	public:
	void show() {cout<<"NAS Soap!"<<endl;}
};
 
class FactoryBase
{
	public:
	virtual soapBase * creatSoap() = 0;
};
 
class SFJFactory:public FactoryBase
{
	public:
	soapBase * creatSoap()
	{
		return new SFJSoap();
	}
};
 
class XSLFactory:public FactoryBase
{
	public:
	soapBase * creatSoap()
	{
		return new XSLSoap();
	}
};
 
class NASFactory:public FactoryBase
{
	public:
	soapBase * creatSoap()
	{
		return new NASSoap();
	}
};
 
 
 
int main()
{
	SFJFactory factory1;
	soapBase* pSoap1 = factory1.creatSoap();
	pSoap1->show();
	XSLFactory factory2;
	soapBase* pSoap2 = factory2.creatSoap();
	pSoap2->show();
	NASFactory factory3;
	soapBase* pSoap3 = factory3.creatSoap();
	pSoap3->show();
	delete pSoap1;
	delete pSoap2;
	delete pSoap3;
	return 0;
}