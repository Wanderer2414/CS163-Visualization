#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include <ctime>
#include <vector>
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

    virtual void        FetchNextCommand(const std::vector<float>& codes),
                        FetchPrevCommand(const std::vector<float>& codes),

                        PushBackMainCommand(const std::vector<float>& code),
                        PushBackSubCommand(const std::vector<float>& code),

                        InsertNextMainCommand(const std::vector<float>& code),
                        InsertNextSubCommand(const std::vector<float>& code),

                        setSpeed(const float& clock_duration),
                        setDuration(const float& clock_count),

                        GotoCommandLine(const float& index),
                        goNext(),
                        goBack(),

                        init(),
                        handle(),
                        setEnable(const bool& isEnable),
                        clear(),
                        setPause(const bool& isPause);
    std::vector<float>  get(const int& index);
    ~CommandList();
private:
    bool                m_is_enable,
                        m_is_pause;
    bool                BeforeFetchNext(),
                        BeforeFetchPrev();
    int                 command_pointer,
                        current_add,
                        main_command_pointer;
    float               m_speed;
    void                update_tail(),
                        update_range();
    std::vector<std::vector<float>>     command_code;
    std::vector<bool>                   temporary;
    std::vector<int>                    sub_count;
    Vector2                             current_segment;
    Clock               m_clock;
};

#endif