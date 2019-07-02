#include "preview.h"

void preview(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	static int num = 1;
	struct tm *ltime;
	char timestr[16];
	time_t local_tv_sec;

	// num : num++

	/*
	local_tv_sec = header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);
	trftime(timestr, sizeof timestr, "%H:%M:%S", ltime);
	header->ts.tv_usec;
	*/

	// time : timestr + header->ts.tv_usec
	//printf("||  Time : %s, %.6d  ||  ", timestr, header->ts.tv_usec);
	
	static ether_header* eth;
	eth = (ether_header*)pkt_data;
	UINT ptype = ntohs(eth->type);

	static ip_header *ih = NULL;
	ih = (ip_header*)(pkt_data + 14);

	if (ptype == IP_HEADER)
	{
		// Source : ih->src_addr[0], ih->src_addr[1], ih->src_addr[2], ih->src_addr[3]
		// Destination : ih->dst_addr[0], ih->dst_addr[1], ih->dst_addr[2], ih->dst_addr[3]
		// Len : header->len
		if (ih->protocol == ICMP)
		{
			// protocol : ICMP
			// info : A
		}

		else if (ih->protocol == TCP)
		{
			// protocol : TCP
			// info : A
		}

		else if (ih->protocol = UDP)
		{
			// protocol : UDP
			// info : A
		}	
	}

	else if (ptype == ARP_HEADER)
	{
		//	Source : eth->src_host[0], eth->src_host[1],
		//			 eth->src_host[2], eth->src_host[3],
		//			 eth->src_host[4], eth->src_host[5]
		// Destination : Broadcast
		// protocol : ARP
		
		// Len : header->len
		// info : A
	}
}


void TCP_header(ip_header *ih)
{
	tcp_header *th = NULL;
	th = (tcp_header*)((u_char*)ih + (ih->length) * 4);

	switch (th->flags)
	{
	case SYN: printf("SYN");			break;
	case PUSH: printf("PUSH");			break;
	case ACK: printf("ACK");			break;
	case SYN_ACK: printf("SYN_ACK");	break;
	case PUSH_ACK: printf("PUSH_ACK");	break;
	case FIN_ACK: printf("FIN_ACK");	break;
	}
}

void UDP_header(ip_header *ih)
{
	udp_header *uh = NULL;
	uh = (udp_header *)((u_char*)ih + (ih->length) * 4);

	printf("%d -> %d LEN = %d", ntohs(uh->dst_port), ntohs(uh->src_port), (uh->len));
}

void ARP_packet(const u_char *pkt_data)
{
	arp_header *ah = NULL;
	ah = (struct ether_arp *)(pkt_data + 14);
	
	if (strcmp(ah->Sender_protocol_addr, ah->Target_protocol_addr) == 0) 
	{
		printf("Gratuitous ARP for %d.%d.%d.%d ", 
			ah->Target_protocol_addr[0], ah->Target_protocol_addr[1],
			ah->Target_protocol_addr[2], ah->Target_protocol_addr[3]);
	}

	else 
	{
		printf("Who has %d.%d.%d.%d? Tell %d.%d.%d.%d",
		ah->Target_protocol_addr[0], ah->Target_protocol_addr[1],
		ah->Target_protocol_addr[2], ah->Target_protocol_addr[3],
		ah->Sender_protocol_addr[0], ah->Sender_protocol_addr[1],
		ah->Sender_protocol_addr[2], ah->Sender_protocol_addr[3]);
	}
	
	if (ntohs(ah->opcode) % 2 == 1)
		printf(" (Request)\n");
	else if (ntohs(ah->opcode) % 2 == 0)
		printf(" (Reply)\n");
}   