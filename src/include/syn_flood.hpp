#include<string>
#include<cstring>
#include<iostream>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include<linux/in.h>
#include<arpa/inet.h>
#include<random>

using namespace std;

/*
    syn_flooding.hpp

    contains SYN flooding function
*/

// pseudo header for checksum calculation
struct pseudo_header
{
    unsigned int src_addr;
    unsigned int dest_addr;
    unsigned char placeholder;
    unsigned char protocol;
    unsigned short tcp_length; 

    struct tcphdr tcp;
};

// checksum calculation
unsigned short chksum(unsigned short *ptr, int nbytes);
int* ip_parser(std::string ip);
int syn_flood(int sock, char dest_ip[], int dport, bool flagLand);
int syn_flood(int sock, std::string dest_ip, std::string src_range1, std::string src_range2, int port);