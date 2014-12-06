
#ifndef _ANT_SOLVER_GRAPH_H_
#define _ANT_SOLVER_GRAPH_H_

#include <vector>
#include <map>
using namespace std;

#include <csp/CSPProblem.h>


//---------------------------------------------------------------------------
/**
 * A class that represents the ant solver graph.
 *
 */
class AntSolverGraph2
{
	public:
	AntSolverGraph2();
	~AntSolverGraph2();

	void init( double minPheromone, double maxPheromone, double ro, const CSPProblem *problem );
	double getPheromone( int var, int value );

	void addPheromone( int var, int value, double pheromone );
	double getMaxCurValue();
	double getMinCurValue();

	void evaporate();

	private:
	double minPheromone;
	double maxPheromone;


	double ro;
	
	// the matrix with all pheromone values
	vector< double > pheromones;
	int numValues;
	vector< int > variableStart;
};
//---------------------------------------------------------------------------

#endif

