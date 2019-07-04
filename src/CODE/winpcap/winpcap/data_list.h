#pragma once
#ifndef __data_list_H__
#define __data_list_H__

#include <WinSock2.h>

typedef struct _node
{
	int number;
	int pkt_len;
	const u_char *pkt_data;
	struct _node *next;
	struct _node *prev;
}node;

node *create_node(node *target, int num, int pkt_len, const u_char *pkt_data);
node *find_node(int number);
void init_list();
void init_list();

#endif