
#ifndef _BIT_ARRAY_OPS_H_
#define _BIT_ARRAY_OPS_H_

//-----------------------------------------------------------------------------
/**
 * A class that implements several common operatiosn on bit arrays.
 *
 * It is important to notice that a bit array doesn't store it's length,
 * so it is up to the user to ensure that the indexes passed as parameters
 * to the several methods are valid.
 */
class BitArrayOps
{
	public:
	/**
	 * Returns the value of a given bit in a bit array.
	 */
	static bool getValue( void *array, int index );
	/**
	 * Sets the value of a given bit in a bit array.
	 */
	static void setValue( void *array, int index, bool value );

    /**
     * Creates a new bit array.
     */
	static void *create( int nBits );
	
	/**
	 * Releases a bit array.
	 */
	static void release( void *array );

    /**
     * Copies n bits from a source bit array into a destination bit array.
     */
	static void copy( void *src, void *dest, int size );

    /**
     * Compares two bit arrays and returns < 0 if array1 is lesser than array2,
     * 0 if array1 is equal to array2 and > 1 if array1 is greater than array2.
     *
     * The meaning of lesses and greater doesn't doesn't refer to the arrays' sizes,
     * but to their lexigraphic order.
     */
	static int  compare( void *array1, int size1, void *array2, int size2 );

    /**
     * Copies a substring from a an array, starting from 'start', into a destination
     * array, starting from startDest.
     */
	static void subString( void *array, int start, int size, void *dest, int startDest );
	
	/**
	 * Concatenates two bit arrays into a third one.
	 */
	static void concatenate( void *array1, int start1, int size1, void *array2, int start2, int size2, void *dest, int startDest );

	static void append( void *src, int src_start, int src_size, void *dest, int dest_size );

	static int  getArraySize( int nBits, int elem_size = 1 );
};
//-----------------------------------------------------------------------------

#endif

