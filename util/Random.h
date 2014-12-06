
#ifndef _XRANDOM_H_
#define _XRANDOM_H_

#include <vector>
using namespace std;

#define __MT_SIZE   624
#define MT_RAND_MAX 4294967295UL

//---------------------------------------------------------------------------
/**
 * A utility class that centralizes the generation
 * of random variables.
 */
class Random
{	
	public:
	Random();

	void seed( unsigned long i );
	void randomize();
	unsigned long urand();
	double generateUniformVariable( double min, double max );
	double generateUnitUniformVariable();
	bool randomBoolean();
	double pick( const vector< double > &values, double sum );
	/**
	 * Returns a value ranging from min up to, but not including, max
	 */
	int randomInt( int min, int max );
	
	static void s_seed( unsigned long i );
	static void s_randomize();
	static unsigned long s_urand();
	static double s_generateUniformVariable( double min, double max );
	static double s_generateUnitUniformVariable();
	static bool s_randomBoolean();
	static double s_pick( const vector< double > &values, double sum );
	static int s_randomInt( int min, int max );

	private:
	unsigned long mt[__MT_SIZE]; /* the array for the state vector  */
	int mti; /* mti==N+1 means mt[N] is not initialized */

	static Random r;
};
//---------------------------------------------------------------------------

#endif

