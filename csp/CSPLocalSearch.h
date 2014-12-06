
#ifndef _CSP_LOCAL_SEARCH_H_
#define _CSP_LOCAL_SEARCH_H_

#include <csp/CSPInterpretation.h>

//---------------------------------------------------------------------------
/**
 * A base class for local search algoritms for the CSP.
 */
class CSPLocalSearch
{
	public:
	virtual void release() = 0;

	virtual void localSearch( const CSPInterpretation &source, CSPInterpretation &dest ) = 0;
};
//---------------------------------------------------------------------------

#endif
