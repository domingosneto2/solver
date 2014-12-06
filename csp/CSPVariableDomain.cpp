
#include <stdio.h>
#include <csp/CSPVariableDomain.h>


//---------------------------------------------------------------------------
CSPVariableDomain::CSPVariableDomain( int _domainSize )
{
	domainSize = _domainSize;
	values.resize( domainSize );
	for ( int i = 0; i < domainSize; i++ )
	{
		values[i] = NULL;
	}
}
//---------------------------------------------------------------------------
CSPVariableDomain::CSPVariableDomain( const CSPVariableDomain &other )
{
	domainSize = other.domainSize;

	values.resize( domainSize );

	for ( int i = 0; i < domainSize; i++ )
	{
		const CSPVariableValue * value = other.values[i];

		if ( value == NULL )
		{
			values[i] = NULL;
		}
		else
		{
			values[i] = value->clone();
		}
	}
}
//---------------------------------------------------------------------------
CSPVariableDomain::~CSPVariableDomain()
{
	clearValues();
}
//---------------------------------------------------------------------------
CSPVariableDomain *CSPVariableDomain::create( int domainSize )
{
	return new CSPVariableDomain( domainSize );
}
//---------------------------------------------------------------------------
CSPVariableDomain *CSPVariableDomain::clone() const
{
	return new CSPVariableDomain( *this );
}
//---------------------------------------------------------------------------
void CSPVariableDomain::release()
{
	delete this;
}
//---------------------------------------------------------------------------
void CSPVariableDomain::addValue( int index, CSPVariableValue *value )
{
	values[index] = value;
}
//---------------------------------------------------------------------------
int CSPVariableDomain::getSize() const
{
	return domainSize;
}
//---------------------------------------------------------------------------
const CSPVariableValue *CSPVariableDomain::getValue( int index ) const
{
	return values[index];
}
//---------------------------------------------------------------------------
void CSPVariableDomain::clearValues()
{
	for ( int i = 0; i < domainSize; i++ )
	{
		CSPVariableValue * value = values[i];

		if ( value != NULL )
		{
			value->release();
		}
	}
}
//---------------------------------------------------------------------------
//CSPVariableDomain &CSPVariableDomain::operator=( const CSPVariableDomain &other )
//{
//	assign( other );
//
//	return *this;
//}
//---------------------------------------------------------------------------
void CSPVariableDomain::removeValue( int index )
{
	if ( values[index] != NULL )
	{
		values[index]->release();
	}

	domainSize--;
	if ( index <  domainSize )
	{
		values[index] = values[domainSize];
		values.resize( domainSize );
	}
}
//---------------------------------------------------------------------------
void CSPVariableDomain::assign( const CSPVariableDomain &other )
{
	clearValues();
	domainSize = other.domainSize;	

	values.resize( domainSize );

	for ( int i = 0; i < domainSize; i++ )
	{
		const CSPVariableValue * value = other.values[i];

		if ( value == NULL )
		{
			values[i] = NULL;
		}
		else
		{
			values[i] = value->clone();
		}
	}
}
//---------------------------------------------------------------------------

