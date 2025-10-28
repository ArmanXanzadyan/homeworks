#include "../headers/String.hpp"
#include <cstring>
#include <cassert>
#include <iostream>

std::ostream&
operator<<(std::ostream& os, const String& str)
{
    return os << str.c_str();
}

std::istream&
operator>>(std::istream& is, String& str)
{
    char buffer[1024];
    is >> buffer;
    str.assign(buffer);
    return is;
}

String::String(const char* str)
{
    initFrom(str);
}

String::String(const String& other)
{
    initFrom(other.c_str());
}

String::~String()
{
    if (isDynamic() && data.ptr != NULL) {
        delete[] data.ptr;
        data.ptr = NULL;
    }
}

String&
String::operator=(const String& other)
{
    if (this != &other) assign(other.c_str());
    return *this;
}

bool
String::isDynamic() const
{
    return (data.length & (size_t(1) << (sizeof(size_t) * 8 - 1))) != 0;
}

size_t
String::length() const
{
    if (isDynamic()) return getDinamicLength();
    return std::strlen(small_ + 1);
}

size_t
String::capacity() const
{
    return isDynamic() ? data.capacity : (SSO_BUFFER_SIZE - 1);
}

const char*
String::c_str() const
{
    return isDynamic() ? data.ptr : small_ + 1;
}

void
String::initFrom(const char* str)
{
    const size_t len = std::strlen(str);
    if (len < SSO_BUFFER_SIZE - 1) {
        makeStatic(str, len);
        return;
    }
    makeDynamic(str, len);
}

void
String::assign(const char* str)
{
    if (isDynamic()) {
        delete[] data.ptr;
        data.ptr = NULL;
    }
    initFrom(str);
}


void
String::setDinamicLength(const size_t length)
{
    data.length = (length | (size_t(1) << (sizeof(size_t) * 8 - 1)));
}

size_t
String::getDinamicLength() const
{
    return data.length & ~(size_t(1) << (sizeof(size_t) * 8 - 1));
}

void
String::makeDynamic(const char* str, const size_t len)
{
    setDinamicLength(len);
    data.capacity = len;
    data.ptr = new char[len + 1];
    std::memcpy(data.ptr, str, len + 1);
}

void
String::makeStatic(const char* str, const size_t len)
{
    small_[0] = 0;
    std::memcpy(small_ + 1, str, len + 1);
}

