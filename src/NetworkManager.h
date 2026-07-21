#include <string>
#include <vector>

struct NetworkInterface
{
    std::string name;
    std::string address;
    int prefixLength;
};

class NetworkManager
{
public:
    std::vector<NetworkInterface> getInterfaces();
};