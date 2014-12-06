
#include <string.h>
#include <util/XString.h>

bool isSpace( char c )
{
	if ( c == ' ' || c == '\t' || c == '\n' || c == '\r' )
	{
		return true;
	}

	return false;
}

void strsubst( char *str, char from, char to )
{
	int i;
	int size = strlen( str );

	for ( i = 0; i < size; i++ )
	{
		if ( str[i] == from )
		{
			str[i] = to;
		}
	}
}

void trim( char *str )
{
	int start = 0;
	int size = strlen( str );

	while ( start < size )
	{
		if ( !isSpace( str[start] ) )
		{
			break;
		}

		start++;
	}

	if ( start == size )
	{
		str[0] = 0;
		return;
	}

	int end = size - 1;

	while ( end > 0 )
	{
		if ( !isSpace( str[end] ) )
		{
			break;
		}
		end--;
	}

	memmove( str, str + start, end - start + 1 );
	str[end - start + 1] = 0;
}