#include <windows.h>
#include <stdlib.h>

#include "Detours.h"

#define _DEBUG_LOG    TRUE
#include "LogFile.h"

#include "BF3_SDK.h"

DWORD CreateDetours()
{
	// init hooks.
	CLogFile logFile = CLogFile("log.txt",true);
	logFile.Write("Create Detours...");
	logFile.Write("Create Detours Finished...");
	fb::DxRenderer* g_dxRenderer = fb::DxRenderer::Singleton( );
	// Test Kommentar
	if( g_dxRenderer == NULL )
	{
		logFile.Write("Swapchain not found...");
	}else
	{
		logFile.Write("Swapchain found %X ... ",g_dxRenderer->pSwapChain);
	}




	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
    if(dwReason == DLL_PROCESS_ATTACH) { 
		CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)CreateDetours,0,0,0);
    } 
    return TRUE;
}