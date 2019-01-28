#include "pch.cpp"
#include <string>
#include <cstdlib>
#include <map>
#include <ctime>
#include <vector>
#include <set>
#include <iostream>

#if 0

THIS is my first C++ project 
using skills include
regex,vector,map,set,time.h...etc
environment centOS(linux)

我的第一个C++的项目，用到的技能包括
正则表达式校验（int，double，数字是否在允许的输入范围）
vector （取值，存值）
map（取值，存值）
set（取值，存值）
time.h(time_t的日期时间操作)
字符串的操作（string转成double，int，char）
class 和 struct的一般用法（例如重载操作运算符）
标准库的一些用法，例如输入输出等等
操作环境是 centOS(linux)
#endif

using namespace std;

map<string, Menu> initMenu(map<string, Menu> menu);
map<string, int> startOrder(map<string, int> order, map<string, Menu> menu);
Client *setClient(Client *currentClient, vector<Client> *totalClient);
int checkOut(map<string, int> order, Client *client, map<string, Menu> menu, vector<OrderDetail> *totalOrders);
Menu *getMenuByName(string name, map<string, Menu>menu);
void statistic(vector<OrderDetail> *totalOrders, map<string, Menu> * const &menuAddr);
Client *addNewClient(vector<Client> *totalClient);

int main()
{

	Client *currentClient;
	vector<Client> *totalClient = new vector<Client>();
	map<string, Menu> menu;
	vector<OrderDetail> *totalOrders = new vector<OrderDetail>();
	map<string, int> order;
	while (true)
	{
#if 1
		std::cout << "******current Situation当前状态*************************************" << endl;
		std::cout << "menu size=" << menu.size() << endl;
		std::cout << "order size=" << order.size() << endl;
		std::cout << "totalOrderNum =" << totalOrders->size() << endl;
		std::cout << "totalClient =" << totalClient->size() << endl;
#endif
		std::cout << "********************************************************************" << endl;
		std::cout << "Welcome 欢迎进入点餐系统" << endl;
		std::cout << "1.Create a menu 创建菜单" << endl;
		std::cout << "2.Enter Client Info 输入客户信息" << endl;
		std::cout << "3.Order Dishes 点餐" << endl;
		std::cout << "4.Check out 结算" << endl;
		std::cout << "5.Statistic 统计" << endl;
		std::cout << "Please choose(key in a number) 请输入您的选项" << endl;

		string input;
		cin >> input;
		RegUtil req;
		int choice = RegUtil::returnIntIfValid(input, 1, 5);
		if (choice == 1) {
			menu = initMenu(menu);
		}
		else if (choice == 2) {
			currentClient = setClient(currentClient, totalClient);
		}
		else if (choice == 3) {
			order = startOrder(order, menu);
		}
		else if (choice == 4) {
			checkOut(order, currentClient, menu, totalOrders);
		}
		else if (choice == 5) {
			statistic(totalOrders, &menu);
		}
	}
	return 0;
}



