#include "../include/SinglyLinkedList.h"
#include <math.h>
#include <string.h>
#include <random>

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

	

}

void SLL::SLLForm::add(const vector<string> &str)
{
	for (int i = str.size()-1; i>=0; i--) {
		InsertNextMainCommand({_insert,(float)stoi(str[i])});
		//console.InsertNextMainCommand("Add " + str[i]);
	}
}

void SLL::SLLForm::handle() {
    Form::handle();
    ListNode* cur = m_head;
	while (cur) {
		cur->handle();
		cur=cur->m_next;
	}
}

void SLL::SLLForm::rePosition() {
    ListNode* cur = m_head;
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
	setDuration(1);
	console.goDown();
	ListNode* cur = m_head;
	int count = 0;
	while (cur) {
		if (cur->getValue() == stoi(str)) break;
		cur=cur->m_next;
		count++;
	}
	if (cur) {
		InsertNextMainCommand({_delete,(float)stoi(str),float(count)});
	} else InsertNextMainCommand({_delete,(float)stoi(str),-1});
}


void SLL::SLLForm::update(const std::string & old_value, const std::string & new_value)
{
	InsertNextMainCommand({_update,float(stoi(old_value)),float(stoi(new_value))});
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
		setDuration(0);
		break;
	}
	case _insertNext:
	{
		insertNext(int(command[1]),int(command[2]));
		rePosition();
		break;
	}
	case _delete:
	{
		remove(int(command[1]),int(command[2]));
		setDuration(0);
		break;
	}
	case _removeNext: 
	{
		removeNext(int(command[1]),int(command[2]));
		rePosition();
		break;
	}
	case _update:
	{
		update(int(command[1]),int(command[2]));
		setDuration(0);
		break;
	}
	case _choose: 
	{
		ListNode* cur = m_head;
		int count = 0;
		while (count < int(command[1])) {
			count++;
			cur=cur->m_next;
		}
		cur->button_setting->normal_color = BLUE;
		setDuration(int(command[2]));
		break;
	}
	case _unchoose:
	{
		ListNode* cur = m_head;
		int count = 0;
		while (count < int(command[1])) {
			count++;
			cur=cur->m_next;
		}
		cur->button_setting->normal_color = form_setting.normal_color;
		console.goDown();
		setDuration(0);
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
		remove(int(command[1]),-1);//delete the last one
		break;
	}
	case _insertNext:
	{
		insertNext(int(command[1]),int(command[2]));
		rePosition();
		break;
	}
	case _delete:
	{
		insert(int(command[1]),int(command[2]));
		setDuration(0);
		break;
	}
	case _removeNext: 
	{
		removeNext(int(command[1]),int(command[2]));
		rePosition();
		break;
	}
	case _update:
	{
		update(int(command[2]),int(command[1]));
		setDuration(0);
		break;
	}
	case _choose: 
	{
		ListNode* cur = m_head;
		int count = 0;
		while (count < int(command[1])) {
			count++;
			cur=cur->m_next;
		}
		cur->text_setting = &form_setting;
		setDuration(int(command[2]));
		break;
	}
	case _unchoose:
	{
		ListNode* cur = m_head;
		int count = 0;
		while (count < int(command[1])) {
			count++;
			cur=cur->m_next;
		}
		cur->text_setting = &form_setting;
		setDuration(int(command[2]));
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
	if (index == -1) return;
	if (!m_head) {
		InsertNextSubCommand({_insertNext,float(value),0});
		size++;
		console.InsertNextSubCommand("Insert " + to_string(value));
		InsertNextSubCommand({_choose,0,1});
		InsertNextSubCommand({_unchoose,0,1});
	} else {
		ListNode* cur = m_head;
		int count=0;
		while (cur->m_next) {
			console.InsertNextSubCommand("Go next");
			InsertNextSubCommand({_choose,float(count),1});
			InsertNextSubCommand({_unchoose,float(count),1});
			cur = cur->m_next;
			count++;
		}
		console.InsertNextSubCommand("Go next");
		InsertNextSubCommand({_choose,float(count),1});
		InsertNextSubCommand({_unchoose,float(count),1});
		InsertNextSubCommand({_insertNext,float(value),float(count+1)});
		size++;
		console.InsertNextSubCommand("Insert " + to_string(value));
		InsertNextSubCommand({_choose,float(count+1),1});
		InsertNextSubCommand({_unchoose,float(count+1),1});
	}
}

