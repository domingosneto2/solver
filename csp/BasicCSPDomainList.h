
#include <csp/CSPDomainList.h>
#include <csp/CSPVariableDomain.h>


//---------------------------------------------------------------------------
class BasicCSPDomainList : public CSPDomainList
{
	public:
	static BasicCSPDomainList *create();

	virtual CSPDomainList *clone() const;
	void release();	

	/**
	 * Inherited from CSPDomainList.
	 */
	int getDomainSize( int variable ) const;

	/**
	 * Sets the number of domains in the list.
	 *
	 * Clears all domains previously set with the setDomain method.
	 */
	void setNumDomains( int numDomains );

	/**
	 * Returns a domain.
	 * <p>
	 * Note that the object returned still belongs to this class.
	 * If you want to retain the ownership of the object returned by
	 * this method you should call getDomain( i )->clone();
	 */
	CSPVariableDomain *getDomain( int i );

	/**
	 * Sets a domain.
	 *
	 * Not that the ownership of the object passed in the 'domain' argument
	 * will belong to this class.  If you want to retain the ownership
	 * of the CSPVariableDomain object you should call 
	 * setDomain( domain->clone() );
	 */
	void setDomain( int i, CSPVariableDomain *domain );

	private:
	BasicCSPDomainList();
	explicit BasicCSPDomainList( const BasicCSPDomainList &other );
	virtual ~BasicCSPDomainList();
	void assign( const BasicCSPDomainList &other );
	void clearDomains();
	vector< CSPVariableDomain * > domains;
};
//---------------------------------------------------------------------------

