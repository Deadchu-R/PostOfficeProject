#include "CustomerList.h"

void customerList::setQueueOrder(Customer customer)
{
	
	//if (head == nullptr) push(customer);
   // else ageSort(customer);
	//printList();
}
void customerList::ageSort(Customer customer)
{
	if (customer.age() < 65)
	{
		Node* current = head;
		while (current->next != nullptr && current->next->data.age() > 65 )
		{
			if (current->next->data.age() < 65) sortByActionType(current, customer);	
			current = current->next;
		}
	}
	else
	{
		Node* current = head;
		while (current->next != nullptr)
		{
			if (customer.actionType < current->data.actionType);
		}
	}
}
void customerList::sortByActionType(Node* current,Customer customer)
{
		while (current->next != nullptr)
		{
			if (customer.actionType < current->data.actionType)
			{
				insertAfter(current, customer);
				return;
			}
			current = current->next;
		}
		append(&head, customer);
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

//void customerList::append(Node** head, Customer customerData)
//{
//	Node* newNode = new Node(customerData);
//	Node* last = *head;
//	//newNode->data = customerData;
//	newNode->next = NULL;
//	if (head == NULL)
//	{
//		newNode->prev = NULL;
//		*head = newNode;
//		return;
//	}
//	while (last->next != NULL)
//	{
//		last = last->next;
//	}
//	last->next = newNode;
//	newNode->prev = last;
//	return;
//}

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