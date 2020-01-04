#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include <emscripten.h>
#include <emscripten/bind.h>

bool writeFileinCpp(const std::string &data)
{
    bool res = false;

    const std::filesystem::path &dir = "DemoDir";

    if (!std::filesystem::exists(dir))
    {
        create_directory(dir);
    }

    std::cout << "directory exist: " << dir << std::endl;

    std::filesystem::path filePath(dir);
    filePath.append("example.txt");

    std::ofstream myfile;
    myfile.open(filePath, std::ios_base::app);

    if (myfile.is_open())
    {
        myfile << data;
        myfile.close();

        res = true;
        std::cout << "file opetaion successful" << std::endl;
    }
    else
    {
        EM_ASM({console.error('Can not open file for writing')});
    }

    return res;
}

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::function("writeFileinCpp", &writeFileinCpp);
}