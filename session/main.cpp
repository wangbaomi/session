#include "sessionHead.h"





int main(int argc, char* argv[])
{
	
	switch(argc)
	{
	case 1:
		{
			displayAll();
			break;
		}
	case 2:
		{
			
			if (0 == _strcmpi(argv[1], "SessionId"))
			{
				GetSessionId();
			}
			else if(0 == _strcmpi(argv[1], "LoginSessionUserName"))
			{
				GetLoginSessionUserName();
			}
			else if (0 == _strcmpi(argv[1], "WinStationName"))
			{
				GetWinStationName();
			}
			else if (0 == _strcmpi(argv[1], "LoginSessionUserDomainName"))
			{
				GetLoginSessionUserDomainName();
			}
			else if (0 == _strcmpi(argv[1], "LoginSessionUserClientName"))
			{
				GetLoginSessionUserClientName();
			}
			else if (0 == _strcmpi(argv[1], "LoginSessionUserClientAddress"))
			{
				GetLoginSessionUserClientAddress();
			}
			else if (0 == _strcmpi(argv[1], "help"))
			{
				help();
			}
			else if (0 == _strcmpi(argv[1], "HostName"))
			{
				GetHostName();
			}
			else if (0 == _strcmpi(argv[1], "HostAddress"))
			{
				GetHostAddress();
			}
			else 
			{
				printf("\nsession.exe 参数错误(使用 session.exe help).\n");
			}
			break;
		}
	default:
		{
			printf("\nsession.exe 参数错误(使用 session.exe help).\n");
			break;
		}
	}
	return 0;
}












