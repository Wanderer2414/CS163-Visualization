#include "../include/CommandLists.h"

CommandList::CommandList() {
    command_pointer = 0;
    sub_command_pointer = 0;
    command_code.clear();
    sub_command.clear();
    m_speed = 1;
    m_is_enable = true;
    m_is_pause = false;
    cur_time = 0;
}
bool CommandList::isEnd() {
    return command_pointer == command_code.size();
}
bool CommandList::isEnable() {
    return m_is_enable;
}
bool CommandList::isPause() {
    return m_is_pause;
}
int CommandList::getCommandCount() {
    return command_code.size();
}
float CommandList::getProgress() {
    if (command_code.empty()) return 1;
    float ans = 1.0f * command_pointer / command_code.size();
    if (sub_command.size()) 
        ans += 1.0f * sub_command_pointer / sub_command[command_pointer].size() / command_code.size();
    return ans;
}
float CommandList::getSpeed() const {
    return m_speed;
}
void CommandList::setPause(const bool& isPause) {
    m_is_pause = isPause;
}

void CommandList::FetchNextCommand(const std::vector<float>& codes) {}
void CommandList::FetchPrevCommand(const std::vector<float>& codes) {}
bool CommandList::BeforeFetchNext() {
    if (command_pointer == command_code.size()) return false;
    if (!sub_command_pointer) {
        sub_command[command_pointer].clear();
        sub_command[command_pointer].push_back(command_code[command_pointer]);
    }
    FetchNextCommand(sub_command[command_pointer][sub_command_pointer]);
    sub_command_pointer++;
    if (sub_command_pointer == sub_command[command_pointer].size()) {
        sub_command_pointer = 0;
        command_pointer++;
    }
    return true;
}
bool CommandList::BeforeFetchPrev() {
    if (!command_pointer && !sub_command_pointer) return false;
    if (sub_command_pointer) {
        sub_command_pointer--;
        FetchPrevCommand(sub_command[command_pointer][sub_command_pointer]);
    } else {
        command_pointer--;
        sub_command_pointer = sub_command[command_pointer].size()-1;
        FetchPrevCommand(sub_command[command_pointer][sub_command_pointer]);
    }
    return false;
}
void CommandList::goMainNext() {
    if (command_pointer==command_code.size()) return;
    int next = command_pointer+1;
    while (command_pointer<next) BeforeFetchNext();
}
void CommandList::goMainPrev() {
    if (!command_pointer && !sub_command_pointer) return;
    if (sub_command_pointer) {
        while (sub_command_pointer) BeforeFetchPrev();
    } else {
        int prev = command_pointer-1;
        while (command_pointer>prev || sub_command_pointer) BeforeFetchPrev();
    }
}
void CommandList::InsertNextMainCommand(const std::vector<float>& code) {
    if (m_is_enable) {
        if (!sub_command_pointer) {
            command_code.insert(command_code.begin() + command_pointer, code);
            sub_command.insert(sub_command.begin()+command_pointer, {code});
        }
        else {
            command_code.insert(command_code.begin() + command_pointer + 1, code);
            sub_command.insert(sub_command.begin()+command_pointer+1, {code});
        }
    }
}
void CommandList::InsertNextSubCommand(const std::vector<float>& code) {
    if (m_is_enable) {
        sub_command[command_pointer].push_back(code);
    }
}

void CommandList::setDuration(const float& clock_count) {
    m_clock.setDuration(clock_count * m_speed);
}
void CommandList::setSpeed(const float& clock_duration) {
    m_speed = clock_duration;
}

void CommandList::GotoCommandLine(const float& percent) {
    cur_time = GetTime();
    if (command_code.empty() && sub_command.empty()) return;
    if (percent < 0) GotoCommandLine(0);
    else if (percent > 1) GotoCommandLine(1);
    else {
        int cur = percent*command_code.size();
        while (command_pointer < cur) BeforeFetchNext();
        while (command_pointer>cur) BeforeFetchPrev();

        float delta = percent*command_code.size() - cur;
        int sub_cur = delta*sub_command[command_pointer].size();
        
        while (sub_cur > sub_command_pointer) BeforeFetchNext();
        while (sub_cur < sub_command_pointer) BeforeFetchPrev();
    }
}
void CommandList::handle() {
    if (m_is_enable && !m_is_pause && command_pointer< command_code.size() && m_clock.get()
        && GetTime()-cur_time>0.5) {
        BeforeFetchNext();
    }
}

void CommandList::goNext() {
    if (sub_command_pointer == sub_command[command_pointer].size()) return;
    BeforeFetchNext();
    if (!m_clock.getDuration() && sub_command_pointer) goNext();
}
void CommandList::goBack() {
    if (!command_pointer && !sub_command_pointer) return;
    BeforeFetchPrev();
    if (!m_clock.getDuration() && sub_command_pointer) goBack();
}

void CommandList::setEnable(const bool& isEnable) {
    m_is_enable = isEnable;
}
void CommandList::clear() {
    command_code.clear();
}
std::vector<float>  CommandList::get(const int& index) {
    if (index < 0 || index >= command_code.size()) return {};
    return command_code[index];
}
CommandList::~CommandList() {

}