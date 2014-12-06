
#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include <string>
#include <vector>
#include <map>
using namespace std;

//---------------------------------------------------------------------------
/**
 * A utility class that reads property files.
 * <p>
 * The properties file format is very simple.
 * it contains one property per line in the format
 * <name>=<value>
 * Blanks are removed from the beggining and from the end of both fields.
 * Blank lines are allowed, they are silently ignored.
 * Lines beginning with # are comment lines.
 * Comments are only allowed in the beginning of lines. Lines in the format
 * <name>=<value> #comment here
 * are not allowed.
 *
 * Multivalue properties are allowed, in the format:
 * <name>=<value1>,<value2>,...,<valuen>
 * They can be retrieved with the getPropertyXXXVector methods.
 */
class Properties
{
    public:
    Properties();
    ~Properties();
    
    bool read( const char *filename );
    
    int getNumProperties();    

	int getErrorLine();
    
    string getPropertyString( string name );
    int    getPropertyInt( string name );
    double getPropertyDouble( string name );
    bool   getPropertyBoolean( string name );

	// These methods returns either the property value
	// or a default value
	string getPropertyString( string name, const string &default_val );
    int    getPropertyInt( string name, int default_val );
    double getPropertyDouble( string name, double default_val );
    bool   getPropertyBoolean( string name, bool default_val );

	vector< string > getPropertyStringVector( string name );
	vector< int > getPropertyIntVector( string name );
	vector< double > getPropertyDoubleVector( string name );
	vector< bool > getPropertyBooleanVector( string name );
    
    private:
    map< string, string > properties;

	bool strToBool( const string &str );
	int errorLine;
};

#endif

