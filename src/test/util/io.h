#ifndef IO_UTIL_H
#define IO_UTIL_H

#include <string>

using std::string;

namespace testfw {
namespace io {
namespace path {

    string makePreferred( string path );
    string makeUnixPreferred( string path );
    string dirPath( string path );
    string addSeparatorToDirIfNeed( string dir );
    string removeSeparatorFromDirIfNeed( string dir );
    bool fileExists( string path );
    string resolvePath( string currDir, string path );

}
}
}

#endif
