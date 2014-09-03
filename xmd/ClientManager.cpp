#include "stdafx.h"
#include "ClientManager.h"

ClientManager* ClientManager::_instance = 0;

ClientManager::ClientManager(void)
{
}


ClientManager::~ClientManager(void)
{
}

ClientManager* ClientManager::Instance() 
{
    if (_instance == 0) {
        _instance = new ClientManager;
    }
    return _instance;
}

void ClientManager::AddClient(ClientXm* client)
{
	m_ClientList.push_back(client);
}