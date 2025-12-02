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

String::String(const String& rhv)
{
    initFrom(rhv.c_str());
}

char&
String::at(const size_t index)
{
    return (*this)[index];
}

char*
String::begin()
{
    return isDynamic() ? data.ptr : small_ + 1;
}

const char*
String::begin() const
{
    return isDynamic() ? data.ptr : small_ + 1;
}

char*
String::end()
{
    return begin() + length();
}

const char*
String::end() const
{
    return begin() + length();
}


const char&
String::operator[](const size_t index) const
{
    if (isDynamic()) return data.ptr[index];
    return small_[index + 1];
}

char&
String::operator[](const size_t index)
{
    if (isDynamic()) return data.ptr[index];
    return small_[index + 1];
}



String::String(String&& rhv) noexcept
{
    if (rhv.isDynamic()) {
        data = rhv.data;
        rhv.data.ptr = NULL;
        rhv.data.length = 0;
        rhv.data.capacity = 0;
        rhv.small_[0] = 0;
        return;
    }
    std::memcpy(small_, rhv.small_, SSO_BUFFER_SIZE);
    rhv.small_[0] = 0;
    rhv.small_[1] = '\0';
}

bool
String::operator!=(const String& other) const
{
    return !(*this == other);
}

void
String::clear()
{
    if (isDynamic()) {
        delete[] data.ptr;
        data.ptr = NULL;
        data.capacity = 0;
        setDinamicLength(0);
        return;
    }

    small_[0] = 0;
    small_[1] = '\0';
}

bool
String::operator==(const String& other) const
{
    return std::strcmp(c_str(), other.c_str()) == 0;
}

String&
String::operator=(String&& rhv) noexcept
{
    if (this == &rhv) return *this;
    if (isDynamic()) {
        delete[] data.ptr;
        data.ptr = NULL;
    }

    if (rhv.isDynamic()) {
        data = rhv.data;
        rhv.data.ptr = NULL;
        rhv.data.length = 0;
        rhv.data.capacity = 0;
        rhv.small_[0] = 0;
        return *this;
    }
    std::memcpy(small_, rhv.small_, SSO_BUFFER_SIZE);
    rhv.small_[0] = 0;
    rhv.small_[1] = '\0';
    return *this;
}

void
String::reserve(const size_t newCap)
{
    if (newCap < length())
        return;

    if (!isDynamic()) {
        if (newCap < SSO_BUFFER_SIZE - 1)
            return;

        char* newBuf = new char[newCap + 1];

        size_t len = length();
        std::memcpy(newBuf, c_str(), len + 1);

        data.ptr = newBuf;
        data.capacity = newCap;
        setDinamicLength(len);
        return;
    }

    if (newCap <= data.capacity)
        return;

    char* newBuf = new char[newCap + 1];

    std::memcpy(newBuf, data.ptr, length() + 1);

    delete[] data.ptr;
    data.ptr = newBuf;
    data.capacity = newCap;
}


String::~String()
{
    if (isDynamic() && data.ptr != NULL) {
        delete[] data.ptr;
        data.ptr = NULL;
    }
}

