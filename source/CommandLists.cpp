#include "../include/CommandLists.h"
#include <vector>

CommandList::CommandList() {
    command_pointer = 0;
    current_add = 0;
    m_speed = 1;
    m_is_enable = true;
    m_is_pause = false;
    main_command_pointer = 0;
    current_segment = { -10,-10 };
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
    return sub_count.size();
}
float CommandList::getProgress() {
    if (sub_count.empty()) return 1;
    float ans = 1.0f * main_command_pointer / sub_count.size();
    if (main_command_pointer < sub_count.size())
        ans += 1.0f * (command_pointer - main_command_pointer) / (sub_count[main_command_pointer] + 1) / sub_count.size();
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
    FetchNextCommand(command_code[command_pointer]);
    command_pointer++;
    if (command_pointer == temporary.size() || !temporary[command_pointer]) {
        while (command_pointer > 0 && temporary[command_pointer - 1]) {
            command_code.erase(command_code.begin() + command_pointer - 1);
            temporary.erase(temporary.begin() + command_pointer - 1);
            sub_count[main_command_pointer]--;
            command_pointer--;
        }
        main_command_pointer++;
        return false;
    }
    return true;
}
bool CommandList::BeforeFetchPrev() {
    if ((command_pointer == temporary.size()) || (!temporary[command_pointer])) main_command_pointer--;
    command_pointer--;
    FetchPrevCommand(command_code[command_pointer]);
    if (!temporary[command_pointer]) {
        while (command_pointer < temporary.size() - 1 && temporary[command_pointer + 1]) {
            command_code.erase(command_code.begin() + command_pointer + 1);
            temporary.erase(temporary.begin() + command_pointer + 1);
            sub_count[main_command_pointer]--;
        }
        return true;
    }
    return false;
}
void CommandList::PushBackMainCommand(const std::vector<float>& code) {
    if (m_is_enable) {
        command_code.push_back(code);
        temporary.push_back(false);
        sub_count.push_back(0);
        update_range();
    }
}
void CommandList::PushBackSubCommand(const std::vector<float>& code) {
    if (m_is_enable) {
        command_code.push_back(code);
        temporary.push_back(true);
        update_tail();
        update_range();
        sub_count.back()++;
    }
}
void CommandList::InsertNextMainCommand(const std::vector<float>& code) {
    if (m_is_enable) {
        if (command_pointer == temporary.size() || !temporary[command_pointer]) {
            command_code.insert(command_code.begin() + command_pointer, code);
            temporary.insert(temporary.begin() + command_pointer, false);
            sub_count.insert(sub_count.begin() + main_command_pointer, 0);
        }
        else {
            command_code.insert(command_code.begin() + current_add, code);
            temporary.insert(temporary.begin() + current_add, false);
            sub_count.insert(sub_count.begin() + main_command_pointer + 1, 0);
        }
        update_tail();
        update_range();
    }
}
void CommandList::InsertNextSubCommand(const std::vector<float>& code) {
    if (m_is_enable) {
        command_code.insert(command_code.begin() + current_add, code);
        temporary.insert(temporary.begin() + current_add, true);
        update_tail();
        update_range();
        sub_count[main_command_pointer]++;
    }
}

void CommandList::setDuration(const float& clock_count) {
    m_clock.setDuration(clock_count * m_speed);
}
void CommandList::setSpeed(const float& clock_duration) {
    m_speed = clock_duration;
}
void CommandList::update_tail() {
    //Update currrent_add pointer -> Point to the next main command to insert next main/sub command
    if (command_pointer < temporary.size()) {
        current_add = command_pointer + 1;
        //Incease current while current_add exist and not a main command
        while (current_add < temporary.size() && temporary[current_add]) current_add++;
    }
    else current_add = temporary.size();
}
void CommandList::update_range() {
    current_segment.x = current_segment.y;
}

void CommandList::GotoCommandLine(const float& percent) {
    if (sub_count.empty()) return;
    // if (percent >= current_segment.x && percent <= current_segment.y) return;
    if (percent < 0) GotoCommandLine(0);
    else if (percent > 1) GotoCommandLine(1);
    else {
        float range = 1.0f/sub_count.size();
        int cur = percent/range;
        // if (main_command_pointer>=sub_count.size() || !sub_count[cur]) {
        //     float progress = getProgress();
            float prev = 1.0f*cur*range;
            if (percent - prev > prev + range - percent) cur++;
            //Go to cur
            if (main_command_pointer>cur) {
                while (main_command_pointer > cur) {
                    BeforeFetchPrev();
                    if (command_pointer>=0 && !temporary[command_pointer]) update_tail();
                }
            } else if (main_command_pointer < cur) {
                while (main_command_pointer < cur) {
                    BeforeFetchNext();
                    if (command_pointer<temporary.size() && !temporary[command_pointer]) update_tail();
                }
            }
    }
}
void CommandList::handle() {
    if (m_is_enable && !m_is_pause && command_pointer < command_code.size() && m_clock.get()) {
        current_add = command_pointer + 1;
        BeforeFetchNext();
    }
}

void CommandList::goNext() {
    if (command_pointer >= command_code.size()) return;
    BeforeFetchNext();
    if (!temporary[command_pointer]) update_tail();
    if (!m_clock.getDuration()) goNext();
}
void CommandList::goBack() {
    if (!command_pointer) return;
    BeforeFetchPrev();
    if (!temporary[command_pointer]) update_tail();
    if (!m_clock.getDuration()) goBack();
}

void CommandList::setEnable(const bool& isEnable) {
    m_is_enable = isEnable;
}
void CommandList::clear() {
    command_code.clear();
    temporary.clear();
}
std::vector<float>  CommandList::get(const int& index) {
    if (index < 0 || index >= command_code.size()) return {};
    return command_code[index];
}
CommandList::~CommandList() {

}