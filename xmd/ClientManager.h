#pragma once

#include <map>
#include <string>
#include "ClientXm.h"
#include <vector>

class ClientManager
{
public:
	static ClientManager* ClientManager::Instance();
	void AddClient(ClientXm* client);
protected:
	ClientManager(void);
	~ClientManager(void);
	std::vector<ClientXm*> m_ClientList;
private:
    static ClientManager* _instance;
};

