#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Helpers/LoggerHelper.h"

const std::string LoggerHelper::LogPath_ = "log.txt";

void LoggerHelper::addNewRecord(std::string record) {

    std::fstream f;

    f.open(LogPath_, std::ios::app);
    if(!f){
        std::cout << "No log was found. Creating one!";

        f.open(LogPath_, std::ios::app | std::ios::trunc);
    }

    auto t = time(nullptr);
    auto tm = *localtime(&t);

    f << std::put_time(&tm, "[%d-%m-%Y | %H:%M] ") << record << std::endl;

    f.close();
}

std::string LoggerHelper::getLastTenRecords() {
    std::fstream f;

    f.open(LogPath_);
    if(!f){
        std::cout << "No log was found! There is nothing to read from!";
        return "";
    }

    std::vector<std::string> strVec;

    if(f.is_open()){

        std::string line;
        while (getline(f, line)){
            strVec.push_back(line + "\n");
        }
    }

    std::string result = "";

    for(int i = strVec.size() > 10 ? strVec.size() - 10 : 0; i < strVec.size(); i++){
        result.append(strVec[i]);
    }

    f.close();

    return result;
}
