#include "CustomerList.h"

void customerList::addToQueue(Customer customer)
{
	Node* newNode = new Node;
	cout << "created new node of customer" << endl;
	push(&newNode, customer);
	printList(newNode);

	
}
void customerList::printList(Node* head)
{
	int queuePlace = 1;
	while (head != NULL)
	{
		cout << head->data.birthYear << ","<< head->data.ID << "," << head->data.name << endl;
		cout << head->data.ID << "is: " << queuePlace << "in line";
		head = head->next;
		queuePlace++;
	}
}
void customerList::push(Node** head, Customer customerData)
{
	Node *newNode = new Node();
	newNode->data = customerData;
	newNode->next = (*head);
	newNode->prev = NULL;
	if ((*head) != NULL)
	{
		(*head)->prev = newNode;
	}
	(*head) = newNode;
}
void customerList::insertAfter(Node* prev_node, Customer customerData)
{
	if (prev_node == NULL)
	{
		std::cout << "Error: the given previous node cannot be NULL";
		return;
	}
	Node *newNode = new Node();
	newNode->data = customerData;
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
	Node *newNode = new Node();
	Node *last = *head;
	newNode->data = customerData;
	newNode->next = NULL;
	if (*head == NULL)
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
void customerList::deleteNode(Node** head, Node* del) 
{
	if (*head == NULL || del == NULL)
	{
		return;
	}
	if (*head == del) // if the node i want to delete is first, change head to it's next then delete it
	{
		*head = del->next;
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