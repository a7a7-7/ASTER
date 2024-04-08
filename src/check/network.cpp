#include"network.hpp"

bool is_valid_IPv4(string addr)
{
    // IPv4 regex
    regex ip_regex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");

    return regex_match(addr, ip_regex);
}

int is_valid_port(string p)
{
    int port = 0;

    for (char c : p){
        if (isdigit(c))
            port = port * 10 + (c - 48);
        else {
            port = -1;
            break;
        }
    }

    return port;
}