#include <iostream>
#include <string>

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

EM_JS(void, call_js, (), {
    jsMethod();
});

bool callJsBack()
{
    emscripten::val Math = emscripten::val::global("Math");
    int x = Math.call<int>("abs", -10);
    std::cout << x << std::endl;

    {
        std::string msg = "Message from C++";
        emscripten::val o = emscripten::val::global("jsMethodWithMsg");
        o.call<int>(msg.c_str());
    }
    call_js();
    return true;
}

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::function("callJsBack", &callJsBack);
}