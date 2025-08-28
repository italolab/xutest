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

class assert_fail : public runtime_error {

    public:
        assert_fail( string msg );

};

assert_fail::assert_fail( string msg ) : runtime_error( msg ) {}

const char* DEFAULT_TEST_CLASS = "default";

map<string, vector<TestCase*>> __test_cases_map;
stringstream __stream;
bool __is_imp_vectors = false;

template <typename T>
string RED( T text ) {
    string output = "\033[31m";
    output += text;
    output += "\033[0m";
    return output;
}

template <typename T>
string GREEN( T text ) {
    string output = "\033[32m";
    output += text;
    output += "\033[0m";
    return output;
}

template <typename T>
string BLUE( T text ) {
    string output = "\033[34m";
    output += text;
    output += "\033[0m";
    return output;
}

template <typename T>
string WHITE( T text ) {
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

#define THROW_FAIL( errorMsg, otherErrorMsg ) { \
    stringstream ss; \
    ss << "Linha(" << __LINE__ << "); "; \
    if ( strlen( #errorMsg ) == 0 ) \
        ss << #otherErrorMsg; \
    ss << #errorMsg; \
    \
    throw assert_fail( ss.str() ); \
}

// ASSERTS PARA VECTORS E ARRAYS

template <typename T>
void ASSERT_EQUALS_VECTORS( vector<T> v1, vector<T> v2, string errorMsg ) {
    if ( !EQUALS_VECTORS( v1, v2 ) ) {
        if ( errorMsg != "" )
            throw assert_fail( errorMsg + "\n" );
        
        stringstream ss;
        if ( isImpVectors ) {
            ss << "\nVetor(1)= " << VECTOR_STR( v1 ) << endl;
            ss << "Vetor(2)= " << VECTOR_STR( v2 ) << endl;
        }
        ss << "Os vetores deveriam ser iguais!";
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
        ss << "Os vetores deveriam ser diferentes!";
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
        ss << "Os arrays deveriam ser iguais!";
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
        ss << "Os arrays deveriam ser diferentes!";
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
        THROW_FAIL( errorMsg, "deveriam ser iguais!" );
}

template <typename T>
void ASSERT_NOT_EQUALS( T a, T b, string errorMsg = "" ) {
    if ( a == b )
        THROW_FAIL( errorMsg, "deveriam ser diferentes!" );
}

void ASSERT_TRUE( bool condicao, string errorMsg = "" ) {
    if ( !condicao )
        THROW_FAIL( errorMsg, "Condição que deveria ser verdadeira é falsa!" );
}

void ASSERT_FALSE( bool condicao, string errorMsg = "" ) {
    if ( condicao )
        THROW_FAIL( errorMsg, "Condição que deveria ser falsa é verdadeira!" );    
}

void ASSERT_NULL( void* obj, string errorMsg = "" ) {
    if ( obj != nullptr )              
        THROW_FAIL( errorMsg, "Objeto deveria ser nulo!" );
}

void ASSERT_NOT_NULL( void* obj, string errorMsg = "" ) {
    if ( obj == nullptr )              
        THROW_FAIL( errorMsg, "Objeto deveria ser não nulo!" );    
}


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


int RUN_TEST_CASES_BY_CLASS( string testClass ) {
    if ( __test_cases_map.find( testClass ) == __test_cases_map.end() ) {
        cout << BLUE( "Nenhum teste registrado para a classe: " + testClass );
        return 0;
    }

    cout << "Executando " << GREEN( testClass ) << "..." << endl;

    int countFails = 0;

    vector<TestCase*> testCases = __test_cases_map[ testClass ];
    for( TestCase* testcase : testCases ) {
        string testName = testcase->name;
        if ( testcase->testClass != "" )
            testName = testcase->testClass +"." + testName;
        cout << "\n\tExecutando " << GREEN( testName ) << "... ";
        try {
            testcase->func();
            cout << GREEN( "Ok" ) << endl;
        } catch ( const assert_fail& e ) {            
            cout << "\n" << RED( "Erro" ) << " em: " << GREEN( testName ) << " --> " << WHITE( e.what() ) << endl;
            countFails++;
        }
    }

    cout << endl;
    if ( countFails == 0 )
        cout << GREEN( testClass ) << " executado sem falhas!" << endl;
    else cout << GREEN( testClass ) << " executado com " << std::to_string( countFails ) << " falha(s)!" << endl;
    cout << endl;

    return countFails;
}

void RUN_ALL_TEST_CASES() {
    cout << "EXECUTANDO TESTES..." << endl;
    cout << endl;
    
    int countFails = 0;
    for( const auto& pair : __test_cases_map )
        countFails += RUN_TEST_CASES_BY_CLASS( pair.first );
    
    if ( countFails == 0 )
        cout << "Todos os testes passaram com sucesso!" << endl;
    else cout << "Houve falha em " << countFails << " teste(s)" << endl;
}

int READ_OPTION( int numberOfOptions ) {
    int op;
            
    bool ok;
    do {
        cout << ">> " << std::flush;
        while( !(cin >> op) ) {
            cout << RED( "Informe uma opção entre 1 e " );
            cout << RED( numberOfOptions );
            cout << RED( "." ) << endl;
            cin.clear();
            cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            cout << ">> " << std::flush;
        }

        ok = true;
        if ( op < 0 || op > numberOfOptions-1 ) {
            cout << RED( "Informe uma opção entre 1 e " );
            cout << RED( numberOfOptions );
            cout << RED( "." ) << endl;
            ok = false;
        }
    } while ( !ok );
    
    return op;
}

void RUN_TEST_CASES_MENU() {
    int op = -1;
        
    cout << endl;
    cout << "Escolha a classe de testes para rodar: " << endl;
    cout << "  (1) Todos os testes" << endl;
    vector<string> testClasses;
    int numberOfOptions = 2;
    for( const auto& pair : __test_cases_map ) {
        testClasses.push_back( pair.first );
        cout << "  (" << numberOfOptions << ") " << GREEN( pair.first ) << endl;
        numberOfOptions++;
    }
    cout << "  (0) Sair" << endl;
    
    op = READ_OPTION( numberOfOptions );

    if ( op > 0 && op-2 < (int)testClasses.size() ) {
        if ( op == 1 ) {
            RUN_ALL_TEST_CASES();
        } else {
            string testClass = testClasses[ op-2 ];
            RUN_TEST_CASES_BY_CLASS( testClass );
            op = 0;
        }
    }
}

#endif