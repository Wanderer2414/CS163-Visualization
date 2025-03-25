#include "../include/SinglyLinkedList.h"
#include <string.h>

SLL::ListNode::ListNode(const int &value, const int &index) : TextButton(0,0)
{
	m_value = value;
	m_index = index;
	TextButton::setText(to_string(m_value));
	m_next = nullptr;
}

int SLL::ListNode::getValue() const
{
    return m_value;
}

int SLL::ListNode::getIndex() const
{
    return m_index;
}

void SLL::ListNode::setValue(const int &value)
{
	m_value = value;
	TextButton::setText(to_string(m_value));
}

void SLL::ListNode::setIndex(const int &index)
{
	m_index = index;
}

void SLL::ListNode::draw()
{
	TextButton::draw();
}

void SLL::ListNode::handle()
{
	TextButton::handle();
}

SLL::SLLForm::SLLForm(const int &index, FormSetting form_setting, const Vector2 &window_size): Form(index,form_setting,window_size)
{
	m_node_size = 50;
	m_node_spacing = 50;
}

void SLL::SLLForm::add(const vector<string> &str)
{
	for (int i = str.size()-1; i>=0; i--) {
		InsertNextMainCommand({_insert,(float)stoi(str[i])});
		console.InsertNextMainCommand("Add " + str[i]);
	}
}

void SLL::SLLForm::handle()
{
	Form::handle();
	ListNode* cur = m_head;
	while (cur) {
		cur->handle();
		cur->button_setting = &form_setting;
		cur->text_setting = &form_setting;
		cur->setPosition(m_workspace.x+100*cur->getIndex()-100*(size)/2,m_workspace.y);
		cur->setSize(m_node_size,m_node_size);
		cur = cur->m_next;
	}
}

void SLL::SLLForm::remove(const std::string & str)
{
	InsertNextMainCommand({_delete,(float)stoi(str)});
}


void SLL::SLLForm::update(const std::string & old_value, const std::string & new_value)
{
}


void SLL::SLLForm::search(const std::string & x)
{
}


void SLL::SLLForm::draw()
{
	Form::draw();
	BeginMode2D(m_camera);
    BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
	ListNode* cur = m_head;
	while (cur) {
		cur->draw();
		cur = cur->m_next;
	}
	EndScissorMode();
    EndMode2D();
}


void SLL::SLLForm::FetchNextCommand(const std::vector<float>& command)
{
	if (command.empty()) return;
	switch ((int)command[0])
	{
	case _insert: 
	{
		insert(int(command[1]),size);
		setDuration(0);
		break;
	}
	case _delete:
	{
		remove(int(command[1]));
		setDuration(0);
		break;
	}
	case _choose: 
	{
		setDuration(int(command[2]));
		break;
	}
	case _unchoose:
	{
		setDuration(int(command[2]));
		break;
	}
	default:
		break;
	}
}


void SLL::SLLForm::FetchPrevCommand(const std::vector<float>& command)
{
	if (command.empty()) return;
	switch ((int)command[0])
	{
	case _insert: 
	{
		remove(int(command[1]));
		setDuration(0);
		break;
	}
	case _delete:
	{
		insert(int(command[1]),size);
		setDuration(0);
		break;
	}
	case _choose: 
	{
		setDuration(int(command[2]));
		break;
	}
	case _unchoose:
	{
		setDuration(int(command[2]));
		break;
	}
	default:
		break;
	}
}

SLL::SLLForm::~SLLForm()
{
	
}

void SLL::SLLForm::insert(const int &value, const int &index)
{
	if (!m_head) {
		m_head = new ListNode(value,0);
		size++;
	} else {
		ListNode* cur = m_head;
		int count=0;
		while (cur->m_next) {
			InsertNextSubCommand({_choose,float(count),0});
			InsertNextSubCommand({_unchoose,float(count),0});
			cur = cur->m_next;
			count++;
		}
		InsertNextSubCommand({_choose,float(count),0});
		cur->m_next = new ListNode(value,count+1);
		size++;
	}
}

void SLL::SLLForm::remove(const int &value)
{
    if (!m_head) return; 
    if (m_head->getValue() == value) {
        ListNode* temp = m_head;
        m_head = m_head->m_next;
        delete temp; 
        size--;
    } else {
        ListNode* cur = m_head;
		int count = 0;
        while (cur->m_next && cur->m_next->getValue() != value) {
			InsertNextSubCommand({_choose,float(count),0});
			InsertNextSubCommand({_unchoose,float(count),0});
            cur = cur->m_next;
			count++;
        }
        if (!cur->m_next) return; 

        ListNode* toDelete = cur->m_next;
        cur->m_next = toDelete->m_next;
        delete toDelete; 
        size--;
    }

    ListNode* cur = m_head;
    int index = 0;
    while (cur) {
        cur->setIndex(index++);
        cur = cur->m_next;
    }
}

