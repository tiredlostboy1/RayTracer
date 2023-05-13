#include "CApp.hpp"
#include <iostream>

int main()
{
    CApp theApp;
    try
    {
        theApp.OnExecute();
    }
    catch (...)
    {
        std::cerr << "good-bye!";
    }
    return 0;
}