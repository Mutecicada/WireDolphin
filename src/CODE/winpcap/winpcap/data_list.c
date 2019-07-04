#include "data_list.h"

node *create_node(node *target, int num, int pkt_len, const u_char *pkt_data)
{
	node *new_node;
	new_node = (node *)malloc(sizeof(node));

	new_node->pkt_data = pkt_data;
	new_node->number = num;
	new_node->pkt_len = pkt_len;

	target->next->prev = new_node;
	new_node->next = target->next;
	target->next = new_node;
	new_node->prev = target;

	return new_node;
}

node *head;
node *tail;
node *now;

node *find_node(int number)
{
	node *find_node;
	find_node = (node *)malloc(sizeof(node));

	for (find_node = head; find_node->number != number;)
		find_node = find_node->next;

	return find_node;
}

void init_list()
{
	head = (node *)malloc(sizeof(node));
	tail = (node *)malloc(sizeof(node));

	head->pkt_data = 0;
	head->number = 0;
	head->next = tail;
	head->prev = NULL;

	tail->pkt_data = 0;
	tail->number = 0;
	tail->prev = head;
	tail->next = NULL;
}