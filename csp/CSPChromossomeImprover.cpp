#include <iostream>
#include <csp/CSPChromossomeImprover.h>
#include <csp/CSPProblem.h>
#include <util/Random.h>


//---------------------------------------------------------------------------
CSPChromossomeImprover *CSPChromossomeImprover::create()
{
	return new CSPChromossomeImprover();
}
//---------------------------------------------------------------------------
void CSPChromossomeImprover::release()
{
	delete this;
}
//---------------------------------------------------------------------------
CSPChromossomeImprover::CSPChromossomeImprover()
{
	bQuickLoop   = false;
	bPermutation = true;
	bStrictFlip  = false;
	bInit        = false;
}
//---------------------------------------------------------------------------
CSPChromossomeImprover::~CSPChromossomeImprover()
{

}
//---------------------------------------------------------------------------
void CSPChromossomeImprover::setProblem( CSPProblem *_problem )
{
	problem = _problem;
	numVariables = problem->getNumVars();
	bInit = false;
	permutation.resize( 0 );
	variableConstraints.resize( 0 );
}
//---------------------------------------------------------------------------
void CSPChromossomeImprover::improve( void *individual )
{
	if ( !bInit )
	{
		init();
	}

	CSPInterpretation *interpretation = (CSPInterpretation *)individual;

	if ( bPermutation )
	{
		for ( int k2 = 0; k2 < numVariables / 2; k2++ )
		{
			int aux = permutation[k2];
			int random = Random::s_urand() % numVariables;
			permutation[k2] = permutation[random];
			permutation[random] = aux;
		}
	}

	bool bImproved = true;

	while ( bImproved )
	{
		bImproved = false;

		for ( int i = 0; i < numVariables; i++ )
		{
			int variable = permutation[i];
			int domainSize = problem->getDomainList()->getDomainSize( variable );
			int value = interpretation->getVariableValue( variable );
			int numSatisfiedConstraints = getNumVariableSatisfiedConstraints( variable, interpretation );

			if ( numSatisfiedConstraints == variableConstraints[variable].size() )
			{
				continue;
			}
			
			for ( int j = 0; j< domainSize; j++ )
			{
				interpretation->setVariableValue( variable, j );
				int newNumSatisfiedConstraints = getNumVariableSatisfiedConstraints( variable, interpretation );			
				if ( newNumSatisfiedConstraints > numSatisfiedConstraints && bQuickLoop == false )
				{
					bImproved = true;
				}

				if ( newNumSatisfiedConstraints > numSatisfiedConstraints )
				{
					numSatisfiedConstraints = newNumSatisfiedConstraints;
					value = j;
				}
				else if ( newNumSatisfiedConstraints == numSatisfiedConstraints && bStrictFlip == false )
				{
					numSatisfiedConstraints = newNumSatisfiedConstraints;
					value = j;
				}
				else
				{
					interpretation->setVariableValue( variable, value );
				}
			}

		}
	}
}
//---------------------------------------------------------------------------
/**
 * If true, only one step of the loop will be performed
 */
void CSPChromossomeImprover::useQuickLoop( bool _bQuickLoop )
{
	bQuickLoop = _bQuickLoop;
}
//---------------------------------------------------------------------------
/**
 * If true, when iterating over the variables, the algorithm
 * will use a random permutation to chose the order in wich
 * the variables will be tested.
 */
void CSPChromossomeImprover::usePermutation( bool _bPermutation )
{
	bPermutation = _bPermutation;
}
//---------------------------------------------------------------------------
/**
 * If true, a variable value will only be changed if the 
 * change makes the number of satisfied constraints improve.
 * If false, the variable will be changed even if the
 * number of satisfied clauses stays the same.
 * Setting this flag to false allows a broader exploration of the
 * search space.
 */
void CSPChromossomeImprover::changeOnStrictImprove( bool _bStrictFlip )
{
	bStrictFlip = _bStrictFlip;
}
//---------------------------------------------------------------------------
/**
 * Performs a lot of one-time initializations.
 */
void CSPChromossomeImprover::init()
{
    // Creates the permutation vector.
    // This vector contains the order in with the variables
    // will be visited in each pass.  If the users didn't ask
    // to use a permutation, the variables will appear here in
    // the correct order.
	permutation.resize( numVariables );

	// Initialize the permutation vector.
	for ( int k = 0; k < numVariables; k++ )
	{
		permutation[k] = k;
	}

    // Scramble the vector if the user asked us to do so.
	if ( bPermutation )
	{
		for ( int k2 = 0; k2 < numVariables; k2++ )
		{
			int aux = permutation[k2];
			int random = Random::s_urand() % numVariables;
			permutation[k2] = permutation[random];
			permutation[random] = aux;
		}
	}

	variableConstraints.resize( numVariables );
	// Initialize the vector of variable constraints
	//int numConstraints = problem->getConstraintList()->getNumConstraints();
	//for ( int i = 0; i < numConstraints; i++ )
	//{
	//	int var1 = problem->getConstraintList()->getVar1( i );
	//	int var2 = problem->getConstraintList()->getVar2( i );

	//	variableConstraints[var1].push_back( i );
	//	variableConstraints[var2].push_back( i );
	//}

	int i = 0;
	CSPConstraintList *constraintList = problem->getConstraintList()->clone();
	constraintList->resetIterator();
	while ( constraintList->nextConstraint() )
	{
		int var1 = constraintList->getVar1();
		int var2 = constraintList->getVar2();

		variableConstraints[var1].push_back( i );
		variableConstraints[var2].push_back( i );
		i++;
	}


	bInit = true;
}
//---------------------------------------------------------------------------
int CSPChromossomeImprover::getNumVariableSatisfiedConstraints( int variable, CSPInterpretation *interpretation )
{
	int numSatisfiedConstraints = 0;

	const CSPConstraintList *constraintList = problem->getConstraintList();
			
	for ( int i = 0; i < variableConstraints[variable].size(); i++ )
	{
		int constraintIndex = variableConstraints[variable][i];
		if ( constraintList->passes( i, *interpretation ) )
		{
			numSatisfiedConstraints++;
		}
	}

	return numSatisfiedConstraints;
}
//---------------------------------------------------------------------------

