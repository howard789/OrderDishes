#ifndef Client_cpp
#define Client_cpp
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

class Client
{
public:
	int customerId;
	string name;
	int age = 0;
	string address;
	int getAge() {
		return this->age;
	}
	int getCustomerId() {
		return this->customerId;
	}
	string getName() {
		return this->name;
	}

	string getAddress() {
		return this->address;
	}

	void setName(string name) {
		this->name = name;
	}

	void setAge(int age) {
		this->age = age;
	}

	void setAddress(string address) {
		this->address = address;
	}

	void setCustomerId(int customerId) {
		this->customerId = customerId;
	}
	void toString() {
		cout << this->name << "," << this->age << "," << this->address << endl;
	}

	//重载操作符,比较是否是同一人 reload +=:compare name
	bool operator += (string cname) {
		if (cname == this->name) {
			return true;
		}
		else {
			return false;
		}

	}


	static bool existClient(string customerName, vector<Client> *totalClient)
	{
		for (vector<Client> ::iterator ite = totalClient->begin(); ite != totalClient->end(); ite++)
		{
			{
				//如果两个字符串equal，就返回true
				if (ite->getName()==customerName) {
					return true;
				}
			}
			return false;
		}
	}

	static Client *getExistClient(string customerName, vector<Client> *totalClient)
	{
		for (vector<Client> :: iterator ite = totalClient->begin(); ite != totalClient->end(); ite++)
		{
			if (customerName == ite->getName())
			{
				return &(*ite);
			}
		}
	}
};

#endif 