void statistic(vector<OrderDetail> *totalOrders, map<string, Menu> * const &menuAddr) {
	map<string, Menu> *menu = menuAddr;
	bool exit = false;
	while (!exit)
	{
		std::cout << "1.group by dish name 依照所选菜名统计" << endl;
		std::cout << "2.group by client 依照所选用户统计" << endl;
		std::cout << "3.group by date依照所选日期统计" << endl;
		std::cout << "4.exit 退出模块" << endl;
		std::cout << "please choose 请输入您的选项：" << endl;
		string input;
		cin >> input;
		int choice = RegUtil::returnIntIfValid(input, 1, 4);
		if (choice) {
			StatisticResult *sta = new StatisticResult();
			if (choice == 1) {
				int orderNum = 0;
				int totalPrice = 0;
				double totalWeight = 0;

				std::cout << "key in dish name请输入菜名：" << endl;
				string dishName;
				cin >> dishName;

				Menu *menuP = getMenuByName(dishName, *menu);
				int stdPrice = menuP->price;
				double stdWeight = menuP->weight;
				for (int i = 0; i < (totalOrders->size()); i++) {
					cout << "totalOrders->size=" << totalOrders->size() << endl;
					map<string, int> order = (*totalOrders)[i].order;
					map<string, int> ::iterator orderIte;
					for (orderIte = order.begin(); orderIte != order.end(); orderIte++) {
						if (orderIte->first == dishName) {
							orderNum += orderIte->second;
							totalPrice += (stdPrice*(orderIte->second));
							totalWeight += (stdWeight*(orderIte->second));
						}
					}
				}
				cout << "complete 依照菜名统计完成" << endl;
				cout << "total order总份数:" << orderNum << ", total amount总金额:" << totalPrice << ", total weight总重量:" << totalWeight << endl;

			}
			else if (choice == 2) {
				int orderNum = 0;
				int totalPrice = 0;
				double totalWeight = 0;


				cout << "please key in client name 请输入用户：" << endl;
				string userName;
				cin >> userName;

				for (int i = 0; i < totalOrders->size(); i++) {
					Client cli = (*totalOrders)[i].client;

					if (cli.getName() == userName) {
						orderNum++;
						totalPrice += (*totalOrders)[i].totalPrice;
						totalWeight += (*totalOrders)[i].totalWeight;
					}
				}
				cout << "complete 依照菜名统计完成" << endl;
				cout << "total order总份数:" << orderNum << ", total amount总金额:" << totalPrice << ", total weight总重量:" << totalWeight << endl;
			
			}
			else if (choice == 3) {
				int orderNum = 0;
				int totalPrice = 0;
				double totalWeight = 0;

				string yearStr;
				string monthStr;
				string dateStr;
				cout << "key in year 请输入查询年：" << endl;
				cin >> yearStr;
				cout << "key in month 请输入查询月：" << endl;
				cin >> monthStr;
				cout << "key in date 请输入查询日：" << endl;
				cin >> dateStr;
				int year = RegUtil::returnIntIfValid(yearStr, 2019, 2300);
				int month = RegUtil::returnIntIfValid(monthStr, 1, 12);
				int date = RegUtil::returnIntIfValid(dateStr, 1, 31);
				if (year&&month&&date)
				{
					for (int i = 0; i < totalOrders->size(); i++) {
						tm orderTm = (*totalOrders)[i].time;
						MyTime mytime;
						int orderYear = mytime.getYear(orderTm);
						int orderMonth = mytime.getMonth(orderTm);
						int orderDate = mytime.getDate(orderTm);
						if (year == orderYear && month == orderMonth && date == orderDate) {
							orderNum++;
							totalPrice += (*totalOrders)[i].totalPrice;
							totalWeight += (*totalOrders)[i].totalWeight;
						}
					}
					cout << "complete 依照菜名统计完成" << endl;
					cout << "total order总份数:" << orderNum << ", total amount总金额:" << totalPrice << ", total weight总重量:" << totalWeight << endl;

				}
				else {
					cout << "illegal input 输入格式不合法！" << endl;
				}
			}
			else if (choice == 4) {
				exit = true;
			}
		}
	}

}



Client *setClient(Client *currentClient, vector<Client> *totalClient) {
	bool complete = false;

	while (!complete)
	{
		cout << "**********enter client setup进入用户设定**********" << endl;
		cout << "请选择 1新建用户并登录 2 登录用户 3 修改当前用户 4 登出当前用户 5退出用户设定" << endl;
		cout << "choice: 1add new client and login 2 login 3 amend login user 4 logout 5 exit" << endl;
		
		string input;
		cin >> input;
		int choice = RegUtil::returnIntIfValid(input, 1, 5);
		if (choice)
		{
			if (choice == 1) {
				currentClient = addNewClient(totalClient);
				complete = true;
			}
			if (choice == 2) {
				if (totalClient->size() < 1) {
					cout << "no registered user当前没有注册用户" << endl;
					complete = true;
				}
				else
				{
					string customerName;
					cout << "key in user name请输入欲登录的用户名" << endl;
					cin >> customerName;
	
					if (currentClient != nullptr) {
						Client temp = *currentClient;
						//重载操作符,比较是否是同一人
						if (temp += customerName) {
							cout << "the user already logged in输入的用户为当前用户" << endl;
							complete = true;
						}
					}

					bool existClient = Client::existClient(customerName, totalClient);
					if (existClient)
					{
						currentClient = Client::getExistClient(customerName, totalClient);
						if (currentClient != nullptr) {
							cout << "success 登录用户成功" << endl;
							complete = true;
						}
					}
					else
					{
						cout << "unregistered user name系统里不不存在所输入的customer Name" << endl;
						complete = true;
					}

				}

			}
			if (choice == 3) {
				if (currentClient == nullptr) {
					cout << "please login 情先登录!" << endl;
				}
				else {
					cout << "current user 当前用户信息:" << endl;;
					currentClient->toString();
					cout << "请选择要修改的信息:1姓名2年龄3地址" << endl;
					cout << "item to amend:1 name 2 age 3 address" << endl;
					string input;
					cin >> input;
					int chice2 = RegUtil::returnIntIfValid(input, 1, 3);

					if (chice2 == 1) {
						string name;
						cout << "key in the new name请输入姓名" << endl;
						cin >> name;
						currentClient->setName(name);
					}

					if (chice2 == 2) {
						string input;
						cout << "key in the new age 请输入年龄" << endl;
						cin >> input;
						int age = RegUtil::returnIntIfValid(input, 1, 100);
						currentClient->setAge(age);
					}
					if (chice2 == 3) {
						string address;
						cout << "key in the new address 请输入地址" << endl;
						cin >> address;
						currentClient->setAddress(address);
					}
				}
				complete = true;
			}
			if (choice == 4) {
				currentClient = nullptr;
				complete = true;
			}
			if (choice == 5) {
				complete = true;
			}
		}
	}
	return currentClient;
};



