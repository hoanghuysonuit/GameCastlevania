#include "SceneResource.h"
#include "Class\Game\Utill\stdafx.h"

CSceneResource::CSceneResource()
{
}


CSceneResource::CSceneResource(int type) {
	this->m_TypeObject = type;
}

CSceneResource::~CSceneResource()
{
}

wchar_t* CSceneResource::getImage(int tag, int state) {
	switch (tag)
	{
	default:
		break;
	}
	return nullptr;
}
