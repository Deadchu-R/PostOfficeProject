#include "PostOfficeLogic.h"
#include "CustomerList.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void PostOfficeLogic::runPostOffice()
{
	setOfficeSettings();
	string exitText = "Exit";
	bool running = true;
	while (running)
	{
		string IDString;
		int ID{};
		cout << "Welcome to the Post Office! please enter your {9 digit} ID" << std::endl;
		cout << "or enter 1 digit then press Enter to" << exitText << std::endl;
		cin >> IDString;

		switch (IDString.length()) {
		case 1:
			std::cout << "Goodbye" << std::endl;
			std::cout << "Exiting...";
			running = false;
			break;
		case 9:
			ID = stoi(IDString);
			searchInCustomersList(ID);
			break;
		default:
			cout << "ID sas not found" << std::endl;
			cout << "either customer not registered or ID is invalid" << std::endl;
			cout << "choose action:" << endl;
			cout << "1. try inserting ID again" << endl;
			cout << "2. Create Customer account" << endl;
			string input;
			cin >> input;
			int inputNum = stoi(input);
			switch (inputNum)
			{
			default:
				cout << "returning to menu" << endl;
				cout << "press enter to continue" << endl;
				cin;
				break;
			case 2:
				//create customer method
				break;

			}
			

			break;
		}

	}
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
void PostOfficeLogic::searchInCustomersList(int ID)
{
	cout << "setCustomersList" << endl;
	Customer customer;
	customerList listOfCustomers;
	customer = findCustomer(ID); // find the customer in customers.txt
	system("CLS"); // Console.Clear c++ editon
	cout << "Customer ID: " << customer.ID << endl
		<< "Customer Name: " << customer.name << endl
		<< "Customer Birth Year: " << customer.birthYear << endl;
	queuePlace(customer);
	// will start CustomerList.addToQueue
	listOfCustomers.addToQueue(customer);
	// will read from a file and set the list of customers
	// will be used to find a customer
}

int PostOfficeLogic::queuePlace(Customer customer)
{
	string input;
	bool choseAction = false;
	cin >> input;
	int inputNum = stoi(input);
	while (!choseAction)
	{
		cout << "what would you like to do?" << endl;
		cout << "1. package pickup" << endl;
		cout << "2. send a package" << endl;
		cout << "3. make payments" << endl;
		cout << "4. order a product" << endl;
			switch (inputNum)
			{
			 case 1:

				break;
			 default:
				 cout << "error, we accept only numbers" << endl;
				 break;
			};

	}
}
Customer PostOfficeLogic::findCustomer(int ID)
{
	Customer customer;
	fstream customers("Customers.txt");
	string line;
	bool found = false;
	if (customers.is_open())
	{
		
		while (getline(customers, line))
		{
			if (line.find(to_string(ID)) != string::npos) /// find the line of the ID inside the file (ID of the customer)
			{
				// Format Symbols: Format Symbols: ~ID~, $Name$, %Year% 
				customer.ID = stoi(findDataBySymbol(line, "~"));
				customer.name = findDataBySymbol(line, "$");
				customer.birthYear = stoi(findDataBySymbol(line, "%"));
				found = true;
				return customer;
			}

		}
		if (!found)
		{
			cout << "Customer not found" << endl;
			cout << "have you written the right ID?" << endl;
			cout << "press any key then Enter to return to main menu" << endl;
			cin >> line;
			system("CLS");
			runPostOffice();
		}
		customers.close();
	}
	else
	{
		cout << "Error: Unable to open file, please check Customers.txt";
		
	}
	// will search for customer in an outside list of customers
	// if customer exists , return customer
	// if customer does not exist, prompt user to enter their information
	//customer.ID = ID;
	//return customer;
}

bool PostOfficeLogic::tryFindCustomer(int ID, Customer customer)
{
	// will search for customer in an outside list of customers
	// if customer exists , return true
	// if customer does not exist, return false
    customer =	findCustomer(ID);
	return customer.ID != 0;
}
/// <summary>
/// finding data between symbols at line from a file
/// </summary>
/// <param name="line">it is the line from the file which you read</param>
/// <param name="symbol">it is the symbol of which you search data between</param>
/// <returns></returns>
string PostOfficeLogic::findDataBySymbol(string line, string symbol)
{
	size_t symbolStart = line.find(symbol) + 1;
	size_t symbolEnd = line.find(symbol, symbolStart);
	return line.substr(symbolStart, symbolEnd - symbolStart);
}





