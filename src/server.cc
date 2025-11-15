/* Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Please refer the documentation / README.md for more information
 * Goblin's Demonic Tiny Web Server - GDTWS is a free and open source program written with the help of cpp-httplib by Yuji Hirose, But the one which is maintained by the GDTWS Project not the official one, So any bugs related to the webserver are intended to go to the issues of GDTWS.
 * Feel free to write your own backend on top of this or modify this as your wish
 */


#define GDWFM_VERSION 1.0
#define GDWFM_SERVER_FILESYSTEM_CONFIG_ICON_DIR_PATH "/.gdwfm-server/config/icon/"
#define GDWFM_SERVER_FILESYSTEM_CONFIG_DIR_PATH "/.gdwfm-server/config/"
#define GDWFM_HOST_FILESYSTEM_CONFIG_DIR_PATH "~/.config/gdwfm/"
#define GDWFM_FD_FILE_NAME "GDWFM_FD_FILE_NAME_FD-GDWFM_VERSION0644" // Just a unique name for a temporary fd
#include "../include/httplib/httplib.h"
#include <iostream>
#include <fstream>
#include <filesystem>

int is_valid_integer (std::string val){
    for (char c : val){
        if (c >= '0' or c <= '9'){
            continue;
        }
        else {
            return 0;
        }
    }
    return 1;
}

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    if (from.empty()) return str; // avoid infinite loop

    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // move past the replacement
    }
    return str;
}

std::vector<std::string> list_files(const std::string& path) {
    std::vector<std::string> files;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                files.push_back(entry.path().filename().string());
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading directory: " << e.what() << "\n";
    }

    return files;
}


std::vector<std::string> list_directories(const std::string& path) {
    std::vector<std::string> dirs;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_directory()) {
                dirs.push_back(entry.path().filename().string());
            }
        }
    }
    catch (const std::exception&) {
        // unreadable directory → return empty vector
    }

    return dirs;
}

std::string read_file(std::string path){
    std::string content = "", temp;
    std::ifstream ifile(path);
    if (ifile.is_open()){ // it is a file
        std::cout<<"It is a file!\n";
        char c;
        while (std::getline(ifile, temp)) content += temp + '\n';
        content.pop_back();
    }
    else {
        std::cout<<"It is not a file!\n"<<path<<" is the server path\n";
    }
    return content;
}

