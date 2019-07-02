#include "print_pktdata.h"

void print_packet_data(int len, const u_char *pkt_data)
{
	static int i;
	
	for (i = 1; i < len + 1; i++)
	{
		printf("%.2x ", pkt_data[i - 1]);
		if ((i % 16) == 0) 
			printf("\n");
	}
}
