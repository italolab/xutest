#ifndef SOURCE_CODE_MANAGER_H
#define SOURCE_CODE_MANAGER_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

typedef struct TTestClassInfo {
    string className;
    vector<string> testNames;
    bool beforeAllFlag;
    bool afterAllFlag;
    bool beforeEachFlag;
    bool afterEachFlag;
} TestClassInfo;

class SourceCodeManager {

    private:
        string defaultTestClass;

        void loadTestInfos( 
                vector<TestClassInfo*>& testClassInfosVect, 
                vector<string>& processedFilePaths, 
                string filePath );

        bool interpretsInclude( string line, string filePath, string& includePath );
        
        bool interpretsTestCase( 
                string line, 
                string& testClass, 
                string& testName );

        bool interpretsClassMethod( string line, string macroName, string& testClass );

        bool removeComments( string& line );

        TestClassInfo* getAndAddClassIfNeed( 
            vector<TestClassInfo*>& testClassInfosVect, string& testClass );

        TestClassInfo* getTestClassFromVector( 
                vector<TestClassInfo*>& testClassInfoVect, string testClass );

    public:
        SourceCodeManager( string defaultTestClass );
        
        vector<TestClassInfo*> testInfos( string filePath );

};

#endif