#include "Customer.h"


int Customer::age()
{
	return time.getCurrentYear() - birthYear;
}

void Customer::setCustomerHour()
{
	int currentHour = time.currentTimeAsInt();
	cout << "current hour is: " << currentHour << endl;
	customerHour = currentHour;
}
int Customer::getCustomerHour()
{
	return customerHour;
}
string Customer::getCustomerHourAsFormattedString()
{
	return time.timeAsIntToFormattedString(customerHour);
}
bool Customer::isElderly()
{
	return age() >= 65;
}







