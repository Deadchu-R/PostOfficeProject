#include "PostOfficeLogic.h"
#include "CustomerList.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void PostOfficeLogic::runPostOffice()
{
	
	system("CLS"); // Console.Clear c++ editon
	setOfficeSettings();
	while (running)
	{
		cout << "Welcome to the Post Office, choose division or exit" << endl;
		cout << "1. Officer" << endl;
		cout << "2. Customer" << endl;
		cout << "3. Exit" << endl;
		int input;
		cin >> input;
		switch (input)
		{
		case 1:
			officerActions();
			break;
		case 2:
			customerActions();
			break;
		case 3: 
			running = false;
			break;
		default:
			cout << "didn't not recive a valid input" << endl;
			waitForInput();
			break;
		}
	}
	customerActions();

}
void PostOfficeLogic::officerActions()
{
}
void PostOfficeLogic::customerActions()
{
	bool customerActionRunning = true;
		while (customerActionRunning)
		{
			system("CLS");
			string IDString;
			int ID{};
			cout << "Welcome to the Post Office! please enter your {9 digit} ID" << std::endl;
			cout << "or enter 1 digit then press Enter to exit" << endl;
			cin >> IDString;
		
				if (!isNumber(IDString))
				{
					cout << "error , we only accept numbers" << endl;
					waitForInput();
					customerActions();
				}
		

			ID = stoi(IDString);
			switch (IDString.length()) {
			case 1:
				std::cout << "Goodbye" << std::endl;
				std::cout << "Exiting...";
				customerActionRunning = false;
				break;
			case 9:
				searchInCustomersList(ID);
				break;
			default:
				cout << "ID Should be 9 digit and you inserted: " << IDString.length() << endl;
				waitForInput();
				customerActions();
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
			if (line.find("currentYear") != string::npos)
			{
				currentYear = stoi(line.substr(line.find("=") + 1));
				cout << "current year is: " << currentYear << endl;

			}
		}
		config.close();
	}
	else
	{
		cout << "Unable to open file, please check config.txt";
	}

}
void PostOfficeLogic::searchInCustomersList(int ID)
{
	Customer customer;
	customerList listOfCustomers;
	customer = findCustomer(ID); // find the customer in customers.txt
	system("CLS"); 
	cout << "Customer ID: " << customer.ID << endl
		<< "Customer Name: " << customer.name << endl
		<< "Customer Birth Year: " << customer.birthYear << endl;
	customer = queuePlace(customer);
	// will start CustomerList.addToQueue
	listOfCustomers.addToQueue(customer);
	listOfCustomers.printList();
}
Customer PostOfficeLogic::createNewCustomer(int ID)
{
	Customer customer;
	string input;
	int year = 0;
	cout << "what is your name?" << endl;
	cin >> input;
	string name = input;
	cout << "In which year were you born?" << endl;
	cin >> input;
	if (isNumber(input))
	{
		 year = stoi(input);
	}
	else if (!isNumber(input) || year - currentYear < 0 || year - currentYear > maxAge) 
	{
		cout << "year is not valid, please enter a valid year";
		waitForInput();
		createNewCustomer(ID);
	}


	ofstream customers("Customers.txt", ios::app); // app is short for append
	if (customers.is_open())
	{
		customers << IDSymbol << ID << IDSymbol << " " << nameSymbol << name << nameSymbol << " " << yearSymbol << year << yearSymbol << std::endl;
		customers.close();
	}
	customer.ID = ID;
	customer.name = name;
	customer.birthYear = year;
	return customer;
	
}
Customer PostOfficeLogic::queuePlace(Customer customer)
{
	bool choseAction = false;
	int actionNum;
	while (!choseAction)
	{
		string input;
		cout << "what would you like to do?" << endl;
		cout << "1. package pickup" << endl;
		cout << "2. send a package" << endl;
		cout << "3. make payments" << endl;
		cout << "4. order a product" << endl;
		cin >> input;
		int inputNum = stoi(input);
			switch (inputNum)
			{
			 case 1:
				 customer.actionType = 1;
				 choseAction = true;
				break;
			 case 2:
				 customer.actionType = 2;
				 choseAction = true;
				 break;
			 case 3:
				 customer.actionType = 3;
				 choseAction = true;
				 break;
			 case 4: 
				 customer.actionType = 4;
				 choseAction = true;
				 break;
			 default:
				 cout << "error, we accept only numbers" << endl;
				 waitForInput();
				 break;
			};
	}
	return customer;
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
				customer = setCustomerValues(line);
				found = true;
				return customer;
			}

		}
		if (!found)
		{
			cout << "Customer sas not found" << std::endl;
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
				customers.close();
				customerActions();
				break;
			case 2:
				customer = createNewCustomer(ID);
				return customer;
				break;

			}
			system("CLS");
			customerActions();
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
	return customer;
}
Customer PostOfficeLogic::setCustomerValues(string line)
{
	// Format Symbols: Format Symbols: ~ID~, $Name$, %Year% 
	Customer customer;
	customer.ID = stoi(findDataBySymbol(line, IDSymbol));
	customer.name = findDataBySymbol(line, nameSymbol);
	customer.birthYear = stoi(findDataBySymbol(line, yearSymbol));
	return customer;
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
bool PostOfficeLogic::isNumber(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (!isdigit(s[i]))
		{
			return false;
		}
	}
	return true;
}
void PostOfficeLogic::waitForInput()
{
	cout << "press any key to return" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}





