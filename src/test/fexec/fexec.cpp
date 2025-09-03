
#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include "fexec.h"
#include "../output/output.h"

#include <sstream>

using std::stringstream;
using std::runtime_error;

#include <iostream>
using namespace std;

namespace fexec {

#ifdef _WIN32

void exec( string funcName ) {
    HMODULE hModule = GetModuleHandleA( NULL );
     if ( hModule == NULL ) {
        stringstream ss;
        ss << __red( "Executável de funções de teste não carregado." ) << "\n"; 
        ss << __red( GetLastError() );

        throw runtime_error( ss.str() );
    }

    FARPROC funcAddress = GetProcAddress( hModule, funcName.c_str() );
    if ( funcAddress == NULL ) {
        stringstream ss;
        ss << __red( "Função de teste não carregada." ) << "\n";
        ss << __red( GetLastError() );

        throw runtime_error( ss.str() );
    }

    typedef void (*FunctionType)();
    FunctionType func = reinterpret_cast<FunctionType>( funcAddress );

    func();
}

#else

void exec( string funcName ) {
    void* handle = dlopen( nullptr, RTLD_LAZY );

    if ( !handle ) {
        stringstream ss;
        ss << __red( "Shared library de funções de teste não carregada." ) << "\n"; 
        ss << __red( dlerror() );

        throw runtime_error( ss.str() );
    }

    dlerror();

    typedef void (*FunctionType)();
    FunctionType func = (FunctionType)dlsym( handle, funcName.c_str() );
    const char* error = dlerror();
    if ( error ) {
        stringstream ss;
        ss << __red( "Função de teste não carregada." ) << "\n";
        ss << __red( error );
        dlclose( handle );

        throw runtime_error( ss.str() );
    }

    func();

    dlclose( handle );
}

#endif

}