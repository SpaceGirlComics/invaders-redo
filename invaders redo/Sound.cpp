#include "includes.h"
#include <stdio.h>

Sound::Sound()
{
	/*FILE* file = fopen("Deleted_Aliens", "a");
	fprintf(file, "%d\n", this);
	fclose(file);*/
}

Sound::Sound(char *fname)
{
	/*FILE* file = fopen("Deleted_Aliens", "a");
	fprintf(file, "%d\n", this);
	fclose(file);*/
	load(fname);
}

Sound::~Sound()
{
	/*FILE* file = fopen("Deleted_Aliens", "a");
	fprintf(file, "%d\n", this);
	fclose(file);*/
//	delete buffer;
}

bool Sound::load(char* fname)
{
	DWORD lockedSize;
	unsigned char* buffer;
	FILE* file = fopen(fname, "rb");
	fread(&chunkID, sizeof(char), 4, file);
	chunNum = chunkID[0] + chunkID[1] + chunkID[2] + chunkID[3];
	if(chunNum == MAIN)
	{	
		do
		{
			chunNum = chunkID[0] + chunkID[1] + chunkID[2] + chunkID[3];
			switch(chunNum)
			{
				case MAIN:
				{
					fread(&size, sizeof(int), 1, file);
					break;
				}
				case WAVE:
				{
					break;
				}

				case FMT_:
				{
					fread(&Header, sizeof(FmtHeader), 1, file);
					break;
				}

				case DATA:
				{
					fread(&datSize, sizeof(int), 1, file);
					if(size!=(datSize+36))
					{
						fclose(file);
						return(false);
					}
					
					//buffer = (unsigned char*) malloc(sizeof(unsigned char)*datSize);//new unsigned char[datSize];
					createSecondaryBuffer(0);
					DXbuffer->Lock(0, datSize, (void**)&buffer, &lockedSize, NULL, NULL, 0L);
						fread(buffer, sizeof(unsigned char), datSize, file);
					DXbuffer->Unlock((void*)buffer, lockedSize, NULL, 0);
//					cleanUp();
					break;
				}
				default:
				{
					fclose(file);
					return(false);
				}
			}
		}while(fread(&chunkID, sizeof(char), 4, file)!=0);
	}
	else
	{
		fclose(file);
		return(false);
	}
	if(Header.format!=1)
	{
		fclose(file);
		return(false);
	}
	fclose(file);
	//delete(buffer);
	return(true);
}

int Sound::createSecondaryBuffer(int flags)
{
	WAVEFORMATEX wfx;
	ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
	wfx.wFormatTag = Header.format;
	wfx.nChannels = Header.channels;
	wfx.nSamplesPerSec = Header.sampleRate;
	wfx.wBitsPerSample =  Header.bitsPerSample;
	wfx.nBlockAlign = Header.blockAlign;
	wfx.nAvgBytesPerSec = Header.byteRate;
	
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = flags;
	dsbd.dwBufferBytes = Header.sampleRate * Header.bitsPerSample / 8 * Header.channels * 2;
	dsbd.guid3DAlgorithm = GUID_NULL;
	dsbd.lpwfxFormat = &wfx;

	if(DS_OK!=lpDS->CreateSoundBuffer(&dsbd, &DXbuffer, NULL))
	{
		return(NULL);
	}
	return(dsbd.dwBufferBytes);
}

void Sound::play()
{
	DXbuffer->Play(0, 0, 0);
}
/*
void Sound::cleanUp()
{
	if(buffer)
	{
		delete(buffer);
	}
}*/

HRESULT Sound::isPlaying()
{
    return(DXbuffer->GetStatus(NULL));
}