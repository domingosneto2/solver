
#ifndef _DIRECT_ENCODING_CSP_TO_SAT_H_
#define _DIRECT_ENCODING_CSP_TO_SAT_H_

#include <vector>
using namespace std;

#include <sat2csp/CSP2SAT.h>

//---------------------------------------------------------------------------
class DirectEncodingCSP2SAT : public CSP2SAT
{
	public:
	static DirectEncodingCSP2SAT *create();
	virtual void release();
	virtual void setCSP( const CSPProblem *problem );
	virtual const CNFFormula getFormula() const;

	virtual bool getCSPInterpratation( const Interpretation &interpretation, CSPInterpretation &cspInterpretation );

	private:
	DirectEncodingCSP2SAT();
	~DirectEncodingCSP2SAT();

	// a vector that tells where the SAT variables that represent the values
	// of each CSP variable begin
	vector<int> cspVariableStart;
	
	// the converted formula.
	CNFFormula formula;
};
//---------------------------------------------------------------------------

#endif

