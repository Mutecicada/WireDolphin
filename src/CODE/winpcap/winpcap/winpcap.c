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
	int mode = 0; // pcap_open_live()사용시 모드
	int cnt = 0, i = 0, num = 0, input = 0;
	char errbuf[PCAP_ERRBUF_SIZE];
	
	init_list();
	now = head;

	/* int pcap_findalldevs(pcap_if_t **alldevsp, char *errbuf) */
	// 네트워크 디바이스 목록을 가져온다.
	// alldevs에 List형태로 저장, 에러 발생시 errbuf에 에러 내용 저장
	// 성공 : 0			실패 : -1

	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs : %s\n", errbuf);
		exit(1);
	}

	/* 네트워크 디바이스명 출력 */
	// Linked List 이므로 순차적으로 하나씩 검색
	for (d = alldevs; d; d = d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}

	/* 디바이스가 하나도 없다면 */
	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}

	/* 캡쳐할 네트워크 디바이스 선택 */
	printf("Enter the interface number (1~%d) : ", i);
	scanf("%d", &num);

	/* 입력값의 유효성판단 */
	if (num < 1 || num > i)
	{
		printf("\nInterface number out of range\n");
		/* 장치  목록 해제 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* 사용자가 선택한 디바이스 선택 */
	// Single Linked List 이므로 처음부터 순회하여 선택한 걸 찾음
	for (d = alldevs, i = 0; i < num - 1; d = d->next, i++);


	/* 선택한 실제 네트워크 디바이스 오픈 */
	if ((adhandle = pcap_open_live(d->name, 65536, 1, 1000, errbuf)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		/* 장치 목록 해제 */
		pcap_freealldevs(alldevs);
		return -1;
	}

	printf("\nlistening on %s...\n", d->description);

	// 선택된 디바이스를 pcap_open_live로 열고 그것을 제어하기 위한 Handle을 받았으므로
	// 더 이상 그 디바이스에 대한 정보가 필요없다.
	// pcap_findalldevs를 통해 생성된 Linked List 삭제
	pcap_freealldevs(alldevs);

	/* 패킷 캡쳐 시작 */
	// 인자1 : pcap_open_live를 통해 얻은 네트워크 디바이스 핸들
	// 인자2 : 0=무한루프, 양의 정수=캡쳐할 패킷수
	// 인자3 : 패킷이 캡쳐되었을때, 호출될 함수 핸들러
	// 인자4 : 콜백함수로 넘겨줄 파라미터


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
