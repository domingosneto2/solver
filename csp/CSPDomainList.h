
#ifndef _CSP_DOMAIN_LIST_H_
#define _CSP_DOMAIN_LIST_H_

#include <csp/CSPVariableDomain.h>

//---------------------------------------------------------------------------
/**
 * The list of variable domains of a CSP problem.
 * <p>
 * This class must be implemented for every CSP type.  There are two 
 * default implementations that might meet most needs:  VirtualCSPDomainList
 * and BasicCSPDomainList.  The former is used when the variable values
 * can be represented as an ordered set of integers.  The latter is used
 * when the variable values must be explictly represented.  When using
 * the VirtualCSPDomainList it's impossible to use any algorithm that
 * changes the variable domains, like the Arc-Consistency algorithm, because
 * in this class the domains are virtual and cannot be manipulated.
 *
 * @see VirtualCSPDomainList
 * @see BasicCSPDomainList
 */
class CSPDomainList
{
	public:
	virtual void release() = 0;
	virtual CSPDomainList *clone() const = 0;
	/**
	 * Returns the size of a given domain.
	 */
	virtual int getDomainSize( int variable ) const = 0;

	/**
	 * Returns a domain.
	 *
	 * This method is not implemented in the VirtualCSPDomainList class
	 * and will generate an assertion error if called.
	 *
	 * The underlying implementation will retain the ownership of the
	 * returned object.  If you want a copy of the object you should call
	 * getDomain( i )->clone();
	 */
	virtual CSPVariableDomain *getDomain( int i ) = 0;
	const CSPVariableDomain *getDomain( int i ) const
	{
		return ((CSPDomainList *)this)->getDomain( i );
	}
	
};
//---------------------------------------------------------------------------

#endif

