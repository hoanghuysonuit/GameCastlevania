#include "CAudio.h"

CSoundManager *dsound;
CAudio*  CAudio::m_Instance = NULL;

CAudio::CAudio(){
}
CAudio::~CAudio(){}

bool CAudio::Init_DirectSound(HWND hWnd){
	HRESULT result;
	
	dsound = new CSoundManager();

	result = dsound->Initialize(hWnd, DSSCL_PRIORITY);

	if (result != DS_OK)
		return false;
	
	result = dsound->SetPrimaryBufferFormat(2, 22050, 16); 

	if (result != DS_OK)
		return false;

	return true; 

}

CSound* CAudio::LoadSound(wchar_t* fileName){
	HRESULT result;

	CSound *wave;

	result = dsound->Create(&wave, fileName);

	if (result != DS_OK)
		return NULL;
	return wave; 

}

void CAudio::PlaySoundW(CSound *sound){
	sound->Play();
}

void CAudio::LoopSound(CSound *sound){
	sound->Play(0, DSBPLAY_LOOPING);
}

void CAudio::StopSound(CSound *sound){
	sound->Stop();
}

void CAudio::DestroySound(CSound *sound){
	if (sound != NULL)
		delete sound;
}

CAudio* CAudio::getInstance(){
	if (!m_Instance)
	{
		m_Instance = new CAudio();
	}
	return m_Instance;
}