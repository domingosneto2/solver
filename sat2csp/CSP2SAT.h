
#ifndef _CSP_2_SAT_H_
#define _CSP_2_SAT_H_

#include <csp/CSPProblem.h>
#include <sat/CNFFormula.h>

//---------------------------------------------------------------------------
/**
 * Base class for CSP to SAT converters.
 *
 * There will be a derived class for each implemented encoding (eg, direct
 * encoding and log encoding).
 * 
 * This class has methods for setting the CSP problem to be converted,
 * and then methods to retrieve the corresponding formula.  There is also
 * a method that will translate a SAT interpretation into a CSP candidate
 * solution.
 */
class CSP2SAT
{
	public:
	virtual void release() = 0;	
	virtual void setCSP( const CSPProblem *problem ) = 0;
	virtual const CNFFormula getFormula() const = 0;

	virtual bool getCSPInterpratation( const Interpretation &interpretation, CSPInterpretation &cspInterpretation ) = 0;

	protected:
	virtual ~CSP2SAT();
};
//---------------------------------------------------------------------------

#endif

