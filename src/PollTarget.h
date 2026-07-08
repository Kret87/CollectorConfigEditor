#include <string>
#include <vector>

struct PollTarget
{
    std::string description;
    std::string enabled;
    std::string interface;
    std::string url;
    int interval_ms;
};

void showPollTarget(const PollTarget& target);

void showTargetList(const std::vector<PollTarget>& targets);

PollTarget createPollTarget();