String&
String::operator=(const String& rhv)
{
    if (this != &rhv) assign(rhv.c_str());
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

bool
String::empty() const
{
    return length() == 0;
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
String::assign(const size_t count, const char ch)
{
    if (count == 0) {
        clear();
        return;
    }

    if (count < SSO_BUFFER_SIZE - 1) {
        if (isDynamic()) {
            delete[] data.ptr;
            data.ptr = nullptr;
        }

        small_[0] = 0;
        for (size_t i = 0; i < count; ++i)
            small_[i + 1] = ch;

        small_[count + 1] = '\0';
        return;
    }

    if (isDynamic() && data.capacity >= count) {
        for (size_t i = 0; i < count; ++i)
            data.ptr[i] = ch;

        data.ptr[count] = '\0';
        setDinamicLength(count);
        return;
    }

    if (isDynamic())
        delete[] data.ptr;

    data.capacity = count;
    data.ptr = new char[count + 1];
    for (size_t i = 0; i < count; ++i)
        data.ptr[i] = ch;

    data.ptr[count] = '\0';
    setDinamicLength(count);
}

void
String::push_back(char ch)
{
    const size_t len = length();

    if (!isDynamic()) {
        if (len < SSO_BUFFER_SIZE - 2) {
            small_[len + 1] = ch;
            small_[len + 2] = '\0';
            return;
        }
        size_t newCap = (len + 1) * 2;
        char* newPtr = new char[newCap + 1];
        std::memcpy(newPtr, small_ + 1, len);
        newPtr[len] = ch;
        newPtr[len + 1] = '\0';

        data.ptr = newPtr;
        data.capacity = newCap;

        setDinamicLength(len + 1);
        return;
    }

    if (len + 1 > data.capacity) {
        const size_t newCap = (len + 1) * 2;
        char* newPtr = new char[newCap + 1];
        std::memcpy(newPtr, data.ptr, len);
        delete[] data.ptr;
        data.ptr = newPtr;
        data.capacity = newCap;
    }

    data.ptr[len] = ch;
    data.ptr[len + 1] = '\0';
    setDinamicLength(len + 1);
}


String&
String::append(const char* str)
{
    const size_t addLen = std::strlen(str);
    const size_t oldLen = length();

    if (!isDynamic() && oldLen + addLen < SSO_BUFFER_SIZE - 1)
    {
        std::memcpy(small_ + 1 + oldLen, str, addLen + 1);
        return *this;
    }

    const size_t newLen = oldLen + addLen;
    if (!isDynamic() || newLen > data.capacity) {
        const size_t newCap = newLen * 2;
        char* newPtr = new char[newCap + 1];
        if (isDynamic())
            std::memcpy(newPtr, data.ptr, oldLen);
        else
            std::memcpy(newPtr, small_ + 1, oldLen);

        if (isDynamic())
            delete[] data.ptr;

        data.ptr = newPtr;
        data.capacity = newCap;
        setDinamicLength(newLen);
    } else {
        setDinamicLength(newLen);
    }
    std::memcpy(data.ptr + oldLen, str, addLen + 1);
    return *this;
}

String&
String::append(const String& other)
{
    return append(other.c_str());
}

void
String::makeStatic(const char* str, const size_t len)
{
    small_[0] = 0;
    std::memcpy(small_ + 1, str, len + 1);
}

void
String::assign(const String& rhv)
{
    if (this == &rhv) return;
    if (isDynamic()) {
        delete[] data.ptr;
        data.length = 0;
        data.capacity = 0;
        data.ptr = nullptr;
    }
    initFrom(rhv.c_str());
}

void
String::resize(const size_t newSize)
{
    const size_t oldSize = length();
    if (newSize <= oldSize) {
        if (isDynamic()) {
            data.ptr[newSize] = '\0';
            setDinamicLength(newSize);
        } else {
            small_[newSize + 1] = '\0';
        }
        return;
    }
    reserve(newSize);

    if (isDynamic()) {
        for (size_t i = oldSize; i < newSize; ++i)
            data.ptr[i] = '\0';
        data.ptr[newSize] = '\0';
        setDinamicLength(newSize);
    } else {
        for (size_t i = oldSize; i < newSize; ++i)
            small_[i + 1] = '\0';
        small_[newSize + 1] = '\0';
    }
}

String
String::operator+(const String& other) const
{
    String result;
    const size_t newLen = length() + other.length();
    result.reserve(newLen);

    result.assign(*this);
    result += other;
    return result;
}

String&
String::operator+=(const String& other)
{
    const size_t oldLen = length();
    const size_t newLen = oldLen + other.length();

    reserve(newLen);

    if (isDynamic()) {
        std::memcpy(data.ptr + oldLen, other.c_str(), other.length() + 1);
        setDinamicLength(newLen);
    } else {
        std::memcpy(small_ + oldLen + 1, other.c_str(), other.length() + 1);
    }

    return *this;
}

void
String::swap(String& other) noexcept
{
    std::swap(data, other.data);
    char temp[SSO_BUFFER_SIZE];
    std::memcpy(temp,    small_,           SSO_BUFFER_SIZE);
    std::memcpy(small_,  other.small_,     SSO_BUFFER_SIZE);
    std::memcpy(other.small_, temp,        SSO_BUFFER_SIZE);
}
String
String::substr(size_t pos, size_t count) const
{
    if (pos >= length())
        return String("");

    if (pos + count > length())
        count = length() - pos;

    String result;
    result.assign(count, '\0');

    char* dst = (char*)result.c_str();
    const char* src = c_str() + pos;

    for (size_t i = 0; i < count; ++i)
        dst[i] = src[i];

    dst[count] = '\0';

    return result;
}
size_t
String::find(const String& what, size_t start) const
{
    const size_t hayLen = length();
    const size_t needleLen = what.length();

    if (needleLen == 0)
        return 0;


    for (size_t i = start; i + needleLen <= hayLen; ++i) {
        if (std::memcmp(c_str() + i, what.c_str(), needleLen) == 0)
            return i;
    }

    return length() - 1;
}
bool
String::starts_with(const String& str) const
{
    const size_t M = str.length();
    if (M > length()) return false;
    return std::memcmp(c_str(), str.c_str(), M) == 0;

}
bool
String::ends_with(const String& str) const
{
    const size_t N = length();
    const size_t M = str.length();
    if (M > N) return false;
    return std::memcmp(c_str() + (N - M), str.c_str(), M) == 0;
}

