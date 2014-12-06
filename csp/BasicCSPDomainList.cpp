
#include <stdio.h>
#include <csp/BasicCSPDomainList.h>


//---------------------------------------------------------------------------
BasicCSPDomainList *BasicCSPDomainList::create()
{
	return new BasicCSPDomainList();
}
//---------------------------------------------------------------------------
CSPDomainList *BasicCSPDomainList::clone() const
{
	return new BasicCSPDomainList( *this );
}
//---------------------------------------------------------------------------
void BasicCSPDomainList::release()
{
	delete this;
}
//---------------------------------------------------------------------------
int BasicCSPDomainList::getDomainSize( int variable ) const
{
	return domains[variable]->getSize();
}
//---------------------------------------------------------------------------
void BasicCSPDomainList::setNumDomains( int numDomains )
{
	clearDomains();

	domains.resize( numDomains );
}
//---------------------------------------------------------------------------
CSPVariableDomain *BasicCSPDomainList::getDomain( int i )
{
	return domains[i];
}
//---------------------------------------------------------------------------
void BasicCSPDomainList::setDomain( int i , CSPVariableDomain *domain )
{
	domains[i] = domain;
}
//---------------------------------------------------------------------------
BasicCSPDomainList::BasicCSPDomainList()
{
	
}
//---------------------------------------------------------------------------
BasicCSPDomainList::BasicCSPDomainList( const BasicCSPDomainList &other )
{	
	assign( other );
}
//---------------------------------------------------------------------------
BasicCSPDomainList::~BasicCSPDomainList()
{
	clearDomains();
}
//---------------------------------------------------------------------------
void BasicCSPDomainList::assign( const BasicCSPDomainList &other )
{
	clearDomains();
	domains.resize( other.domains.size() );

	for ( int i = 0; i < domains.size(); i++ )
	{
		if ( other.domains[i] != NULL )
		{
			domains[i] = other.domains[i]->clone();
		}
		else
		{
			domains[i] = NULL;
		}
	}
}
//---------------------------------------------------------------------------
void BasicCSPDomainList::clearDomains()
{
	for ( int i = 0; i < domains.size(); i++ )
	{
		if ( domains[i] != NULL )
		{
			domains[i]->release();
			domains[i] = NULL;
		}
	}
}
//---------------------------------------------------------------------------

