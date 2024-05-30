#pragma once

#include <exception>

class FileTemplateError : public std::exception{
public:
    const char* what()const noexcept{
        return "Wrong file template";
    }
};