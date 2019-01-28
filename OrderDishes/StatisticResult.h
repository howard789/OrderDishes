#pragma once
#include <string>
using namespace std;

struct StatisticResult
{
public:
	string name;
	int price;
	double weight;
	StatisticResult();
	virtual ~StatisticResult();

	string getName();
	int getPrice();
	double getWeight();
	void setName(string name);
	void setPrice(int price);
	void setWeight(double weight);



};

