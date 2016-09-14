// Sound for game

#ifndef _CAUDIO_H
#define _CAUDIO_H

#include "Class/Framework/dsutil.h"

extern CSoundManager *dsound;

class CAudio
{
public:
	CSound *LoadSound(wchar_t *);
	void PlaySound(CSound *);
	void LoopSound(CSound *);
	void StopSound(CSound *);
	void DestroySound(CSound *);
	static bool Init_DirectSound(HWND);

public:
	static CAudio* getInstance();

private:
	static CAudio* m_Instance;
	CAudio();
	~CAudio();
};

#endif

