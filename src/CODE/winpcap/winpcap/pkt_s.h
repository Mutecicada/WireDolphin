#ifndef __PKT_S_H__
#define __PKT_S_H__

#include <WinSock2.h>

#define IP_HEADER 0x0800
#define ARP_HEADER 0x0806
#define SYN 0x02
#define PUSH 0x08
#define ACK 0x10
#define SYN_ACK 0x12
#define PUSH_ACK 0x18
#define FIN_ACK 0x11
#define ICMP 1
#define TCP 6
#define UDP 11
#define CAPTIT_DATA_TYPES_H


/* ARP packet structure */
typedef struct arp_header 
{
	u_short   hd_type;				/* Format of Hardware address */
	u_short   protocol_type;				/* Format of Protocol address */
	u_char    hd_len;				/* Length of Hardware address */
	u_char    protocol_len;				/* Length of Protocol address */
	u_short   opcode;				/* One of: */
	u_char    Sender_hd_addr[6];	/* Sender Hardware address */
	u_char    Sender_protocol_addr[4];	/* Sender Protocol address */
	u_char    Target_hd_addr[6];	/* Target Hardware address */
	u_char    Target_protocol_addr[4];	/* Target Protocol address*/
}arp_header;


typedef struct ether_header 
{
	u_char dst_host[6];	/* Destination Host */
	u_char src_host[6];	/* Source Host */
	u_short type;					/* Type */
}ether_header;


typedef struct ip_header 
{
	u_char length : 4;				/* Header Length */
	u_char version : 4;				/* Version */	
	u_char tos;						/* Type of servise */
	u_short Total_len;				/* Total Length */
	u_short identification;			/* Identification */
	u_short flags_fo;				/* Flags (3 bits) + Fragment offset (13 bits) */
	u_char TTL;						/* Time To Live */
	u_char protocol;				/* Protocol */
	u_short checksum;				/* Header Checksum */
	u_char src_addr[4];		/* Source address */
	u_char dst_addr[4];		/* Destination address */
	u_int op_pad;					/* Option + Padding */
}ip_header;


/* UDP header */
typedef struct udp_header 
{
	u_short src_port;				/* Source Port */
	u_short dst_port;				/* Destination Port */
	u_short len;					/* Datagram Length */
	u_short crc;					/* Checksum */
	// data ¸â¹ö Ãß°¡
}udp_header;


typedef struct tcp_header 
{
	u_short src_port;				/* Source Port */
	u_short dst_port;				/* Destination Port */
	u_int seq_num;					/* Sequence Number*/
	u_int ack_num;					/* Acknowledgement Number */
	u_char header_len;				/* Header Length */
	u_char flags;					/* Flags Field */
	u_short win;					/* Windows Size */
	u_short crc;					/* Checksum */
	u_short urgptr;					/* Urgent Point */
}tcp_header;


typedef struct icmp_header 
{
	u_char    type;				    /* type of message */
	u_char    code;				    /* type sub code */
	u_short   cksum;				/* ones complement cksum of struct */
	u_short   id;
	u_short   seq;
	u_char    date[1];
}icmp_header;

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
void preview(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
void print_packet_data(int len, const u_char *pkt_data);
void Show_pktdata(const u_char *pkt_data);


#endif