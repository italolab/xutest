
#include "cbtest.h"

const char* DEFAULT_TEST_CLASS = "default";

map<string, vector<TestCase*>> __test_cases_map;
bool __is_imp_vectors = true;

stringstream __stream;
int __countFails = 0;

SourceCodeManager* sourceCodeManager = new SourceCodeManager( DEFAULT_TEST_CLASS );
map<string, vector<TestInfo*>> __test_infos_map;
vector<string> __test_classes;
string __test_class = "";
int __op = -1;
int __number_of_options = 0;


__assert_fail::__assert_fail( string msg ) : msg( msg ) {}

string __assert_fail::what() const {
    return msg;
}

namespace cbtest {
    void setImpVectors( bool isImpVectors ) {
        __is_imp_vectors = isImpVectors;
    }
}

void __exec_function_by_name( string testName, string testClassName ) {
    void* handle = dlopen( nullptr, RTLD_LAZY );

    if ( !handle ) {
        cout << "Shared library de funções de teste não carregada: " << "\n"; 
        cout << dlerror() << endl;
        return;
    }

    dlerror();

    string fname = __test_function_name( testName, testClassName );

    typedef void (*FunctionType)();
    FunctionType func = (FunctionType)dlsym( handle, fname.c_str() );
    const char* error = dlerror();
    if ( error ) {
        cout << "Função de teste não carregada: " << fname << "\n" << error << endl;
        dlclose( handle );
        return;
    }

    func();

    dlclose( handle );
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
