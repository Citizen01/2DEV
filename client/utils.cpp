#include "utils.h"
#include <io.h>   // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <iostream>
#include <fstream>


bool isDir(const std::string sDir)
{
	if ( _access( sDir.c_str(), 0 ) == 0 )
	{
		struct stat status;
		stat( sDir.c_str(), &status );

		if ( status.st_mode & S_IFDIR )
			return true;
	}
	return false;
}

bool isValidPath(const std::string path)
{
	return isDir(path);
}

bool isFile(const std::string file)
{
	std::ifstream ifile(file.c_str());
	return (bool)ifile;
}

