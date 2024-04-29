#pragma once
#include <ctime>
#include <iostream>
class MyTime
{
public:
    int getCurrentYear();
    tm getCurrentTime();
    int getCurrentHour();
    int getCurrentMinute();
    int getCurrentSecond();
    int currentTimeAsFormat();
};

