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
/// <summary>
/// this method will help the specified customer
/// </summary>
/// <param name="customer"></param>
void Officer::helpCustomer(Customer customer)
{
	ofstream data(officerDataName, ios::app);
	// check if the config file exists
	if (data.is_open())
	{
		writeToData(data, customer);
	}
	else
	{
		data.open(officerDataName);
		if (data.is_open())
		{
			writeToData(data, customer);
		}
		else
		{
			cerr << "Unable to open file, please check " << officerDataName << endl;
			cin.get();
		}
	}
}
/// <summary>
/// will raise the action type of the officer or reset it to 1 if it is at the max
/// </summary>
void Officer::raiseOfficerActionType()
{
	if (actionType >= maxActions)
	{
		cin.get();
		actionType = 1;
	}
	else
	{
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
