
#include <memory.h>
#include <util/BitArrayOps.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
//---------------------------------------------------------------------------
bool BitArrayOps::getValue( void *array, int index )
{
	int h_ndx = index / ( sizeof( int ) * 8 );
	int l_ndx = index % ( sizeof( int ) * 8 );

	int *vector = (int*)array;

	int t = 1;
	t <<= l_ndx;
	return ( vector[h_ndx] & t ) == 0 ? false : true;
}
//---------------------------------------------------------------------------
void BitArrayOps::setValue( void *array, int index, bool value )
{
	int h_ndx = index / ( sizeof( int ) * 8 );
	int l_ndx = index % ( sizeof( int ) * 8 );

	int *vector = (int*)array;

	int t = 1;
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
void *BitArrayOps::create( int nBits )
{
	int size = ( nBits + 8 * sizeof( int ) - 1 ) / ( 8 * sizeof(int ) );
	return new int[size];
}
//---------------------------------------------------------------------------
void BitArrayOps::release( void *array )
{
	delete[] (int *)array;
}
//---------------------------------------------------------------------------
int BitArrayOps::getArraySize( int nBits, int elem_size )
{
	return ( nBits + 8 * elem_size - 1 ) / ( 8 * elem_size );
}
//---------------------------------------------------------------------------
void BitArrayOps::subString( void *src, int start, int size, void *dest, int startDest )
{
	int *src_ptr  = (int *)src;
	int *dest_ptr = (int *)dest;

	int word_size = sizeof( int ) * 8;
	
	int src_word   = start / word_size;
	int src_offset = start % word_size;
	
	int dest_word   = startDest / word_size;
	int dest_offset = startDest % word_size;

	int copied_bits = 0;

	int cur_src_word = src_word;
	int cur_dest_word  = dest_word;
	int cur_src_offset = src_offset;
	int cur_dest_offset = dest_offset;
	
	while ( copied_bits < size )
	{
		int available_bits = MIN( word_size - cur_src_offset, word_size - cur_dest_offset );
		int mask = (1 << available_bits) - 1;

		int bits = src_ptr[cur_src_word] & (mask << cur_src_offset);
		bits >>= cur_src_offset;
		dest_ptr[cur_dest_word]  &= ~(mask << cur_dest_offset);
		dest_ptr[cur_dest_word] |= (bits << cur_dest_offset);

		cur_src_offset += available_bits;
		cur_dest_offset += available_bits;

		if ( cur_src_offset == word_size )
		{
			cur_src_offset = 0;
			cur_src_word++;
		}
		if ( cur_dest_offset == word_size )
		{
			cur_dest_offset = 0;
			cur_dest_word++;
		}

		copied_bits += available_bits;
	}
}
//---------------------------------------------------------------------------
void BitArrayOps::concatenate( void *array1, int start1, int size1, void *array2, int start2, int size2, void *dest, int startDest )
{
	subString( array1, start1,size1, dest, startDest );
	subString( array2, start2, size2, dest, startDest + size1 );
}
//---------------------------------------------------------------------------
void BitArrayOps::append( void *src, int src_start, int src_size, void *dest, int dest_size )
{
	subString( src, src_start, src_size, dest, dest_size );
}
//---------------------------------------------------------------------------
void BitArrayOps::copy( void *src, void *dest, int size )
{
	// how many words to copy
	int word_size = 8 * sizeof( int );
	int words_to_copy = (size + word_size - 1 ) / word_size;
	int remainder = size % word_size;

	memcpy( dest, src, words_to_copy * sizeof( int ) );
	if ( remainder > 0 )
	{
		int *src_ptr = (int *)src;
		int *dest_ptr = (int *)dest;

		int mask = 1 << remainder - 1;
		dest_ptr[words_to_copy] = src_ptr[words_to_copy] & mask;
	}
}
//---------------------------------------------------------------------------
int BitArrayOps::compare( void *array1, int size1, void *array2, int size2 )
{
	int minSize = MIN( size1, size2 );
	int word_size = 8 * sizeof( int );
	int words_to_compare = ( minSize + word_size - 1 ) / word_size;
	int remainder = minSize % word_size;

	int order = memcmp( array1, array2, words_to_compare * sizeof( int ) );
	if ( order != 0 )
	{
		return order;
	}

	int *ptr1 = (int *)array1;
	int *ptr2 = (int *)array2;
	int i1, i2;

	int mask = 1 << remainder - 1;
	i1 = ptr1[words_to_compare] & mask;
	i2 = ptr2[words_to_compare] & mask;
	
	order = memcmp( &i1, &i2, sizeof( int ) );
	if ( order != 0 )
	{
		return order;
	}

	if ( size1 == size2 )
	{
		return 0;
	}

	if ( size1 < size2 )
	{
		return -1;
	}
	return 1;
}
//---------------------------------------------------------------------------

