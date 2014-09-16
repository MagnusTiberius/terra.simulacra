#include "CommandAnalyticsClient.h"

namespace bbg {

CommandAnalyticsClient::CommandAnalyticsClient()
{
	srand(time(NULL));
}

CommandAnalyticsClient::~CommandAnalyticsClient()
{
}

void CommandAnalyticsClient::Execute(void)
{
	int m = rand();

	printf("[0x%08lx] >>> CommandAnalyticsClient Execute: \n", GetCurrentThreadId());

	//HRESULT hres = Initialize(appid, L"2.0", contextid, L"", app_policy1, true);
	::Sleep(m % 500);
	printf("[0x%08lx] ... CommandAnalyticsClient Execute: working... \n", GetCurrentThreadId());
	::Sleep(m % 500);
	printf("[0x%08lx] ... CommandAnalyticsClient Execute: working... \n", GetCurrentThreadId());
	::Sleep(m % 500);
	//hres = Deinitialize(IAS_INFINITE);

	printf("[0x%08lx] <<< CommandAnalyticsClient Execute: \n", GetCurrentThreadId());
}

}