#pragma once

#include <string>
#include <vector>

struct PollTarget
{
    std::string description;
    bool enabled;
    std::string interface;
    std::string url;
    int interval_ms;
};

void showPollTarget(const PollTarget& target);

void showPollTargetsList(const std::vector<PollTarget>& targets);

PollTarget createPollTarget();

void removePollTarget(std::vector<PollTarget>& targets);