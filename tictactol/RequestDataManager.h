#pragma once
#include "RequestData.h"
#include <vector>
#include "CircularBuffer.h"
#include "Mutex.h"
#include "Event.h"

class RequestDataManager
{
public:
	RequestDataManager(void);
	~RequestDataManager(void);
	static RequestDataManager* Instance();
	void AddRequestData(RequestData* d);
	void ReadRequestData(RequestData* d);
	void GrantReaderAccess();
	void ReleaseReaderAccess();
	void GrantWriterAccess();
	void ReleaseWriterAccess();
protected:
	CircularBuffer<RequestData> m_RequestDataList;
	bbg::Mutex m_mNowriters;
	bbg::Event m_eNoreaders;
	int m_nReaderSize;
private:
    static RequestDataManager* _instance;
};

