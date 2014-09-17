#include "ChannelManager.h"

ChannelManager* ChannelManager::m_Instance = 0;
ChannelManager* ChannelManager::Instance()
{
	if (m_Instance == 0) {
		m_Instance = new ChannelManager();
	}
	return m_Instance;
}

ChannelManager::ChannelManager() : Thread(this), ThreadHandler()
{
}


ChannelManager::~ChannelManager()
{
}

unsigned ChannelManager::ThreadHandlerProc(void)
{
	return 0;
}