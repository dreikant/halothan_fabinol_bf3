#include <windows.h>
#include <stdlib.h>

#include "Detours.h"

#define _DEBUG_LOG    TRUE
#include "LogFile.h"

#include "BF3_SDK.h"

//typedef HRESULT (WINAPI* tPresent)(LPDIRECT3DSWAPCHAIN9 pSwapChain, const RECT *pSourceRect,const RECT *pDestRect,HWND hDestWindowOverride,const RGNDATA *pDirtyRegion,DWORD dwFlags);
//tPresent oPresent;

typedef HRESULT (WINAPI* tPresent)(IDXGISwapChain* theClass, unsigned int, unsigned int);
tPresent oPresent;



//HRESULT WINAPI hkPresent(LPDIRECT3DSWAPCHAIN9 pSwapChain, const RECT *pSourceRect,const RECT *pDestRect,HWND hDestWindowOverride,const RGNDATA *pDirtyRegion,DWORD dwFlags)
HRESULT WINAPI hkPresent(IDXGISwapChain* theclass, unsigned int d, unsigned int e)
{
	fb::DebugRenderer2* engineRender = fb::DebugRenderer2::Singleton( );

	if( VALID(engineRender) )
	{
		engineRender->drawText(5,5,fb::Color32(255,0,0,255),"Test",1);
	}
	return oPresent(theclass, d, e);
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

			// ALTERNATIVE:
			DWORD dxgi_base = (DWORD)GetModuleHandle("dxgi.dll") + (DWORD)0x2D9D1;
			//DWORD dxgi_base = (DWORD)vtable[8];


			oPresent = ( tPresent )DetourCreate( (PBYTE)dxgi_base, (PBYTE)&hkPresent, 5);



			logFile.Write("Detoured Swapchain Function: %X -> %X ... ", dxgi_base, (DWORD)oPresent);
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