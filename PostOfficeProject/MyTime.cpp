#include "MyTime.h"


/// <summary>
/// returning the current year
/// </summary>
/// <returns></returns>
int MyTime::getCurrentYear()
{
 	return getCurrentTime().tm_year + 1900;
}
/// <summary>
/// Returning the current hour
/// </summary>
/// <returns></returns>
int MyTime::getCurrentHour()
{
	return getCurrentTime().tm_hour;
}
/// <summary>
/// Returning the current minute
/// </summary>
/// <returns></returns>
int MyTime::getCurrentMinute()
{
	return getCurrentTime().tm_min;
}
/// <summary>
/// returning the current second
/// </summary>
/// <returns></returns>
int MyTime::getCurrentSecond()
{
	return getCurrentTime().tm_sec;
}
/// <summary>
/// returning the current time as an integer in the format of HHMMSS
/// </summary>
/// <returns></returns>
int MyTime::currentTimeAsInt()
{
	return (getCurrentTime().tm_hour * 10000) + (getCurrentTime().tm_min * 100) + getCurrentTime().tm_sec;
}
/// <summary>
/// returning the current time as a string in the format of "HH:MM:SS"
/// </summary>
/// <returns></returns>
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
	time_t current = time(nullptr);
	tm current_tm;

	if (localtime_s(&current_tm, &current) != 0)
	{
		cerr << "Error getting local time." << endl;
		return current_tm;
	}
	return current_tm;
}