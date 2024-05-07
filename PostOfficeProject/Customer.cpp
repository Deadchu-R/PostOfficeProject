#include "Customer.h"


string Customer::getAppointmentNumber()
{
	return appointmentNumber;
}
void Customer::setAppointmentNumber(int customersInQueue, int elderCustomersInQueue)
{
	if (customersInQueue == elderCustomersInQueue || customersInQueue == 0) customersInQueue++; 
	if (isElderly()) appointmentNumber = "E" + to_string(elderCustomersInQueue);
	else appointmentNumber = "Y" + to_string(customersInQueue - elderCustomersInQueue);
}
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







