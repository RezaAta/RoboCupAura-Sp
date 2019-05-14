#pragma once
#include <vector>
#include "ObjHandler.h"

using namespace std;
struct Order
{
	enum OrderType{buy,sell};
	OrderType orderType;
	double amount;

	double profit;
};

class Client
{
public:
	Client();
	~Client();

	void TakeActionBasedOnMarket();

private:
	double equity;
	double balance;
	double totalNetProfit;
	double totalLoss;
	double profit;
	vector<Order> allPendingOrders;
	vector<Order> orderLog;

	void SendNewOrder();
};

