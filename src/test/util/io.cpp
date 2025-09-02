
#include "io.h"
#include "../util/strutil.h"

#include <filesystem>

namespace filesystem = std::filesystem;

namespace io {

    string currentPath() {
        filesystem::path currPathFS = filesystem::current_path();
        return currPathFS.string();
    }

    string makePreferred( string path ) {
        filesystem::path p( path );
        p = p.make_preferred();
        return p.string();
    }

    string addSeparatorToDirIfNeed( string dir ) {
        string d = makePreferred( dir );
        if ( d.length() > 0 )
            if( d[ d.length()-1 ] != filesystem::path::preferred_separator )
                d += filesystem::path::preferred_separator;
        return d;
    }

    string absolutePath( string path ) {
        if ( path == "." )
            return currentPath();

        string sep = "";
        sep += filesystem::path::preferred_separator;

        string path2 = path;
        if ( strutil::startsWith( path2, "."+sep ) )
            path2 = path2.substr( 2, path2.length()-2 );
            
        filesystem::path p( path2 );
        if ( p.is_absolute() ) {
            return makePreferred( path2 );
        } else {
            string pp = currentPath();
            
            if ( path2 != "" )
                pp = addSeparatorToDirIfNeed( pp );
                
            pp += path2;
            return makePreferred( pp );
        }
    }

    string dirPath( string path ) {
        string p = makePreferred( path );

        size_t i = p.find_last_of( filesystem::path::preferred_separator );
        if ( i == string::npos ) {
            if ( filesystem::is_directory( path ) )
                return p;
            return "";
        }
        return p.substr( 0, i+1 );
    }

    string fileOrDirNameWithoutExtension( string path ) {
        string fname = io::fileOrDirName( path );
        if ( !filesystem::is_directory( path ) ) {
            size_t i = fname.find_last_of( '.' );
            if ( i != string::npos )
                fname = fname.substr( 0, i );
        }
        return fname;        
    }

    string fileOrDirName( string path ) {
        string p = makePreferred( path );

        size_t i = p.find_last_of( filesystem::path::preferred_separator );
        if ( i == string::npos )
            return p;

        if ( p.length() > 0 ) {
            if ( p[ p.length()-1 ] == filesystem::path::preferred_separator ) {
                size_t j = p.find_last_of( filesystem::path::preferred_separator, i-1 );
                size_t k = ( j == string::npos ? 0 : j+1 );
                return p.substr( k, p.length()-k-1 );
            }
        }

        return p.substr( i+1, p.length()-i );
    }

    bool fileExists( string path ) {
        return filesystem::exists( path );
    }

    void countTwoDotsAndSlash( string path, int index, size_t& count, size_t& i, size_t& j, size_t& k ) {
        string sep = "";
        sep += filesystem::path::preferred_separator;

        string rpath = path.substr( index, path.length()-index );
        rpath = makePreferred( rpath );

        size_t len = rpath.length();

        if ( rpath == ".." ) {
            k = 2;
            i = index;
            j = index+2;
            count = 1;
        } else {
            i = rpath.find( ".."+sep, index );
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
                    isContinue &= rpath[ k+2 ] == filesystem::path::preferred_separator;
                } else {
                    isContinue = false;
                }
            }
        }
    }

    string absoluteResolvePath( string path ) {
        return resolvePath( absolutePath( path ) );
    }

     string parentPath( string path ) {
        string p = makePreferred( path );
        if ( p.length() > 0 ) {
            if ( p[ p.length()-1 ] == filesystem::path::preferred_separator )
                p = p.substr( 0, p.length()-1 );

            size_t i = p.find_last_of( filesystem::path::preferred_separator );
            if ( i != string::npos ) {                
                if ( i == 0 ) {
                    p = "/";
                } else {
                    p = p.substr( 0, i );
                }                
            } else {
                p = "";                
            }
        }
        return p;
    }

    string resolvePath( string path ) {
        if ( path == "." )
            return "";

        string sep = "";
        sep += filesystem::path::preferred_separator;

        string rpath = makePreferred( path );
        if ( strutil::startsWith( rpath, "."+sep ) )
            rpath = strutil::replace( rpath, "."+sep, "" );

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
        string sep = "";
        sep += filesystem::path::preferred_separator;

        string resolvedPath = makePreferred( path );
        if ( strutil::startsWith( resolvedPath, "."+sep ) )
            resolvedPath = strutil::replace( resolvedPath, "."+sep, "" );

        size_t i = resolvedPath.find( ".."+sep );
        bool isRepeat = i != string::npos;
        string dir = addSeparatorToDirIfNeed( currDir );
        while( isRepeat ) {
            dir = parentPath( dir );
            dir = addSeparatorToDirIfNeed( dir );

            size_t j = resolvedPath.find( ".."+sep, i+3 );
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