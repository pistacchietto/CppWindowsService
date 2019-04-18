/****************************** Module Header ******************************\
* Module Name:  CppWindowsService.cpp
* Project:      CppWindowsService
* Copyright (c) Microsoft Corporation.
* 
* The file defines the entry point of the application. According to the 
* arguments in the command line, the function installs or uninstalls or 
* starts the service by calling into different routines.
* 
* This source is subject to the Microsoft Public License.
* See http://www.microsoft.com/en-us/openness/resources/licenses.aspx#MPL.
* All other rights reserved.
* 
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
* EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
\***************************************************************************/

#pragma region Includes
#include <stdio.h>
#include <windows.h>
#include "ServiceInstaller.h"
#include "ServiceBase.h"
#include "SampleService.h"
#pragma endregion
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

// 
// Settings of the service
// 

// Internal name of the service
#define SERVICE_NAME             L"CppWindowsService"
//#define SERVICE_NAME             L"sys1svc"

// Displayed name of the service
#define SERVICE_DISPLAY_NAME     L"CppWindowsService Sample Service"

// Service start options.
#define SERVICE_START_TYPE       SERVICE_AUTO_START

// List of service dependencies - "dep1\0dep2\0\0"
#define SERVICE_DEPENDENCIES     L""

// The name of the account under which the service should run
#define SERVICE_ACCOUNT          L"NT AUTHORITY\\LocalService"

// The password to the service account name
#define SERVICE_PASSWORD         NULL


//
//  FUNCTION: wmain(int, wchar_t *[])
//
//  PURPOSE: entrypoint for the application.
// 
//  PARAMETERS:
//    argc - number of command line arguments
//    argv - array of command line arguments
//
//  RETURN VALUE:
//    none
//
//  COMMENTS:
//    wmain() either performs the command line task, or run the service.
//
int wmain(int argc, wchar_t *argv[])
{
    if ((argc > 1) && ((*argv[1] == L'-' || (*argv[1] == L'/'))))
    {
        if (_wcsicmp(L"install", argv[1] + 1) == 0)
        {
            // Install the service when the command is 
            // "-install" or "/install".
            InstallService(
                SERVICE_NAME,               // Name of service
                SERVICE_DISPLAY_NAME,       // Name to display
                SERVICE_START_TYPE,         // Service start type
                SERVICE_DEPENDENCIES,       // Dependencies
                SERVICE_ACCOUNT,            // Service running account
                SERVICE_PASSWORD            // Password of the account
                );
			//Sleep(10000);
			
			/*CSampleService service(SERVICE_NAME);
			if (!CServiceBase::Run(service))
			{
				wprintf(L"Service failed to run w/err 0x%08lx\n", GetLastError());
			}
			SC_HANDLE schSCManager = NULL;
			SC_HANDLE schService = NULL;
			SERVICE_STATUS ssSvcStatus = {};

			// Open the local default service control manager database
			schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
			if (schSCManager == NULL)
			{
				wprintf(L"OpenSCManager failed w/err 0x%08lx\n", GetLastError());
				goto Cleanup;
			}

			// Open the service with delete, stop, and query status permissions
			schService = OpenService(schSCManager, SERVICE_NAME, SERVICE_START);
			if (schService == NULL)
			{
				wprintf(L"OpenService failed w/err 0x%08lx\n", GetLastError());
				goto Cleanup;
			}
			// Get a handle to the service.

			// Attempt to start the service.

			if (!StartService(
				schService,  // handle to service 
				0,           // number of arguments 
				NULL))      // no arguments 
			{
				printf("StartService failed (%d)\n", GetLastError());
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return 1;
			}
			else printf("Service start pending...\n");
		Cleanup:
			// Centralized cleanup for all allocated resources.
			if (schSCManager)
			{
				CloseServiceHandle(schSCManager);
				schSCManager = NULL;
			}
			if (schService)
			{
				CloseServiceHandle(schService);
				schService = NULL;
			}
	      */
        }
        else if (_wcsicmp(L"remove", argv[1] + 1) == 0)
        {
            // Uninstall the service when the command is 
            // "-remove" or "/remove".
            UninstallService(SERVICE_NAME);
        }
    }
    else
    {
        wprintf(L"Parameters:\n");
        wprintf(L" -install  to install the service.\n");
        wprintf(L" -remove   to remove the service.\n");
		CSampleService service(SERVICE_NAME);
		if (!CServiceBase::Run(service))
		{
			wprintf(L"Service failed to run w/err 0x%08lx\n", GetLastError());
		}
        

    }

    return 0;
}