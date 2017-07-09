/* 
 * File:   packet_parse.h
 * Author: tanya
 *
 * Created on 19 Февраль 2015 г., 16:21
 */

#ifndef PACKET_H
#define	PACKET_H

#include <pcap.h> 
#include <stdlib.h>
#include <errno.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netinet/if_ether.h>
#include <vector>
#include <iostream>
#include <cstring>

#define IP_start 14
#define TCP_start 36
#define TCP_flags 49
#define IP_source 28
#define data_start 66

typedef struct ip_hdr{
    unsigned int ipSource[4];
    unsigned int ipDest[4];
    //unsigned int protocol;
}IP_HEADER;

typedef struct tcp_hdr{
	unsigned int portSource = 0;
	unsigned int portDest = 0;
}TCP_HEADER;


class packet{
        public :
            std :: vector<u_char>data;
            IP_HEADER iph;
            TCP_HEADER tcph;
            bool calculate_hash = false;
            std :: string hash_data;
            std :: string data_c;
        
	public : 
		packet(const u_char *packet , const struct pcap_pkthdr* pkthdr);
		~packet();
	public :
		void parse();

};

#endif	/* PACKET_PARSE_H */

