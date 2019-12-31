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
    call_js();
    return true;
}

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::function("callJsBack", &callJsBack);
}