#pragma once
#include <ctime>
#include <iostream>
#include <string>
using namespace std;
class MyTime
{
public:
    int getCurrentYear();
    tm getCurrentTime();
    int getCurrentHour();
    int getCurrentMinute();
    int getCurrentSecond();
    int currentTimeAsInt();
    string currentTimeAsFormattedString();
    string timeAsIntToFormattedString(int timeAsInt);

};

