
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include <util/Timer.h>

//-------------------------------------------------------------------------
Timer::Timer()
{
	reset();
}
//-------------------------------------------------------------------------
void Timer::reset()
{
	#ifdef WIN32
	resetTime = timeGetTime();
	#else
	struct timeval tv;
	struct timezone tz;
	gettimeofday( &tv, &tz );
	resetTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	#endif
}
//-------------------------------------------------------------------------
unsigned int Timer::evaluate()
{
	#ifdef WIN32
	return timeGetTime() - resetTime;
	#else
	struct timeval tv;
	struct timezone tz;
	gettimeofday( &tv, &tz );
	long newTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return newTime - resetTime;
	#endif
}
//-------------------------------------------------------------------------

