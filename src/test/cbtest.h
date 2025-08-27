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



vector<TestCase*> testCases;

#define TEST_CASE( name, testClass ) \
    void _##testClass##_##name () \

#define ADD_TEST_CASE( name2, testClass2 ) \
    TestCase* tc = new TestCase { \
        #name2, \
        #testClass2, \
        _##testClass2##_##name2 }; \
    testCases.push_back( tc ); \

#define RUN_ALL_TEST_CASES() \
    cout << "EXECUTANDO TESTES..." << endl; \
    cout << endl; \
    for( TestCase* test : testCases ) { \
        string testName = test->name; \
        if ( test->testClass != "" ) \
            testName = test->testClass +"." + testName; \
        cout << "Executando " << testName << "... "; \
        try { \
            test->func(); \
            cout << "Ok" << endl; \
        } catch ( const assert_fail& e ) { \
            cerr << "Erro." << endl; \
            cerr << "\tErro em: " << testName << e.what(); \
        } \
    } \
    

#define ASSERT_EQUAL( a, b, errorMsg ) \
    if ( (a) != (b) ) { \
        if ( strlen( #errorMsg ) == 0 ) \
            throw assert_fail( #errorMsg ); \
        \
        stringstream ss; \
        ss << a << " != " << b << endl; \
        throw assert_fail( ss.str() ); \
    } \

#endif