#ifndef SOUND_H
#define SOUND_H

#define MAIN ('R'+'I'+'F'+'F')
#define WAVE ('W'+'A'+'V'+'E')
#define FMT_ ('f'+'m'+'t'+' ')
#define DATA ('d'+'a'+'t'+'a')

typedef struct _FmtHeader
{
	unsigned int size;
	unsigned short format;
	unsigned short channels;
	unsigned int sampleRate;
	unsigned int byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
} FmtHeader;

class Sound
{
	public:
		Sound();
		Sound(char* fname);
		~Sound();
		bool load(char* fname);
		//void Swap(unsigned char* buff, int size);
		//void cleanUp();
		FmtHeader Header;	
		char chunkID[4];
		int chunNum, size, datSize;
		LPDIRECTSOUNDBUFFER DXbuffer;
		int createSecondaryBuffer(int flags);
		HRESULT isPlaying();
		void play();
		static LPDIRECTSOUND lpDS;
		Sound *next, *prev;
	protected:
};
#endif