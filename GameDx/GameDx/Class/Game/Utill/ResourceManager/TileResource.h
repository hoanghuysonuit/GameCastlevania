#ifndef __C_TILE_RESOURCE_H__
#define __C_TILE_RESOURCE_H__

#include "BaseResource.h"

class CTileResource : public CBaseResource
{
public:
	CTileResource();
	CTileResource(int type);
	~CTileResource();

	virtual wchar_t* getImage(int tag, int state) override;
};

#endif
