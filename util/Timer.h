
#ifndef _TIMER_H_
#define _TIMER_H_

//-------------------------------------------------------------------------
class Timer
{
	public:
	Timer();

	void reset();
	unsigned int evaluate();

	private:
	unsigned int resetTime;
};
//-------------------------------------------------------------------------

#endif

