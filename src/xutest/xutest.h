#ifndef xutest_H
#define xutest_H

#include "sourcecode/SourceCodeManager.h"
#include "output/output.h"

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <limits>

using std::string;
using std::stringstream;
using std::vector;
using std::map;
using std::runtime_error;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::cin;

class __assert_fail {

    private:
        string msg;

    public:
        __assert_fail( string msg );

        string what() const;

};

extern const char* DEFAULT_TEST_CLASS;

extern bool __xutest_is_print_vectors;

extern stringstream __xutest_stream;
extern stringstream __xutest_throws_fail_stream;
extern int __xutest_count_fails;

extern SourceCodeManager* __xutest_source_code_manager;
extern vector<TestClassInfo*> __xutest_test_class_infos_vect;
extern TestClassInfo* __xutest_test_class_info;
extern vector<string> __xutest_test_classes;
extern string __xutest_test_class;
extern int __xutest_op;
extern int __xutest_number_of_options;

namespace xutest {

    void set_print_vectors( bool is_print_vectors );
    
}

void __exec_function_by_name( string testClass, string testName );
void __exec_before_all_by_name( string testClass );
void __exec_after_all_by_name( string testClass );
void __exec_before_each_by_name( string testClass );
void __exec_after_each_by_name( string testClass );

TestClassInfo* getTestClassInfo( vector<TestClassInfo*> tcInfos, string testClass );

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

#define THROW_FAIL( errorMsg, otherErrorMsg ) { \
    __xutest_throws_fail_stream.str( "" ); \
    __xutest_throws_fail_stream.clear(); \
    __xutest_throws_fail_stream << __FILE__ << "(" << __LINE__ << "): "; \
    if ( strlen( #errorMsg ) == 0 ) \
        __xutest_throws_fail_stream << __blue( otherErrorMsg ); \
    __xutest_throws_fail_stream << __blue( #errorMsg ); \
    \
    throw __assert_fail( __xutest_throws_fail_stream.str() ); \
} \

// ASSERTS PARA VECTORS E ARRAYS

#define ASSERT_EQUALS_VECTORS( v1, v2, errorMsg ) { \
    if ( !__equals_vectors( v1, v2 ) ) { \
        if ( strlen( #errorMsg ) != 0 ) \
            THROW_FAIL( errorMsg, "" ) \
        \
        __xutest_stream.str( "" ); \
        __xutest_stream.clear(); \
        __xutest_stream << __FILE__ << "(" << __LINE__ << "): Os vetores deveriam ser iguais!" << endl; \
        if ( __xutest_is_print_vectors ) { \
            __xutest_stream << "\nVetor(1)= " << __vector_str( v1 ) << endl; \
            __xutest_stream << "Vetor(2)= " << __vector_str( v2 ); \
        } \
        throw __assert_fail( __xutest_stream.str() ); \
    } \
} \

#define ASSERT_NOT_EQUALS_VECTORS( v1, v2, errorMsg ) { \
    if ( __equals_vectors( v1, v2 ) ) { \
        if ( strlen( #errorMsg ) != 0 ) \
            THROW_FAIL( errorMsg, "" ) \
        \
        __xutest_stream.str( "" ); \
        __xutest_stream.clear(); \
        __xutest_stream << __FILE__ << "(" << __LINE__ << "): Os vetores deveriam ser diferentes!" << endl; \
        if ( __xutest_is_print_vectors ) { \
            __xutest_stream << "\nVetor(1)= " << __vector_str( v1 ) << endl; \
            __xutest_stream << "Vetor(2)= " << __vector_str( v2 ); \
        } \
        throw __assert_fail( __xutest_stream.str() ); \
    } \
} \

#define ASSERT_EQUALS_ARRAYS( a1, a2, len, errorMsg ) { \
    if ( !__equals_arrays( a1, a2, len ) ) { \
        if ( strlen( #errorMsg ) != 0 ) \
            THROW_FAIL( errorMsg, "" ) \
        \
        __xutest_stream.str( "" ); \
        __xutest_stream.clear(); \
        __xutest_stream << __FILE__ << "(" << __LINE__ << "): Os arrays deveriam ser iguais!" << endl; \
        if ( __xutest_is_print_vectors ) { \
            __xutest_stream << "\nArray(1)= " << __array_str( a1, len ) << endl; \
            __xutest_stream << "Array(2)= " << __array_str( a2, len ); \
        } \
        throw __assert_fail( __xutest_stream.str() ); \
    } \
} \

#define ASSERT_NOT_EQUALS_ARRAYS( a1, a2, len, errorMsg ) { \
    if ( __equals_arrays( a1, a2, len ) ) { \
        if ( strlen( #errorMsg ) != 0 ) \
            THROW_FAIL( errorMsg, "" ) \
        \
        __xutest_stream.str( "" ); \
        __xutest_stream.clear(); \
        __xutest_stream << __FILE__ << "(" << __LINE__ << "): Os arrays deveriam ser diferentes!" << endl; \
        if ( __xutest_is_print_vectors ) { \
            __xutest_stream << "\nArray(1)= " << __array_str( a1, len ) << endl; \
            __xutest_stream << "Array(2)= " << __array_str( a2, len ); \
        } \
        throw __assert_fail( __xutest_stream.str() ); \
    } \
} \

// OUTROS ASSERTS

#define ASSERT_EQUALS( a, b, errorMsg ) { \
    if ( a != b ) { \
        __xutest_stream.str( "" ); \
        __xutest_stream << a << " != " << b; \
        THROW_FAIL( errorMsg, __xutest_stream.str() ) \
    } \
} \

#define ASSERT_NOT_EQUALS( a, b, errorMsg ) { \
    if ( a == b ) { \
        __xutest_stream.str( "" ); \
        __xutest_stream << a << " == " << b; \
        THROW_FAIL( errorMsg, __xutest_stream.str() ) \
    } \
} \

#define ASSERT_TRUE( condicao, errorMsg ) { \
    if ( !(condicao) ) { \
        __xutest_stream.str( "" ); \
        __xutest_stream << "( " << #condicao << " ) != true"; \
        THROW_FAIL( errorMsg, __xutest_stream.str() ) \
    } \
} \

#define ASSERT_FALSE( condicao, errorMsg ) { \
    if ( condicao ) { \
        __xutest_stream.str( "" ); \
        __xutest_stream << "( " << #condicao << " ) != false"; \
        THROW_FAIL( errorMsg, __xutest_stream.str() ) \
    } \
} \

#define ASSERT_NULL( obj, errorMsg ) { \
    if ( obj != nullptr && obj != NULL ) { \
        __xutest_stream.str( "" ); \
        __xutest_stream << #obj << " != nullptr"; \
        THROW_FAIL( errorMsg, __xutest_stream.str() ) \
    } \
} \

#define ASSERT_NOT_NULL( obj, errorMsg ) { \
    if ( obj == nullptr || obj == NULL ) { \
        __xutest_stream.str( "" ); \
        __xutest_stream << #obj << " == nullptr"; \
        THROW_FAIL( errorMsg, __xutest_stream.str() ) \
    } \
} \