int main(int argc, char* argv[]){
    int port = 8080; // Default Port
    std::string root_dir = "."; // Default Root Directory
    std::string host = "0.0.0.0"; // Default host
    for (int i = 0;i < argc;i++){
        std::string command = argv[i];
        if (command == "--version" or command == "-v"){
            std::cout << "GDWFM " << GDWFM_VERSION << "\n";
            return 0;
        }
        else if (command == "--port" or command == "-p" and i+1 < argc){
            if (is_valid_integer(argv[i+1])){
                port = std::stoi (argv[i+1]);
            }
            else {
                std::cout << "The value to the port must be a valid integer!\n";
                return 3;
            }
        }
        else if (command == "--root" or command == "-r" and i+1 < argc){
            root_dir = argv[i+1];
        }
        else if (command == "--host" or command == "-h" and i+1 < argc){
            host = argv[i+1];
        }
    }



    // Main logic starts here
    httplib::Server svr;
    if (svr.is_valid()){
        std::cout << "Setting up the server...\n";
        std::string cfg_dir_path = GDWFM_HOST_FILESYSTEM_CONFIG_DIR_PATH;
        std::string srv_cfg_dir_path = GDWFM_SERVER_FILESYSTEM_CONFIG_DIR_PATH;
        if (std::filesystem::is_regular_file(cfg_dir_path + "/index.html") and std::filesystem::is_regular_file(cfg_dir_path + "/android.button.js")){
            std::cout << "Server starter failed! Critical error found! no index.html file was found and no android.button.js file was found at the standard host config ~/.config/gdwfm/ directory. Please reinstall or fix this problem by installing a theme for the GDWFM. If you believe that this was a bug then please report on https://github.com/daryboys/gdwfm/issues\n";
            std::exit ( 3 );
        }
        std::system (std::string("mkdir -p 2>/dev/null " + root_dir + srv_cfg_dir_path).c_str());
        std::system (std::string("cp -r " + cfg_dir_path + "/* " + root_dir + srv_cfg_dir_path).c_str());
        std::cout << "The server was started on http://" << host << ":" << port << "\n";
    }
    

    svr.set_pre_routing_handler([root_dir](const httplib::Request &req, httplib::Response &res){
        std::cout << "\nGot the request: "<<req.path<<"\n";
        // res.set_content("<h1>This is a nice hi! From the server</h1>", "text/html"); // Only for testing purpose to see if the server is handling thwe requests or not
        std::string path = root_dir + req.path;
        if (std::filesystem::is_regular_file(path)){
            std::string file = read_file(path);
            std::size_t html_file_extension = req.path.rfind(".html"); // len 5
            std::size_t css_file_extension = req.path.rfind(".css"); // len 5
            std::size_t js_file_extension = req.path.rfind(".js"); // len 5
            std::size_t png_file_extension = req.path.rfind(".png"); // len 5
            std::size_t jpg_file_extension = req.path.rfind(".jpg"); // len 5
            std::size_t jpeg_file_extension = req.path.rfind(".jpeg"); // len 5
            if (html_file_extension != std::string::npos and html_file_extension + 5 == req.path.length())
                res.set_content(file.c_str(), "text/html; charset=utf-8");
            else if (css_file_extension != std::string::npos and css_file_extension + 4 == req.path.length())
                res.set_content(file.c_str(), "text/css; charset=utf-8");
            else if (js_file_extension != std::string::npos and js_file_extension + 3 == req.path.length())
                res.set_content(file.c_str(), "application/javascript; charset=utf-8");
            else if (png_file_extension != std::string::npos and png_file_extension + 4 == req.path.length())
                res.set_content(file.c_str(), file.length(), "image/png");
            else if (jpg_file_extension != std::string::npos and jpg_file_extension + 4 == req.path.length())
                res.set_content(file.c_str(), file.length(), "image/jpg");
            else if (jpeg_file_extension != std::string::npos and jpeg_file_extension + 5 == req.path.length())
                res.set_content(file.c_str(), file.length(), "image/jpeg");
            else {
                res.set_content(file.c_str(), "text/plain; charset=utf-8");
            }
            // res.set_content(file.c_str(), file.length(), "image/png");
        }
        else if (std::filesystem::is_directory(path)){
            std::string ui_file_path = ".";
            ui_file_path += GDWFM_SERVER_FILESYSTEM_CONFIG_DIR_PATH;
            ui_file_path += "ui.html";
            std::string ui = read_file(ui_file_path);
            ui += "<script>";
            for (std::string file_name : list_files(path)){
                if (req.path == "/"){
                    ui += "add_file(`" + replaceAll(file_name, "`", "\\`") + "`, `" + replaceAll(req.path, "`", "\\`") + file_name + "`);\n";
                }
                else {
                    ui += "add_file(`" + replaceAll(file_name, "`", "\\`") + "`, `" + replaceAll(req.path, "`", "\\`") + "/" + file_name + "`);\n";
                }
            }
            for (std::string dir_name : list_directories(path)){
                if (req.path == "/"){
                    ui += "add_directory(`" + replaceAll(dir_name, "`", "\\`") + "`, `" + replaceAll(req.path, "`", "\\`") + dir_name + "`);\n";
                }
                else {
                    ui += "add_directory(`" + replaceAll(dir_name, "`", "\\`") + "`, `" + replaceAll(req.path, "`", "\\`") + "/" + dir_name + "`);\n";
                }
            }
            ui += "apply_ripple();</script>";
            res.set_content(ui, "text/html");
        }
        else {
            std::string ui_file_path = ".";
            ui_file_path += GDWFM_SERVER_FILESYSTEM_CONFIG_DIR_PATH;
            ui_file_path += "ui.html";
            std::string ui = read_file(ui_file_path);
            ui += "<script>files_container.innerHTML += `<div class='not-found-404-cont'><div><h1 class='not-found-404'>404 Not Found</h1><p class='not-found-404-msg'>No such file or directory</p></div></div>`;</script>";
            res.set_content(ui, "text/html");
        }
        return httplib::Server::HandlerResponse::Handled;
    });

    svr.listen(host, port);

}