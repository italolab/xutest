
#include "cbtest.h"
#include "fexec/fexec.h"

const char* DEFAULT_TEST_CLASS = "default";

bool __cbtest_is_imp_vectors = true;

stringstream __cbtest_stream;
stringstream __cbtest_throws_fail_stream;
int __cbtest_count_fails = 0;

SourceCodeManager* __ctest_source_code_manager = new SourceCodeManager( DEFAULT_TEST_CLASS );
map<string, vector<TestInfo*>> __cbtest_test_infos_map;
vector<string> __cbtest_test_classes;
string __cbtest_test_class = "";
int __cbtest_op = -1;
int __cbtest_number_of_options = 0;

__assert_fail::__assert_fail( string msg ) : msg( msg ) {}

string __assert_fail::what() const {
    return msg;
}

namespace cbtest {
    void setImpVectors( bool isImpVectors ) {
        __cbtest_is_imp_vectors = isImpVectors;
    }
}

void __exec_function_by_name( string testName, string testClassName ) {
    string funcName = __test_function_name( testName, testClassName );
    fexec::exec( funcName );
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
