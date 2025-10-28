#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>

struct StringData
{
    size_t length;
    size_t capacity;
    char* ptr;
};


const size_t SSO_BUFFER_SIZE = 24;

class String
{
    friend std::ostream& operator<<(std::ostream& os, const String& str);
    friend std::istream& operator>>(std::istream& is, String& str);

public:
    String(const char* str = "");
    String(const String& other);
    ~String();

    String& operator=(const String& other);

    const char* c_str() const;
    size_t length() const;
    size_t capacity() const;
    bool isDynamic() const;

private:
    size_t getDinamicLength() const;
    void setDinamicLength(const size_t length);
    void initFrom(const char* str);
    void assign(const char* str);
    void makeDynamic(const char* str, const  size_t len);
    void makeStatic(const char* str, const size_t len);

private:
    union
    {
        StringData data;
        char small_[SSO_BUFFER_SIZE];
    };
};

#endif // STRING_HPP

