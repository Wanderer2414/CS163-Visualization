#include "../include/SinglyLinkedList.h"
#include <math.h>
#include <string.h>
#include <random>
#include "SinglyLinkedList.h"

int getRandom(int min, int max) {
    static std::random_device rd; 
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max); 
    return dist(gen);
}

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

void SLL::ListNode::setPosition(const float &x, const float &y)
{
	TextButton::setPosition(x, y);
    m_center = m_position + m_size / 2;
}
void SLL::ListNode::draw()
{
	TextButton::draw();
}

void SLL::ListNode::handle()
{
	if (this->m_next) {
		this->m_arrow.setPosition(
			{this->getCenter().x + m_size.x / 2, this->getCenter().y}, 
			{this->m_next->getCenter().x - m_size.y / 2, this->m_next->getCenter().y}
		);
		this->m_arrow.m_thickness = m_size.y / 10;
		this->m_arrow.color = text_setting->color;
	}
	TextButton::handle();
	SlowMotion::handle();
}

Vector2 SLL::ListNode::getCenter() const
{
    return m_center;
}

Vector2 SLL::ListNode::getPosition() const
{
	return TextButton::getPosition();
}

SLL::SLLForm::SLLForm(const int &index, FormSetting form_setting, const Vector2 &window_size): Form(index,form_setting,window_size)
{
	m_node_size = 50;
	m_node_spacing = 50;

	temp_b_setting.click_color = form_setting.click_color;
	temp_b_setting.hover_color = form_setting.hover_color;
	temp_b_setting.normal_color = RED;
	temp_b_setting.roundness = form_setting.roundness;
	temp_b_setting.segment = form_setting.segment;

	temp_t_setting.color = BLACK;
	temp_t_setting.font = form_setting.font;
	temp_t_setting.font_size = form_setting.font_size;
	temp_t_setting.spacing = form_setting.spacing;
	
	m_dummy = new ListNode(-1,-1);
	m_head = m_dummy;
}

void SLL::SLLForm::add(const vector<string> &str)
{
	for (int i = str.size()-1; i>=0; i--) {
		InsertNextMainCommand({_insert,1.0f * to_int(str[i])});
		//console.InsertNextMainCommand("Add " + str[i]);
	}
}

void SLL::SLLForm::handle() {
    Form::handle();
    ListNode* cur = m_head->m_next;
	while (cur) {
		cur->handle();
		cur=cur->m_next;
	}
}

void SLL::SLLForm::rePosition() {
    ListNode* cur = m_head->m_next;
    while (cur) {
		if (cur) {
			float target_x = m_workspace.x + 100 * cur->getIndex() - 100 * (size) / 2;
    		float target_y = m_workspace.y;
    		cur->setDuration(getSpeed()/2); 
    		cur->setSlowPosition(target_x, target_y);
		}
		cur->setSize(m_node_size, m_node_size);
		cur=cur->m_next;
	}
}

void SLL::SLLForm::remove(const std::string & str)
{
	console.InsertNextMainCommand("Remove " + str);
	console.goDown();
	ListNode* cur = m_head;
	int value = stoi(str);
	while (cur && cur->getValue() != value)
	{
		cur = cur->m_next;
	}
	if (cur) {
		InsertNextMainCommand({_delete,float(value),float(cur->getIndex())});
	} else InsertNextMainCommand({_delete,float(value),float(size)});
}


void SLL::SLLForm::update(const std::string & old_value, const std::string & new_value)
{
	int count = 0;
	ListNode* cur = m_head;
	int value = stoi(old_value);
	while (cur) {
		if (cur->getValue() == value) break;
		cur = cur->m_next;
		count++;
	}
	if (!cur) {
		InsertNextMainCommand({_update,float(stoi(old_value)),float(stoi(new_value)),-1});
	}
	InsertNextMainCommand({_update,float(stoi(old_value)),float(stoi(new_value)),float(count)});
}

void SLL::SLLForm::search(const std::string & x)
{
}


void SLL::SLLForm::draw()
{
	Form::draw();
	BeginMode2D(m_camera);
    BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
	ListNode* cur = m_head->m_next;
	while (cur) {
		cur->draw();
		if (cur->m_next) cur->m_arrow.draw();
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
		setDuration(0.001);
		break;
	}
	case _insertSilent:
	{
		insertSilent(int(command[1]),int(command[2]));
		rePosition();
		break;
	}
	case _delete:
	{
		remove(int(command[1]),int(command[2]));
		setDuration(0.001);
		break;
	}
	case _removeSilent:
	{
		cout << 1;
		removeSilent(int(command[1]),int(command[2]));
		rePosition();
		break;
	}
	case _choose:
	{
		ListNode* cur = m_head;
		while (cur->getIndex() != int(command[1])) cur = cur->m_next;
		cur->text_setting = &temp_t_setting;
		cur->button_setting = &temp_b_setting;
		setDuration(int(command[2]));
		break;
	}
	case _unchoose:
	{
		ListNode* cur = m_head;
		while (cur->getIndex() != int(command[1])) cur = cur->m_next;
		cur->text_setting = &form_setting;
		cur->button_setting = &form_setting;
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
		case _choose:
		{
			ListNode* cur = m_head;
			while (cur->getIndex() != int(command[1])) cur = cur->m_next;
			cur->text_setting = &form_setting;
			cur->button_setting = &form_setting;
			break;
		}
		case _unchoose:
		{
			ListNode* cur = m_head;
			while (cur->getIndex() != int(command[1])) cur = cur->m_next;
			cur->text_setting = &temp_t_setting;
			cur->button_setting = &temp_b_setting;
			break;
		}
		case _insertSilent:
		{
			removeSilent(int(command[1]),int(command[2]));
			rePosition();
			break;
		}
		case _removeSilent:
		{
			insertSilent(int(command[1]),int(command[2]));
			rePosition();
			break;
		}
		default:
			break;
	}
}

