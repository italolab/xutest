#ifndef SOURCE_CODE_MANAGER_H
#define SOURCE_CODE_MANAGER_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

typedef struct TTestInfo {
    string name;
    string className;
} TestInfo;

class SourceCodeManager {

    private:
        string defaultTestClass;

        void loadTestInfos( 
                map<string, vector<TestInfo*>>& testInfos, 
                vector<string>& processedFilePaths, 
                string filePath );

        bool interpretsInclude( string line, string filePath, string& includePath );
        bool interpretsTestCase( string line, string filePath, TestInfo*& testInfo );

    public:
        SourceCodeManager( string defaultTestClass );
        
        map<string, vector<TestInfo*>> testInfos( string filePath );

};

#endif