#ifndef __C_SCENE_RESOURCE_H__
#define __C_SCENE_RESOURCE_H__

#include "BaseResource.h"

class CSceneResource : public CBaseResource
{
public:
	CSceneResource();
	CSceneResource(int type);
	~CSceneResource();

	virtual wchar_t* getImage(int tag, int state) override;
};

#endif