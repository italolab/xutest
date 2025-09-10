#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <stdexcept>

using std::string;
using std::vector;

namespace testfw {
namespace strutil {

    bool endsWith( string str, string suffix );
    bool endsWithSome( string str, string prefixes );
    bool startsWith( string str, string prefix );
    string trim( string str );
    string replace( string str, string replaceStr, string newReplaceStr );
    string replaceAll( string str, char ch, char newCh );    
    string removeStartWhiteSpaces( string str );
    bool isWhiteSpace( char ch );

}
}

#endif
