
#include "strutil.h"

#include <sstream>
#include <iostream>

using std::stringstream;
using std::istringstream;

namespace testfw {
namespace strutil {

    bool endsWithSome( string str, string prefixes ) {
        istringstream iss( prefixes );
        string prefix;

        while( iss >> prefix )
            if ( endsWith( str, prefix ) )
                return true;
        return false;
    }

    bool isEqualToSome( string str, string values ) {
        istringstream iss( values );
        string value;

        while( iss >> value )
            if ( str == value )
                return true;
        return false;
    }

    bool endsWith( string str, string suffix ) {
        size_t suffixLen = suffix.length();
        size_t strLen = str.length();
        if ( suffixLen <= strLen ) {
            for( size_t i = 0; i < suffixLen; i++ )
                if ( suffix[ suffixLen - i - 1 ] != str[ strLen - i - 1 ] )
                    return false;
            return true;
        }
        return false;
    }

    bool startsWith( string str, string prefix ) {
        size_t prefixLen = prefix.length();
        size_t strLen = str.length();
        if ( prefixLen <= strLen ) {
            for( size_t i = 0; i < prefixLen; i++ )
                if ( prefix[ i ] != str[ i ] )
                    return false;
            return true;
        }
        return false;
    }

    string trim( string str ) {
        stringstream ss;
        size_t len = str.length();
        for( size_t i = 0; i < len; i++ )
            if ( str[ i ] != ' ' && str[ i ] != '\t' && str[ i ] != '\r' && str[ i ] != '\n' )
                ss << str[ i ];
        return ss.str();
    }

    string replace( string str, string replaceStr, string newReplaceStr ) {
        string newStr = str;
        size_t i = newStr.find( replaceStr );
        if ( i != string::npos ) {
            int replaceStrLen = replaceStr.length();
            newStr.replace( i, replaceStrLen, newReplaceStr );
        }
        return newStr;
    }

    string replaceAll( string str, string replaceStr, string newReplaceStr ) {
        string newStr = str;
        int replaceStrLen = replaceStr.length();

        size_t i = newStr.find( replaceStr );
        while ( i != string::npos ) {
            newStr.replace( i, replaceStrLen, newReplaceStr );
            i = newStr.find( replaceStr );
        }
        return newStr;
    }
    
    string removeStartWhiteSpaces( string str ) {
        int len = str.length();

        int i = 0;
        bool notWhiteSpace = false;
        while( !notWhiteSpace && i < len ) {
            if ( isWhiteSpace( str[ i ] ) ) {
                i++;
            } else {
                notWhiteSpace = true;
            }
        }

        if ( i < len )
            return str.substr( i, len-i );
        return "";
    }

    bool isWhiteSpace( char ch ) {
        return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
    }

}
}
