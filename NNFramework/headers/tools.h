

#pragma once

#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <iostream>
#include <string>
#include <Python.h>

#ifdef _WIN32   // Windows
    #include <direct.h>
#else           // Linux or Mac
    #include <unistd.h>
#endif


namespace Tools{

class GenHelper {
public:
    static std::string GetCurrentWorkingPath() {
        std::vector<char> _buf(1024);
        char* _res = nullptr;

#ifdef _WIN32
        _res = _getcwd(_buf.data(), _buf.size());
#else
        _res = getcwd(buf.data(), _buf.size());
#endif


        while(_res == nullptr && errno == ERANGE){  /* if _buf not enough */
            _buf.resize(_buf.size() * 2);
#ifdef _WIN32
            _res = _getcwd(_buf.data(), _buf.size());
#else
            _res = getcwd(_buf.data(), _buf.size());
#endif
        }

        if(_res != nullptr)
            return std::string(_buf.data());
        else{
            perror("getcwd() error!");
            return "";
        }
    }


};






}


#endif