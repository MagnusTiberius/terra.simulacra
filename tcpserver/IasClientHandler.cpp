#include "IasClientHandler.h"


IasClientHandler::IasClientHandler(void):ThreadHandler()
{
}


IasClientHandler::~IasClientHandler(void)
{
}

unsigned IasClientHandler::ThreadHandlerProc(void)
{
	HRESULT hres = Initialize(appid, L"2.0", contextid, L"", app_policy1, true);
	hres = Deinitialize(IAS_INFINITE);
	return 0;
}