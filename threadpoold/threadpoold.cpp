// threadpoold.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ThreadPool.h"
#include "TaskThreadHandler.h"
#define MAX_JOB_COUNT 9000

namespace bbg {

int JustGoDoIt(void)
{
	ThreadPool threadPool;
	TaskThreadHandler job1;
	threadPool.DispatchThread(&job1);
	TaskThreadHandler job2;
	threadPool.DispatchThread(&job2);
	int n = 0;
	int m = MAX_JOB_COUNT;
	while (threadPool.IsRunning())
	{
		if (n < m)
		{
			::Sleep(50);
			TaskThreadHandler* moreJobRightHere = new TaskThreadHandler();
			threadPool.DispatchThread(moreJobRightHere);
			printf("Dispatching job #%d\n", n);
			n++;
		}
		if (n >= m)
			threadPool.Shutdown();
	}
	printf("Done\n");
	::Sleep(1000);
	return 0;
}


}

int _tmain(int argc, _TCHAR* argv[])
{
	return JustGoDoIt();
}