SLL::SLLForm::~SLLForm()
{
	for (int i = 0;i<size;i++) {
		ListNode* del = m_head;
		m_head = m_head->m_next;
		delete del;
	}
}

void SLL::SLLForm::insert(const int &value, const int &index)
{
	ListNode* cur = m_head;
	while (cur && cur->getIndex() != index-1) {
		if (cur->getIndex() == -1) {
			cur = cur->m_next;
			continue;
		}
		InsertNextSubCommand({_choose,float(cur->getIndex()),1});
		InsertNextSubCommand({_unchoose,float(cur->getIndex()),1});
		cur = cur->m_next;
	}
	InsertNextSubCommand({_choose,float(cur->getIndex()),1});
	InsertNextSubCommand({_unchoose,float(cur->getIndex()),1});
	InsertNextSubCommand({_insertSilent,float(value),float(index)});
	InsertNextSubCommand({_choose,float(cur->getIndex()+1),1});
	InsertNextSubCommand({_unchoose,float(cur->getIndex()+1),1});
}

void SLL::SLLForm::insertSilent(const int& value, const int& index) {
    ListNode* cur = m_head;
    while (cur && cur->getIndex() != index - 1) {
        cur = cur->m_next;
    }
    if (!cur) return; 
    ListNode* newNode = new ListNode(value, index);
    newNode->m_next = cur->m_next;
    cur->m_next = newNode;
    newNode->button_setting = &form_setting;
    newNode->text_setting = &form_setting;
    newNode->setPosition(getRandom(0, m_workspace.width), getRandom(0, m_workspace.height));
    ListNode* temp = newNode->m_next;
    while (temp) {
        temp->setIndex(temp->getIndex() + 1);
        temp = temp->m_next;
    }
    size++;
}


void SLL::SLLForm::remove(const int &value,const int& index)
{
	ListNode* cur = m_head->m_next;
	if (index == 0) {
		InsertNextSubCommand({_removeSilent,float(value),float(index)});
		return;
	}
	while (cur && cur->getIndex() != index-1) {
		InsertNextSubCommand({_choose,float(cur->getIndex()),1});
		InsertNextSubCommand({_unchoose,float(cur->getIndex()),1});
		cur = cur->m_next;
	}
	if (cur && cur->m_next) {
		InsertNextSubCommand({_choose,float(cur->getIndex()),1});
		InsertNextSubCommand({_removeSilent,float(value),float(index)});
		InsertNextSubCommand({_unchoose,float(cur->getIndex()),1});
	} else {
		//There is nothing to delete
		InsertNextSubCommand({_choose,float(cur->getIndex()),1});
		InsertNextSubCommand({_unchoose,float(cur->getIndex()),1});
	}
}

void SLL::SLLForm::removeSilent(const int &value, const int &index)
{
    if (!m_dummy || !m_dummy->m_next) return;

    ListNode* cur = m_dummy;
    while (cur->m_next && cur->m_next->getIndex() != index) {
        cur = cur->m_next;
    }

    if (cur->m_next) {
        ListNode* del = cur->m_next;
        cur->m_next = del->m_next;
        delete del;

        ListNode* temp = cur->m_next;
        while (temp) {
            temp->setIndex(temp->getIndex() - 1);
            temp = temp->m_next;
        }

        size--;
    }
}


// void SLL::SLLForm::update(const int &old_value, const int &new_value)
// {
// 	ListNode* cur = m_head;
// 	int count = 0;
// 	while (cur) {
// 		if (cur->getValue() == old_value) break;
// 		InsertNextSubCommand({_choose,float(count),1});
// 		console.InsertNextSubCommand(to_string(cur->getValue()) + " is not " + to_string(old_value));
// 		InsertNextSubCommand({_unchoose,float(count),1});
// 		cur = cur->m_next;
// 		count++;
// 	}
// 	if (!cur) return;
// 	InsertNextSubCommand({_choose,float(count),1});
// 	console.InsertNextSubCommand("Change " + to_string(old_value) + " to " + to_string(new_value));
// 	InsertNextSubCommand({_updateSilent,float(new_value),float(count)});
// 	InsertNextSubCommand({_unchoose,float(count),1});
// }

// void SLL::SLLForm::updateSilent(const int &value, const int &index)
// {
// 	ListNode* cur = m_head;
// 	while (cur && cur->getIndex() != index) cur = cur->m_next;
// 	cur->setValue(value);
// }
void SLL::Arrow::setPosition(Vector2 tail, Vector2 head)
{
    m_tail = tail;
    m_t1 = head;
    Vector2 dir = { head.x - tail.x, head.y - tail.y };
    float len = sqrt(dir.x * dir.x + dir.y * dir.y);
    dir.x /= len;
    dir.y /= len;
    float arrowSize = 10.0f;
    m_t2.x = m_t1.x - dir.x * arrowSize - dir.y * arrowSize;
    m_t2.y = m_t1.y - dir.y * arrowSize + dir.x * arrowSize;
    m_t3.x = m_t1.x - dir.x * arrowSize + dir.y * arrowSize;
    m_t3.y = m_t1.y - dir.y * arrowSize - dir.x * arrowSize;
	
}


void SLL::Arrow::handle()
{

}

void SLL::Arrow::draw()
{
	DrawLineEx(m_tail,{m_t2.x,m_t1.y},m_thickness,color);
	DrawTriangleLines(m_t1,m_t2,m_t3,color);
}
