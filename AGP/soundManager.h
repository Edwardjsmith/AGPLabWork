#pragma once

#pragma comment (lib, "Dsound.lib")
#include <map>
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>


class soundManager
{
public:

	static soundManager* getInstance();
	~soundManager();
	HRESULT initSound(HWND);
	
	HRESULT playWav(const char* filename);

private:

	IDirectSound8* mDirectSound;
	IDirectSoundBuffer* mPrimaryBuffer;
	IDirectSoundBuffer8* mSecondaryBuffer;

	

	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

	soundManager();
	static soundManager* instance;
	HRESULT loadWav(const char* filename);
	
};


