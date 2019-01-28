#include "StatisticResult.h"
#include <iostream>
using namespace std;


StatisticResult::StatisticResult()
{
}


StatisticResult::~StatisticResult()
{
	cout<<"delete "<<this->getName()<<endl;
}


string StatisticResult::getName() {
	return this->name;
};
int StatisticResult::getPrice() {
	return this->price;
};
double StatisticResult::getWeight() {
	return this->weight;
};
void StatisticResult::setName(string name) {
	this->name = name;
};
void StatisticResult::setPrice(int price) {
	this->price = price;
};
void StatisticResult::setWeight(double weight) {
	this->weight = weight;
};