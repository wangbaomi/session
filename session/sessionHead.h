#include <Winsock2.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <Wtsapi32.h>
#include <stdlib.h>



#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Wtsapi32.lib")

//sessionInfos保存所有session的所有信息
PWTS_SESSION_INFO sessionInfos = NULL;
//sessionCount保存session数量,infoSize保存获取的session信息大小
DWORD sessionCount = 0, infoSize = 0;


int GetSessionId();
int GetLoginSessionUserName();
int GetWinStationName();
int GetLoginSessionUserDomainName();
int GetLoginSessionUserClientName();
int GetLoginSessionUserClientAddress();
int help();
int displayAll();
int GetHostName();
int GetHostAddress();

//获取当前主机IP地址
int GetHostAddress()
{
	try
	{
		char hostName[128] = "";
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2,2), &wsaData);
		gethostname(hostName, sizeof(hostName));
		struct hostent *ent = gethostbyname(hostName);
		if (ent != 0)
		{
			printf("%d.%d.%d.%d", ent->h_addr_list[0][0]&0x00ff, ent->h_addr_list[0][1]&0x00ff, ent->h_addr_list[0][2]&0x00ff, ent->h_addr_list[0][3]&0x00ff);
			WSACleanup();
			return 0;
		}
		else 
		{
			wprintf(L"-1");
			return 1;
		}
	}
	catch(...)
	{
		wprintf(L"-1");
		return 1;
	}
}

//获取当前主机名
int GetHostName()
{
	try
	{
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2,2), &wsaData);
		char hostName[128] = "";
		gethostname(hostName, sizeof(hostName));
		printf("%s", hostName);
		WSACleanup();
		return 0;
	}
	catch(...)
	{
		wprintf(L"-1");
		return 1;
	}
}


//获取当前会话标识
int GetSessionId()
{
	PULONG sessionId = 0;
	try
	{
		//枚举会话
		WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &sessionInfos, &sessionCount);
		WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSSessionId, (LPTSTR*)(&sessionId), &infoSize);
		//wprintf(L"sessionId = %x\n", *sessionId);
		wprintf(L"%d", *sessionId);
		WTSFreeMemory(sessionId);
		return 0;
	} 
	catch(...)
	{
		//wprintf(L"GetSessionID Failed! Error:%d\n", GetLastError());
		wprintf(L"-1");
		return 1;
	}
}

//获取登录当前会话的用户名
int GetLoginSessionUserName()
{
	wchar_t *userName = NULL;
	try
	{
		//枚举会话
		WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &sessionInfos, &sessionCount);	
		WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSUserName, (LPTSTR*)(&userName), &infoSize);
		wprintf(L"%s", userName);
		WTSFreeMemory(userName);
		return 0;
	} 
	catch(...)
	{
		wprintf(L"-1");
		return 1;
	}
}

//获取当前远程桌面服务会话的名称
int GetWinStationName()
{
	char *winStationName = NULL;
	try
	{
		//枚举会话
		WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &sessionInfos, &sessionCount);
		WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSWinStationName, (LPTSTR*)(&winStationName), &infoSize);
		wprintf(L"%s", winStationName);
		WTSFreeMemory(winStationName);
		return 0;
	} 
	catch(...)
	{
		wprintf(L"-1");
		return 1;
	}
}

//获取登录当前会话用户的所在的域名称
int GetLoginSessionUserDomainName()
{
	char *domainName = NULL;
	try
	{
		//枚举会话
		WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &sessionInfos, &sessionCount);
		WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSDomainName, (LPTSTR*)(&domainName), &infoSize);
		wprintf(L"%s", domainName);
		WTSFreeMemory(domainName);
		return 0;
	} 
	catch(...)
	{
		wprintf(L"-1");
		return 1;
	}
}

//获取登录当前会话用户的客户端名称
int GetLoginSessionUserClientName()
{
	char* clientName = NULL;
	try
	{
		//枚举会话
		WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &sessionInfos, &sessionCount);
		WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSClientName, (LPTSTR*)(&clientName), &infoSize);
		wprintf(L"%s", clientName);
		WTSFreeMemory(clientName);
		return 0;
	} 
	catch(...)
	{
		wprintf(L"-1");
		return 1;
	}
}

//获取登录当前会话用户的客户端IP地址
int GetLoginSessionUserClientAddress()
{
	WTS_CLIENT_ADDRESS *clientAddress = (WTS_CLIENT_ADDRESS*)malloc(sizeof(WTS_CLIENT_ADDRESS));
	try
	{
		//枚举会话
		WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &sessionInfos, &sessionCount);
		WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSClientAddress, (LPTSTR*)(&clientAddress), &infoSize);
		wprintf(L"%d.%d.%d.%d", clientAddress->Address[2], clientAddress->Address[3], clientAddress->Address[4], clientAddress->Address[5]);
		WTSFreeMemory(clientAddress);
		//free(clientAddress);
		return 0;
	} 
	catch(...)
	{
		wprintf(L"-1");
		free(clientAddress);
		return 1;
	}
}



int help()
{
	printf(  "\nsession.exe用于获取会话信息.\n\n"
			 "用法: session.exe\t[SessionId] [LoginSessionUserName] [WinStationName]\n"
			 "\t\t\t[LoginSessionUserDomainName] [HostName] [HostAddress]\n"
			 "\t\t\t[LoginSessionUserClientAddress] [Help]\n"
			 "\t\t\t[LoginSessionUserClientName]\n"
			 "\n"
			 "参数:\n"
			 "Help\t\t\t\t显示这条帮助信息.\n"
			 "SessionId\t\t\t获取当前会话标识.\n"
			 "LoginSessionUserName\t\t获取登录当前会话的用户名.\n"
			 "WinStationName\t\t\t获取当前远程桌面服务会话的名称.\n"
			 "LoginSessionUserDomainName\t获取登录当前会话用户的所在的域名称.\n"
			 "LoginSessionUserClientName\t获取登录当前会话用户的客户端名称.\n"
			 "LoginSessionUserClientAddress\t获取登录当前会话用户的客户端IP地址.\n"
			 "HostName\t\t\t获取本会话所在主机的主机名.\n"
			 "HostAddress\t\t\t获取本会话所在主机的IPv4地址.\n");
	return 0;
}


int displayAll()
{
	printf("当前会话标识\t\t\t=\t");
	GetSessionId();
	printf("\n登录当前会话的用户名\t\t=\t");
	GetLoginSessionUserName();
	printf("\n当前远程桌面服务会话的名称\t=\t");
	GetWinStationName();
	printf("\n登录当前会话用户的所在的域名称\t=\t");
	GetLoginSessionUserDomainName();
	printf("\n登录当前会话用户的客户端名称\t=\t");
	GetLoginSessionUserClientName();
	printf("\n登录当前会话用户的客户端IP地址\t=\t");
	GetLoginSessionUserClientAddress();
	printf("\n本会话所在主机的主机名\t\t=\t");
	GetHostName();
	printf("\n本会话所在主机的IPv4地址\t=\t");
	GetHostAddress();
	printf("\n");
	printf("获取帮助 请执行\"session.exe help\".\n");
	return 0;
}