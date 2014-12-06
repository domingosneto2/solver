
#ifndef _MIN_CONFLICTS_H_
#define _MIN_CONFLICTS_H_

#include <vector>

#include <csp/CSPProblem.h>
#include <csp/CSPLocalSearch.h>

//---------------------------------------------------------------------------
/**
 * A class that implements the Min-Conflicts heuristic for local search.
 */
class MinConflicts : public CSPLocalSearch
{
	public:
	static MinConflicts *create( CSPProblem *problem );
	virtual void release();
	virtual void localSearch( const CSPInterpretation &source, CSPInterpretation &dest );

	void setNumSidewaysSteps( int numSidewaysSteps );

	protected:
	MinConflicts( CSPProblem *problem );
	~MinConflicts();

	private:
	void init( CSPProblem *problem );
	CSPProblem *problem;	
	vector< vector< int > >variablesConstraints;
	int numSidewaysSteps;

	void changeConflictCount( int var, int count, vector< int > &numConflicts, 
	                          vector< int > &conflictingVariables,
                                  vector< int > &conflictingIndex,
		                  int &numConflictingVars );
};
//---------------------------------------------------------------------------

#endif
