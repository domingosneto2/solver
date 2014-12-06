
#include <csp/CSPGeneticOperators.h>
#include <util/Random.h>


//---------------------------------------------------------------------------
CSPFitnessEvaluator *CSPFitnessEvaluator::create()
{
	return new CSPFitnessEvaluator();
}
//---------------------------------------------------------------------------
void CSPFitnessEvaluator::release()
{
	delete this;
}
//---------------------------------------------------------------------------
CSPFitnessEvaluator::CSPFitnessEvaluator()
{
	// we still didn't get a result
	bLastIsResult = false;
}
//---------------------------------------------------------------------------
CSPFitnessEvaluator::~CSPFitnessEvaluator()
{
}
//---------------------------------------------------------------------------
void CSPFitnessEvaluator::setProblem( const CSPProblem *_problem )
{
	// Store the problem definition.
	// This is required so we can evaluate the individuals.
	problem = _problem;
}
//---------------------------------------------------------------------------
double CSPFitnessEvaluator::evaluate( void *individual )
{	
	bLastIsResult = false;

	// The individual is actually an interpretation object
	CSPInterpretation *interpretation = (CSPInterpretation *)individual;

	// Get the number of satisfied constraints.  This is going to be
	// our fitness value.
	int numSatisfiedConstraints = problem->getNumSatisfiedConstraints( *interpretation );
	
	// If all constraints are satisfied, we have a result, se we set the
	// corresponding flag.
	if ( numSatisfiedConstraints == problem->getConstraintList()->getNumConstraints() )
	{
		bLastIsResult = true;
	}

	// return the fitness value
	return numSatisfiedConstraints;
}
//---------------------------------------------------------------------------
bool CSPFitnessEvaluator::lastIsResult()
{
	return bLastIsResult;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
CSPGeneticOperators *CSPGeneticOperators::create()
{
	return new CSPGeneticOperators();
}
//---------------------------------------------------------------------------
void CSPGeneticOperators::release()
{
	delete this;
}
//---------------------------------------------------------------------------
CSPGeneticOperators::CSPGeneticOperators()
{
}
//---------------------------------------------------------------------------
CSPGeneticOperators::~CSPGeneticOperators()
{
}
//---------------------------------------------------------------------------
void CSPGeneticOperators::setProblem( const CSPProblem *_problem )
{
	problem = _problem;
}
//---------------------------------------------------------------------------
void CSPGeneticOperators::setMutationProbability( double _mutationProbability )
{
	mutationProbability = _mutationProbability;
}
//---------------------------------------------------------------------------
void *CSPGeneticOperators::allocateIndividual()
{
	return new CSPInterpretation( problem->getNumVars() );
}
//---------------------------------------------------------------------------
/**
 * Randomly initializes a previously create individual.
 */
void *CSPGeneticOperators::initializeRandomIndividual( void *individual )
{
	// cast it to the appropriate type:  a interprettion object
	CSPInterpretation *interpretation = (CSPInterpretation *)individual;

	int numVars = problem->getNumVars();

	// For each variable, set it to a random value within it's domain
	for ( int i = 0; i < numVars; i++ )
	{
		int domainSize = problem->getDomainList()->getDomainSize( i );
		int value      = Random::s_urand() % domainSize;

		interpretation->setVariableValue( i, value );
	}

	// returns the individual (that wasn't really required)
	return individual;
}
//---------------------------------------------------------------------------
/**
 * Releases an individual previously allocated by a call to
 * allocateIndividual
 */
void CSPGeneticOperators::releaseIndividual( void *individual )
{
	CSPInterpretation *interpretation = (CSPInterpretation *)individual;
	delete interpretation;
}
//---------------------------------------------------------------------------
/**
 * Returns a copy of a previously allocated individual.
 */
void *CSPGeneticOperators::copyIndividual( void *src )
{
	CSPInterpretation *interpretation = (CSPInterpretation *)src;

	return new CSPInterpretation( *interpretation );
}
//---------------------------------------------------------------------------
/**
 * Copies one individual into another.
 */
void CSPGeneticOperators::copyIndividual( void *src, void *dest )
{
	CSPInterpretation *interpretationSrc = (CSPInterpretation *)src;
	CSPInterpretation *interpretationDest = (CSPInterpretation *)dest;

	*interpretationDest = *interpretationSrc;
}
//---------------------------------------------------------------------------
/**
 * Perform a crossover within two individuals and store the result
 * in a third individual previously allocated.
 */
void CSPGeneticOperators::crossover( void *individual1, void *individual2, void *_dest1, void *_dest2 )
{
	// How to crossover?
	// The simplest way:  at every variable, throw a coin to find from
	// wich parent the value will come from
	CSPInterpretation *src1= (CSPInterpretation *)individual1;
	CSPInterpretation *src2= (CSPInterpretation *)individual2;
	CSPInterpretation *dest1= (CSPInterpretation *)_dest1;
	CSPInterpretation *dest2= (CSPInterpretation *)_dest2;

	int numVariables = dest1->getNumVariables();
	for ( int i = 0; i < numVariables; i++ )
	{
		int pick = Random::s_urand() % 2;
		if ( pick == 0 )
		{
			dest1->setVariableValue( i, src1->getVariableValue( i ) );
			dest2->setVariableValue( i, src2->getVariableValue( i ) );

		}
		else
		{
			dest1->setVariableValue( i, src2->getVariableValue( i ) );
			dest2->setVariableValue( i, src1->getVariableValue( i ) );
		}
	}
}
//---------------------------------------------------------------------------
/**
 * Mutate an individual with a given probability.
 *
 * The mutation is done by picking a variable at random and then setting
 * a random value from it's domain.
 */
void CSPGeneticOperators::mutate( void *individual )
{
	CSPInterpretation *interpretation = (CSPInterpretation *)individual;

	// throw a biased coin to check wether we must perform the mutation or not.
	double r = (double)Random::s_generateUnitUniformVariable();

	// If we must perform the mutation...
	if ( r <= mutationProbability )
	{
		// pick a random var
		int randVar = Random::s_urand() % problem->getNumVars();
		// pick a random value from it's domain
		int randVal = Random::s_urand() % problem->getDomainList()->getDomainSize( randVar );

		// set the variable's value in the interpretation object.
		interpretation->setVariableValue( randVar, randVal );
	}
}
//---------------------------------------------------------------------------

