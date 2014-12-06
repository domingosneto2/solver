

#include <vector>
using namespace std;

#include <sat2csp/CSP2SAT.h>

#ifndef _LOG_ENCODING_CSP_2_SAT_H
#define _LOG_ENCODING_CSP_2_SAT_H

//---------------------------------------------------------------------------
/**
 * A class that translates CSP instances to SAT instances using the
 * log encoding.  This class has also a method to translate a SAT
 * interpretation into the corresponding CSP assignment.
 */
class LogEncodingCSP2SAT : public CSP2SAT
{
	public:
	static LogEncodingCSP2SAT *create();
	virtual void release();	
	virtual void setCSP( const CSPProblem *problem );
	virtual const CNFFormula getFormula() const;

	virtual bool getCSPInterpratation( const Interpretation &interpretation, CSPInterpretation &cspInterpretation );


	private:
	LogEncodingCSP2SAT();
	virtual ~LogEncodingCSP2SAT();

	CNFFormula formula;
	vector<int> cspVariablesStart;
	vector<int> cspVariablesSize;
	vector<int> cspDomainSizes;
	int cspNumVars;
	int satNumVars;

	int getVarRepresentation( int value );
	
};
//---------------------------------------------------------------------------

#endif

