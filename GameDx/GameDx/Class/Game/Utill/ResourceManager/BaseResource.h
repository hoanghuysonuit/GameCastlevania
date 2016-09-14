#ifndef __C_BASE_RESOURCE_H__
#define __C_BASE_RESOURCE_H__

class CBaseResource
{
public:
	CBaseResource();
	CBaseResource(int type);
	virtual ~CBaseResource() = 0;

	virtual wchar_t* getImage(int tag = 0, int state = 0) = 0;

public:
	int m_TypeObject;
};

#endif
