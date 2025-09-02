
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

map<string, vector<TestInfo*>> SourceCodeManager::testInfos( string filePath ) {
    map<string, vector<TestInfo*>> testInfosMap;
    vector<string> processedFilePaths;

    this->loadTestInfos( testInfosMap, processedFilePaths, filePath );

    return testInfosMap;
}

void SourceCodeManager::loadTestInfos( 
            map<string, vector<TestInfo*>>& testInfosMap, 
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
    while( getline( in, line ) ) {
        string includePath;
        bool interpreted = this->interpretsInclude( line, filePath, includePath );
        if ( interpreted ) {
            includePaths.push_back( includePath );
        } else {
            TestInfo* testInfo;
            interpreted = this->interpretsTestCase( line, filePath, testInfo );
            if ( interpreted ) {
                if ( testInfo->className == "" )
                    testInfo->className = defaultTestClass;
                
                if ( testInfosMap.find( testInfo->className ) == testInfosMap.end() ) {
                    vector<TestInfo*> testInfosVect;
                    testInfosMap[ testInfo->className ] = testInfosVect;
                }

                testInfosMap[ testInfo->className ].push_back( testInfo );            
            }
        }
    }

    in.close();

    processedFilePaths.push_back( filePath );

    for( string includePath : includePaths )
        this->loadTestInfos( testInfosMap, processedFilePaths, includePath );
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

bool SourceCodeManager::interpretsTestCase( string line, string filePath, TestInfo*& testInfo ) {
    string line2 = strutil::removeStartWhiteSpaces( line );
    if ( !strutil::startsWith( line2, "TEST_CASE" ) )
        return false;
    
    size_t i = line2.find( '(' );
    size_t j = line2.find( ')' );

    if ( i == string::npos || j == string::npos )
        return false;

    string params = line2.substr( i+1, j-i-1 );
    size_t k = params.find( ',' );

    string testName = params.substr( 0, k );
    string className = params.substr( k+1, params.length()-k-1 );
    testName = strutil::trim( testName );
    className = strutil::trim( className );

    testInfo = new TestInfo{ testName, className };

    return true;
}