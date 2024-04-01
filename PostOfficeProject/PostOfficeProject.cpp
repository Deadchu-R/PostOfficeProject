#include <iostream>
#include "PostOfficeLogic.h"

int main()
{
    // create an instance of PostOfficeLogic
    PostOfficeLogic postOfficeLogic;
    // will adjust setting according to config file
    // run the post office logic
    postOfficeLogic.chooseAction();
    std::cout << "Hello World!\n";

}
// create a class for post office itself (aka logic)
// create a class for post office worker
// create a class for Customer


