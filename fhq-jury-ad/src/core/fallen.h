#ifndef FALLEN_H
#define FALLEN_H

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <json.hpp>
#include <deque>

class Fallen {
    public:
        static long currentTime_milliseconds();
        static long currentTime_seconds();
        static std::string currentTime_forFilename();
        static std::string currentTime_logformat();
        static std::string threadId();
        static std::string formatTimeForWeb(long nTimeInSec);
        static std::string formatTimeForFilename(long nTimeInSec);
        static std::string formatTimeUTC(int nTimeInSec);

        static bool dirExists(const std::string &sFilename);
        static bool fileExists(const std::string &sFilename);
        static std::vector<std::string> listOfDirs(const std::string &sDirname);
        static std::vector<std::string> listOfFiles(const std::string &sDirname);     
        static bool makeDir(const std::string &sDirname);
        static bool writeFile(const std::string &sFilename, const std::string &sContent);
        static bool writeFile(const std::string &sFilename, const char *pBuffer, const int nBufferSize);

        static std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
        static std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
        static std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
        static std::string& to_lower(std::string& str);

        static void initRandom();
        static std::string createUuid();
        static unsigned long convertVoid2Int(void *p);
        static std::string getPointerAsHex(void *p);
        
        
};

class WSJCppCore {
    public:
        static bool init(
            int argc, char** argv, 
            const std::string &sApplicationName,
            const std::string &sApplicationVersion,
            const std::string &sApplicationAuthor,
            const std::string &sLibraryNameForExports
        );

        static std::string doNormalizePath(const std::string & sPath);
        static std::string getCurrentDirectory();
};

// 
// ---------------------------------------------------------------------

enum FallenHelpParseArgType {
    PARAMETER,
    SINGLE_OPTION
};

// ---------------------------------------------------------------------

class FallenHelpParseArg {
    public:
        // TODO redesign to alias list {"1", "2"}
        FallenHelpParseArg(const std::string &sName, const std::string &sAlias, FallenHelpParseArgType nType, const std::string &sDescription);
        FallenHelpParseArg();
        std::string name();
        std::string alias();
        std::string description();
        bool isOption();

    private:
        std::string m_sName;
        std::string m_sAlias;
        std::string m_sDescription;
        bool m_bIsOption;
};

// ---------------------------------------------------------------------

class FallenHelpParseArgs {
    public:
        FallenHelpParseArgs(int argc, char** argv);
        void setAppName(const std::string &sAppName);
        void setAppVersion(const std::string &sAppVersion);
        bool has(const std::string &sName);
        std::string option(const std::string &sName);
        void addHelp(const std::string &sName, const std::string &sAlias, FallenHelpParseArgType nType, const std::string &sDescription);
        void printHelp();
        bool checkArgs(std::string &sArgsErrors);

    private:
        std::vector<std::string> m_vArgs;
        std::vector<FallenHelpParseArg *> m_vHelpArgs;
        std::string m_sAppName;
        std::string m_sAppVersion;
};

// ---------------------------------------------------------------------

#endif // FALLEN_H
