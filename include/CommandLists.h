#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include <ctime>
#include <vector>
#include "Clock.h"
class CommandList {
public:
    CommandList();
    bool                isEnd(),
                        isEnable();
    std::vector<float>  PullCommand(),
                        PullPrevCommand();
    virtual void        FetchCommandQueue(const std::vector<float>& codes),
                        PushCommand(const std::vector<float>& code),
                        setSpeed(const float& clock_duration),
                        GotoCommandLine(const int& index),
                        handle(),
                        setEnable(const bool& isEnable),
                        Clear();
    std::vector<float>  get(const int& index);
    ~CommandList();
private:
    bool                m_is_enable;
    int                 command_pointer;
    float               m_speed;
    std::vector<std::vector<float>>  command_code;
    Clock               m_clock;
};

#endif