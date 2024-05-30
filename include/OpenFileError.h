#pragma once

#include <exception>

class OpenFileError : public std::exception{
public:
    const char* what()const noexcept{
        return "Can't open file";
    }
};