#include "Class\Framework\Timer.h"
#include "Class\Game\Utill\Config.h"

CTimer* CTimer::m_Instance = NULL;

CTimer::CTimer()
{
	this->m_Millisecond		=	0;
	this->m_Second			=	0;
	this->m_Minute			=	0;
	this->m_Hours			=	0;
	this->m_ElapedTime		=	0;

	QueryPerformanceFrequency(&m_freq);

}


CTimer::~CTimer()
{
	SAFE_RELEASE(m_Instance);
}

CTimer*	CTimer::getInstance()
{
	if (!m_Instance)
		m_Instance		= new CTimer();
	return m_Instance;
}

void	CTimer::begin()
{
	ZeroMemory(&m_start,	sizeof(m_start));
	QueryPerformanceCounter(&m_start);
}

void	CTimer::end()
{
	ZeroMemory(&m_end,		sizeof(m_end));
	QueryPerformanceCounter(&m_end);
}

double	CTimer::getMillisecond()
{
	m_Millisecond		= m_ElapedTime;
	return m_Millisecond;
}

double	CTimer::getSecond()
{
	m_Second			= m_ElapedTime * 1000;
	return m_Second;
}

double	CTimer::getMinute()
{
	m_Minute			= m_ElapedTime / 60000;
	return m_Minute;
}

double	CTimer::getHours()
{
	m_Hours				= m_ElapedTime / 3600000;
	return	m_Hours;
}

void	CTimer::setElapedTime()
{
	if (((double)(m_end.QuadPart - m_start.QuadPart) / m_freq.QuadPart)*1000.00 > 0)
		m_ElapedTime = ((double)(m_end.QuadPart - m_start.QuadPart) / m_freq.QuadPart)*1000.00;
}

void	CTimer::setElapedTime(double second)
{
	m_ElapedTime		= second;
}

double	CTimer::getElapedTime()
{
	return m_ElapedTime;
}

