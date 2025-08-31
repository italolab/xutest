
#include "cbtest.h"

const char* DEFAULT_TEST_CLASS = "default";

map<string, vector<TestCase*>> __test_cases_map;
stringstream __stream;
bool __is_imp_vectors = true;

__assert_fail::__assert_fail( string msg ) : msg( msg ) {}

string __assert_fail::what() const {
    return msg;
}

namespace cbtest {
    void setImpVectors( bool isImpVectors ) {
        __is_imp_vectors = isImpVectors;
    }
}

int RUN_TEST_CASES_BY_CLASS( string testClass ) {
    if ( __test_cases_map.find( testClass ) == __test_cases_map.end() ) {
        cout << __blue( "Nenhum teste registrado para a classe: " + testClass );
        return 0;
    }

    cout << "Executando " << __green( testClass ) << "..." << endl;

    int countFails = 0;

    vector<TestCase*> testCases = __test_cases_map[ testClass ];
    for( TestCase* testcase : testCases ) {
        string testName = testcase->name;
        cout << "\tExecutando " << __green( testName ) << "... ";
        try {
            testcase->func();
            cout << __white( "Ok" ) << endl;
        } catch ( const __assert_fail& e ) {            
            cout << endl;
            cout << "\n" << __red( "Falha" ) << " em: " << __green( testName ) << " --> " << e.what() << endl;
            cout << endl;
            countFails++;
        }
    }

    if ( countFails == 0 )
        cout << __green( testClass ) << __white( " Ok!" ) << endl;
    else cout << __green( testClass ) << ": " << __red( std::to_string( countFails ) ) << __white( " falha(s)!" ) << endl;
    cout << endl;

    return countFails;
}

void RUN_ALL_TEST_CASES() {
    cout << __white( "**** EXECUTANDO TESTES ****" ) << endl;
    cout << endl;
    
    int countFails = 0;
    for( const auto& pair : __test_cases_map )
        countFails += RUN_TEST_CASES_BY_CLASS( pair.first );
    
    if ( countFails == 0 )
        cout << "Todos os testes passaram com sucesso!" << endl;
    else cout << "Houve falha em " << countFails << " teste(s)" << endl;
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

void RUN_TEST_CASES_MENU() {
    int op = -1;
        
    cout << endl;
    cout << "Escolha a classe de testes para rodar: " << endl;
    cout << "  (1) Todos os testes" << endl;
    vector<string> testClasses;
    int numberOfOptions = 2;
    for( const auto& pair : __test_cases_map ) {
        testClasses.push_back( pair.first );
        cout << "  (" << numberOfOptions << ") " << __green( pair.first ) << endl;
        numberOfOptions++;
    }
    cout << "  (0) Sair" << endl;
    
    op = __read_option( numberOfOptions );

    if ( op > 0 && op-2 < (int)testClasses.size() ) {
        cout << endl;
        if ( op == 1 ) {
            RUN_ALL_TEST_CASES();
        } else {
            cout << __white( "**** EXECUTANDO TESTES ****" ) << endl;
            cout << endl;

            string testClass = testClasses[ op-2 ];
            RUN_TEST_CASES_BY_CLASS( testClass );
            op = 0;
        }
    }
}