Client *addNewClient(vector<Client> *totalClient)
{
	bool complete = false;
	Client *newClient = new Client();
	int totalClientSize = totalClient->size();
	while (!complete)
	{
		string input;

		int customerId = totalClientSize + 1;
		newClient->setCustomerId(customerId);
		std::cout << "key in name 请输入姓名" << endl;
		cin >> input;
		newClient->setName(input);
		std::cout << "key in age 请输入年龄" << endl;
		cin >> input;
		int age = RegUtil::returnIntIfValid(input, 1, 100);
		if (age)
		{
			newClient->setAge(age);
			std::cout << "key in address 请输入地址" << endl;
			cin >> input;
			newClient->setAddress(input);
			totalClient->push_back(*newClient);
			complete = true;
		}
	}
	totalClientSize++;
	std::cout << "total clients now加入后总客户人数：" << totalClientSize << endl;
	for (int i = 0; i < totalClientSize; i++) {
		Client temp = (*totalClient)[i];
		temp.toString();
		return newClient;
	}
}






int checkOut(map<string, int> order, Client *currentClient, map<string, Menu> menu, vector<OrderDetail> *totalOrders)
{
	if (currentClient == nullptr) {
		cout << "no login user 当前没有登录用户" << endl;
		return 0;
	}

	if (order.size() == 0) {
		cout << "not order yet尚未点餐" << endl;
		return 0;
	}

	cout << "start close balance 开始结算" << endl;
	double totlaWeight = 0;
	int totalPrice = 0;

	map<string, int>::iterator orderIte;
	for (orderIte = order.begin(); orderIte != order.end(); orderIte++) {
		string name = orderIte->first;
		int num = orderIte->second;
		Menu *temp = getMenuByName(name, menu);
		cout << "num=" << num << endl;
		cout << "getPrice=" << temp->getPrice() << endl;
		cout << "getWeight=" << temp->getWeight() << endl;
		totalPrice += (temp->getPrice())*num;
		totlaWeight += (temp->getWeight())*num;
	}

	MyTime myTime;
	tm nowTime = myTime.getCurrentTm();
	OrderDetail orderdetail(order, *currentClient, totlaWeight, totalPrice, nowTime);
	totalOrders->push_back(orderdetail);


	for (int i = 0; i < totalOrders->size(); i++) {
		OrderDetail temp = (*totalOrders)[i];
		cout << "total amouts 结算完成，总金额=" << temp.totalPrice << ",total weight 总重量=" << temp.totalWeight << endl;
		myTime.printTime(nowTime);
	}
	return 1;
};


Menu *getMenuByName(string name, map<string, Menu>menu) {



	map<string, Menu>::iterator ite;
	for (ite = menu.begin(); ite != menu.end(); ite++) {
		if (ite->first == name) {
			Menu *temp = &(ite->second);
			return temp;
		}
	}
	return 0;
}

