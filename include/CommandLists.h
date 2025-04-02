#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include "Global.h"
#include "Clock.h"

class CommandList {
public:
    CommandList();
    bool                isEnd(),
                        isEnable(),
                        isPause();

    int                 getCommandCount();
    float               getSpeed() const,
                        getProgress();

    virtual void        FetchNextCommand(const vector<float>& codes),
                        FetchPrevCommand(const vector<float>& codes),

                        PushBackMainCommand(const vector<float>& code),
                        PushBackSubCommand(const vector<float>& code),

                        InsertNextMainCommand(const vector<float>& code),
                        InsertNextSubCommand(const vector<float>& code),

                        setSpeed(const float& clock_duration),
                        setDuration(const float& clock_count),

                        GotoCommandLine(const float& index),
                        goNext(),
                        goBack(),

                        handle(),
                        setEnable(const bool& isEnable),
                        clear(),
                        setPause(const bool& isPause);
    vector<float>  get(const int& index);
    ~CommandList();
private:
    bool                m_is_enable,
                        m_is_pause;
    bool                BeforeFetchNext(),
                        BeforeFetchPrev();
    int                 command_pointer,
                        sub_command_pointer;
    float               m_speed, cur_time;
    vector<vector<float>>     command_code;
    vector<vector<float>>       sub_command;
    Clock               m_clock;
};

#endif