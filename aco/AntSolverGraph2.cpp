
#include <iostream>
#pragma warning(disable: 4786)

#include <aco/AntSolverGraph2.h>

//---------------------------------------------------------------------------
AntSolverGraph2::AntSolverGraph2()
{
}
//---------------------------------------------------------------------------
AntSolverGraph2::~AntSolverGraph2()
{
}
//---------------------------------------------------------------------------
void AntSolverGraph2::init( double _minPheromone, double _maxPheromone, double _ro, const CSPProblem *problem )
{
	minPheromone = _minPheromone;
	maxPheromone = _maxPheromone;
	ro = _ro;

	numValues = 0;
	int numVars = problem->getNumVars();
	variableStart.resize( 0 );
	for ( int i = 0; i < numVars; i++ )
	{
		variableStart.push_back( numValues );
		numValues += problem->getDomainList()->getDomainSize( i );
	}

	pheromones.resize( numValues );
	for ( int j = 0; j < numValues; j++ )
	{
		pheromones[j] = maxPheromone;
	}
}
//---------------------------------------------------------------------------
double AntSolverGraph2::getPheromone( int var, int value )
{
	int x = variableStart[var] + value;

	return pheromones[x];
}
//---------------------------------------------------------------------------
void AntSolverGraph2::evaporate()
{
	for ( int i = 0; i < numValues; i++ )
	{
		pheromones[i] *= ro;		
		if ( pheromones[i] < minPheromone )
		{
			pheromones[i] = minPheromone;
		}
	}
	
}
//---------------------------------------------------------------------------
void AntSolverGraph2::addPheromone( int var, int value, double pheromone )
{
	int index = variableStart[var] + value;

	pheromones[index] += pheromone;
	if ( pheromones[index] > maxPheromone )
	{
		pheromones[index] = maxPheromone;
	}
}
//---------------------------------------------------------------------------
double AntSolverGraph2::getMaxCurValue()
{
	int i;
	int max = 0;
	for ( i = 0; i < pheromones.size(); i++ )
	{
		if ( pheromones[i] > max )
		{
			max = pheromones[i];
		}
	}

	return max;
}
//---------------------------------------------------------------------------
double AntSolverGraph2::getMinCurValue()
{
	int i;
	int min = pheromones[0];
	for ( i = 0; i < pheromones.size(); i++ )
	{
		if ( pheromones[i] < min )
		{
			min = pheromones[i];
		}
	}

	return min;
}
//---------------------------------------------------------------------------
