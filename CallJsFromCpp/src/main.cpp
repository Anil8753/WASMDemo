#include <iostream>
#include <string>

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

//////////////////////////////////////////////////////////////////
EM_JS(void, call_js, (), {
    jsMethod();
});

bool callJsBack()
{
    call_js();
    return true;
}

//////////////////////////////////////////////////////////////////
EM_JS(void, call_js_agrs, (const char *title, int lentitle, const char *msg, int lenmsg), {
    jsMethodAgrs(UTF8ToString(title, lentitle), UTF8ToString(msg, lenmsg));
});

bool callJsBackWithAgrs()
{
    const std::string title = "Hello from C++";
    const std::string msg = "This string is passed as a paramter from C++ code!";
    call_js_agrs(title.c_str(), title.length(), msg.c_str(), msg.length());
    return true;
}

//////////////////////////////////////////////////////////////////
EM_JS(void, callback, (int index, const char *msg, int lenmsg), {
    functionMap(index, UTF8ToString(msg, lenmsg));
});

void cppFunctionWithJsCallback(int index)
{
    const std::string msg = "Js callback called with this data from C++ code!";
    callback(index, msg.c_str(), msg.length());
}

//////////////////////////////////////////////////////////////////
EMSCRIPTEN_BINDINGS(module)
{
    emscripten::function("callJsBack", &callJsBack);
    emscripten::function("callJsBackWithAgrs", &callJsBackWithAgrs);
    emscripten::function("cppFunctionWithJsCallback", &cppFunctionWithJsCallback);
}