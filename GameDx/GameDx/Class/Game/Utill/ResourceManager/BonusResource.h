#ifndef __C_BONUS_RESOURCE_H__
#define __C_BONUS_RESOURCE_H__

#include "BaseResource.h"

class CBonusResource : public CBaseResource
{
public:
	CBonusResource();
	CBonusResource(int type);
	~CBonusResource();

	virtual wchar_t* getImage(int tag, int state) override;
};

#endif