#define ASSERT_THROWS( except, block, errorMsg ) { \
    try { \
        block \
        __xutest_stream.str(); \
        __xutest_stream << "Deveria lancar uma exceção: " << #except; \
        THROW_FAIL( errorMsg, __xutest_stream.str() ) \
    } catch ( const except& ex ) { \
        \
    } \
} \

#define ASSERT_NOT_THROWS( except, block, errorMsg ) { \
    try { \
        block \
    } catch ( const except& ex ) { \
        __xutest_stream.str(); \
        __xutest_stream << "Exceção lançada: " << #except; \
        __xutest_stream << "\nMensagem de exceção: " << ex.what(); \
        THROW_FAIL( errorMsg, __xutest_stream.str() ); \
    } \
} \

#define FAIL( errorMsg ) { \
    THROW_FAIL( errorMsg, "" ) \
} \

// TEST CASES DEFINES E FUNCTIONS

#ifdef __WIN32

    #define TEST_CASE( name, testClass ) \
        extern "C" __declspec(dllexport) void __##testClass##_##name () \

    #define BEFORE_ALL( testClass ) \
        extern "C" __declspec(dllexport) void __##testClass##_before_all () \

    #define BEFORE_EACH( testClass ) \
        extern "C" __declspec(dllexport) void __##testClass##_before_each () \

    #define AFTER_ALL( testClass ) \
        extern "C" __declspec(dllexport) void __##testClass##_after_all () \

    #define AFTER_EACH( testClass ) \
        extern "C" __declspec(dllexport) void __##testClass##_after_each () \

#else

    #define TEST_CASE( name, testClass ) \
        extern "C" void __##testClass##_##name () \

    #define BEFORE_ALL( testClass ) \
        extern "C" void __##testClass##_before_all () \

    #define BEFORE_EACH( testClass ) \
        extern "C" void __##testClass##_before_each () \

    #define AFTER_ALL( testClass ) \
        extern "C" void __##testClass##_after_all () \

    #define AFTER_EACH( testClass ) \
        extern "C" void __##testClass##_after_each () \

