
#ifndef _ANT_SOLVER_H_
#define _ANT_SOLVER_H_

#include <csp/CSPProblem.h>
#include <aco/AntSolverGraph2.h>

//---------------------------------------------------------------------------
class AntSolver2
{
	public:
	AntSolver2();
	~AntSolver2();

	void setProblem( CSPProblem *problem );

	void setNumAnts( int numAnts );
	void setAlpha( double alpha );
	void setBeta( double beta );
	void setRo( double ro );
	void setUseLocalSearch( bool useLocalSearch );

	void setMinPheromone( double minPheromone );
	void setMaxPheromone( double maxPheromone );

	const CSPInterpretation &getResult();
	int getNumSteps();

	bool solve( int numSteps );

	private:
	int pickUninstantiatedVariable( const CSPInterpretation &interpretation, vector<int> &uninstantiatedVariables, int numUninstVars );
	int pickValue( int variable, vector< vector< double > > &valuesScore );
	void layPheromone( const CSPInterpretation &interpretation );
	void calculateValuesScore( vector< vector< double > > &valuesScore );
	double calculateValueScore( int var, int value );

	double getTrailFactor( int variable, int value );	

	void init();

	void printPheromones( int step, int maxSatisfiedConstraints );

	CSPInterpretation result;

	CSPProblem *problem;
	int numAnts;
	double alpha;
	double beta;
	double ro;
	double minPheromone;
	double maxPheromone;
	bool   useLocalSearch;
	int stepsPerformed;

	AntSolverGraph2 graph;
	vector< vector< int > >variableConstraints;	
};
//---------------------------------------------------------------------------

#endif

