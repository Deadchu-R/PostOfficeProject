#include "CustomerList.h"

void customerList::setQueueOrder(Customer customer)
{
	push(customer);
	sortCustomers();
	//printList();

	//if (head == nullptr) push(customer);
   // else ageSort(customer);

}
/// <summary>
/// this sort function will sort the customers by age and then by action type
/// by splitting the list into two lists, one for seniors and one for younger customers
/// </summary>
void customerList::sortCustomers()
{
	sortByAge(head);
	//seniorHead = sortByActionType(seniorHead);
	//youngerHead = sortByActionType(youngerHead);


}
void customerList::sortByAge(Node* current)
{
	while (current != nullptr)
	{
		Node* nextNode = current->next;
		if (current->data.age() >= 65)
		{
			current->next = seniorHead;
			if (seniorHead != nullptr) seniorHead->prev = current;
			seniorHead = current;
			current->prev = nullptr;
		}
		else
		{
			current->next = youngerHead;
			if (youngerHead != nullptr) youngerHead->prev = current;
			youngerHead = current;
			current->prev = nullptr;
		}
		current = nextNode;
	}
}

Node* customerList::insertSorted(Node* sortedHead, Node* newNode)
{
	if (sortedHead == nullptr || newNode->data.actionType < sortedHead->data.actionType)
	{
		newNode->next = sortedHead;
		if (sortedHead != nullptr) sortedHead->prev = newNode;
		return newNode;
	}

	Node* current = sortedHead;
	while (current->next != nullptr && current->next->data.actionType <= newNode->data.actionType)
	{
		current = current->next;
	}

	newNode->next = current->next;
	if (current->next != nullptr) current->next->prev = newNode;
	current->next = newNode;
	newNode->prev = current;

	return sortedHead;
}
void customerList::push(Customer customerData)
{
	Node* newNode = new Node(customerData);
	newNode->next = head;
	newNode->prev = nullptr;

	if (head != nullptr)
	{
		head->prev = newNode;
		head = newNode;
		cout << "added: " << newNode->data.name << " after: " << head->data.name << endl;
	}
	else
	{
		cout << "added: " << newNode->data.name << " as head" << endl;
		this->head = newNode;
	}
}
Node* customerList::findNode(int ID)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->data.ID == ID)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}
Customer customerList::findCustomerByActionType(int actionType, bool elderly)
{
	Node* temp;
	if (elderly)
	{
		temp = findNodeByActionType(actionType, seniorHead);
	}
	else
	{
		temp = findNodeByActionType(actionType, youngerHead);
	}
	if (temp == nullptr)
	{
		cout << "Customer not found" << endl;
		Customer tempCustomer;
		tempCustomer.actionType = -1;
		return tempCustomer;
	}
	return temp->data;
}
/// <summary>
/// this method will return the 1st node with the specified action type
/// </summary>
/// <param name="actionType"></param>
/// <returns></returns>
Node* customerList::findNodeByActionType(int actionType, Node* fromHere)
{
	bool found = false;
	Node* startPoint;
	Node* current;
	if (fromHere != nullptr) startPoint = fromHere;
	else startPoint = head;
	current = startPoint;
			while (current != nullptr)
			{
				if (current->data.actionType == actionType)
				{
					return current;
				}
				cout << "searching for: " << actionType << endl;
				cout << "current action type: " << current->data.actionType << " currentType: " << current->data.isElderly() << endl;
				cin.get();
				current = current->next;
			}
		return nullptr; 
}
void customerList::printList()
{
	Node* current = head;
	cout << "Printing list:" << endl;
	int queuePlace = 1;
	while (current != NULL)
	{
		cout << current->data.name << " is: " << queuePlace << " in line" << endl;
		current = current->next;
		queuePlace++;
	}
}

void customerList::deleteNode(Node* del)
{
	if (head == nullptr || del == nullptr)
	{
		return;
	}
	if (head == del) // if the node i want to delete is first, change head to it's next then delete it
	{
		head = del->next;
	}
	if (del->next != nullptr) // if the node i want to delete is not the last one, change the next node's prev to the previous node of the one i want to delete
	{
		del->next->prev = del->prev;
	}
	if (del->prev != nullptr) // if the node i want to delete is not the first one, change the previous node's next to the next node of the one i want to delete
	{
		del->prev->next = del->next;
	}
	delete(del);

	return;
}