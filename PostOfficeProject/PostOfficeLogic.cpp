#include "PostOfficeLogic.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void PostOfficeLogic::runPostOffice()
{
	setOfficeSettings();
	std::string exitText = "Exit";
	bool running = true;
	while (running)
	{
		string IDString;
		int ID{};
		std::cout << "Welcome to the Post Office! please enter your ID" << std::endl;
		std::cout << "or enter 1 digit then press Enter to" << exitText << std::endl;
		std::cin >> IDString;

			switch (IDString.length()) {
			case 1:
				std::cout << "Goodbye" << std::endl;
				std::cout << "Exiting...";
				running = false;
				break;
			case 9:
				ID = stoi(IDString);
				std::cout << "Choose an action: " << std::endl;
				// Add your actions here
				break;
			default:
				std::cout << "Invalid ID" << std::endl;
				std::cout << "ID must be a 9 digit number" << std::endl;
				break;
			}

	}
}
int PostOfficeLogic::countDigits(int number) // might delete this function later
{
	int count = 0;
	while (number != 0)
	{
		number = number / 10;
		++count;
	}
	return count;
}
void PostOfficeLogic::setOfficeSettings()
{
	// will adjust setting according to config file
	fstream config("OfficeConfig.txt");
	string line;
	if (config.is_open())
	{
		while (getline(config, line))
		{
			if (line.find("officerCount") != string::npos)
			{
				officerCount = stoi(line.substr(line.find("=") + 1)); // stoi is basiclly like .parse in c# (converts string to int)
				cout << "officerCount: " << officerCount << endl;
			}
		}
		config.close();
	}
	else
	{
		cout << "Unable to open file, please check config.txt";
	}

	// add a file and make a format to accept each setting (same will be later for the list of Customers)
}
void SetCustomersList()
{
	 
	// will read from a file and set the list of customers
	// will be used to find a customer
}
Customer PostOfficeLogic::findCustomer(int ID)
{
	Customer customer;
	// will search for customer in an outside list of customers
	// if customer exists , return customer
	// if customer does not exist, prompt user to enter their information
	customer.ID = ID;
	return customer;
}





