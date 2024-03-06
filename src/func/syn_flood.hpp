/*
    IP header

    contains header length, version, service type, packet length, etc..
    main purpose is IP spoofing

    structure follows ip header form
    -> https://upload.wikimedia.org/wikipedia/commons/thumb/6/60/IPv4_Packet-en.svg/1920px-IPv4_Packet-en.svg.png
    : (number) means bit field
    : 4 means 4 bit
*/
struct ipHeader
{
    // version, length
    unsigned char version : 4,
        length : 4;
    // Type of service
    unsigned char tos;
    unsigned short int total_length;
    unsigned short int id;
    unsigned short int frag_flags : 3,
        offset : 13;
    // Time to Live
    unsigned char ttl;
    unsigned char protocol;
    
    struct in_addr sourceIP;
    struct in_addr destIP;
};

/*
    TCP header

    contains lot of things
    -> https://upload.wikimedia.org/wikipedia/commons/4/4e/TCP_Protocol_Diagram.png
*/
struct tcpheader
{
    unsigned short sourcePort;
    unsigned short destPort;
    unsigned int sequence;
    unsigned int ack;
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        unsigned int reserved:4,
            offset:4;
    #endif
    #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        unsigned int offset:4,
            reserved:4;
    #endif

    unsigned char flags;

    #define TH_FIN 0x01
    #define TH_SYN 0x02
    #define TH_RST 0x04
    #define TH_PUSH 0x08
    #define TH_ACK 0x10
    #define TH_URG 0x20
    #define TH_ECE 0x40
    #define TH_CWR 0x80
    #define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)

    unsigned short window;
    unsigned short checksum;
    unsigned short urgentPointer;
};

https://github.com/adamalston/SYN-Flood/blob/master/tcp_syn_flood.c