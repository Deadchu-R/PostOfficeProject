#pragma once
#include <string>
#include <ctime>
#include "MyTime.h"
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
	bool isElderly();
	void setCustomerHour();
	int getCustomerHour();
	string getCustomerHourAsFormattedString();
	bool operator==(const Customer& other) const
	{
		return ID == other.ID;
	}

private:
	int customerHour = 0;
	MyTime time;
};

