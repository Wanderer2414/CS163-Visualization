#include "../include/CommandLists.h"
CommandList::CommandList() {
    command_pointer = -1;
    command_code.clear();
    m_speed = 1;
    m_is_enable = true;
}
bool CommandList::isEnd() {
    return command_pointer == command_code.size()-1;
}
bool CommandList::isEnable() {
    return m_is_enable;
}
std::vector<float> CommandList::PullCommand() {
    if (!isEnd()) return command_code[command_pointer++];
    else return {};
}
std::vector<float> CommandList::PullPrevCommand() {
    if (command_pointer>=0 && command_pointer<=command_code.size()) return command_code[--command_pointer];
    else if (command_pointer>command_code.size()) {
        command_pointer = command_code.size();
        return PullPrevCommand();
    }
    else return {};
}
void CommandList::FetchCommandQueue(const std::vector<float>& codes) {}
void CommandList::PushCommand(const std::vector<float>& code) {
    command_code.push_back(code);
}
void CommandList::setSpeed(const float& clock_duration) {
    m_speed = clock_duration;
}
void CommandList::GotoCommandLine(const int& index) {
    if (index>=command_code.size()) GotoCommandLine(command_code.size()-1);
    else if (command_pointer<index) {
        while (command_pointer<index)
            FetchCommandQueue(command_code[command_pointer++]);
    } else if (command_pointer > index) {
        while (command_pointer > index) FetchCommandQueue(command_code[--command_pointer]);
    }
}
void CommandList::handle() {
    if (m_is_enable && command_pointer < command_code.size() && m_clock.get()) FetchCommandQueue(command_code[command_pointer++]); 
}
void CommandList::setEnable(const bool& isEnable) {
    m_is_enable = isEnable;
}
void CommandList::Clear() {
    command_code.clear();
}
std::vector<float>  CommandList::get(const int& index) {
    if (index<0 || index>=command_code.size()) return {};
    return command_code[index];
}
CommandList::~CommandList() {

}