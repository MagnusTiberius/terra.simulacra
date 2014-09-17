#include "ConnectionManager.h"


ConnectionManager* ConnectionManager::m_Instance = 0;

ConnectionManager::ConnectionManager(void)
{

}
ConnectionManager::~ConnectionManager(void)
{

}
ConnectionManager* ConnectionManager::Instance()
{
	if (m_Instance == 0) {
		m_Instance = new ConnectionManager();
	}
	return m_Instance;
}
void ConnectionManager::Add(int n, ConnectedSocketInfo* p)
{
	m_ConnectionListManager.insert(std::pair<int, ConnectedSocketInfo*>(n, p));
}