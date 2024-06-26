#pragma once
#include <iostream>
#include <string>
#include "Customer.h"
#include "MyTime.h"
#include <fstream>
using namespace std;
class Officer
{
	public:
	Officer(int officerNumber);
	~Officer();
	bool isAvailable = true;
	bool shouldHelpElderly = false;
	string dataFolderPath = "Data\\OfficersData\\";
	void helpCustomer(Customer customer);
	int getOfficerNumber();
	int maxActions = 4;
	void raiseOfficerActionType();
	int actionType = 1;

private:
	int officerNumber;
	string officerDataName;
	void writeToData(ofstream& data, Customer customer);


};

