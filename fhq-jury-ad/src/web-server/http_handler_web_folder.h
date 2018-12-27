#ifndef HTTP_HANDLER_WEB_FOLDER_H
#define HTTP_HANDLER_WEB_FOLDER_H

#include <light_http_handler_base.h>

class HttpHandlerWebFolder : LightHttpHandlerBase {
    public:
        HttpHandlerWebFolder(const std::string &sWebFolder);
        virtual bool canHandle(const std::string &sWorkerId, LightHttpRequest *pRequest);
        virtual bool handle(const std::string &sWorkerId, LightHttpRequest *pRequest);

    private:
        std::string TAG;
        std::string m_sWebFolder;
};

#endif // HTTP_HANDLER_WEB_FOLDER_H
