#ifndef CBTEST_H
#define CBTEST_H

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <limits>

using std::string;
using std::stringstream;
using std::vector;
using std::map;
using std::function;
using std::runtime_error;
using std::cout;
using std::cerr;
using std::endl;
using std::cin;

typedef struct TTestCase {
    string name;
    string testClass;
    function<void()> func;
} TestCase;

class __assert_fail {

    private:
        string msg;

    public:
        __assert_fail( string msg );

        string what() const;

};

extern const char* DEFAULT_TEST_CLASS;

extern map<string, vector<TestCase*>> __test_cases_map;
extern bool __is_imp_vectors;
extern string __testName;
extern int __countFails;

extern stringstream __stream;

namespace cbtest {

    void setImpVectors( bool isImpVectors );
    
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

template <typename T>
string __array_str( T* arr, int len ) {
    stringstream ss;
    for( int i = 0; i < len; i++ )
        ss << arr[ i ] << " ";
    return ss.str();
}

template <typename T>
string __vector_str( vector<T> vect ) {
    stringstream ss;
    for( T el : vect )
        ss << el << " ";
    return ss.str();
}

template <typename T>
bool __equals_arrays( T* a1, T* a2, int len ) {
    for( int i = 0; i < len; i++ )
        if ( a1[ i ] != a2[ i ] )
            return false;
    return true;
}

template <typename T>
bool __equals_vectors( vector<T> v1, vector<T> v2 ) {
    if ( v1.size() != v2.size() )
        return false;

    int len = v1.size();
    for( int i = 0; i < len; i++ )
        if ( v1[ i ] != v2[ i ] )
            return false;
    return true;
}

#define THROW_FAIL( errorMsg, otherErrorMsg ) { \
    __stream.str( "" ); \
    __stream.clear(); \
    __stream << __FILE__ << "(" << __LINE__ << "): "; \
    if ( strlen( #errorMsg ) == 0 ) \
        __stream << #otherErrorMsg; \
    __stream << #errorMsg; \
    \
    throw __assert_fail( __stream.str() ); \
}

// ASSERTS PARA VECTORS E ARRAYS

#define ASSERT_EQUALS_VECTORS( v1, v2, errorMsg ) \
    if ( !__equals_vectors( v1, v2 ) ) { \
        if ( strlen( #errorMsg ) != 0 ) \
            THROW_FAIL( errorMsg, ); \
        \
        __stream.str( "" ); \
        __stream.clear(); \
        __stream << __FILE__ << "(" << __LINE__ << "): Os vetores deveriam ser iguais!" << endl; \
        if ( __is_imp_vectors ) { \
            __stream << "\nVetor(1)= " << __vector_str( v1 ) << endl; \
            __stream << "Vetor(2)= " << __vector_str( v2 ); \
        } \
        throw __assert_fail( __stream.str() ); \
    } \

#define ASSERT_NOT_EQUALS_VECTORS( v1, v2, errorMsg ) \
    if ( __equals_vectors( v1, v2 ) ) { \
        if ( strlen( #errorMsg ) != 0 ) \
            THROW_FAIL( errorMsg, ); \
        \
        __stream.str( "" ); \
        __stream.clear(); \
        __stream << __FILE__ << "(" << __LINE__ << "): Os vetores deveriam ser diferentes!" << endl; \
        if ( __is_imp_vectors ) { \
            __stream << "\nVetor(1)= " << __vector_str( v1 ) << endl; \
            __stream << "Vetor(2)= " << __vector_str( v2 ); \
        } \
        throw __assert_fail( __stream.str() ); \
    } \

#define ASSERT_EQUALS_ARRAYS( a1, a2, len, errorMsg ) \
    if ( !__equals_arrays( a1, a2, len ) ) { \
        if ( strlen( #errorMsg ) != 0 ) \
            THROW_FAIL( errorMsg, ); \
        \
        __stream.str( "" ); \
        __stream.clear(); \
        __stream << __FILE__ << "(" << __LINE__ << "): Os arrays deveriam ser iguais!" << endl; \
        if ( __is_imp_vectors ) { \
            __stream << "\nArray(1)= " << __array_str( a1, len ) << endl; \
            __stream << "Array(2)= " << __array_str( a2, len ); \
        } \
        throw __assert_fail( __stream.str() ); \
    } \

#define ASSERT_NOT_EQUALS_ARRAYS( a1, a2, len, errorMsg ) \
    if ( __equals_arrays( a1, a2, len ) ) { \
        if ( strlen( #errorMsg ) != 0 ) \
            THROW_FAIL( errorMsg, ); \
        \
        __stream.str( "" ); \
        __stream.clear(); \
        __stream << __FILE__ << "(" << __LINE__ << "): Os arrays deveriam ser diferentes!" << endl; \
        if ( __is_imp_vectors ) { \
            __stream << "\nArray(1)= " << __array_str( a1, len ) << endl; \
            __stream << "Array(2)= " << __array_str( a2, len ); \
        } \
        throw __assert_fail( __stream.str() ); \
    } \

// OUTROS ASSERTS

#define ASSERT_EQUALS( a, b, errorMsg ) \
    if ( a != b ) \
        THROW_FAIL( errorMsg, deveriam ser iguais! ); \

#define ASSERT_NOT_EQUALS( a, b, errorMsg ) \
    if ( a == b ) \
        THROW_FAIL( errorMsg, Deveriam ser diferentes! ); \

#define ASSERT_TRUE( condicao, errorMsg ) \
    if ( !condicao ) \
        THROW_FAIL( errorMsg, Condição que deveria ser verdadeira é falsa! ); \

#define ASSERT_FALSE( condicao, errorMsg ) \
    if ( condicao ) \
        THROW_FAIL( errorMsg, Condição que deveria ser falsa é verdadeira! ); \

#define ASSERT_NULL( obj, errorMsg ) \
    if ( obj != nullptr ) \
        THROW_FAIL( errorMsg, Objeto deveria ser nulo! ); \

#define ASSERT_NOT_NULL( obj, errorMsg ) \
    if ( obj == nullptr ) \
        THROW_FAIL( errorMsg, Objeto deveria ser não nulo! ); \

#define ASSERT_THROWS( except, block, errorMsg ) \
    try { \
        block \
        THROW_FAIL( errorMsg, Deveria lancar uma exceção: #except ); \
    } catch ( const except& ex ) { \
        \
    } \

#define ASSERT_NOT_THROWS( except, block, errorMsg ) \
    try { \
        block \
    } catch ( const except& ex ) { \
        THROW_FAIL( errorMsg, Não deveria lancar exceção: #except ); \
    } \

#define FAIL( errorMsg ) \
    THROW_FAIL( errorMsg, ); \

// TEST CASES DEFINES E FUNCTIONS


#define TEST_CASE( name, testClass ) \
    void _##testClass##_##name () \

#define ADD_TEST_CASE( name, testClass ) \
    if ( strlen( #testClass ) == 0 ) { \
        if ( __test_cases_map.find( DEFAULT_TEST_CLASS ) == __test_cases_map.end() ) { \
            vector<TestCase*> vect; \
            __test_cases_map[ DEFAULT_TEST_CLASS ] = vect; \
        } \
        __test_cases_map[ DEFAULT_TEST_CLASS ].push_back(  \
            new TestCase { \
                #name, \
                #testClass, \
                _##testClass##_##name } ); \
    } else { \
        if ( __test_cases_map.find( #testClass ) == __test_cases_map.end() ) { \
            vector<TestCase*> vect; \
            __test_cases_map[ #testClass ] = vect; \
        } \
        __test_cases_map[ #testClass ].push_back(  \
            new TestCase { \
                #name, \
                #testClass, \
                _##testClass##_##name } ); \
    } \

#define RUN_TEST_CASES_BY_CLASS( testClass ) \
    if ( __test_cases_map.find( testClass ) == __test_cases_map.end() ) { \
        cout << __blue( "Nenhum teste registrado para a classe: " ) << __green( testClass ); \
    } else { \
        cout << "Executando " << __green( testClass ) << "..." << endl; \
        \
        __countFails = 0; \
        \
        vector<TestCase*> testCases = __test_cases_map[ testClass ]; \
        for( TestCase* testcase : testCases ) { \
            __testName = testcase->name; \
            cout << "\tExecutando " << __green( __testName ) << "... "; \
            try { \
                testcase->func(); \
                cout << __white( "Ok" ) << endl; \
            } catch ( const __assert_fail& e ) { \
                cout << endl; \
                cout << "\n" << __red( "Falha" ) << " em: " << __green( __testName ) << " --> " << e.what() << endl; \
                cout << endl; \
                __countFails++; \
            } catch ( const exception& e ) { \
                cout << endl; \
                cout << "\nException em: " << __green( __testName ) << " --> "; \
                cout << __FILE__ << "(" << __LINE__ << "): " << __red( e.what() ) << endl; \
                cout << endl; \
                __countFails++; \
            } catch ( ... ) { \
                cout << endl; \
                cout << "\nException desconhecida em: " << __green( __testName ) << endl; \
                cout << endl; \
                __countFails++; \
            } \
        } \
        \
        if ( __countFails == 0 ) \
            cout << __green( testClass ) << __white( " Ok!" ) << endl; \
        else cout << __green( testClass ) << ": " << __red( std::to_string( __countFails ) ) << __white( " falha(s)!" ) << endl; \
        cout << endl; \
    } \

void RUN_ALL_TEST_CASES();
void RUN_TEST_CASES_MENU();

#endif