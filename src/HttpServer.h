#pragma once
#include <string>
#include "httplib.h"

class HttpServer
{
private:

    httplib::Server server_;

    std::string readFile(const std::string& path);
    void serveStaticFile(const std::string& path, const std::string& content, const std::string& content_type);

public:
    void run(int port = 8080);

};

