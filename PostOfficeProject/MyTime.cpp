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
int MyTime::currentTimeAsInt()
{
	return (getCurrentTime().tm_hour * 10000) + (getCurrentTime().tm_min * 100) + getCurrentTime().tm_sec;
}
string MyTime::currentTimeAsFormattedString()
{
	return to_string(getCurrentTime().tm_hour) + ":" + to_string(getCurrentTime().tm_min) + ":" + to_string(getCurrentTime().tm_sec);
}
/// <summary>
/// will return the time as a string in the format of "HH:MM:SS"
/// </summary>
/// <param name="timeAsInt"></param>
/// <returns></returns>
string MyTime::timeAsIntToFormattedString(int timeAsInt)
{
	int hour = timeAsInt / 10000;
	int minute = (timeAsInt % 10000) / 100;
	int second = timeAsInt % 100;
	return to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
}
/// <summary>
/// will returns the current time
/// </summary>
/// <returns></returns>
tm MyTime::getCurrentTime()
{
	time_t current = std::time(nullptr);
	tm current_tm;

	if (localtime_s(&current_tm, &current) != 0)
	{
		std::cerr << "Error getting local time." << std::endl;
		return current_tm;
	}
	return current_tm;
}