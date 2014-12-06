
#ifndef _VIRTUAL_CSP_DOMAIN_LIST_H_
#define _VIRTUAL_CSP_DOMAIN_LIST_H_

#include <csp/CSPDomainList.h>

//---------------------------------------------------------------------------
/**
 * A Virtual domain list.
 * <p>
 * This class is called a Virtual domain list because it doesn't store
 * the actual domains.  It is useful when the number of domains or each
 * domain's size is huge, and the variable values can be
 * represente as an ordered set of sequential integers.
 * <p>
 * The NQueensCSP uses this class as a domain list, making it possible
 * to create problems with millions domains.
 */
class VirtualCSPDomainList : public CSPDomainList
{
	public:
	static VirtualCSPDomainList *create();

	virtual CSPDomainList *clone() const;
	void release();

	/**
	 * Sets the number of domains.
	 * <p>
	 * This class sets the number of domains.
	 * the equalSizes argument indicates wether all domains
	 * in this list have the same size or not.
	 * If all domains have the same size, , the class will store one 
	 * single integer with the common size.  If the sizes are no the same,
	 * the class will store a vector with one size for each domain.
	 */
	void setNumDomains( int i, bool equalSizes );

	/**
	 * Sets the common size.
	 * <p>
	 * This method should only be called if the equalSizes parameter
	 * in the setNumDomains method was set to true.
	 */
	void setCommonSize( int size );

	/**
	 * Sets a given domain size.
	 * <p>
	 * This method should only be called if the equalSizes parameter
	 * in the setNumDomains method was set to false.
	 */
	void setDomainSize(int domain, int size );

	/**
	 * Returns the size of a given domain.
	 * <p>
	 * If the equalSizes parameter of the setNumDomains method
	 * was set to true, this method will return the common value.
	 * Otherwise, it will return the individual size of the domain.
	 */
	virtual int getDomainSize( int variable ) const;

	/**
	 * Not implemented.  If called, this method will
	 * generate an assertion error.
	 */
	virtual CSPVariableDomain *getDomain( int i );

	private:
	void assign( const VirtualCSPDomainList &other );
	VirtualCSPDomainList();
	explicit VirtualCSPDomainList( const VirtualCSPDomainList &other );
	virtual ~VirtualCSPDomainList();

	vector< int > sizes;
	bool equalSizes;
	int commonSize;
	int numDomains;
	
};
//---------------------------------------------------------------------------

#endif

