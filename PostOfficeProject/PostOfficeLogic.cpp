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
	fstream config(officeSettingsFolderPath);
	//fstream config("OfficeConfig.txt");
	string line;
	if (config.is_open())
	{
		while (getline(config, line))
		{
			if (line.find("officerCount") != string::npos)
			{
				officerCount = stoi(line.substr(line.find("=") + 1)); // stoi is basiclly like .parse in c# (converts string to int)
				for (int i = 0; i < officerCount; i++)
				{
					officers.push_back(Officer(i));
					officers[i].maxActions = maxActions;
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
	runPostOffice();
}
/// <summary>
/// this method will run the post office
/// </summary>
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

/// <summary>
/// this method contains the actions of the officer
/// </summary>
void PostOfficeLogic::officerActions()
{
	Customer customer;
	if (currentOfficer < officerCount || !officers[currentOfficer].isAvailable) currentOfficer++;
	else currentOfficer = 0;
	Officer officer = officers[currentOfficer];
	bool officerActionRunning = true;
	while (officerActionRunning)
	{
		system("CLS");
		cout << "Welcome Officer: " << officer.getOfficerNumber() << ", please choose an action" << endl;
		cout << "there are: " << customersInQueue << " customers in queue" << endl;
		cout << "1. help next customer" << endl;
		cout << "2. Exit" << endl;
		int input;
		cin >> input;
		switch (input)
		{
		case 1:
			customer = findNextCustomer(officer);
            #pragma region SetOfficerValues
			if (customer.isElderly()) officer.shouldHelpElderly = false;
			if (officer.actionType != customer.actionType)
			{
				officer.actionType = customer.actionType;
				officer.raiseOfficerActionType();
			}
			else officer.shouldHelpElderly = true;
			officer.isAvailable = false;
			// -------------------------------------------------------------
            #pragma endregion SetOfficerValues
			officer.helpCustomer(customer);
			removeCustomerFromQueue(customer);
			cin.get(); /// for debuging
			customersInQueue--;
			officerActionRunning = false;
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
Customer PostOfficeLogic::findNextCustomer(Officer officer)
{
	Customer customer;
	bool found = false;
	while (!found)
	{
		cin.get();
		if (nodeMode == true)
		{
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
		else if (nodeMode == false)
		{
			if (customersQueueSTL.findCustomerByActionType(officer.actionType, officer.shouldHelpElderly).actionType == -1)
			{
				officer.raiseOfficerActionType();
			}
			else
			{
				customer = customersQueueSTL.findCustomerByActionType(officer.actionType, officer.shouldHelpElderly);
				found = true;
			}
		}
	}
	return customer;
}
void PostOfficeLogic::removeCustomerFromQueue(Customer customer)
{
	if (nodeMode == true)
	{
		if (listOfCustomers.deleteNode(listOfCustomers.findNode(customer.ID)) == true)
		{
			cout << "customer deleted" << endl;
			listOfCustomers.sortCustomers();
		}
		else
		{
			cout << "customer not deleted" << endl;
		}
	}
	else if (nodeMode == false) customersQueueSTL.eraseCustomer(customer);
}
/// <summary>
/// this method contains the actions of the customer
/// </summary>
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

/// <summary>
/// this method will search for customers in queue by their ID
/// </summary>
/// <param name="ID">the ID of the customer</param>
void PostOfficeLogic::searchInCustomersQueue(int ID)
{

	if (listOfCustomers.findNode(ID) != nullptr || isCustomerInQueueSTL(ID))
	{
		cout << "you are already in the queue" << endl;
		cout << "would you like to cancel your appointment?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		string input;
		cin >> input;
		if (input == "1")
		{
			if (nodeMode == true)
			{
				listOfCustomers.deleteNode(listOfCustomers.findNode(ID));
			}
			else if (nodeMode == false)
			{
				for (auto it = customersQueueSTL.begin(); it != customersQueueSTL.end(); )
				{
					if (it->ID == ID)
					{
						it = customersQueueSTL.erase(it);
					}
					else
					{
						++it;
					}
				}
			}
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
bool PostOfficeLogic::isCustomerInQueueSTL(int ID)
{
	for (Customer customer : customersQueueSTL)
	{
		if (customer.ID == ID)
		{
			return true;
		}
	}
	return false;
}
/// <summary>
/// this method will add the customer to the queue by his ID
/// </summary>
/// <param name="ID">The ID of the customer</param>
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
	if (nodeMode == true)listOfCustomers.setQueueOrder(customer);
	else if (nodeMode == false) customersQueueSTL.setQueueOrder(customer);
	customersInQueue++;
	cout << "if you are a new customer." << endl;
	waitForInput();
	runPostOffice();
}
/// <summary>
/// this method will return the senior age
/// </summary>
/// <returns></returns>
int PostOfficeLogic::getSeniorAge()
{
	return seniorAge;
}
/// <summary>
/// this method will create a new customer and add it to the customers.txt file
/// </summary>
/// <param name="ID">This is the ID of the customer</param>
/// <returns></returns>
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
/// <summary>
/// this method is for the customer to choose action
/// </summary>
/// <param name="customer">Is the customer itself</param>
/// <returns>The customer with his Action defined</returns>
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
			cout << "you chose number:" << input << endl;
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
/// <summary>
/// this method will find the customer by his ID
/// </summary>
/// <param name="ID">The ID of the customer</param>
/// <returns>will return cerain customer</returns>
Customer PostOfficeLogic::findCustomer(int ID)
{
	Customer customer;
	fstream customers(officeCustomersFolderPath);
	//fstream customers("Customers.txt");
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
	return customer;
}
/// <summary>
/// this method will set the values of the customer (ID, Name, BirthYear))
/// </summary>
/// <param name="line">is the line of the txt file which this method looks at</param>
/// <returns>will return redefined customer</returns>
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
/// <summary>
/// this method will wait for input before continuing
/// </summary>
void PostOfficeLogic::waitForInput()
{
	cout << "press any key to return" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}





