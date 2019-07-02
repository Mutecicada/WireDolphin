#include "Show_pktdata.h"

void Show_pktdata(const u_char *pkt_data)
{
	ether_header* eth;
	eth = (ether_header*)pkt_data;
	UINT ptype = ntohs(eth->type);

	Show_Ethernet(eth);
	if (ptype == IP_HEADER)
	{
		ip_header *ih = NULL;
		ih = (ip_header*)(pkt_data + 14);
		Show_IP(pkt_data);

		if (ih->protocol == ICMP);
		// Call Show_ICMP
		else if (ih->protocol == TCP)
			Show_TCP(ih);
		else if (ih->protocol = UDP)
			Show_UDP(ih);
	}

	else if (ptype == ARP_HEADER)
		Show_ARP(pkt_data);
}

void Show_Ethernet(ether_header *eth)
{
	printf("\nEthernet II\n");
	printf("=======================================\n");
	printf("Destination Mac Address : %x:%x:%x:%x:%x:%x\n",
		eth->dst_host[0], eth->dst_host[1],
		eth->dst_host[2], eth->dst_host[3],
		eth->dst_host[4], eth->dst_host[5]);
	printf("Source Mac Address : %x:%x:%x:%x:%x:%x\n",
		eth->src_host[0], eth->src_host[1],
		eth->src_host[2], eth->src_host[3],
		eth->src_host[4], eth->src_host[5]);
	printf("Tpye : %#x\n", ntohs(eth->type));
	printf("=======================================\n\n");
}

void Show_ARP(const u_char *pkt_data)
{
	arp_header *ah = NULL;
	ah = (struct ether_arp *)(pkt_data + 14);

	printf("ARP\n");
	printf("=======================================\n");
	printf("\nHardware type : %d\n", ntohs(ah->hd_type));
	printf("Protocol type : %#x\n", ntohs(ah->protocol_type));
	printf("Hardware size : %d\n", ntohs(ah->hd_len));
	printf("Protocol size : %d\n", ntohs(ah->protocol_len));
	printf("OPcode : %d\n", ntohs(ah->opcode));
	printf("Sender MAC address : %x:%x:%x:%x:%x:%x\n",
		ah->Sender_hd_addr[0], ah->Sender_hd_addr[1],
		ah->Sender_hd_addr[2], ah->Sender_hd_addr[3],
		ah->Sender_hd_addr[4], ah->Sender_hd_addr[5]);
	printf("Sender IP address : %d.%d.%d.%d\n",
		ah->Sender_protocol_addr[0], ah->Sender_protocol_addr[1],
		ah->Sender_protocol_addr[2], ah->Sender_protocol_addr[3],
		ah->Sender_protocol_addr[4], ah->Sender_protocol_addr[5]);
	printf("Target MAC address : %x:%x:%x:%x:%x:%x\n",
		ah->Target_hd_addr[0], ah->Target_hd_addr[1],
		ah->Target_hd_addr[2], ah->Target_hd_addr[3],
		ah->Target_hd_addr[4], ah->Target_hd_addr[5]);
	printf("Target IP address : %d.%d.%d.%d\n",
		ah->Target_protocol_addr[0], ah->Target_protocol_addr[1],
		ah->Target_protocol_addr[2], ah->Target_protocol_addr[3],
		ah->Target_protocol_addr[4], ah->Target_protocol_addr[5]);
	printf("=======================================\n\n");
}

void Show_IP(const u_char *pkt_data)
{
	ip_header *ih = NULL;
	ih = (ip_header*)(pkt_data + 14);

	printf("\nInternet Protocol Version 4\n");
	printf("=======================================\n");
	printf("Version : %d\n", ih->version);
	printf("Header Length %d byte\n", ih->length * 4);
	printf("Differentiated Services Field : %#x\n", ih->tos);
	printf("Total Length : %d\n", ntohs(ih->Total_len));
	printf("Identification : %#x\n", ntohs(ih->identification));
	printf("Flags : %#x\n", ntohs(ih->flags_fo));
	printf("Time to live : %d\n", ih->TTL);
	printf("Protocol : %d\n", ih->protocol);
	printf("Header checksum : %#x\n", ntohs(ih->checksum));
	printf("Source : %d.%d.%d.%d\n",
		ih->src_addr[0], ih->src_addr[1],
		ih->src_addr[2], ih->src_addr[3]);
	printf("Destination : %d.%d.%d.%d\n",
		ih->dst_addr[0], ih->dst_addr[1],
		ih->dst_addr[2], ih->dst_addr[3]);
	printf("=======================================\n\n");
}

void Show_UDP(ip_header *ih)
{
	udp_header *uh = NULL;
	uh = (udp_header *)((u_char*)ih + (ih->length) * 4);

	printf("UDP\n");
	printf("=======================================\n");
	printf("Source Port : %d\n", ntohs(uh->src_port));
	printf("Destination Port : %d\n", ntohs(uh->dst_port));
	printf("Length : %d\n", ntohs(uh->len));
	printf("Checksum : %#x\n", ntohs(uh->crc));
	// print data
}

void Show_TCP(ip_header *ih)
{
	tcp_header *th = NULL;
	th = (tcp_header*)((u_char*)ih + (ih->length) * 4);

	printf("TCP\n");
	printf("=======================================\n");
	printf("Source Port : %d\n", ntohs(th->src_port));
	printf("Destination Port : %d\n", ntohs(th->dst_port));
	printf("Sequence number : %d\n", ntohs(th->seq_num));
	printf("Acknowleadgment number : %d\n", ntohs(th->ack_num));
	printf("Flags : %#x ", ntohs(th->flags));
	switch (th->flags)
	{
	case SYN: printf("SYN\n");			break;
	case PUSH: printf("PUSH\n");			break;
	case ACK: printf("ACK\n");			break;
	case SYN_ACK: printf("SYN_ACK\n");	break;
	case PUSH_ACK: printf("PUSH_ACK\n");	break;
	case FIN_ACK: printf("FIN_ACK\n");	break;
	}
	printf("Window size value : %d\n", ntohs(th->win));
	printf("Checksum : %#x\n", ntohs(th->crc));
	printf("Urgent pointer : %d\n", ntohs(th->urgptr));
}