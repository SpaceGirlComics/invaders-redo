#include "includes.h"

DXSound::DXSound()
{
}

DXSound::~DXSound()
{
}

bool DXSound::DXSoundInit()
{
	if(DS_OK!=DirectSoundCreate(NULL, &lpDS, NULL))
	{
		return(false);
	}
	if(DS_OK!=IDirectSound_SetCooperativeLevel(lpDS, g_hWnd, DSSCL_NORMAL))
	{
		return(false);
	}
	return(true);
}

void DXSound::DXSoundExit()
{
	if(lpDS)
	{
		IDirectSound_Release(lpDS);
	}
}