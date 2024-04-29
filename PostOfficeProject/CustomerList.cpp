#include "CustomerList.h"

void customerList::setQueueOrder(Customer customer)
{
	push(customer);
	sortCustomers();
	printList();
	
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
		}
		else
		{
			current->next = youngerHead;
			if (youngerHead != nullptr) youngerHead->prev = current;
			youngerHead = current;
		}
		current = nextNode;
	}
}
Node* customerList::sortByActionType(Node* specifiedHead)
{
	if (specifiedHead == nullptr || specifiedHead->next == nullptr) return specifiedHead;

	Node* sortedHead = nullptr;
	Node* current = specifiedHead;

	while (current != nullptr)
	{
		Node* nextNode = current->next;
		sortedHead = insertSorted(sortedHead, current);
		current = nextNode;
	}

	return sortedHead;
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
	//newNode->data = customerData;
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
/// <summary>
/// this method will return the 1st node with the specified action type
/// </summary>
/// <param name="actionType"></param>
/// <returns></returns>
Node* customerList::findNodeByActionType(int actionType, Node* fromHere)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->data.actionType == actionType)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}
void customerList::printList()
{
	Node* current = head;
	cout << "Printing list:" << endl;
	int queuePlace = 1;
	while (current != NULL)
	{
		//cout << head->data.birthYear << "," << head->data.ID << "," << head->data.name << endl;
		cout << current->data.name << " is: " << queuePlace << " in line" << endl;
		current = current->next;
		queuePlace++;
	}
}
void customerList::insertAfter(Node* prev_node, Customer customerData)
{
	if (prev_node == NULL)
	{
		std::cout << "Error: the given previous node cannot be NULL";
		return;
	}
	Node* newNode = new Node(customerData);
	//newNode->data = customerData;
	newNode->next = prev_node->next;
	prev_node->next = newNode;
	newNode->prev = prev_node;
	if (newNode->next != NULL)
	{
		newNode->next->prev = newNode;
	}
}

void customerList::append(Node** head, Customer customerData)
{
	Node* newNode = new Node(customerData);
	Node* last = *head;
	//newNode->data = customerData;
	newNode->next = NULL;
	if (head == NULL)
	{
		newNode->prev = NULL;
		*head = newNode;
		return;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = newNode;
	newNode->prev = last;
	return;
}

void customerList::deleteNode(Node* del)
{
	if (head == NULL || del == NULL)
	{
		return;
	}
	if (head == del) // if the node i want to delete is first, change head to it's next then delete it
	{
		head = del->next;
	}
	if (del->next != NULL) // if the node i want to delete is not the last one, change the next node's prev to the previous node of the one i want to delete
	{
		del->next->prev = del->prev;
	}
	if (del->prev != NULL) // if the node i want to delete is not the first one, change the previous node's next to the next node of the one i want to delete
	{
		del->prev->next = del->next;
	}
	delete(del);

	return;
}