#include "Customer.h"


int Customer::age()
{
	return time.getCurrentYear() - birthYear;
}

void Customer::setCustomerHour()
{
	int currentHour = time.currentTimeAsFormat();
	cout << "current hour is: " << currentHour << endl;
	customerHour = currentHour;
}
int Customer::getCustomerHour()
{
	return customerHour;
}







