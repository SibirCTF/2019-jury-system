#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <syslog.h>
#include <chrono>
#include <thread>
#include <algorithm>
#include <service_checker_thread.h>
#include <team.h>
#include <utils_logger.h>
#include <light_http_server.h>
#include <http_handler_web_folder.h>
#include <http_handler_api_v1.h>
#include <utils_help_parse_args.h>
#include <storages.h>
#include <unistd.h>
#include <limits.h>
#include <fs.h>
#include <fallen.h>
#include <resources_manager.h>

LightHttpServer g_httpServer;
std::vector<ServiceCheckerThread *> g_vThreads;

// ---------------------------------------------------------------------

void quitApp(int signum) {
  std::cout << std::endl << "Terminating server by signal " << signum << std::endl;
  g_httpServer.stop();
  exit(1);
}

// ---------------------------------------------------------------------

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";

    HelpParseArgs helpParseArgs(argc, argv);

    helpParseArgs.addHelp("help", "-h", false,
        "This help");

    helpParseArgs.addHelp("clean", "-cl", false, 
        "Clean all flags from storage");

    helpParseArgs.addHelp("version", "-v", false,
        "Print version");

    helpParseArgs.addHelp("start", "-s", false, 
        "Start jury");

    helpParseArgs.addHelp("check", "-ch", false,
        "Just check config");

    helpParseArgs.addHelp("check-http", "-cht", false, 
        "Start alone http server for check");

    helpParseArgs.addHelp("--workspace-dir", "-wd", true, 
        "Custom workspace folder with configs, logging, services and etc.");

    helpParseArgs.addHelp("--extract-files", "-ef", false, 
        "Will be created all default files");

    std::string sArgsErrors;
    if (!helpParseArgs.checkArgs(sArgsErrors)){
        Log::err(TAG, "Arguments has errors " + sArgsErrors);
        return -1;
    }

    if (helpParseArgs.has("version")) {
        std::cout << "" << JURY_AD_APP_NAME << " " << JURY_AD_VERSION << "\n";
        return 0;
    }

    if (helpParseArgs.has("help")) {
        helpParseArgs.printHelp();
        return 0;
    }

    std::string sWorkspace = "/usr/share/fhq-jury-ad/jury.d"; // default workspace
    if (helpParseArgs.has("--workspace-dir")) {
        // todo replace workspace path
        sWorkspace = helpParseArgs.option("--workspace-dir");
        sWorkspace = WSJCppCore::getCurrentDirectory() + sWorkspace;
        sWorkspace = WSJCppCore::doNormalizePath(sWorkspace);
        if (!Fallen::dirExists(sWorkspace)) {
            Log::err(TAG, "Directory " + sWorkspace + " does not exists");
            return -1;
        }
        // TODO check directory existing and apply dir
    }
    
    /*if (sWorkspace.length() > 0) {
        if (sWorkspace[0] != '/') { // linux
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Current working dir: %s\n", cwd);
                sWorkspace = std::string(cwd) + "/" + sWorkspace;
            } else {
                std::cout << "getcwd() error" << std::endl;
            }
        }
    }*/

    if (!FS::dirExists(sWorkspace)) {
        std::cout << "Error: Folder " << sWorkspace << " does not exists \n";
        return -1;
    }

    // create default folders and files
    if (helpParseArgs.has("--extract-files")) {
        if (!ResourcesManager::make(sWorkspace)) {
            std::cout << "Could not create some folders or files in " << sWorkspace << " please check access" << std::endl;
            return -1;
        }
    }

    std::string sLogDir = sWorkspace + "/logs";
    if (!FS::dirExists(sLogDir)) {
        std::cout << "Error: Folder " << sLogDir << " does not exists \n";
        return -1;
    }

    Log::setDir(sLogDir);
    std::cout << "Logger: '" + sWorkspace + "/logs/' \n";
    Log::info(TAG, "Version: " + std::string(JURY_AD_VERSION));

    Config *pConfig = new Config(sWorkspace);
    if(!pConfig->applyConfig()){
        Log::err(TAG, "Configuration file has some problems");
        return -1;
    }

    if (helpParseArgs.has("check")) {
        return 0;
    }

    if (helpParseArgs.has("clean")) {
        Log::warn(TAG, "Cleaning flags from storage...");
        pConfig->storage()->clean();
        Log::ok(TAG, "DONE");
        return 0;
    }

    // configure http handlers
    g_httpServer.handlers()->add((LightHttpHandlerBase *) new HttpHandlerWebFolder(pConfig->scoreboardHtmlFolder()));

    signal( SIGINT, quitApp );
    signal( SIGTERM, quitApp );

    if (helpParseArgs.has("check-http")) {
        pConfig->setStorage(Storages::create("file", pConfig->gameStartUTCInSec(), pConfig->gameEndUTCInSec())); // replace storage to ram for tests
        // std::cout << "==== SCOREBOARD ==== \n" << pConfig->scoreboard()->toString() << "\n";
        g_httpServer.handlers()->add((LightHttpHandlerBase *) new HttpHandlerApiV1(pConfig));
        g_httpServer.setPort(pConfig->scoreboardPort());
        g_httpServer.setMaxWorkers(1);
        g_httpServer.startSync(); // will be block thread
        return 0;
    }

    if (helpParseArgs.has("start")) {
        Log::info(TAG, "Starting...");

        pConfig->scoreboard()->initStateFromStorage();

        for (unsigned int iservice = 0; iservice < pConfig->servicesConf().size(); iservice++) {
            for (unsigned int iteam = 0; iteam < pConfig->teamsConf().size(); iteam++) {
                Team teamConf = pConfig->teamsConf()[iteam];
                Service serviceConf = pConfig->servicesConf()[iservice];

                // reset status to down
                pConfig->scoreboard()->setServiceStatus(teamConf.id(), serviceConf.id(), ServiceStatusCell::SERVICE_DOWN);
                // pConfig->scoreboard()->setTeamTries();

                ServiceCheckerThread *thr = new ServiceCheckerThread(pConfig, teamConf, serviceConf);
                thr->start();
                g_vThreads.push_back(thr);
            }
        }

        Log::ok(TAG, "Start scoreboard on " + std::to_string(pConfig->scoreboardPort()));
        g_httpServer.handlers()->add((LightHttpHandlerBase *) new HttpHandlerApiV1(pConfig));
        // pConfig->setStorage(new RamStorage(pConfig->scoreboard())); // replace storage to ram for tests
        g_httpServer.setPort(pConfig->scoreboardPort());
        g_httpServer.setMaxWorkers(10);
        g_httpServer.startSync(); // will be block thread

        // TODO: stop all threads

        /*while(1) {
            Log::info(TAG, "wait 2 minutes");
            std::this_thread::sleep_for(std::chrono::minutes(2));
            Log::info(TAG, "wait ended");
        }*/
        return 0;
    }

    helpParseArgs.printHelp();
    return 0;
}
