
#include <stdio.h>
#include <assert.h>


#include <csp/VirtualCSPDomainList.h>


//---------------------------------------------------------------------------
VirtualCSPDomainList *VirtualCSPDomainList::create()
{
	return new VirtualCSPDomainList();
}
//---------------------------------------------------------------------------
CSPDomainList *VirtualCSPDomainList::clone() const
{
	return new VirtualCSPDomainList( *this );
}
//---------------------------------------------------------------------------
void VirtualCSPDomainList::release()
{
	delete this;
}
//---------------------------------------------------------------------------
VirtualCSPDomainList::VirtualCSPDomainList()
{
	numDomains = 0;
	commonSize = 0;
}
//---------------------------------------------------------------------------
VirtualCSPDomainList::VirtualCSPDomainList( const VirtualCSPDomainList &other )
{
	numDomains = 0;
	commonSize = 0;
	assign( other );
}
//---------------------------------------------------------------------------
VirtualCSPDomainList::~VirtualCSPDomainList()
{

}
//---------------------------------------------------------------------------
void VirtualCSPDomainList::assign( const VirtualCSPDomainList &other )
{
	sizes = other.sizes;
	equalSizes = other.equalSizes;
	commonSize = other.commonSize;
	numDomains = other.numDomains;
}
//---------------------------------------------------------------------------
void VirtualCSPDomainList::setNumDomains( int i, bool _equalSizes )
{
	numDomains = i;
	equalSizes = _equalSizes;
}
//---------------------------------------------------------------------------
void VirtualCSPDomainList::setCommonSize( int size )
{
	commonSize = size;
}
//---------------------------------------------------------------------------
void VirtualCSPDomainList::setDomainSize(int domain, int size )
{
	if ( equalSizes == false )
	{
		sizes[domain] = size;
	}
}
//---------------------------------------------------------------------------
int VirtualCSPDomainList::getDomainSize( int variable ) const
{
	if ( equalSizes )
	{
		return commonSize;
	}
	return sizes[variable];
}
//---------------------------------------------------------------------------
CSPVariableDomain *VirtualCSPDomainList::getDomain( int i )
{
	assert( ("Method getDomain not implemented in class VirtualCSPDomainList", 0) );
	return NULL;
}
//---------------------------------------------------------------------------

