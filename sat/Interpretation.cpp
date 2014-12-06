
#include <sat/Interpretation.h>
#include <iostream>
#include <memory.h>


//---------------------------------------------------------------------------
Interpretation::Interpretation( int _size )
{
	size = _size;

	// Calculamos o vetor para conter todas as vari�veis
	vectorSize = size / sizeof( inner_type );
	if ( size % sizeof( inner_type ) != 0 )
	{
		vectorSize ++;
	}

	vector = new inner_type[vectorSize];
	owner = true;
}
//---------------------------------------------------------------------------
Interpretation::Interpretation( const Interpretation &other )
{
	size = other.size;
	vectorSize = other.vectorSize;
	vector = new inner_type[vectorSize];

	owner = true;

	memcpy( vector, other.vector, vectorSize * sizeof( inner_type ) );
}
//---------------------------------------------------------------------------
Interpretation::~Interpretation()
{
	if ( owner )
		delete[]vector;
}
//---------------------------------------------------------------------------
void Interpretation::assign( const Interpretation &other )
{
	delete[]vector;

	size = other.size;
	vectorSize = other.vectorSize;
	vector = new inner_type[vectorSize];

	memcpy( vector, other.vector, vectorSize * sizeof( inner_type ) );
}
//---------------------------------------------------------------------------
void Interpretation::assign( void *_vector, int _size )
{
	if ( owner )
	{
		delete[] vector;
	}	
	owner = false;

	vector = (inner_type*)_vector;
	size = _size;
	vectorSize = size / sizeof( inner_type );
	if ( size % sizeof( inner_type ) != 0 )
	{
		vectorSize ++;
	}
}
//---------------------------------------------------------------------------
void Interpretation::assignCopy( void *_vector, int _size )
{
	if ( owner )
	{
		delete[] vector;
	}

	owner = true;

	size = _size;
	vectorSize = ( size + sizeof( inner_type ) - 1 ) / sizeof( inner_type );
	
	vector = new inner_type[vectorSize];

	memcpy( vector, _vector, vectorSize * sizeof( inner_type ) );
}
//---------------------------------------------------------------------------
Interpretation &Interpretation::operator=( const Interpretation &other )
{
	assign( other );

	return *this;
}
//---------------------------------------------------------------------------
bool Interpretation::getValue( int index ) const
{
	int h_ndx = index / ( sizeof( inner_type ) * 8 );
	int l_ndx = index % ( sizeof( inner_type ) * 8 );

	inner_type t = 1;
	t <<= l_ndx;
	return ( vector[h_ndx] & t ) == 0 ? false : true;
}
//---------------------------------------------------------------------------
void Interpretation::setValue( int index, bool value )
{
	int h_ndx = index / ( sizeof( inner_type ) * 8 );
	int l_ndx = index % ( sizeof( inner_type ) * 8 );

	//cout << "h_ndx: " << h_ndx << endl;
	//cout << "l_ndx: " << l_ndx << endl;

	inner_type t = 1;
	t <<= l_ndx;

	//cout << "t: " << t << endl;
	if ( value == true )
	{
		vector[h_ndx] |= t;
	}
	else
	{
		t = ~t;
		vector[h_ndx] &= t;
	}
}
//---------------------------------------------------------------------------
int Interpretation::getSize() const
{
	return size;
}
//---------------------------------------------------------------------------
bool Interpretation::getValue( void *_vector, int index )
{
	int h_ndx = index / ( sizeof( inner_type ) * 8 );
	int l_ndx = index % ( sizeof( inner_type ) * 8 );

	inner_type *vector = (inner_type*)_vector;

	inner_type t = 1;
	t <<= l_ndx;
	return ( vector[h_ndx] & t ) == 0 ? false : true;
}
//---------------------------------------------------------------------------
void Interpretation::setValue( void *_vector, int index, bool value )
{
	int h_ndx = index / ( sizeof( inner_type ) * 8 );
	int l_ndx = index % ( sizeof( inner_type ) * 8 );

	inner_type *vector = (inner_type*)_vector;

	inner_type t = 1;
	t <<= l_ndx;
	if ( value == true )
	{
		vector[h_ndx] |= t;
	}
	else
	{
		t = ~t;
		vector[h_ndx] &= t;
	}
}
//---------------------------------------------------------------------------
void Interpretation::flip( int index )
{
	if ( getValue( index ) )
	{
		setValue( index, false );
	}
	else
	{
		setValue( index, true );
	}
}
//---------------------------------------------------------------------------
void Interpretation::flip( void *vector, int index )
{
	if ( getValue( vector, index ) )
	{
		setValue( vector, index, false );
	}
	else
	{
		setValue( vector, index, true );
	}
}
//---------------------------------------------------------------------------

