#include <iostream>
#include <string>
#include <locale>
#include <algorithm>
#include <future>
#include <chrono>

#include <emscripten.h>
#include <emscripten/bind.h>

std::string makeUppperCase(const std::string &in)
{
    auto str = in;

    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::toupper(c);
    });

    return str;
}

class MyClass
{
public:
    MyClass(int x, std::string y)
        : x(x), y(y)
    {
    }

    void incrementX()
    {
        ++x;
    }

    int getX() const { return x; }
    void setX(int x_) { x = x_; }

    static std::string getStringFromInstance(const MyClass &instance)
    {
        return instance.y;
    }

private:
    int x;
    std::string y;
};

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::function("makeUppperCase", &makeUppperCase);

    emscripten::class_<MyClass>("MyClass")
        .constructor<int, std::string>()
        .function("incrementX", &MyClass::incrementX)
        .property("x", &MyClass::getX, &MyClass::setX)
        .class_function("getStringFromInstance", &MyClass::getStringFromInstance);
}