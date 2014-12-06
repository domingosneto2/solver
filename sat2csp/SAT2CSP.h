
#ifndef _SAT_2_CSP_H_
#define _SAT_2_CSP_H_

#include <sat/CNFFormula.h>
#include <csp/CSPProblem.h>

//---------------------------------------------------------------------------
/**
 * Base class for SAT to CSP converters.
 *
 * There will be a derived class for each implemented encoding.
 *
 * This class has methods for setting the SAT problem to be converted,
 * and then methods to retrieve the corresponding CSP.  There is also
 * a method that will translate a CSP candidate solution into a
 * SAT interpretation.
 */
class SAT2CSP
{
	public:
	virtual void release() = 0;
	virtual void setFormula( const CNFFormula *formula ) = 0;
	virtual CSPProblem *getProblem() const = 0;

	virtual bool getSATInterpretation( const CSPInterpretation &cspi, Interpretation &sati ) = 0;
};
//---------------------------------------------------------------------------

#endif
