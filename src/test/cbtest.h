#ifndef CBTEST_H
#define CBTEST_H

#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <cstring>

using std::string;
using std::stringstream;
using std::vector;
using std::function;
using std::runtime_error;
using std::cout;
using std::cerr;
using std::endl;

typedef struct TTestCase {
    string name;
    string testClass;
    function<void()> func;
} TestCase;

class assert_fail : public runtime_error {

    public:
        assert_fail( string msg );

};

assert_fail::assert_fail( string msg ) : runtime_error( msg ) {}

vector<TestCase*> __test_cases;

template <typename T>
inline string RED( T text ) {
    string output = "\033[31m";
    output += text;
    output += "\033[0m";
    return output;
}

template <typename T>
inline string GREEN( T text ) {
    string output = "\033[32m";
    output += text;
    output += "\033[0m";
    return output;
}

template <typename T>
inline string BLUE( T text ) {
    string output = "\033[34m";
    output += text;
    output += "\033[0m";
    return output;
}

template <typename T>
inline string WHITE( T text ) {
    string output = "\033[37m";
    output += text;
    output += "\033[0m";
    return output;
}

template <typename T>
string ARRAY_STR( T* arr, int len ) {
    stringstream ss;
    for( int i = 0; i < len; i++ )
        ss << arr[ i ] << " ";
    return ss.str();
}

template <typename T>
string VECTOR_STR( vector<T> vect ) {
    stringstream ss;
    for( T el : vect )
        ss << el << " ";
    return ss.str();
}

string ERROR_MSG( string errorMsg, string otherErrorMsg ) {
    stringstream ss;
    ss << "Linha(" << __LINE__ << "): ";
    if ( errorMsg == "" )
        ss << otherErrorMsg << endl;
    else ss << errorMsg << endl;
    return ss.str();
}

template <typename T>
bool EQUALS_ARRAYS( T* a1, T* a2, int len ) {
    for( int i = 0; i < len; i++ )
        if ( a1[ i ] != a2[ i ] )
            return false;
    return true;
}

template <typename T>
bool EQUALS_VECTORS( vector<T> v1, vector<T> v2 ) {
    if ( v1.size() != v2.size() )
        return false;

    int len = v1.size();
    for( int i = 0; i < len; i++ )
        if ( v1[ i ] != v2[ i ] )
            return false;
    return true;
}

template <typename T>
void ASSERT_EQUALS_VECTORS( vector<T> v1, vector<T> v2, string errorMsg = "", bool isImpVectors = true ) {
    if ( !EQUALS_VECTORS( v1, v2 ) ) {
        if ( errorMsg != "" )
            throw assert_fail( errorMsg + "\n" );
        
        stringstream ss;
        if ( isImpVectors ) {
            ss << "\nVetor(1)= " << VECTOR_STR( v1 ) << endl;
            ss << "Vetor(2)= " << VECTOR_STR( v2 ) << endl;
        }
        ss << "Os vetores deveriam ser iguais!" << endl;
        throw assert_fail( ss.str() );
    } 
}

template <typename T>
void ASSERT_NOT_EQUALS_VECTORS( vector<T> v1, vector<T> v2, string errorMsg = "", bool isImpVectors = true ) {
    if ( EQUALS_VECTORS( v1, v2 ) ) {
        if ( errorMsg != "" )
            throw assert_fail( errorMsg );
        
        stringstream ss;
        if ( isImpVectors ) {
            ss << "\nVetor(1)= " << VECTOR_STR( v1 ) << endl;
            ss << "Vetor(2)= " << VECTOR_STR( v2 ) << endl;
        }
        ss << "Os vetores deveriam ser diferentes!" << endl;
        throw assert_fail( ss.str() );
    } 
}

template <typename T>
void ASSERT_EQUALS_ARRAYS( T* a1, T* a2, int len, string errorMsg = "", bool isImpArrays = true ) {
    if ( !EQUALS_ARRAYS( a1, a2, len ) ) {
        if ( errorMsg != "" )
            throw assert_fail( errorMsg );
        
        stringstream ss;
        if ( isImpArrays ) {
            ss << "\nArray(1)= " << ARRAY_STR( a1, len ) << endl;
            ss << "Array(2)= " << ARRAY_STR( a2, len ) << endl;
        }
        ss << "Os arrays deveriam ser iguais!" << endl;
        throw assert_fail( ss.str() );
    } 
}

