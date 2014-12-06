
#include <stdlib.h>
#include <sat/CNFGeneticOperators.h>
#include <util/Random.h>

#define INT_BITSIZE ( sizeof(int) * 8 )


//-----------------------------------------------------------------------------
CNFGeneticOperators *CNFGeneticOperators::create()
{
	return new CNFGeneticOperators();
}
//-----------------------------------------------------------------------------
void CNFGeneticOperators::release()
{
	delete this;
}
//-----------------------------------------------------------------------------
/**
 * Constructor.
 */
CNFGeneticOperators::CNFGeneticOperators()
{

}
//-----------------------------------------------------------------------------
/**
 * Sets the 'string size'.
 *
 * The string size is the number of different variables in the formula
 * that will be solved.
 */
void CNFGeneticOperators::setStringSize( int _stringSize )
{
    // Number of variables.
	stringSize = _stringSize;
	
	// The individual is represented as an array of integers.
	// The size is the stringSize / number of bits of an int.
	individualSize = (stringSize + INT_BITSIZE - 1)/ INT_BITSIZE;
}
//-----------------------------------------------------------------------------
/**
 * Stores the mutation probability.
 */
void CNFGeneticOperators::setMutationProbability( double _mutationProbability )
{
	mutationProbability = _mutationProbability;
}
//-----------------------------------------------------------------------------
/**
 * Initializes randomly a previously allocated random individual.
 */
void *CNFGeneticOperators::initializeRandomIndividual( void *individual )
{
	for ( int i = 0; i < stringSize; i++ )
	{
		setBit( individual, i, ( Random::s_urand() % 2 ? true : false ) );
	}

	return individual;
}
//-----------------------------------------------------------------------------
/**
 * Allocates and return a new individual.
 */
void *CNFGeneticOperators::allocateIndividual()
{
	return new int[individualSize];
}
//-----------------------------------------------------------------------------
/**
 * Releases a previously allocated individual.
 */
void CNFGeneticOperators::releaseIndividual( void *individual )
{
	delete[](int *)individual;
}
//-----------------------------------------------------------------------------
/**
 * Performs a genetic crossover.
 *
 * This method performs a crossover of two individuals src1 and src2
 * and stores the result in the individuals dest1 and dest2.
 */
void CNFGeneticOperators::crossover( void *src1, void *src2, void *dest1, void *dest2 )
{
    // Find the crossover site.
	int pos = (int)((double)stringSize*Random::s_generateUnitUniformVariable());

	// generate the offsprings
	offspring( pos, src1, src2, dest1 );
	offspring( pos, src2, src1, dest2 );	
}
//-----------------------------------------------------------------------------
/**
 * Generates one offspring of a crossover
 */
void CNFGeneticOperators::offspring( int pos, void *src1, void *src2, void *dest )
{
	int *idest = (int*)dest;
	int *isrc1 = (int*)src1;
	int *isrc2 = (int*)src2;

    // This is the index of the integer variable within the individuals
    // where the crossover will happen.  Remember that an individual
    // is represented as an array of integers.
	int crossoverInt = pos / INT_BITSIZE;
	// This is the index of the bit within the crossover integer,
	// where the crossover will happen.
	int crossoverBit = pos % INT_BITSIZE;

    // We copy all integers before the crossover site directly
    // from src1 to destination.
	for ( int i = 0; i <= crossoverInt; i++ )
	{
		*(idest + i ) = *(isrc1 + i );
	}

    // We apply a smart bit operation to copy only some bits
    // from src1[i] to destination[i] and the remaining bits from src2[i] to
    // destination[i].
	int pattern = ( 1 << crossoverBit ) - 1;
	
	*( idest + crossoverInt ) &= pattern;
	pattern = ~pattern;
	*( idest + crossoverInt ) |= (pattern & *( isrc2 + crossoverInt ));

    // copy the remaining integers after the crossover site
    // directly from src2 to destination.
	for ( int i2 = crossoverInt + 1; i2 < individualSize; i2++ )
	{
		*(idest + i2 ) = *( isrc2 + i2 );
	}
}
//-----------------------------------------------------------------------------
/**
 * Performs a mutation with a given probability.
 */
void CNFGeneticOperators::mutate( void *individual )
{
    // Creates a random value between zero and one.
	double v = Random::s_generateUnitUniformVariable();

    // If it is less than the mutation probability, we perform the mutation.
	if ( v <= mutationProbability )
	{
	    // Chose a random bit where the mutation will take place.
		int bit = (int)((double)stringSize * Random::s_generateUnitUniformVariable());
		// Get the value of the bit.
		bool   value = getBit( individual, bit );
		// change it.
		setBit( individual, bit, !value );
	}
}
//-----------------------------------------------------------------------------
/**
 * Returns a copy of an individual.
 */
void *CNFGeneticOperators::copyIndividual( void *src )
{
	int *individual = new int[individualSize];
	int *ptr = individual;
	int *isrc = (int *)src;

	for ( int i = 0; i < individualSize; i++ )
	{
		*ptr = *isrc;
		ptr++;isrc++;
	}

	return individual;
}
//-----------------------------------------------------------------------------
void CNFGeneticOperators::copyIndividual( void *src, void *dest )
{
	int *isrc = (int *)src;
	int *idest = (int*)dest;

	for ( int i = 0; i < individualSize; i++ )
	{
		*idest = *isrc;
		idest++;isrc++;
	}
}
//-----------------------------------------------------------------------------
/**
 * Sets a given bit to a given value.
 */
void CNFGeneticOperators::setBit( void *individual, int bit, bool value )
{
    // Index of the integer variable that holds the bit.
	int h_ndx = bit / INT_BITSIZE;
	// Index of the bit within that integer variable.
	int l_ndx = bit % INT_BITSIZE;

	int *vector = (int*)individual;

    // Do some bitwise operation.
	int t = 1;
	t <<= l_ndx;
	if ( value == true )
	{
		vector[h_ndx] |= t;
	}
	else
	{
		t = ~t;
		vector[h_ndx] &= t;
	}
}
//-----------------------------------------------------------------------------
/**
 * Returns the value of a given bit.
 */
bool CNFGeneticOperators::getBit( void *individual, int bit )
{
    // Index of the integer variable that holds the bit.
	int h_ndx = bit / INT_BITSIZE;
	// Index of the bit within that integer variable.
	int l_ndx = bit % INT_BITSIZE;

	int *vector = (int*)individual;

	int t = 1;
	t <<= l_ndx;
	return ( vector[h_ndx] & t ) == 0 ? false : true;
}
//-----------------------------------------------------------------------------

