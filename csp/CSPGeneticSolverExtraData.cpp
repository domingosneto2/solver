
#include <stdio.h>
#include <csp/CSPGeneticSolverExtraData.h>

//---------------------------------------------------------------------------
CSPGeneticSolverExtraData *CSPGeneticSolverExtraData::create( CSPProblem *problem )
{
	return new CSPGeneticSolverExtraData( problem );
}
//---------------------------------------------------------------------------
void CSPGeneticSolverExtraData::release()
{
	delete this;
}
//---------------------------------------------------------------------------
CSPGeneticSolverExtraData::CSPGeneticSolverExtraData( CSPProblem *_problem )
{
	problem = _problem;
}
//---------------------------------------------------------------------------
CSPGeneticSolverExtraData::~CSPGeneticSolverExtraData()
{
	if ( problem != NULL )
	{
		problem->release();
	}
}
//---------------------------------------------------------------------------
