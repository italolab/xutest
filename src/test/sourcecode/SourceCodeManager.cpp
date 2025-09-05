
#include "SourceCodeManager.h"
#include "../util/io.h"
#include "../util/strutil.h"

#include <fstream>

using std::ifstream;

namespace strutil = testfw::strutil;
namespace io = testfw::io;

SourceCodeManager::SourceCodeManager( string defaultTestClass ) {
    this->defaultTestClass = defaultTestClass;
}

vector<TestClassInfo*> SourceCodeManager::testInfos( string filePath ) {
    vector<TestClassInfo*> testClassInfosVect;
    vector<string> processedFilePaths;

    this->loadTestInfos( testClassInfosVect, processedFilePaths, filePath );

    return testClassInfosVect;
}

void SourceCodeManager::loadTestInfos( 
            vector<TestClassInfo*>& testClassInfosVect, 
            vector<string>& processedFilePaths,
            string filePath ) {

    for( string processedFilePath : processedFilePaths ) 
        if ( processedFilePath == filePath )
            return;

    ifstream in( filePath );
    if ( !in.is_open() )
        return;
    
    vector<string> includePaths;

    string line;
    bool isIgnoreLine = false;
    while( getline( in, line ) ) {
        if ( isIgnoreLine ) {
            size_t i = line.find( "*/" );
            if ( i == string::npos )
                continue;

            line = line.substr( i+2, line.length()-i-2 );
            isIgnoreLine = false;            
        }

        bool isFinishedComment = removeComments( line );
        if ( !isFinishedComment ) {
            isIgnoreLine = true;
            if ( strutil::trim( line ) == "" )
                continue;
        }

        string includePath;
        bool interpreted = this->interpretsInclude( line, filePath, includePath );
        if ( interpreted ) {
            includePaths.push_back( includePath );
            continue;
        } 
        
        string testClass;
        string testName;
        interpreted = this->interpretsTestCase( line, testClass, testName );        
        if ( interpreted ) {
            TestClassInfo* tcInfo = this->getAndAddClassIfNeed( testClassInfosVect, testClass );
            tcInfo->testNames.push_back( testName );           
            continue;
        }

        interpreted = this->interpretsClassMethod( line, "BEFORE_ALL", testClass );
        if ( interpreted ) {
            TestClassInfo* tcInfo = this->getAndAddClassIfNeed( testClassInfosVect, testClass );
            tcInfo->beforeAllFlag = true;         
            continue;
        }

        interpreted = this->interpretsClassMethod( line, "AFTER_ALL", testClass );
        if ( interpreted ) {
            TestClassInfo* tcInfo = this->getAndAddClassIfNeed( testClassInfosVect, testClass );
            tcInfo->afterAllFlag = true;         
            continue;
        }

        interpreted = this->interpretsClassMethod( line, "BEFORE_EACH", testClass );
        if ( interpreted ) {
            TestClassInfo* tcInfo = this->getAndAddClassIfNeed( testClassInfosVect, testClass );
            tcInfo->beforeEachFlag = true;         
            continue;
        }

        interpreted = this->interpretsClassMethod( line, "AFTER_EACH", testClass );
        if ( interpreted ) {
            TestClassInfo* tcInfo = this->getAndAddClassIfNeed( testClassInfosVect, testClass );
            tcInfo->afterEachFlag = true;         
            continue;
        }        
    }

    in.close();

    processedFilePaths.push_back( filePath );

    for( string includePath : includePaths )
        this->loadTestInfos( testClassInfosVect, processedFilePaths, includePath );
}

TestClassInfo* SourceCodeManager::getAndAddClassIfNeed( 
            vector<TestClassInfo*>& testClassInfosVect, string& testClass ) {
    if ( testClass == "" )
        testClass = defaultTestClass;
    
    TestClassInfo* tcInfo = this->getTestClassFromVector( testClassInfosVect, testClass );
    if ( tcInfo == nullptr ) {
        tcInfo = new TestClassInfo;
        tcInfo->className = testClass;
        tcInfo->testNames = {};
        tcInfo->beforeAllFlag = false;
        tcInfo->afterAllFlag = false;
        tcInfo->beforeEachFlag = false;
        tcInfo->afterEachFlag = false;
        testClassInfosVect.push_back( tcInfo );
    }

    return tcInfo;
}

TestClassInfo* SourceCodeManager::getTestClassFromVector( 
            vector<TestClassInfo*>& testClassInfoVect, string testClass ) {                
    for( TestClassInfo* tcInfo : testClassInfoVect )
        if ( tcInfo->className == testClass )
            return tcInfo;
    return nullptr;
}

/*
Remove os comentários  da linha e retorna se foi encontrado um abre bloco de comentário 
e foi fechado ou não foi encontrado comentário na linha
*/
bool SourceCodeManager::removeComments( string& line ) {
    size_t i = line.find( "/*" );
    size_t k = line.find( "//" );
    if ( i == string::npos && k == string::npos )
        return true;
        
    size_t j = -1;
    do {
        if ( i != string::npos ) {
            j = line.find( "*/" );
            if ( j != string::npos ) {
                string sub1 = line.substr( 0, i );
                string sub2 = line.substr( j+1, line.length()-j-1 );
                line = sub1 + sub2;

                i = line.find( "/*", i+1 );
            }
        }
    } while( i != string::npos && j != string::npos );

    bool isFinishedComment = true;
    if ( i != string::npos && j == string::npos ) {
        line = line.substr( 0, i );
        isFinishedComment = false;
    }

    k = line.find( "//" );
    if ( k != string::npos )
        line = line.substr( 0, k );

    return isFinishedComment;
}

bool SourceCodeManager::interpretsInclude( string line, string filePath, string& includePath ) {
    if ( !strutil::startsWith( line, "#include" ) )
        return false;

    size_t i = line.find( '\"' );
    size_t j = line.find( '\"', i+1 );

    if ( i == string::npos || j == string::npos )
        return false;

    includePath = line.substr( i+1, j-i-1 );

    string dir = io::path::dirPath( filePath );
    includePath = io::path::resolvePath( dir, includePath );            

    return true;
}

bool SourceCodeManager::interpretsTestCase( 
            string line, 
            string& testClass,
            string& testName ) {
    string line2 = strutil::removeStartWhiteSpaces( line );
    if ( !strutil::startsWith( line2, "TEST_CASE" ) )
        return false;
    
    size_t i = line2.find( '(' );
    size_t j = line2.find( ')' );

    if ( i == string::npos || j == string::npos )
        return false;

    string params = line2.substr( i+1, j-i-1 );
    size_t k = params.find( ',' );

    testName = params.substr( 0, k );
    testClass = params.substr( k+1, params.length()-k-1 );
    testName = strutil::trim( testName );
    testClass = strutil::trim( testClass );

    return true;
}

bool SourceCodeManager::interpretsClassMethod( string line, string macroName, string& testClass ) {
    string line2 = strutil::removeStartWhiteSpaces( line );
    if ( !strutil::startsWith( line2, macroName ) )
        return false;
    
    size_t i = line2.find( '(' );
    size_t j = line2.find( ')' );

    if ( i == string::npos || j == string::npos )
        return false;

    string params = line2.substr( i+1, j-i-1 );

    testClass = strutil::trim( params );

    return true;
}