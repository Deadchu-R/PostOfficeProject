#include "Customer.h"


int Customer::age()
{
    int currentYear = getCurrentTime().tm_year + 1900;
	return currentYear - birthYear;
}

void Customer::setCustomerHour()
{
	int currentHour = (getCurrentTime().tm_hour * 10000) + (getCurrentTime().tm_min * 100) + getCurrentTime().tm_sec;
	cout << "current hour is: " << currentHour << endl;
	customerHour = currentHour;
}
int Customer::getCustomerHour()
{
	return customerHour;
}

tm Customer::getCurrentTime()
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





