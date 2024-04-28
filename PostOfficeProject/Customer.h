#pragma once
#include <string>
#include <ctime>
#include <iostream>
using namespace std;
class Customer // aka data class
{
	public:
	int birthYear = 1998;
	string name = "John Doe";
	int ID = 500000000; // lets say 9 digit number
	int actionType = 0;
	int age();
	void setCustomerHour();
	int getCustomerHour();
	tm getCurrentTime();

private:
	int customerHour = 0;
};

