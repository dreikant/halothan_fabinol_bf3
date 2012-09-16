#include <windows.h>
#include <stdlib.h>

#include "Detours.h"

#define _DEBUG_LOG    TRUE
#include "LogFile.h"

#include "BF3_SDK.h"

typedef HRESULT (WINAPI* tPresent)(LPDIRECT3DSWAPCHAIN9 pSwapChain, const RECT *pSourceRect,const RECT *pDestRect,HWND hDestWindowOverride,const RGNDATA *pDirtyRegion,DWORD dwFlags);
tPresent oPresent;

HRESULT WINAPI hkPresent(LPDIRECT3DSWAPCHAIN9 pSwapChain, const RECT *pSourceRect,const RECT *pDestRect,HWND hDestWindowOverride,const RGNDATA *pDirtyRegion,DWORD dwFlags)
{
	return oPresent(pSwapChain, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion,dwFlags);
}

DWORD CreateDetours()
{
	// init hooks.
	CLogFile logFile = CLogFile("log.txt",true);
	logFile.Write("Create Detours...");
	logFile.Write("Create Detours Finished...");
	fb::DxRenderer* g_dxRenderer = fb::DxRenderer::Singleton( );
	// Test Kommentar
	//insekt du sau
	if( g_dxRenderer == NULL )
	{
		logFile.Write("Renderer not found...");
	}else
	{
		logFile.Write("Swapchain found %X ... ",g_dxRenderer->pSwapChain);

		// try swapchain detour.
		if ( VALID( g_dxRenderer->pSwapChain ) )
		{
			DWORD* vtable    = ( DWORD* )g_dxRenderer->pSwapChain;
			vtable            = ( DWORD* )vtable[0];
			oPresent = ( tPresent )DetourCreate( (PBYTE)vtable[8], (PBYTE)&hkPresent, 7);
			logFile.Write("Detoured Swapchain Function: %X -> %X ... ", g_dxRenderer->pSwapChain, (DWORD)oPresent);
		}else
		{
			logFile.Write("Detour failed. Swapchain Invalid. %X ... ", g_dxRenderer->pSwapChain);
		}
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