#include "PostOfficeLogic.h"

int main()
{
    PostOfficeLogic::getInstance().setOfficeSettings();
    PostOfficeLogic::getInstance().runPostOffice();
}



