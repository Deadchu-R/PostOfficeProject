#include "MyList.h"


MyList::MyList()
{

}
MyList::~MyList()
{
	
}
void MyList::setQueueOrder(Customer customer)
{
   push_front(customer);
}
/// <summary>
/// will return the first customer in the list with specified action type
/// </summary>
/// <param name="actionType"></param>
/// <param name="elderly"></param>
/// <returns></returns>
Customer MyList::findCustomerByActionType(int actionType, bool elderly)
{	
	string ageType = elderly ? "elderly" : "younger";
		for (Customer customer : *this)
		{
			cout << "searching for an: " << ageType << "customer with action type:" << actionType << endl;
			ageType = customer.isElderly() ? "elderly" : "younger";
			cout << "current action type:" << customer.actionType << " currentType:" << ageType << endl;
			cin.get();
			if (customer.actionType == actionType && customer.isElderly() == elderly)
			{
				return customer;
			}
		}
		Customer nonExistentCustomer;
		nonExistentCustomer.actionType = -1;
		return nonExistentCustomer;
}
/// <summary>
/// will erase this customer from the list
/// </summary>
/// <param name="customer"></param>
void MyList::eraseCustomer(Customer customer)
{
	for (auto it = begin(); it != end(); ++it)
	{
		if (*it == customer) 
		{
			erase(it);
			break; 
		}
	}
}