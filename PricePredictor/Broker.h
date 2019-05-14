#pragma once

#include "ObjHandler.h"
#include "Client.h"

class Broker
{


public:
	Broker();
	~Broker();

	void UpdateClientInfo();
private:

	vector<Client> ListOfClients;
};