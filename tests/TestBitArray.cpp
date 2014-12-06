
#include <iostream>
#include <util/BitArrayOps.h>
#include <util/Random.h>

void printArray( void *array, int size )
{
	for ( int i = 0; i < size; i++ )
	{
		if ( BitArrayOps::getValue( array, i ) )
		{
			cout << "1";
		}
		else
		{
			cout << "0";
		}
	}
	cout << endl;
}

int testBitArray( int argc, char **argv )
{
	int size1 = 80, size2 = 104;
	void *array1 = BitArrayOps::create( size1 );
	void *array2 = BitArrayOps::create( size2 );
	void *array3 = BitArrayOps::create( size1 + 10 );
	void *array4 = BitArrayOps::create( size1 );

	int i;
	for ( i = 0; i < size1; i++ )
	{
		BitArrayOps::setValue( array1, i, Random::s_randomBoolean() );
	}

	printArray( array1, size1 );	

	for ( i = 0; i < size2 - size1; i++ )
	{
		BitArrayOps::setValue( array2, i, Random::s_randomBoolean() );
	}

	printArray( array2, size2 - size1 );

	BitArrayOps::subString( array1, 0, size1, array2, size2 - size1 );

	printArray( array2, size2 );

	BitArrayOps::subString( array2, size2 - size1, size1, array3, 10 );

	printArray( array3, size1 + 10 );

	BitArrayOps::subString( array3, 10, size1, array4, 0 );

	printArray( array4, size1 );

	cout << BitArrayOps::compare( array1, size1, array4, size1 ) << endl;
	cout << BitArrayOps::compare( array1, size1, array2, size2 ) << endl;

	return 0;
	
}

