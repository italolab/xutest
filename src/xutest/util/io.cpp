
#include "io.h"
#include "../util/strutil.h"

#include <filesystem>

namespace filesystem = std::filesystem;

namespace testfw {
namespace io {
namespace path {

    string makePreferred( string path ) {
        filesystem::path p( path );
        p = p.make_preferred();
        return p.string();
    }

    string makeUnixPreferred( string path ) {
        return strutil::replaceAll( path, '\\', '/' );
    }

    string addSeparatorToDirIfNeed( string dir ) {
        string d = makeUnixPreferred( dir );
        if ( d.length() > 0 )
            if( d[ d.length()-1 ] != '/' )
                d += "/";
        return d;
    }

    string dirPath( string path ) {
        string p = makeUnixPreferred( path );
        p = removeSeparatorFromDirIfNeed( p );

        if ( filesystem::is_directory( path ) )
            return p;
        
        size_t i = p.find_last_of( '/' );
        size_t j = p.find( ':' );
        if ( i == string::npos && j == string::npos )
            return p;

        if ( i == string::npos && j != string::npos ) {
            if ( p.length() > j+1 )
                return p.substr( 0, j+1 );            
            return "";           
        }
            
        if ( i == 0 )
            return "/";        
        return p.substr( 0, i );
    }

    string removeSeparatorFromDirIfNeed( string dir ) {
        string d = makeUnixPreferred( dir );

        int len = d.length();
        if ( len > 0 ) {
            if( d[ len-1 ] == '/' ) {
                if ( len == 1 )
                    return "/";
                return d = d.substr( 0, d.length()-1 );
            }
        }
        return d;
    }

    bool fileExists( string path ) {
        return filesystem::exists( path );
    }

    string parentPath( string path ) {
        string p = makeUnixPreferred( path );
        p = removeSeparatorFromDirIfNeed( p );
        if ( p.length() > 0 ) {
            size_t i = p.find_last_of( '/' );
            if ( i != string::npos ) {                
                if ( i == 0 ) {
                    if ( p.length() == 1 )
                        p = "";
                    else p = "/";
                } else {
                    p = p.substr( 0, i );
                }                
            } else {
                p = "";                
            }
        }
        return p;
    }

    string resolvePath( string currDir, string path ) {
        string resolvedPath = makeUnixPreferred( path );
        if ( strutil::startsWith( resolvedPath, "./" ) )
            resolvedPath = strutil::replace( resolvedPath, "./", "" );

        size_t i = resolvedPath.find( "../" );
        bool isRepeat = i != string::npos;
        string dir = addSeparatorToDirIfNeed( currDir );
        while( isRepeat ) {
            dir = parentPath( dir );
            dir = addSeparatorToDirIfNeed( dir );

            size_t j = resolvedPath.find( "../", i+3 );
            if ( j == string::npos ) {
                isRepeat = false;
            } else {
                i = j;
            }
        }

        size_t k = ( i == string::npos ? 0 : i+3 );
        return resolvedPath.replace( 0, k, dir );
    }

}
}
}