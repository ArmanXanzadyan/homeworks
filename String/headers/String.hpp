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
    String(const String& rhv);


    String(String&& rhv) noexcept;
    String& operator=(String&& rhv) noexcept;
/*
char& operator[](size_t index);
const char& operator[](size_t index) const;
bool operator==(const String& other) const;
bool operator!=(const String& other) const;
void push_back(char ch);
String& append(const char* str);
String& append(const String& other);
void reserve(size_t newCap);
void resize(size_t newSize);
String operator+(const String& other) const;
String& operator+=(const String& other);
char* begin();
char* end();
const char* begin() const;
const char* end() const;
bool empty() const;
void clear();
void swap(String& other) noexcept;
String substr(size_t pos, size_t count) const;
size_t find(const String& what, size_t start = 0) const;
bool starts_with(const String& str) const;
bool ends_with(const String& str) const;
void assign(const String& other);
void assign(size_t count, char ch);
char& at(size_t index);
*/
    ~String();

    String& operator=(const String& rhv);

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

