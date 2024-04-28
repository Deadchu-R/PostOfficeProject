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
	Node* current = head;
	Node* seniorHead = nullptr;
	Node* youngerHead = nullptr;

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
			if (youngerHead != nullptr)
				youngerHead->prev = current;
			youngerHead = current;
		}
		current = nextNode;
	}

	seniorHead = sortByActionType(seniorHead);
	youngerHead = sortByActionType(youngerHead);

	if (seniorHead != nullptr)
	{
		head = seniorHead;
		while (seniorHead->next != nullptr)	seniorHead = seniorHead->next;
		seniorHead->next = youngerHead;
	}
	else
	{
		head = youngerHead;
	}

	current = head;
	while (current->next != nullptr)
	{
		current->next->prev = current;
		current = current->next;
	}
}

Node* customerList::sortByActionType(Node* head)
{
	if (head == nullptr || head->next == nullptr) return head;

	Node* sortedHead = nullptr;
	Node* current = head;

	while (current != nullptr)
	{
		Node* nextNode = current->next;
		sortedHead = insertSorted(sortedHead, current);
		current = nextNode;
	}

	return sortedHead;
}

Node* customerList::insertSorted(Node* head, Node* newNode)
{
	if (head == nullptr || newNode->data.actionType < head->data.actionType)
	{
		newNode->next = head;
		if (head != nullptr) head->prev = newNode;
		return newNode;
	}

	Node* current = head;
	while (current->next != nullptr && current->next->data.actionType <= newNode->data.actionType)
	{
		current = current->next;
	}

	newNode->next = current->next;
	if (current->next != nullptr) current->next->prev = newNode;
	current->next = newNode;
	newNode->prev = current;

	return head;
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