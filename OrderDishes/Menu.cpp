
#include "Menu.h"
#include <cstdlib>
#include <iostream>
using namespace std;

Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::printMenu() {
	cout 
		<< "ID:" << this->getId() 
		<< ",Name:" << this->getName() 
	    << ",Price:" << this->getPrice()
	    << ",Weight:" << this->getWeight() << endl;
}


Menu::Menu(int id,string name, int price, double weight) {
	this->id = id;
	this->name = name;
	this->price = price;
	this->weight = weight;
	cout << "new dish 创建新菜:" <<id << ":"<<name << ",price 金额:" << price << ", weight 重量:" << weight << endl;

}

string Menu::getName() {
	return this->name;
}

int Menu::getPrice() {
	return this->price;
}


int Menu::getId() {
	return this->id;
}

double Menu::getWeight() {
	return this->weight;
};

void Menu::setPrice(int price) {
	this->price = price;
};

void Menu::setId(int id) {
	this->id = id;
};



void Menu::setWeight(double weight) {
	this->weight = weight;
};


void Menu::setName(string name) {
	this->name = name;
};