#endif

#define RUN_TEST_CASES_BY_CLASS( testClassInfo ) { \
    cout << "Executando " << __green( testClassInfo->className ) << "..." << endl; \
    \
    __xutest_count_fails = 0; \
    \
    if ( testClassInfo->beforeAllFlag ) \
        __exec_before_all_by_name( testClassInfo->className ); \
    \
    for( string testName : testClassInfo->testNames ) { \
        cout << "\tExecutando " << __green( testName ) << "... "; \
        try { \
            if ( testClassInfo->beforeEachFlag ) \
                __exec_before_each_by_name( testClassInfo->className ); \
            \
            __exec_function_by_name( testClassInfo->className, testName ); \
            \
            if ( testClassInfo->afterEachFlag ) \
                __exec_after_each_by_name( testClassInfo->className ); \
            \
            cout << __white( "Ok" ) << endl; \
        } catch ( const __assert_fail& e ) { \
            cout << endl; \
            cout << "\n" <<  __red( "Falha" ) << " em: " << __green( testName ) << " --> " << e.what() << endl; \
            cout << endl; \
            __xutest_count_fails++; \
        } catch ( const exception& e ) { \
            cout << endl; \
            cout << "\nException em: " << __green( testName ) << " --> " << __red( e.what() ) << endl; \
            cout << endl; \
            __xutest_count_fails++; \
        } catch ( ... ) { \
            cout << endl; \
            cout << "\nException desconhecida em: " << __green( testName ) << endl; \
            cout << endl; \
            __xutest_count_fails++; \
        } \
    } \
    \
    if ( testClassInfo->afterAllFlag ) \
        __exec_after_all_by_name( testClassInfo->className ); \
    \
    if ( __xutest_count_fails == 0 ) \
        cout << __green( testClassInfo->className ) << __white( " Ok!" ) << endl; \
    else cout << __green( testClassInfo->className ) << ": " << __red( std::to_string( __xutest_count_fails ) ) << __white( " falha(s)!" ) << endl; \
    cout << endl; \
} \

#define RUN_ALL_TEST_CASES() { \
    cout << __bold( __white( "**** EXECUTANDO TESTES ****" ) ) << endl; \
    cout << endl; \
    \
    int countFails = 0; \
    __xutest_test_class_infos_vect = __xutest_source_code_manager->testInfos( __FILE__ ); \
    for( TestClassInfo* tcInfo : __xutest_test_class_infos_vect ) { \
        RUN_TEST_CASES_BY_CLASS( tcInfo ) \
        countFails += __xutest_count_fails; \
    } \
    \
    if ( countFails == 0 ) \
        cout << __bold( __white( "Todos os testes passaram com sucesso!" ) ) << endl; \
    else cout << "Houve " << __red( "falha" ) << " em " << __red( std::to_string( countFails ) ) << " teste(s)" << endl; \
} \

#define RUN_TEST_CASES_MENU() { \
    __xutest_op = -1; \
    \
    cout << endl; \
    cout << "Escolha a classe de testes para rodar: " << endl; \
    cout << "  (1) Todos os testes" << endl; \
    __xutest_number_of_options = 2; \
    \
    __xutest_test_class_infos_vect = __xutest_source_code_manager->testInfos( __FILE__ ); \
    \
    __xutest_test_classes.clear(); \
    for( TestClassInfo* tcInfo : __xutest_test_class_infos_vect ) { \
        __xutest_test_classes.push_back( tcInfo->className ); \
        cout << "  (" << __xutest_number_of_options << ") " << __green( tcInfo->className ) << endl; \
        __xutest_number_of_options++; \
    } \
    cout << "  (0) Sair" << endl; \
    \
    __xutest_op = __read_option( __xutest_number_of_options ); \
    \
    if ( __xutest_op > 0 && __xutest_op-2 < (int)__xutest_test_classes.size() ) { \
        cout << endl; \
        if ( __xutest_op == 1 ) { \
            RUN_ALL_TEST_CASES() \
        } else { \
            cout << __white( "**** EXECUTANDO TESTES ****" ) << endl; \
            cout << endl; \
            \
            __xutest_test_class = __xutest_test_classes[ __xutest_op-2 ]; \
            __xutest_test_class_infos_vect = __xutest_source_code_manager->testInfos( __FILE__ ); \
            __xutest_test_class_info = getTestClassInfo( __xutest_test_class_infos_vect, __xutest_test_class ); \
            \
            RUN_TEST_CASES_BY_CLASS( __xutest_test_class_info ) \
            \
            __xutest_op = 0; \
        } \
    } \
} \

#endif