template <typename T>
void ASSERT_NOT_EQUALS_ARRAYS( T* a1, T* a2, int len, string errorMsg = "", bool isImpArrays = true ) {
    if ( EQUALS_ARRAYS( a1, a2, len ) ) {
        if ( errorMsg != "" )
            throw assert_fail( errorMsg );
        
        stringstream ss;
        if ( isImpArrays ) {
            ss << "\nArray(1)= " << ARRAY_STR( a1, len ) << endl;
            ss << "Array(2)= " << ARRAY_STR( a2, len ) << endl;
        }
        ss << "Os arrays deveriam ser diferentes!" << endl;
        throw assert_fail( ss.str() );
    } 
}

template <typename T>
void ASSERT_EQUALS_VECTORS( vector<T> v1, vector<T> v2, bool isImpVectors ) {
    ASSERT_EQUALS_VECTORS( v1, v2, "", isImpVectors );
}

template <typename T>
void ASSERT_NOT_EQUALS_VECTORS( vector<T> v1, vector<T> v2, bool isImpVectors ) {
    ASSERT_NOT_EQUALS_VECTORS( v1, v2, "", isImpVectors );
}

template <typename T>
void ASSERT_EQUALS_ARRAYS( T* a1, T* a2, bool isImpVectors ) {
    ASSERT_EQUALS_ARRAYS( a1, a2, "", isImpVectors );
}

template <typename T>
void ASSERT_NOT_EQUALS_ARRAYS( T* a1, T* a2, bool isImpVectors ) {
    ASSERT_NOT_EQUALS_ARRAYS( a1, a2, "", isImpVectors );
}

// OUTROS ASSERTS

template <typename T>
void ASSERT_EQUALS( T a, T b, string errorMsg = "" ) {
    if ( a != b )
        throw assert_fail( ERROR_MSG( errorMsg, "deveriam ser iguais!" ) );
}

template <typename T>
void ASSERT_NOT_EQUALS( T a, T b, string errorMsg = "" ) {
    if ( a == b )
        throw assert_fail( ERROR_MSG( errorMsg, "deveriam ser diferentes!" ) );
}

void ASSERT_TRUE( bool condicao, string errorMsg = "" ) {
    if ( !condicao )
        throw assert_fail( ERROR_MSG( errorMsg, "Condição que deveria ser verdadeira é falsa!" ) );
}

void ASSERT_FALSE( bool condicao, string errorMsg = "" ) {
    if ( condicao )
        throw assert_fail( ERROR_MSG( errorMsg, "Condição que deveria ser falsa é verdadeira!" ) );    
}

void ASSERT_NULL( void* obj, string errorMsg = "" ) {
    if ( obj != nullptr )              
        throw assert_fail( ERROR_MSG( errorMsg, "Objeto deveria ser nulo!" ) );
}

void ASSERT_NOT_NULL( void* obj, string errorMsg = "" ) {
    if ( obj == nullptr )              
        throw assert_fail( ERROR_MSG( errorMsg, "Objeto deveria ser não nulo!" ) );    
}


// TEST CASES DEFINES E FUNCTIONS


#define TEST_CASE( name, testClass ) \
    void _##testClass##_##name () \

#define ADD_TEST_CASE( name, testClass ) \
    TestCase* tc = new TestCase { \
        #name, \
        #testClass, \
        _##testClass##_##name }; \
    __test_cases.push_back( tc ); \

inline void RUN_ALL_TEST_CASES() {
    cout << "EXECUTANDO TESTES..." << endl;
    cout << endl;
    for( TestCase* test : __test_cases ) {
        string testName = test->name;
        if ( test->testClass != "" )
            testName = test->testClass +"." + testName;
        cout << "Executando " << GREEN( testName ) << "... ";
        try {
            test->func();
            cout << "Ok" << endl;
        } catch ( const assert_fail& e ) {
            cout << "\n\tErro em: " << GREEN( testName ) << " --> " << WHITE( e.what() );
        }
    }
    cout << endl;
}

#endif