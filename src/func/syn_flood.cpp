#include <iostream>
#include "syn_flood.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

SOCKET tcpSocket = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

// pseudo header for checksum calc
struct pseudo_header
{
    unsigned int source_address;
    unsigned int dest_address;
    unsigned char placeholder;
    unsigned char protocol;
    unsigned short tcp_length;

    struct  tcp;
};


bool syn_flood(){

    return true;
}