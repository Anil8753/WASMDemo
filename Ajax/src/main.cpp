#include <iostream>
#include <string>

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/fetch.h>

void downloadSucceeded(emscripten_fetch_t *fetch)
{
    printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
    std::cout << "Data: " << std::endl
              << (fetch->data) << std::endl;
    // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
    emscripten_fetch_close(fetch); // Free data associated with the fetch.
}

void downloadFailed(emscripten_fetch_t *fetch)
{
    printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
    emscripten_fetch_close(fetch); // Also free data on failure.
}

void asyncGet()
{
    std::cout << "============= Making async ajax ============" << std::endl;

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = downloadSucceeded;
    attr.onerror = downloadFailed;
    emscripten_fetch(&attr, "http://localhost:8000/data.json");
}

void syncGet()
{
    std::cout << "============= Making sync ajax ============" << std::endl;

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_SYNCHRONOUS;
    emscripten_fetch_t *fetch = emscripten_fetch(&attr, "http://localhost:8000/data.json"); // Blocks here until the operation is complete.

    if (fetch->status == 200)
    {
        printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
        std::cout << "Data: " << std::endl
                  << (fetch->data) << std::endl;
        // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
    }
    else
    {
        printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
    }

    emscripten_fetch_close(fetch);
}

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::function("asyncGet", &asyncGet);
    emscripten::function("syncGet", &syncGet);
}