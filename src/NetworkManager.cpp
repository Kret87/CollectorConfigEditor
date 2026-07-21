#include "NetworkManager.h"
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdexcept>
#include <iostream>
#include <net/if.h>

std::vector<NetworkInterface> NetworkManager::getInterfaces(){

    std::vector<NetworkInterface> interfaces;

    struct ifaddrs* ifaddr = nullptr;

    if (getifaddrs(&ifaddr) == -1)
    {
        throw std::runtime_error("Failed to get network interfaces.");
    }

    struct ifaddrs* current = ifaddr;

    while (current != nullptr)
    {
        NetworkInterface interface;

        if (current->ifa_addr == nullptr)
        {
            current = current->ifa_next;
            continue;
        }

        if (current->ifa_addr->sa_family != AF_INET)
        {
            current = current->ifa_next;
            continue;
        }

        if (current->ifa_flags & IFF_LOOPBACK)
        {
            current = current->ifa_next;
            continue;
        }

        sockaddr_in* ipv4 = reinterpret_cast<sockaddr_in*>(current->ifa_addr);
        sockaddr_in* mask = reinterpret_cast<sockaddr_in*>(current->ifa_netmask);

        interface.name = current->ifa_name;

        char buffer[INET_ADDRSTRLEN];
        if(inet_ntop(AF_INET,&ipv4->sin_addr,buffer, INET_ADDRSTRLEN))
            interface.address = buffer;

        uint32_t value = ntohl(mask->sin_addr.s_addr);
        int count = 0;
        
        while(value & 0x80000000)
            {
                count++;
                value <<= 1;
            }

        interface.prefixLength = count;
        
        interfaces.push_back(interface);

        std::cout << current->ifa_name << std::endl;
        std::cout << " " << interface.address << " | " << interface.prefixLength << std::endl;

        current = current->ifa_next;
    }

    freeifaddrs(ifaddr);
    return interfaces;
    
}