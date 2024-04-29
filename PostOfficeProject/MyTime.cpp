#include "MyTime.h"


int MyTime::getCurrentYear()
{
 	return getCurrentTime().tm_year + 1900;
}
int MyTime::getCurrentHour()
{
	return getCurrentTime().tm_hour;
}
int MyTime::getCurrentMinute()
{
	return getCurrentTime().tm_min;
}
int MyTime::getCurrentSecond()
{
	return getCurrentTime().tm_sec;
}
int MyTime::currentTimeAsFormat()
{
	return (getCurrentTime().tm_hour * 10000) + (getCurrentTime().tm_min * 100) + getCurrentTime().tm_sec;
}
tm MyTime::getCurrentTime()
{
	std::time_t current = std::time(nullptr);
	std::tm current_tm;

	if (localtime_s(&current_tm, &current) != 0)
	{
		std::cerr << "Error getting local time." << std::endl;
		return current_tm;
	}
	return current_tm;
}