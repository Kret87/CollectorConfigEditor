#include "HttpServer.h"
#include <fstream>
#include <iterator>

void HttpServer::run(int port){
    
    std::string html = readFile("../web/index.html");
    std::string js = readFile("../web/app.js");

    std::string json = readFile("config.json");

    serveStaticFile("/",html,"text/html");
    serveStaticFile("/app.js",js,"application/javascript");
    serveStaticFile("/api/config",json,"application/json");

    server_.listen("localhost", port);
}

std::string HttpServer::readFile(const std::string& path){
    std::ifstream file(path);

    if (!file)
        throw(std::runtime_error("Unable to open file: " + path));
    

    std::string text{std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>()};
    return text;
}

void HttpServer::serveStaticFile(const std::string& path, const std::string& content, const std::string& content_type){
        server_.Get(path, [content,content_type](const httplib::Request& req,
                       httplib::Response& res)
    {
        res.set_content(content,content_type);
    });

}
