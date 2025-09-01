#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <stdexcept>

using std::string;
using std::vector;

namespace strutil {

    bool startsWith( string str, string prefix );
    bool endsWith( string str, string suffix );
    bool endsWithSome( string str, string prefixes );
    bool isEqualToSome( string str, string values );
    string trim( string str );
    string replace( string str, string subStr, string newSubStr );
    string replaceAll( string str, string replaceStr, string newReplaceStr );

    bool isWhiteSpace( char ch );
    string removeStartWhiteSpaces( string str );

}

#endif
