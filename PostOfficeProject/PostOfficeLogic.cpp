#include "PostOfficeLogic.h"
using namespace std;
PostOfficeLogic::PostOfficeLogic()
{
	setOfficeSettings();
}
PostOfficeLogic::~PostOfficeLogic()
{
}
/// <summary>
/// adjusting the settings of the office according to the config file
/// </summary>
void PostOfficeLogic::setOfficeSettings()
{
	fstream config("OfficeConfig.txt");
	string line;
	if (config.is_open())
	{
		while (getline(config, line))
		{
			if (line.find("officerCount") != string::npos)
			{
				officerCount = stoi(line.substr(line.find("=") + 1)); // stoi is basiclly like .parse in c# (converts string to int)
				for (int i = 1; i < officerCount; i++)
				{
					officers.push_back(Officer(i));
					officers[i - 1].maxActions = maxActions;
				}
				cout << "officerCount: " << officerCount << endl;
			}
			if (line.find("seniorAge") != string::npos)
			{
				seniorAge = stoi(line.substr(line.find("=") + 1));
				cout << "senrior age is: " << seniorAge << endl;
			}
			if (line.find("maxAge") != string::npos)
			{
				maxAge = stoi(line.substr(line.find("=") + 1));
				cout << "max age is: " << maxAge << endl;
			}
		}
		config.close();
	}
	else
	{
		cout << "Unable to open file, please check config.txt";
	}
}
void PostOfficeLogic::runPostOffice()
{
	system("CLS"); // Console.Clear c++ editon
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
			if (customersInQueue == 0)
			{
				cout << "there are no customers in queue" << endl;
				waitForInput();
				runPostOffice();
			}
			else officerActions();
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
	Customer customer;
	if (currentOfficer < officerCount-1 || !officers[currentOfficer].isAvailable) currentOfficer++;
	else currentOfficer = 1;
	Officer officer = officers[currentOfficer - 1];
	bool officerActionRunning = true;
	while (officerActionRunning)
	{
		bool found = false;
		system("CLS");
		cout << "Welcome Officer: " << officer.getOfficerNumber()<<", please choose an action" << endl;
		cout << "there are: " << customersInQueue << " customers in queue" << endl;
		cout << "1. help next customer" << endl;
		cout << "2. Exit" << endl;
		int input;
		cin >> input;
		switch (input)
		{
		case 1:
			cout << "1" << endl;
			while (!found)
			{
				if (officer.shouldHelpElderly == false)
				{
					cin.get();
					if (listOfCustomers.findCustomerByActionType(officer.actionType, officer.shouldHelpElderly).actionType == -1)
					{		
						officer.raiseOfficerActionType();
					}
					else
					{
						customer = listOfCustomers.findCustomerByActionType(officer.actionType, officer.shouldHelpElderly);
						found = true;
					}
				}
			}
			if (customer.isElderly()) officer.shouldHelpElderly = false;
			if (officer.actionType != customer.actionType)
			{
				officer.actionType = customer.actionType;
				officer.raiseOfficerActionType();
			}
			else officer.shouldHelpElderly = true;
			cout << "3" << endl;
			officer.isAvailable = false;
			officer.helpCustomer(customer);
			break;
		case 2:
			officerActionRunning = false;
			break;
		default:
			cout << "didn't not recive a valid input" << endl;
			waitForInput();
			officerActions();
			break;
		}
	}
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
				searchInCustomersQueue(ID);
				break;
			default:
				cout << "ID Should be 9 digit and you inserted: " << IDString.length() << endl;
				waitForInput();
				customerActions();
				break;
			}

		}
	
}

void PostOfficeLogic::searchInCustomersQueue(int ID)
{
	if (listOfCustomers.findNode(ID) != nullptr)
	{
		cout << "you are already in the queue" << endl;
		cout << "would you like to cancle your appointment?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		string input;
		cin >> input;
		if (input == "1")
		{
			listOfCustomers.deleteNode(listOfCustomers.findNode(ID));
			customersInQueue--;
			cout << "you have been removed from the queue" << endl;
			waitForInput();
			customerActions();
		}
		else if (input == "2")
		{
			cout << "returning to menu" << endl;
			waitForInput();
			customerActions();
		}
		else
		{
			cout << "error, please enter a valid number" << endl;
			waitForInput();
			searchInCustomersQueue(ID);
		}
		waitForInput();
		runPostOffice();
	}
	else
	{
		addToQueue(ID);
	}

}
void PostOfficeLogic::addToQueue(int ID)
{
	Customer customer;
	customer = findCustomer(ID); // find the customer in customers.txt
	system("CLS");
	cout << "Customer ID: " << customer.ID << endl
		<< "Customer Name: " << customer.name << endl
		<< "Customer Birth Year: " << customer.birthYear << endl;
	customer = customerChooseAction(customer);
	customer.setCustomerHour();
	listOfCustomers.setQueueOrder(customer);
	customersInQueue++;
	cout << "if you are a new customer." << endl;
	waitForInput();
	runPostOffice();
}
int PostOfficeLogic::getSeniorAge()
{
	return seniorAge;
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
		customers << IDSymbol << ID << IDSymbol << " " << nameSymbol << name << nameSymbol << " " << yearSymbol << year << yearSymbol << endl;
		customers.close();
	}
	customer.ID = ID;
	customer.name = name;
	customer.birthYear = year;
	return customer;
	
}
Customer PostOfficeLogic::customerChooseAction(Customer customer)
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
		if (isNumber(input) && stoi(input) < 4 && stoi(input) > 0)
		{
			cout << "you chose number:" << input  << endl;
			customer.actionType = stoi(input);
			choseAction = true;
			actionNum = stoi(input);
		}
		else
		{
			cout << "error, we accept only numbers between 1 and 4" << endl;
			waitForInput();
		}
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





