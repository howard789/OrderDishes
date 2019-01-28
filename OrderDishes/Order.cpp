#include <map>
#include <ctime>
#include <string>
#include "Client.cpp"
using namespace std;

struct OrderDetail
{
public:
	map<string, int> order;
	Client client;
	double totalWeight;
	int totalPrice;
	tm time;


	OrderDetail() {};

	OrderDetail(map<string, int> order,Client client,double totalWeight,int totalPrice,tm time) {
		this->order = order;
		this->client = client;
		this->totalPrice = totalPrice;
		this->totalWeight = totalWeight;
		this->time = time;
	}


	~OrderDetail() {

	}

	






};