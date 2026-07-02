
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

    string currentPath() {
        filesystem::path currPathFS = filesystem::current_path();
        return makeUnixPreferred( currPathFS.string() );
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

    void countTwoDotsAndSlash( string path, int index, size_t& count, size_t& i, size_t& j, size_t& k ) {
        string rpath = path.substr( index, path.length()-index );
        rpath = makeUnixPreferred( rpath );

        size_t len = rpath.length();

        if ( rpath == ".." ) {
            k = 2;
            i = index;
            j = index+2;
            count = 1;
        } else {
            i = rpath.find( "../", index );
            j = ( i != string::npos ? i : index );
            k = ( i != string::npos ? i : index );
            count = 0;
            bool isContinue = i != string::npos;
            while( isContinue ) {
                count++;
                j = k+3;
                k += 3;
                if ( k+2 < len ) {
                    isContinue = rpath[ k ] == '.';
                    isContinue &= rpath[ k+1 ] == '.';
                    isContinue &= rpath[ k+2 ] == '/';
                } else {
                    isContinue = false;
                }
            }
        }
    }

    string resolvePath( string path ) {
        if ( path == "." )
            return "";

        string rpath = makeUnixPreferred( path );
        if ( strutil::startsWith( rpath, "./" ) )
            rpath = strutil::replace( rpath, "./", "" );

        size_t count, i, j, k;
        countTwoDotsAndSlash( rpath, 0, count, i, j, k );

        if( count == 0 )
            return rpath;
        
        string basePath = rpath.substr( 0, i );
        string relativePath = rpath.substr( i, rpath.length()-i ).replace( 0, j-i, "" );

        for( size_t l = 0; l < count; l++ )
            basePath = parentPath( basePath );        
        basePath = addSeparatorToDirIfNeed( basePath );
        
        return basePath + relativePath;
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

    string absolutePath( string path ) {
        if ( path == "." )
            return makeUnixPreferred( currentPath() );

        string path2 = makeUnixPreferred( path );
        if ( strutil::startsWith( path2, "./" ) )
            path2 = path2.substr( 2, path2.length()-2 );
           
        if ( strutil::startsWith( path2, "/" ) )
            return path2;

        size_t i = path2.find( ':' );
        if ( i != string::npos )
            return path2;    

        filesystem::path p( path2 );
        if ( p.is_absolute() ) {
            return path2;
        } else {
            string pp = currentPath();
            pp = makeUnixPreferred( pp );

            if ( path2 != "" )
                pp = addSeparatorToDirIfNeed( pp );
                
            pp += path2;
            return pp;
        }
    }

    string absoluteResolvePath( string path ) {
        return resolvePath( absolutePath( path ) );
    }

}
}
}