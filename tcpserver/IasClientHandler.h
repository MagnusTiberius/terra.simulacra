#pragma once
#include "stdafx.h"
#include "SocketServer.h"
#include "BoardManager.h"
#include "ThreadPool.h"
#include "TaskThreadHandler.h"
#include "ThreadHandler.h"
#include "QueueManager.h"
#include "iaslib.h"



static const std::wstring application_json(L"application/json");
static const std::wstring zlib(L"zlib");
static const std::wstring last_upload_epoch_str(L"last_upload_epoch");
static const std::wstring last_upload_filename(L"lastupload.json");
const wchar_t* const appid = L"deadbeef";
const wchar_t* const contextid = L"deadbeef-dead-beef-dead-beefdeadbeef";
const wchar_t* const segkeys[] = { L"VID", L"DecileViewed", L"VidVer" };
const wchar_t* const segvals[] = { L"VID_IPT", L"2", L"3" };

static wchar_t* app_policy1 =
	L"{																								  "
	L"	\"version\": {																				  "
	L"		\"version\": 2,																			  "
	L"			\"id\": \"f95b7efc-1423-449a-8310-05bff3fb7b62\",									  "
	L"			\"ts\": 1387303286																	  "
	L"	},																							  "
	L"	\"expiration\": 0,																			  "
	L"  \"authorities\":{																				"
	L" 		\"telemetry\":{																				"
	L"			\"authority\":\"http://localhost:8080\", "
	L"			\"whitelist\":[\"515fe543ff8b42d4c286ac234aad9a9040c5557ea1016a47a266d24f9c1c3377\"]	"
	L"	}},																								"
	L"	\"policies\":[{																					"
	L"		\"retention\":{																				"
	L"			\"telemetry_max_cache\":101,															"
	L"			\"session_max_age\":1,																	"
	L"			\"session_min_upload_backoff\":0														"
	L"		},																							"
	L"		\"v1\":{																					"
	L"			\"data\":{																				"
	L"				\"authority\":\"telemetry\",														"
	L"				\"resource\":\"/v1/collector\"														"
	L"		}} "
	L"	}] "
	L"}";

class IasClientHandler:ThreadHandler
{
public:
	IasClientHandler(void);
	~IasClientHandler(void);
	virtual unsigned ThreadHandlerProc(void);
private:
};

