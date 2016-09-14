/****************************************************************************/
/* Create by Michael Le*/
/* 07/07/2015 */
/***************************************************************************/

#ifndef __TIMER_H__
#define __TIMER_H__

#include <time.h>
#include <windows.h>

class CTimer
{
public:
	~CTimer();
	
	static	CTimer*			getInstance();
			void			setElapedTime();
			void			setElapedTime(double newTime);
			double			getElapedTime();

			double			getMillisecond();
			double			getSecond();
			double			getMinute();
			double			getHours();

			void			begin();
			void			end();


private:

			double			m_Millisecond;
			double			m_Second;
			double			m_Minute;
			double			m_Hours;
			double			m_ElapedTime;

			LARGE_INTEGER	m_start, 
							m_end, 
							m_freq;

private:
	static	CTimer*			m_Instance;
	CTimer();
};

#endif

