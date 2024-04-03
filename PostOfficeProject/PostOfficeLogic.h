#pragma once
#include "Customer.cpp"
class PostOfficeLogic
{
public:
	void chooseAction();
private:
	void setOfficeSettings();
	int countDigits(int number);
	Customer findCustomer(int ID);
	int officerCount;

};

