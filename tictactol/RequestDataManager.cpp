#include "RequestDataManager.h"


RequestDataManager* RequestDataManager::_instance = 0;


RequestDataManager::RequestDataManager(void)
	: m_mNowriters(), m_eNoreaders(TRUE,TRUE)
{
	m_nReaderSize=0;
	m_RequestDataList.Init(5000);
}


RequestDataManager::~RequestDataManager(void)
{
}

RequestDataManager* RequestDataManager::Instance() {
    if (_instance == 0) {
        _instance = new RequestDataManager;
    }
    return _instance;
}

void RequestDataManager::AddRequestData(RequestData* d)
{
	m_RequestDataList.Write(d);
}

void RequestDataManager::ReadRequestData(RequestData* d)
{
	if (!m_RequestDataList.IsEmpty())
		m_RequestDataList.Read(d);
}

void RequestDataManager::GrantReaderAccess()
{
    m_mNowriters.Wait(INFINITE);
    m_nReaderSize++;
    m_eNoreaders.Reset();
    m_mNowriters.Release();
}

void RequestDataManager::ReleaseReaderAccess()
{
    m_mNowriters.Wait(INFINITE);
    if (--m_nReaderSize == 0) 
	{
        m_eNoreaders.Set();
    }
    m_mNowriters.Release();
}

void RequestDataManager::GrantWriterAccess()
{
	m_mNowriters.WaitForTwo( m_eNoreaders, TRUE, INFINITE);
}

void RequestDataManager::ReleaseWriterAccess()
{
	m_mNowriters.Release();
}
