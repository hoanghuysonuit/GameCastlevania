#include "BaseResource.h"
#include "Class\Game\Utill\stdafx.h"

CBaseResource::CBaseResource()
{
}

CBaseResource::CBaseResource(int type)
{
	m_TypeObject = type;
}


CBaseResource::~CBaseResource()
{
}

wchar_t* CBaseResource::getImage(int tag, int state) {
	return nullptr;
}
