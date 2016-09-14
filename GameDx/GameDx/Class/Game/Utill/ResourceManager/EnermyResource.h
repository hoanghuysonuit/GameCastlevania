#ifndef __C_ENERMY_RESOURCE_H__
#define __C_ENERMY_RESOURCE_H__

#include "BaseResource.h"

class CEnermyResource : public CBaseResource
{
public:
	CEnermyResource();
	CEnermyResource(int type);
	~CEnermyResource();

	virtual wchar_t* getImage(int tag, int state) override;
};

#endif