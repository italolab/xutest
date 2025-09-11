
#include "cbtest.h"
#include "fexec/fexec.h"

const char* DEFAULT_TEST_CLASS = "default";

bool __cbtest_is_print_vectors = true;

stringstream __cbtest_stream;
stringstream __cbtest_throws_fail_stream;
int __cbtest_count_fails = 0;

SourceCodeManager* __ctest_source_code_manager = new SourceCodeManager( DEFAULT_TEST_CLASS );
vector<TestClassInfo*> __cbtest_test_class_infos_vect;
TestClassInfo* __cbtest_test_class_info;
vector<string> __cbtest_test_classes;
string __cbtest_test_class = "";
int __cbtest_op = -1;
int __cbtest_number_of_options = 0;

__assert_fail::__assert_fail( string msg ) : msg( msg ) {}

string __assert_fail::what() const {
    return msg;
}

namespace cbtest {
    void set_print_vectors( bool is_print_vectors ) {
        __cbtest_is_print_vectors = is_print_vectors;
    }
}

inline string __function_name( string testClass, string suffix )  {
    if ( testClass == DEFAULT_TEST_CLASS ) 
        return "___" + suffix;
    return "__" + testClass + "_" + suffix;
}

void __exec_function_by_name( string testClass, string testName ) {
    string funcName = __function_name( testClass, testName );
    fexec::exec( funcName );
}

void __exec_before_all_by_name( string testClass ) {
    string funcName = __function_name( testClass, "before_all" );
    fexec::exec( funcName );
}

void __exec_after_all_by_name( string testClass ) {
    string funcName = __function_name( testClass, "after_all" );
    fexec::exec( funcName );
}

void __exec_before_each_by_name( string testClass ) {
    string funcName = __function_name( testClass, "before_each" );
    fexec::exec( funcName );
}

void __exec_after_each_by_name( string testClass ) {
    string funcName = __function_name( testClass, "after_each" );
    fexec::exec( funcName );
}

TestClassInfo* getTestClassInfo( vector<TestClassInfo*> tcInfos, string testClass ) {
    for( TestClassInfo* tcInfo : tcInfos )
        if ( tcInfo->className == testClass )
            return tcInfo;
    return nullptr;
}

int __read_option( int numberOfOptions ) {
    int op;
            
    bool ok;
    do {
        cout << ">> " << std::flush;
        while( !(cin >> op) ) {
            cout << __red( "Informe uma opção entre 1 e " );
            cout << __red( numberOfOptions );
            cout << __red( "." ) << endl;
            cin.clear();
            cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            cout << ">> " << std::flush;
        }

        ok = true;
        if ( op < 0 || op > numberOfOptions-1 ) {
            cout << __red( "Informe uma opção entre 1 e " );
            cout << __red( numberOfOptions );
            cout << __red( "." ) << endl;
            ok = false;
        }
    } while ( !ok );
    
    return op;
}