void SLL::SLLForm::insertNext(const int &value,const int& index)
{
	ListNode* cur = m_head;
	if (!m_head) {
		m_head = new ListNode(value,index);
		cur = m_head;
	}
	else if (index == 0) {
		ListNode* newNode = new ListNode(value,index);
		newNode->m_next = m_head;
		m_head=newNode;
		ListNode* temp = m_head->m_next;
		while (temp) {
			temp->setIndex(temp->getIndex()+1);
			temp=temp->m_next;
		}
	} else {
		for (int i=0;i<index-1;i++) {
			cur = cur->m_next;
		}
		ListNode* newNode = new ListNode(value,index);
		newNode->m_next = cur->m_next;
		cur->m_next = newNode;
		cur = cur->m_next;
		ListNode* temp = cur->m_next;
		while (temp) {
			temp->setIndex(temp->getIndex()+1);
		}
	}
	cur->button_setting = new ButtonSetting;
	cur->button_setting->click_color = form_setting.click_color;
	cur->button_setting->hover_color = form_setting.hover_color;
	cur->button_setting->normal_color = form_setting.normal_color;
	cur->button_setting->roundness = form_setting.roundness;
	cur->button_setting->segment = form_setting.segment;
	cur->text_setting = new TextSetting;
	cur->text_setting->color = form_setting.color;
	cur->text_setting->font = form_setting.font;
	cur->text_setting->font_size = form_setting.font_size;
	cur->text_setting->spacing = form_setting.spacing;
	cur->setPosition(getRandom(0,m_workspace.width),getRandom(0,m_workspace.height));
	float target_x = m_workspace.x + 100 * index - 100 * (size) / 2;
    float target_y = m_workspace.y;
    cur->setDuration(getSpeed()/2); 
    cur->setSlowPosition(target_x, target_y);
}
void SLL::SLLForm::remove(const int &value,const int& index)
{
	ListNode* cur = m_head;
	int count = 0;
	if (!cur) return;
	if (index == -1) {
		size--;
		InsertNextSubCommand({_removeNext,float(value),float(index)});
		return;
	}
	if (cur->getValue() == value) {
		size--;
		InsertNextSubCommand({_choose,float(count),1});
		console.InsertNextSubCommand("Head is " + to_string(value));
		InsertNextSubCommand({_removeNext,float(value),0});
		console.goDown();
		return;
	}
	while (cur && cur->m_next && cur->m_next->getValue() != value) {
		console.InsertNextSubCommand("Next is not " + to_string(value)); 
		InsertNextSubCommand({_choose,float(count),1});
		InsertNextSubCommand({_unchoose,float(count),1});
		cur=cur->m_next;
		count++;
	}
	if (cur->m_next) {
		size--;
		InsertNextSubCommand({_choose,float(count),1});
		console.InsertNextSubCommand("Next is  " + to_string(value));
		setDuration(1);
		InsertNextSubCommand({_removeNext,float(value),float(count)+1});
		InsertNextSubCommand({_unchoose,float(count),1});
	}
}

void SLL::SLLForm::removeNext(const int &value,const int& index)
{
	if (index == -1) {
		if (!m_head) return;
		if (!m_head->m_next) {
			delete m_head;
			m_head = nullptr;
			return;
		}
		ListNode* pre = m_head;
		while (pre->m_next->m_next) pre = pre->m_next;
		ListNode* del = pre->m_next;
		delete del;
		pre->m_next = nullptr;
		return;
	}
	if (index == 0) {
		ListNode* del = m_head;
		m_head = m_head->m_next;
		delete del;
		ListNode* cur = m_head;
		while (cur) {
			cur->setIndex(cur->getIndex()-1);
			cur=cur->m_next;
		}
	} else {
		ListNode* pre = m_head;//1 2 3 4
		while (pre->getIndex() != index-1) pre=pre->m_next;
		ListNode* del = pre->m_next;
		pre->m_next = pre->m_next->m_next;
		delete del;
		pre=pre->m_next;
		while (pre) {
			pre->setIndex(pre->getIndex()-1);
			pre = pre->m_next;
		}
	}
}

void SLL::SLLForm::update(const int &old_value, const int &new_value)
{
	ListNode* cur = m_head;
	int count = 0;
	while (cur && cur->m_next && cur->getValue() != old_value) {
		console.InsertNextSubCommand(to_string(cur->getValue()) + " is not " + to_string(old_value)); 
		InsertNextSubCommand({_choose,float(count),1});
		InsertNextSubCommand({_unchoose,float(count),1});
		cur=cur->m_next;
		count++;
	}
	if (!cur) return;
	console.InsertNextSubCommand("Change " + to_string(cur->getValue()) + " to " + to_string(new_value));
	InsertNextSubCommand({_choose,float(count),1});
	cur->setValue(new_value);
	InsertNextSubCommand({_unchoose,float(count),1});
}

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
