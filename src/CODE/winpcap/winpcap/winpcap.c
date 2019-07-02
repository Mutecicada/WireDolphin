#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pkt_s.h"
#include "pcap.h"

#pragma comment(lib,"ws2_32")
#pragma comment(lib, "wpcap.lib")  

typedef struct _node
{
	int number;
	int pkt_len;
	const u_char *pkt_data;
	struct _node *next;
	struct _node *prev;
}node;


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

pcap_t *adhandle;

void init_list();
int del_node(node *target);

int main()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int mode = 0; // pcap_open_live()���� ���
	int cnt = 0, i = 0, num = 0, input = 0;
	char errbuf[PCAP_ERRBUF_SIZE];
	
	init_list();
	now = head;

	/* int pcap_findalldevs(pcap_if_t **alldevsp, char *errbuf) */
	// ��Ʈ��ũ ����̽� ����� �����´�.
	// alldevs�� List���·� ����, ���� �߻��� errbuf�� ���� ���� ����
	// ���� : 0			���� : -1

	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs : %s\n", errbuf);
		exit(1);
	}

	/* ��Ʈ��ũ ����̽��� ��� */
	// Linked List �̹Ƿ� ���������� �ϳ��� �˻�
	for (d = alldevs; d; d = d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}

	/* ����̽��� �ϳ��� ���ٸ� */
	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}

	/* ĸ���� ��Ʈ��ũ ����̽� ���� */
	printf("Enter the interface number (1~%d) : ", i);
	scanf("%d", &num);

	/* �Է°��� ��ȿ���Ǵ� */
	if (num < 1 || num > i)
	{
		printf("\nInterface number out of range\n");
		/* ��ġ  ��� ���� */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* ����ڰ� ������ ����̽� ���� */
	// Single Linked List �̹Ƿ� ó������ ��ȸ�Ͽ� ������ �� ã��
	for (d = alldevs, i = 0; i < num - 1; d = d->next, i++);


	/* ������ ���� ��Ʈ��ũ ����̽� ���� */
	if ((adhandle = pcap_open_live(d->name, 65536, 1, 1000, errbuf)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		/* ��ġ ��� ���� */
		pcap_freealldevs(alldevs);
		return -1;
	}

	printf("\nlistening on %s...\n", d->description);

	// ���õ� ����̽��� pcap_open_live�� ���� �װ��� �����ϱ� ���� Handle�� �޾����Ƿ�
	// �� �̻� �� ����̽��� ���� ������ �ʿ����.
	// pcap_findalldevs�� ���� ������ Linked List ����
	pcap_freealldevs(alldevs);

	/* ��Ŷ ĸ�� ���� */
	// ����1 : pcap_open_live�� ���� ���� ��Ʈ��ũ ����̽� �ڵ�
	// ����2 : 0=���ѷ���, ���� ����=ĸ���� ��Ŷ��
	// ����3 : ��Ŷ�� ĸ�ĵǾ�����, ȣ��� �Լ� �ڵ鷯
	// ����4 : �ݹ��Լ��� �Ѱ��� �Ķ����


	pcap_loop(adhandle, -2, packet_handler, NULL);
	
	A:
	scanf("%d", &input);

	if (input == 0)
		pcap_loop(adhandle, -2, packet_handler, NULL);

	now = find_node(input);
	
	print_pktdata(now->pkt_len, now->pkt_data);

	Show_pktdata(now->pkt_data);
	goto A;
			
	pcap_close(adhandle);
	return 0;
}

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	
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

int del_node(node *target)
{
	if (target->next == NULL)
		return 0;

	target->prev->next = target->next;
	target->next->prev = target->prev;
	free(target);

	return 1;
}
