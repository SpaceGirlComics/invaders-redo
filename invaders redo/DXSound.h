#ifndef DXSOUND_H
#define DXSOUND_H
#include <dsound.h>
#include "Sound.h"

class DXSound
{
	public:
		DXSound();
		~DXSound();

		void DXSoundExit();
		bool DXSoundInit();
LPDIRECTSOUND lpDS;
	protected:
				
		//Sound m_Sound;
};
#endif
