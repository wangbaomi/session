#include <Winsock2.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <Wtsapi32.h>
#include <stdlib.h>



#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Wtsapi32.lib")

//sessionInfos��������session��������Ϣ
PWTS_SESSION_INFO sessionInfos = NULL;
//sessionCount����session����,infoSize�����ȡ��session��Ϣ��С
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

//��ȡ��ǰ����IP��ַ
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

//��ȡ��ǰ������
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


//��ȡ��ǰ�Ự��ʶ
int GetSessionId()
{
	PULONG sessionId = 0;
	try
	{
		//ö�ٻỰ
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

//��ȡ��¼��ǰ�Ự���û���
int GetLoginSessionUserName()
{
	wchar_t *userName = NULL;
	try
	{
		//ö�ٻỰ
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

//��ȡ��ǰԶ���������Ự������
int GetWinStationName()
{
	char *winStationName = NULL;
	try
	{
		//ö�ٻỰ
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

//��ȡ��¼��ǰ�Ự�û������ڵ�������
int GetLoginSessionUserDomainName()
{
	char *domainName = NULL;
	try
	{
		//ö�ٻỰ
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

//��ȡ��¼��ǰ�Ự�û��Ŀͻ�������
int GetLoginSessionUserClientName()
{
	char* clientName = NULL;
	try
	{
		//ö�ٻỰ
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

//��ȡ��¼��ǰ�Ự�û��Ŀͻ���IP��ַ
int GetLoginSessionUserClientAddress()
{
	WTS_CLIENT_ADDRESS *clientAddress = (WTS_CLIENT_ADDRESS*)malloc(sizeof(WTS_CLIENT_ADDRESS));
	try
	{
		//ö�ٻỰ
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
	printf(  "\nsession.exe���ڻ�ȡ�Ự��Ϣ.\n\n"
			 "�÷�: session.exe\t[SessionId] [LoginSessionUserName] [WinStationName]\n"
			 "\t\t\t[LoginSessionUserDomainName] [HostName] [HostAddress]\n"
			 "\t\t\t[LoginSessionUserClientAddress] [Help]\n"
			 "\t\t\t[LoginSessionUserClientName]\n"
			 "\n"
			 "����:\n"
			 "Help\t\t\t\t��ʾ����������Ϣ.\n"
			 "SessionId\t\t\t��ȡ��ǰ�Ự��ʶ.\n"
			 "LoginSessionUserName\t\t��ȡ��¼��ǰ�Ự���û���.\n"
			 "WinStationName\t\t\t��ȡ��ǰԶ���������Ự������.\n"
			 "LoginSessionUserDomainName\t��ȡ��¼��ǰ�Ự�û������ڵ�������.\n"
			 "LoginSessionUserClientName\t��ȡ��¼��ǰ�Ự�û��Ŀͻ�������.\n"
			 "LoginSessionUserClientAddress\t��ȡ��¼��ǰ�Ự�û��Ŀͻ���IP��ַ.\n"
			 "HostName\t\t\t��ȡ���Ự����������������.\n"
			 "HostAddress\t\t\t��ȡ���Ự����������IPv4��ַ.\n");
	return 0;
}


int displayAll()
{
	printf("��ǰ�Ự��ʶ\t\t\t=\t");
	GetSessionId();
	printf("\n��¼��ǰ�Ự���û���\t\t=\t");
	GetLoginSessionUserName();
	printf("\n��ǰԶ���������Ự������\t=\t");
	GetWinStationName();
	printf("\n��¼��ǰ�Ự�û������ڵ�������\t=\t");
	GetLoginSessionUserDomainName();
	printf("\n��¼��ǰ�Ự�û��Ŀͻ�������\t=\t");
	GetLoginSessionUserClientName();
	printf("\n��¼��ǰ�Ự�û��Ŀͻ���IP��ַ\t=\t");
	GetLoginSessionUserClientAddress();
	printf("\n���Ự����������������\t\t=\t");
	GetHostName();
	printf("\n���Ự����������IPv4��ַ\t=\t");
	GetHostAddress();
	printf("\n");
	printf("��ȡ���� ��ִ��\"session.exe help\".\n");
	return 0;
}