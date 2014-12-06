
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <util/Properties.h>
#include <util/XString.h>

#ifdef WIN32
#define strcasecmp strcmpi
#endif


//---------------------------------------------------------------------------
/**
 * Constructor.
 */
Properties::Properties()
{
}
//---------------------------------------------------------------------------
/**
 * Destructor.
 */
Properties::~Properties()
{
}
//---------------------------------------------------------------------------    
/**
 * Reads properties from a file.
 *
 * If this method fails it returns false, and you can call getErrorLine
 * to get the line where the error was found.
 * If the error line is -1 the file was not found.
 */
bool Properties::read( const char *filename )
{
    char buff[1024];
	char name[1024];
	char value[1024];

	properties.clear();
	errorLine = -1;

    FILE *fptr = fopen( filename, "rt" );
    
    if ( fptr == NULL )
    {
        return false;
    }
    
	errorLine = 0;
    while ( !feof( fptr ) )
    {
        fgets( buff, 1024, fptr );
		errorLine++;

		trim( buff );

		if ( strlen( buff ) == 0 )
		{
			continue;
		}

		if ( buff[0] == '#' )
		{
			continue;
		}

		char *sign = strchr( buff, '=' );
		if ( sign == NULL )
		{
			fclose( fptr );
			return false;
		}

		*sign = 0;
		sign++;

		strcpy( name, buff );
		trim( name );
		strcpy( value, sign );
		trim( value );

		properties[name] = value;
    }

	fclose( fptr );
	return true;
}
//---------------------------------------------------------------------------    
/**
 * 
 */
int Properties::getErrorLine()
{
	return errorLine;
}
//---------------------------------------------------------------------------    
/**
 * 
 */
int Properties::getNumProperties()
{
	return properties.size();
}
//---------------------------------------------------------------------------    
/**
 * 
 */
string Properties::getPropertyString( string name )
{
	if ( properties.count( name ) == 0 )
	{
		return "";
	}

	return properties[name];
}
//---------------------------------------------------------------------------
/**
 * 
 */
string Properties::getPropertyString( string name, const string &default_val )
{
	if ( properties.count( name ) == 0 )
	{
		return default_val;
	}

	return getPropertyString( name );
}
//---------------------------------------------------------------------------
/**
 * 
 */
int    Properties::getPropertyInt( string name )
{
	if ( properties.count( name ) == 0 )
	{
		return 0;
	}

	return atoi( properties[name].c_str() );
}
//---------------------------------------------------------------------------
int    Properties::getPropertyInt( string name, int default_val )
{
	if ( properties.count( name ) == 0 )
	{
		return default_val;
	}

	return getPropertyInt( name );
}
//---------------------------------------------------------------------------
double Properties::getPropertyDouble( string name )
{
	if ( properties.count( name ) == 0 )
	{
		return 0;
	}

	return atof( properties[name].c_str() );
}
//---------------------------------------------------------------------------
double Properties::getPropertyDouble( string name, double default_val )
{
	if ( properties.count( name ) == 0 )
	{
		return default_val;
	}

	return getPropertyDouble( name );
}
//---------------------------------------------------------------------------
bool   Properties::getPropertyBoolean( string name )
{
	if ( properties.count( name ) == 0 )
	{
		return false;
	}

	string str = properties[name];
	return strToBool( str );	
}
//---------------------------------------------------------------------------
bool   Properties::getPropertyBoolean( string name, bool default_val )
{
	if ( properties.count( name ) == 0 )
	{
		return default_val;
	}

	return getPropertyBoolean( name );
}
//---------------------------------------------------------------------------
vector< string > Properties::getPropertyStringVector( string name )
{
	// This isn't the cleanest implementation at all,
	// but I got it from a previous code with copy & paste
	// and wasn't willing to rewrite it
	static char Buffer[1024*64]; // grande o suficiente
	static char Buff2[1024];

	vector<string> res;

	string str = getPropertyString( name );
	if ( str == "" )
	{
		return res;
	}

	strcpy( Buffer,  str.c_str() );

	int len = strlen( Buffer );


	int prev = 0;
	int strcount = 0;
	int i;
	for ( i = 0; i < len; i++ )
	{
		if ( Buffer[i] == ',' )
		{
			if ( i - prev > 0 )
			{
				char *newString = new char[ i - prev + 1];
				memcpy( newString, Buffer + prev, i - prev );
				newString[i-prev] = 0;
				res.push_back( string( newString ) );
				delete[] newString;
			}
			prev = i + 1;
		}
	}

	if ( i - prev > 0 )
	{
		char *newString = new char[ i - prev + 1];
		memcpy( newString, Buffer + prev, i - prev );
		newString[i-prev] = 0;
		res.push_back( string( newString ) );
		delete[] newString;
	}


	return res;
}
//---------------------------------------------------------------------------
vector< int > Properties::getPropertyIntVector( string name )
{
	vector<string> strings = getPropertyStringVector( name );
	vector<int> ret;

	for ( int i = 0; i < strings.size(); i++ )
	{
		ret.push_back( atoi( strings[i].c_str() ) );
	}

	return ret;
}
//---------------------------------------------------------------------------
vector< double > Properties::getPropertyDoubleVector( string name )
{
	vector<string> strings = getPropertyStringVector( name );
	vector<double> ret;

	for ( int i = 0; i < strings.size(); i++ )
	{
		ret.push_back( atof( strings[i].c_str() ) );
	}

	return ret;
}
//---------------------------------------------------------------------------
vector< bool > Properties::getPropertyBooleanVector( string name )
{
	vector<string> strings = getPropertyStringVector( name );
	vector<bool> ret;

	for ( int i = 0; i < strings.size(); i++ )
	{
		ret.push_back( strToBool( strings[i] ) );
	}

	return ret;
}
//---------------------------------------------------------------------------
bool Properties::strToBool( const string &str )
{
	if ( strcasecmp( str.c_str(), "true" ) == 0 ||
		 strcasecmp( str.c_str(), "yes" ) == 0 ||
		 strcasecmp( str.c_str(), "1" ) == 0 )
	{
		return true;
	}

	return false;
}
//---------------------------------------------------------------------------
