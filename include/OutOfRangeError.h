#pragma once

#include <exception>

class OutOfRangeError : public std::exception{
public:
    const char* what()const noexcept{
        return "Value out of range";
    }
};