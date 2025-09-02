#ifndef CBTEST_H
#define CBTEST_H

#include "sourcecode/SourceCodeManager.h"

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
using std::exception;
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

extern bool __cbtest_is_imp_vectors;

extern stringstream __cbtest_stream;
extern int __cbtest_count_fails;

extern SourceCodeManager* __ctest_source_code_manager;
extern map<string, vector<TestInfo*>> __cbtest_test_infos_map;
extern vector<string> __cbtest_test_classes;
extern string __cbtest_test_class;
extern int __cbtest_op;
extern int __cbtest_number_of_options;

namespace cbtest {

    void setImpVectors( bool isImpVectors );
    
}

void __exec_function_by_name( string testName, string testClassName );
int __read_option( int numberOfOptions ) ;

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


#define THROW_FAIL( errorMsg, otherErrorMsg ) { \
    __cbtest_stream.str( "" ); \
    __cbtest_stream.clear(); \
    __cbtest_stream << __FILE__ << "(" << __LINE__ << "): "; \
    if ( strlen( #errorMsg ) == 0 ) \
        __cbtest_stream << #otherErrorMsg; \
    __cbtest_stream << #errorMsg; \
    \
    throw __assert_fail( __cbtest_stream.str() ); \
}

// ASSERTS PARA VECTORS E ARRAYS

#define ASSERT_EQUALS_VECTORS( v1, v2, errorMsg ) \
    if ( !__equals_vectors( v1, v2 ) ) { \
        if ( strlen( #errorMsg ) != 0 ) \
            THROW_FAIL( errorMsg, ); \
        \
        __cbtest_stream.str( "" ); \
        __cbtest_stream.clear(); \
        __cbtest_stream << __FILE__ << "(" << __LINE__ << "): Os vetores deveriam ser iguais!" << endl; \
        if ( __cbtest_is_imp_vectors ) { \
            __cbtest_stream << "\nVetor(1)= " << __vector_str( v1 ) << endl; \
            __cbtest_stream << "Vetor(2)= " << __vector_str( v2 ); \
        } \
        throw __assert_fail( __cbtest_stream.str() ); \
    } \

#define ASSERT_NOT_EQUALS_VECTORS( v1, v2, errorMsg ) \
    if ( __equals_vectors( v1, v2 ) ) { \
        if ( strlen( #errorMsg ) != 0 ) \
            THROW_FAIL( errorMsg, ); \
        \
        __cbtest_stream.str( "" ); \
        __cbtest_stream.clear(); \
        __cbtest_stream << __FILE__ << "(" << __LINE__ << "): Os vetores deveriam ser diferentes!" << endl; \
        if ( __cbtest_is_imp_vectors ) { \
            __cbtest_stream << "\nVetor(1)= " << __vector_str( v1 ) << endl; \
            __cbtest_stream << "Vetor(2)= " << __vector_str( v2 ); \
        } \
        throw __assert_fail( __cbtest_stream.str() ); \
    } \

#define ASSERT_EQUALS_ARRAYS( a1, a2, len, errorMsg ) \
    if ( !__equals_arrays( a1, a2, len ) ) { \
        if ( strlen( #errorMsg ) != 0 ) \
            THROW_FAIL( errorMsg, ); \
        \
        __cbtest_stream.str( "" ); \
        __cbtest_stream.clear(); \
        __cbtest_stream << __FILE__ << "(" << __LINE__ << "): Os arrays deveriam ser iguais!" << endl; \
        if ( __cbtest_is_imp_vectors ) { \
            __cbtest_stream << "\nArray(1)= " << __array_str( a1, len ) << endl; \
            __cbtest_stream << "Array(2)= " << __array_str( a2, len ); \
        } \
        throw __assert_fail( __cbtest_stream.str() ); \
    } \

#define ASSERT_NOT_EQUALS_ARRAYS( a1, a2, len, errorMsg ) \
    if ( __equals_arrays( a1, a2, len ) ) { \
        if ( strlen( #errorMsg ) != 0 ) \
            THROW_FAIL( errorMsg, ); \
        \
        __cbtest_stream.str( "" ); \
        __cbtest_stream.clear(); \
        __cbtest_stream << __FILE__ << "(" << __LINE__ << "): Os arrays deveriam ser diferentes!" << endl; \
        if ( __cbtest_is_imp_vectors ) { \
            __cbtest_stream << "\nArray(1)= " << __array_str( a1, len ) << endl; \
            __cbtest_stream << "Array(2)= " << __array_str( a2, len ); \
        } \
        throw __assert_fail( __cbtest_stream.str() ); \
    } \

// OUTROS ASSERTS

#define ASSERT_EQUALS( a, b, errorMsg ) \
    if ( a != b ) \
        THROW_FAIL( errorMsg, deveriam ser iguais! ); \

#define ASSERT_NOT_EQUALS( a, b, errorMsg ) \
    if ( a == b ) \
        THROW_FAIL( errorMsg, Deveriam ser diferentes! ); \

#define ASSERT_TRUE( condicao, errorMsg ) \
    if ( !(condicao) ) \
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
    extern "C" void __##testClass##_##name () \

inline string __test_function_name( string testName, string testClass ) {
    if ( testClass == DEFAULT_TEST_CLASS ) 
        return "___" + testName;
    return "__" + testClass + "_" + testName;
}

#define RUN_TEST_CASES_BY_CLASS( testClass, testInfos ) \
    cout << "Executando " << __green( testClass ) << "..." << endl; \
    \
    __cbtest_count_fails = 0; \
    \
    for( TestInfo* testInfo : testInfos ) { \
        cout << "\tExecutando " << __green( testInfo->name ) << "... "; \
        try { \
            __exec_function_by_name( testInfo->name, testInfo->className ); \
            cout << __white( "Ok" ) << endl; \
        } catch ( const __assert_fail& e ) { \
            cout << endl; \
            cout << "\n" << __red( "Falha" ) << " em: " << __green( testInfo->name ) << " --> " << e.what() << endl; \
            cout << endl; \
            __cbtest_count_fails++; \
        } catch ( const exception& e ) { \
            cout << endl; \
            cout << "\nException em: " << __green( testInfo->name ) << " --> " << __red( e.what() ) << endl; \
            cout << endl; \
            __cbtest_count_fails++; \
        } catch ( ... ) { \
            cout << endl; \
            cout << "\nException desconhecida em: " << __green( testInfo->name ) << endl; \
            cout << endl; \
            __cbtest_count_fails++; \
        } \
    } \
    \
    if ( __cbtest_count_fails == 0 ) \
        cout << __green( testClass ) << __white( " Ok!" ) << endl; \
    else cout << __green( testClass ) << ": " << __red( std::to_string( __cbtest_count_fails ) ) << __white( " falha(s)!" ) << endl; \
    cout << endl; \

#define RUN_ALL_TEST_CASES() \
    cout << __white( "**** EXECUTANDO TESTES ****" ) << endl; \
    cout << endl; \
    \
    int countFails = 0; \
    __cbtest_test_infos_map = __ctest_source_code_manager->testInfos( __FILE__ ); \
    for( const auto& pair : __cbtest_test_infos_map ) { \
        RUN_TEST_CASES_BY_CLASS( pair.first, pair.second ); \
        countFails += __cbtest_count_fails; \
    } \
    \
    if ( countFails == 0 ) \
        cout << "Todos os testes passaram com sucesso!" << endl; \
    else cout << "Houve falha em " << countFails << " teste(s)" << endl; \

#define RUN_TEST_CASES_MENU() \
    __cbtest_op = -1; \
    \
    cout << endl; \
    cout << "Escolha a classe de testes para rodar: " << endl; \
    cout << "  (1) Todos os testes" << endl; \
    __cbtest_number_of_options = 2; \
    \
    __cbtest_test_infos_map = __ctest_source_code_manager->testInfos( __FILE__ ); \
    \
    __cbtest_test_classes.clear(); \
    for( const auto& pair : __cbtest_test_infos_map ) { \
        __cbtest_test_classes.push_back( pair.first ); \
        cout << "  (" << __cbtest_number_of_options << ") " << __green( pair.first ) << endl; \
        __cbtest_number_of_options++; \
    } \
    cout << "  (0) Sair" << endl; \
    \
    __cbtest_op = __read_option( __cbtest_number_of_options ); \
    \
    if ( __cbtest_op > 0 && __cbtest_op-2 < (int)__cbtest_test_classes.size() ) { \
        cout << endl; \
        if ( __cbtest_op == 1 ) { \
            RUN_ALL_TEST_CASES(); \
        } else { \
            cout << __white( "**** EXECUTANDO TESTES ****" ) << endl; \
            cout << endl; \
            \
            __cbtest_test_class = __cbtest_test_classes[ __cbtest_op-2 ]; \
            __cbtest_test_infos_map = __ctest_source_code_manager->testInfos( __FILE__ ); \
            if ( __cbtest_test_infos_map.find( __cbtest_test_class ) != __cbtest_test_infos_map.end() ) { \
                RUN_TEST_CASES_BY_CLASS( __cbtest_test_class, __cbtest_test_infos_map[ __cbtest_test_class ] ); \
            } \
            __cbtest_op = 0; \
        } \
    } \

#endif