#include "CApp.h"
#include <iostream>

int main(int argc, char* argv[]){

    CApp theApp;
    try{
    theApp.OnExecute();
    } 
    catch(...){
        std::cerr << "good-bye!";
    }
    return 0;

}