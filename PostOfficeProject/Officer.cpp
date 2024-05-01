#include "Officer.h"


Officer::Officer(int officerNumber)
{
  this->officerNumber = officerNumber;
  officerDataName = dataFolderPath + "Officer" + to_string(officerNumber) + "Data" + ".txt";
  // check if the config file exists

  cout << "officer Config is: " << officerDataName << endl;
}

Officer::~Officer()
{
}
void Officer::helpCustomer(Customer customer)
{
	ofstream data(officerDataName);


	// check if the config file exists
	if (data.is_open())
	{
		//data << customer.getCustomerHourAsFormattedString() << "- Customer: " << customer.ID << " elderly: " << customer.isElderly() << " actionType: " << customer.actionType << endl;
	//	data.close();
		writeToData(data, customer);
	}
	else
	{
		data.open(officerDataName);
		if (data.is_open())
		{
			writeToData(data, customer);
		//	data << customer.getCustomerHourAsFormattedString() << "- Customer: " << customer.ID << " elderly: " << customer.isElderly() << " actionType: " << customer.actionType << endl;
			//data.close();
		}
		else
		{
			cerr << "Unable to open file, please check " << officerDataName << endl;
			cin.get();
		}
	}
}
void Officer::raiseOfficerActionType()
{
	if (actionType >= maxActions)
	{
		cout << "debug nonsense at raiseActionType" << endl;
		cin.get();
		actionType = 1;
	}
	else
	{
		cout << "debug nonsense at raiseActionType 2" << endl;
		actionType = actionType + 1;
	}
}
void Officer::writeToData(ofstream& data, Customer customer)
{
	data << customer.getCustomerHourAsFormattedString() << "- Customer: " << customer.ID << " elderly: " << customer.isElderly() << " actionType: " << customer.actionType << endl;
	data.close();
}
int Officer::getOfficerNumber()
{
	return officerNumber;
}
