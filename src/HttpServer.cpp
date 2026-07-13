#include "HttpServer.h"
#include <fstream>
#include <iterator>
#include <iostream>
#include "jsonSerializer.h"

void HttpServer::run(int port){
    
    serveStaticFile("/","../web/index.html","text/html");
    serveStaticFile("/app.js","../web/app.js","application/javascript");
    serveStaticFile("/api/config","config.json","application/json");

    server_.Post("/api/config",[](const httplib::Request& req, httplib::Response& res)
    {
        std::cout << "Received configuration:\n";
        std::cout << req.body << '\n';

        json config;

        try{
            config = json::parse(req.body);
            configToPollTargets(config);
        }catch(const std::exception& e){
            res.status = 400;

            json response;
            response["status"] = "failed";
            response["message"] = e.what();

            res.set_content(response.dump(), "application/json");
            return;
        }
            
            std::ofstream file("config.json");

            if(!file){
                res.set_content(
                R"({"status":"failed"})",
                "application/json");
                res.status = 500;
                return;
            }

            file << config.dump(4);

            res.set_content(
                R"({"status":"saved"})",
                "application/json");

    });

    server_.listen("localhost", port);
}

std::string HttpServer::readFile(const std::string& path){
    std::ifstream file(path);

    if (!file)
        throw(std::runtime_error("Unable to open file: " + path));
    

    std::string text{std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>()};
    return text;
}

void HttpServer::serveStaticFile(const std::string& path, const std::string& filepath, const std::string& content_type){

        server_.Get(path, [this,filepath,content_type](const httplib::Request& req,
                       httplib::Response& res)
    {
        std::string content = readFile(filepath);
        res.set_header("Cache-Control", "no-store");
        res.set_content(content,content_type);
    });

}
