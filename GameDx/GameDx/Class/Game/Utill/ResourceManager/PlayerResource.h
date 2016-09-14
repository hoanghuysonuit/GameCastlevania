#ifndef __C_PLAYER_RESOURCE_H__
#define __C_PLAYER_RESOURCE_H__

#include "BaseResource.h"

class CPlayerResource : public CBaseResource
{
public:
	CPlayerResource();
	CPlayerResource(int type);
	~CPlayerResource();

	virtual wchar_t* getImage(int tag, int state) override;
};

#endif