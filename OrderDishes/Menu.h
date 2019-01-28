#pragma once
#include <string>
using namespace std;
class Menu
{
public:
	Menu();
	Menu(int id, string name, int price, double weight);
	~Menu();
	int getPrice();
	double getWeight();
	string getName();
	int getId();
	virtual void setName(string name);
	virtual void setPrice(int price);
	virtual void setWeight(double weight);
	virtual void printMenu();
	virtual void setId(int id);
	int id;
	string name;
	int price;
	double weight;
};


