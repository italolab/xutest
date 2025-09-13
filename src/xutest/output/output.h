#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>

using std::string;

template <typename T>
string __bold( T text ) {
    string output = "\033[1m";
    output += text;
    output += "\033[0m";
    return output;
}

template <typename T>
string __red( T text ) {
    string output = "\033[31m";
    output += text;
    output += "\033[0m";
    return output;
}

template <typename T>
string __green( T text ) {
    string output = "\033[32m";
    output += text;
    output += "\033[0m";
    return output;
}

template <typename T>
string __blue( T text ) {
    string output = "\033[34m";
    output += text;
    output += "\033[0m";
    return output;
}

template <typename T>
string __white( T text ) {
    string output = "\033[37m";
    output += text;
    output += "\033[0m";
    return output;
}

#endif