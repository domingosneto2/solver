
#ifndef _ENUM_DIR_H
#define _ENUM_DIR_H

#ifdef WIN32
#include <io.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif

class EnumDir
{
	public:
        EnumDir();
        ~EnumDir();

        bool start( const char *cwd, const char *pattern );

        bool next();
        char *getName();

        void close();

        private:
#ifdef WIN32
	struct _finddata_t info;
	int  handle;
	char Name[1024];
#else
        DIR *dir;
        struct dirent *ent;
#endif
        char *pattern;
};

#endif
