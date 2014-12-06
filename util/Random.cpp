
#include <time.h>
#include <stdlib.h>
#include "Random.h"

/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

Random Random::r;
//---------------------------------------------------------------------------
Random::Random()
{
	mti = N + 1;
	seed( 1 );
}
//---------------------------------------------------------------------------
void Random::seed( unsigned long s )
{
	mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++)
	{
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}
//---------------------------------------------------------------------------
void Random::randomize()
{
	seed( (unsigned long)time( NULL ) );
}
//---------------------------------------------------------------------------
unsigned long Random::urand()
{
	unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};

    if (mti >= N) 
	{ 
		/* generate N words at one time */
        int kk;        

        for (kk=0;kk<N-M;kk++) 
		{
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) 
		{
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}
//---------------------------------------------------------------------------
double Random::generateUniformVariable( double min, double max )
{
	double delta = max - min;
	double rand_val = (double)urand() / (double)MT_RAND_MAX;
	return min + rand_val * delta;
}
//---------------------------------------------------------------------------
double Random::generateUnitUniformVariable()
{
	double rand_val = (double)urand() / (double)MT_RAND_MAX;
	return rand_val;
}
//---------------------------------------------------------------------------
double Random::pick( const vector< double > &values, double sum )
{
	double rand_val = generateUniformVariable( 0, sum );

	double acc = 0;
	for ( int i = 0; i < values.size(); i++ )
	{
		acc += values[i];
		if ( acc > rand_val )
		{
			return i;
		}
	}

	return values.size() - 1;
}
//---------------------------------------------------------------------------
bool Random::randomBoolean()
{
	return rand() % 2 == 0;
}
//---------------------------------------------------------------------------
int Random::randomInt( int min, int max )
{
	return (int)generateUniformVariable( min, max );
}
//---------------------------------------------------------------------------
void Random::s_seed( unsigned long i )
{
	r.seed( i );
}
//---------------------------------------------------------------------------
void Random::s_randomize()
{
	r.randomize();
}
//---------------------------------------------------------------------------
unsigned long Random::s_urand()
{
	return r.urand();
}
//---------------------------------------------------------------------------
double Random::s_generateUniformVariable( double min, double max )
{
	return r.generateUniformVariable( min, max );
}
//---------------------------------------------------------------------------
double Random::s_generateUnitUniformVariable()
{
	return r.generateUnitUniformVariable();
}
//---------------------------------------------------------------------------
bool Random::s_randomBoolean()
{
	return r.randomBoolean();
}
//---------------------------------------------------------------------------
double Random::s_pick( const vector< double > &values, double sum )
{
	return r.pick( values, sum );
}
//---------------------------------------------------------------------------
int Random::s_randomInt( int min, int max )
{
	return r.randomInt( min, max );
}
//---------------------------------------------------------------------------
