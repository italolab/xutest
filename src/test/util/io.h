#ifndef IO_UTIL_H
#define IO_UTIL_H

#include <string>

using std::string;

namespace io {

    string absolutePath( string path );

    string resolvePath( string path );
    string resolvePath( string currDir, string path );
    string absoluteResolvePath( string path );

    string dirPath( string path );
    string fileOrDirName( string path );
    string fileOrDirNameWithoutExtension( string path );

}

#endif