map<string, int> startOrder(map<string, int> order, map<string, Menu> menu) {
	if (menu.size() < 1) {
		cout << "there is no menu available尚未创建菜单" << endl;
		return order;
	}
	map<string, int>::iterator orderIte;
	map<string, Menu>::iterator menuIte;
	bool complete = false;
	while (!complete)
	{
		cout << "选择：1重新点餐 2继续点餐 3结束点餐" << endl;
		cout << "choice：1 new order(delete previous orders) 2 continue current order  3 exit 结束点餐" << endl;
		string input;
		cin >> input;
		int choice = RegUtil::returnIntIfValid(input, 1, 3);
		if (choice == 1) {
			order.clear();
		}
		else if (choice == 3) {

			for (orderIte = order.begin(); orderIte != order.end(); orderIte++) {
				cout << "Dish Ordered:" << endl;
				cout << orderIte->first << ":" << orderIte->second << endl;
			}
			complete = true;
		}


		if (!complete) {
			cout << " start order 开始点菜" << endl;

			for (menuIte = menu.begin(); menuIte != menu.end(); menuIte++) {
				Menu temp = menuIte->second;
				temp.printMenu();
			}
			string name;
			string input;
			cout << "key in one dish name above 请选择菜名Name" << endl;
			cin >> name;
			cout << "key in number to order 请输入数量" << endl;
			cin >> input;
			int num = RegUtil::returnIntIfValid(input, 1, -1);
			Menu *menu2 = getMenuByName(name, menu);
			if (menu2 != 0) {
				string name = menu2->getName();
				if (order.size() < 1) {
					order[name] = num;
				}
				else {
					bool hasOrdered = false;

					for (orderIte = order.begin(); orderIte != order.end(); orderIte++) {
						if (orderIte->first == name) {
							hasOrdered = true;
							break;
						}
					}

					if (hasOrdered) {
						for (orderIte = order.begin(); orderIte != order.end(); orderIte++) {

							int currentNum = 0;
							if (order[name] > 0) {
								currentNum = order[name];
							};
							currentNum += num;
							order[name] = currentNum;
						}
					}
					else {
						order[name] = num;
					}
				}
			}
			else {
				cout << "incorrect dish name 查不到所输入的菜品名！" << endl;
			}
		}
	}
	return order;
}





map<string, Menu> initMenu(map<string, Menu> menu)
{
	bool complete = false;
	while (!complete) {
		cout << "add new dish 新增菜单" << endl;
		cout << "1.create default dishes 创建默认菜单请按" << endl;
		cout << "2.create one dish 自定义创建请按" << endl;
		cout << "3.review current menu 查看当前全部菜单" << endl;
		cout << "4.exit 退出" << endl;
		cout << "请输入选择：" << endl;
		string input;
		cin >> input;
		int creatDefault = RegUtil::returnIntIfValid(input, 1, 4);
		if (creatDefault == 1)
		{
			Menu oneDish1(1, "coffee", 20, 1.5);
			Menu oneDish2(2, "tea", 15, 1.5);
			Menu oneDish3(3, "cake", 50, 10);
			menu.insert(pair<string, Menu>("coffee", oneDish1));
			menu.insert(pair<string, Menu>("tea", oneDish2));
			menu.insert(pair<string, Menu>("cake", oneDish3));
		}

		if (creatDefault == 2)
		{
			bool complete = false;
			while (!complete)
			{
				int maxId = 0;
				//load existed dishes
				set<string> *menuString = new set<string>;
				for (map<string, Menu>::iterator ite = menu.begin(); ite != menu.end(); ite++) {
					menuString->insert(ite->first);
					maxId++;
				}
				string dishName;

				cout << "key in dish name 请输入菜名" << endl;
				cin >> dishName;
				Menu temp;
				if (menuString->count(dishName) > 0) {
					cout << "already in the menu 已包含菜名" << endl;
					temp = menu.find(dishName)->second;
					cout << "id:" << temp.getId() << ",name:" << temp.getName() << ",price:" << temp.getPrice() << ",weight:" << temp.getWeight() << endl;
				}
				else {
					temp.setName(dishName);
					cout << "key in the price 请输入金额" << endl;
					cin >> input;
					int price = RegUtil::returnIntIfValid(input, 1, -1);
					if (price) {
						cout << "key in the weight 请输入重量" << endl;
						cin >> input;
						double weight = RegUtil::returnDoubleIfValid(input, 1.0, -1);
						if (weight) {
							temp.setPrice(price);
							temp.setWeight(weight);
							menu.insert(pair<string, Menu>(dishName, temp));
							Menu oneDish(maxId + 1, dishName, price, weight);
							menu.insert(pair<string, Menu>(dishName, oneDish));
							cout << "success 新增菜单完成" << endl;
						}
					}
				}
				complete = true;
			}
		}

		if (creatDefault == 3) {
			if (menu.size() == 0) {
				cout << "no menu available 尚未建立菜单" << endl;
			}
			else {
				cout << "current muenu 已经建立的菜单包括：" << endl;
				map<string, Menu>::iterator ite;
				cout << "menu list:" << endl;
				for (ite = menu.begin(); ite != menu.end(); ite++)
				{
					Menu temp = ite->second;
					temp.printMenu();
				}
			}
		}
		if (creatDefault == 4) {
			complete = true;
		}
	}
	return menu;
}











