
#include <string.h>
#ifndef WIN32
#include <fnmatch.h>
#endif
#include <util/EnumDir.h>
#include <util/XString.h>

//---------------------------------------------------------------------------
EnumDir::EnumDir()
{
#ifdef WIN32
	handle  = -1;
	Name[0] = 0;
#else
	dir     = NULL;
        ent     = NULL;
        pattern = NULL;
#endif
}
//---------------------------------------------------------------------------
EnumDir::~EnumDir()
{
	close();
}
//---------------------------------------------------------------------------
bool EnumDir::start( const char *name, const char *_pattern )
{
	close();
#ifdef WIN32
	//-------------------------------------------------------
	// WIN32 SPECIFIC CODE
	//-------------------------------------------------------
	int namelen = strlen( name );
	int patlen  = strlen( _pattern );
	char *full_path = new char[namelen + patlen + 2];

	strcpy( full_path, name );
	if ( namelen > 0 )
	{
		if ( name[namelen - 1] != '/' && name[namelen - 1] != '\\' )
		{
			strcat( full_path, "\\" );
		}
	}

	strcat( full_path, _pattern );
	strsubst( full_path, '/', '\\' );

	handle = _findfirst( full_path, &info );

	return handle != -1;
#else
	//-------------------------------------------------------
	// UNIX SPECIFIC CODE
	//-------------------------------------------------------
        dir = opendir( name );
        if ( dir != NULL )
        {
        	pattern = new char[strlen(_pattern)];
                strcpy( pattern, _pattern );
        }


        return dir != NULL;
#endif
}
//---------------------------------------------------------------------------
bool EnumDir::next()
{
#ifdef WIN32
	//-------------------------------------------------------
	// WIN32 SPECIFIC CODE
	//-------------------------------------------------------
	if ( handle == -1 )
	{
		Name[0] = 0;
		return false;
	}

	strcpy( Name, info.name );
	int res = _findnext( handle, &info );

	if ( res != 0 )
	{
		_findclose( handle );
		handle = -1;
	}

	return true;
#else
	//-------------------------------------------------------
	// UNIX SPECIFIC CODE
	//-------------------------------------------------------
	while ( 1 )
        {
		ent = readdir( dir );
                if ( ent == NULL )
                {
                	return false;
                }

                if ( fnmatch( pattern, ent->d_name, 0 ) == 0 )
                {
                	return true;
                }
  	}

        return false;
#endif
}
//---------------------------------------------------------------------------
char *EnumDir::getName()
{
#ifdef WIN32
	if ( Name[0] == 0 )
	{
		return NULL;
	}

	return Name;
#else
	if ( ent == NULL )
        {
        	return NULL;
        }

        return ent->d_name;
#endif
}
//---------------------------------------------------------------------------
void EnumDir::close()
{
#ifdef WIN32
	if ( handle != -1 )
	{
		_findclose( handle );
		handle = -1;
		Name[0] = 0;
	}
#else
	if( dir != NULL )
        {
        	closedir( dir );
                dir = NULL;
                delete[] pattern;
                pattern = NULL;
                ent = NULL;
        }
#endif
}
//---------------------------------------------------------------------------
