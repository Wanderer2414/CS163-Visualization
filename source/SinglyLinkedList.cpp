#include "../include/SinglyLinkedList.h"

int getRandom(int min, int max) {
    static std::random_device rd; 
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max); 
    return dist(gen);
}

SLL::ListNode::ListNode(const int &value, const int &index, Camera2D& c) : TextButton(0,0), camera(c)
{
	m_value = value;
	m_index = index;
	TextButton::setText(to_string(m_value));
	m_next = nullptr;
	m_is_focus = false;
}

bool SLL::ListNode::isFocus() const {
	return m_is_focus;	
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
	//m_cur
	if (this->getIndex() == -10) {
		if (this->m_next) {
			this->m_arrow.setPosition(
				{this->getCenter().x, this->getPosition().y}, 
				{this->getCenter().x,this->m_next->getCenter().y+this->m_next->m_size.y/2}
			);
			this->m_arrow.m_thickness = m_size.y / 10;
			this->m_arrow.color = text_setting->color;
		}
	}
	else if (this->m_next) {
		this->m_arrow.setPosition(
			{this->getPosition().x + m_size.x - 5, this->getCenter().y}, 
			{this->m_next->getPosition().x, this->m_next->getCenter().y}
		);
		this->m_arrow.m_thickness = m_size.y / 10;
		this->m_arrow.color = text_setting->color;
	}
	m_is_hovered = CheckCollisionPointRec(TransToGlobalPoint(camera, GetMousePosition()), { m_position.x, m_position.y, m_size.x, m_size.y });
	m_is_pressed = m_is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		m_is_focus = m_is_hovered;
	}
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

SLL::SLLForm::SLLForm(const int &index, FormSetting f_setting, const Vector2 &window_size): Form(index,f_setting,window_size)
{
	m_node_size = 50;
	m_node_spacing = 50;

	temp_b_setting = form_setting;
	temp_b_setting.normal_color = form_setting.hightlight_color1;
	
	m_dummy = new ListNode(-1,-1, m_camera);
	m_head = m_dummy;
	m_dummy->setText("head");
	m_dummy->text_setting = &form_setting;
	m_dummy->button_setting = &form_setting;
	
	null = new ListNode(-1,0, m_camera);
	null->setText("NULL");
	null->text_setting = &form_setting;
	null->button_setting = &form_setting;

	m_cur = new ListNode(-1,-10, m_camera);
	m_cur->setText("cur");
	m_cur->text_setting = &form_setting;
	m_cur->button_setting = &form_setting;
	m_cur->setPosition(m_dummy->getPosition().x,m_dummy->getPosition().y);
	m_cur->setSize(m_node_size,m_node_size);
	m_cur->m_arrow.show = true;
	showCur = false;

	m_head->m_arrow.show = true;
	m_dummy->m_next = null;
	rePosition();
}

void SLL::SLLForm::add(const vector<string> &str)
{
	if (str.size() == 0) return;
	for (int i = str.size()-1; i>=0; i--) {
		InsertNextMainCommand({_insert,1.0f * to_int(str[i])});
	}
}

void SLL::SLLForm::handle() {

    Form::handle();
    ListNode* cur = m_head;
	ListNode* focus_node = 0;
	while (cur) {
		cur->handle();
		if (cur->isFocus()) focus_node = cur;
		cur=cur->m_next;
	}
	if (focus_node && focus_node != m_head && focus_node != null) {
		if (IsKeyDown(KEY_DELETE)) {
			main_box_show();
			option_box.select(4);
			remove_textbox.setText(focus_node->getText());
			remove_textbox.setFocus(true);
		}
		else if (IsKeyDown(KEY_F2)) {
			main_box_show();
			option_box.select(2);
			update_textbox_choice.setText(focus_node->getText());
			update_textbox_value.setFocus(true);
		}
	}
	m_cur->handle();
}

void SLL::SLLForm::rePosition() {
    ListNode* cur = m_head;
    while (cur) {
		if (cur) {
			float target_x = m_workspace.x + 100 * cur->getIndex() - 100 * (size) / 2 - ((cur == m_dummy ) ? m_node_size : 0);
    		float target_y = m_workspace.y;
			if (cur == null) {
				float target_x = m_workspace.x + 100 * cur->getIndex() - 100 * (size) / 2;
				float target_y = m_workspace.y;
			}
    		cur->setDuration(getSpeed()/2); 
    		cur->setSlowPosition(target_x, target_y);
		}
		cur->setSize(m_node_size + ((cur == m_dummy || cur == null) ? m_node_size : 0), m_node_size);
		cur=cur->m_next;
	}
	showCur = false;
	m_cur->setPosition(m_dummy->getPosition().x,m_dummy->getPosition().y+125);
}

void SLL::SLLForm::remove(const std::string & str)
{
	if (str.size() == 0) return;
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
	if (old_value.size() == 0 || new_value.size() == 0) return;
	InsertNextMainCommand({_update,float(stoi(old_value)),float(stoi(new_value))});
}

void SLL::SLLForm::search(const std::string & x)
{
	if (x.size() == 0) return;
	InsertNextMainCommand({_search,float(stoi(x))});
}


void SLL::SLLForm::draw()
{
	BeginMode2D(m_camera);
    BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
	ListNode* cur = m_head;
	while (cur) {
		if (cur->m_next) cur->m_arrow.draw();
		cur->draw();
		cur = cur->m_next;
	}
	if (showCur == true) {
		m_cur->draw();
		if (m_cur->m_next) m_cur->m_arrow.draw();
	}
	EndScissorMode();
    EndMode2D();
	Form::draw();
}


void SLL::SLLForm::FetchNextCommand(const std::vector<float>& command)
{
	if (command.empty()) return;
	switch ((int)command[0])
	{
	//case _moveCorner:
	//{
	//	moveCorner(int(command[1]));
	//	setDuration(1);
	//	break;
	//}
	//case _showArrow:
	//{
	//	int index = int(command[1]);
	//	ListNode* cur = m_head;
	//	while (cur->getIndex() != index) cur = cur->m_next;
	//	cur->m_arrow.show = true;
	//	setDuration(int(command[2]));
	//	break;
	//}
	case _insert:
	{
		console.goDown();
		console.goDown();
		console_add_insert(int(command[1]));
		console.goDown();
		console.goDown();
		insert(int(command[1]),size);
		setDuration(0.001);
		break;
	}
	case _insertSilent:
	{
		insertSilent(int(command[1]),int(command[2]));
		break;
	}
	case _delete:
	{
		console.goDown();
		console.goDown();
		console_add_remove(int(command[1]));
		console.goDown();
		console.goDown();
		remove(int(command[1]),int(command[2]));
		setDuration(0.001);
		break;
	}
	case _removeSilent:
	{
		console.goDown();
		removeSilent(int(command[1]),int(command[2]));
		break;
	}
	case _update:
	{	
		console.goDown();
		console.goDown();
		console_add_update(int(command[1]),int(command[2]));
		update(int(command[1]),int(command[2]));
		console.goDown();
		console.goDown();
		break;
	}
	case _updateSilent:
	{
		console.goDown();
		updateSilent(int(command[1]),int(command[2]),int(command[3]));
		break;
	}
	case _search: 
	{
		console.goDown();
		console.goDown();
		console_add_search(int(command[1]));
		console.goDown();
		console.goDown();
		search(int(command[1]));
		break;
	}
	case _choose:
	{
		ListNode* cur = m_head;
		while (cur->getIndex() != int(command[1])) cur = cur->m_next;
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
		break;
	}
	case _GoDowm:
	{
		for (int i = 0 ;i<int(command[1]);i++) {
			console.goDown();
		}
		setDuration(int(command[2]));
		break;
	}
	case _GoUp: 
	{
		for (int i = 0 ;i<int(command[1]);i++) {
			console.goUp();
		}
		setDuration(int(command[2]));
		break;
	}
	case _rePo:
	{
		rePosition();
		//setDuration(1);
		break;
	}
	case _rePoCur:
	{
		rePoCur(int(command[1]));
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
	/*	case _forRemove: 
		{
			moveCorner(int(command[1]));
			setDuration(1);
			break;
		}
		case _showArrow:
		{
			int index = int(command[1]);
			ListNode* cur = m_head;
			while (cur->getIndex() != index) cur = cur->m_next;
			cur->m_arrow.show = false;
			break;
		}*/
		case _rePoCur:
		{
			if (int(command[1] == -1)) return;
			rePoCur(int(command[1])-1);
			break;
		}
		case _GoDowm:
		{
			for (int i = 0 ;i<int(command[1]);i++) {
				console.goUp();
			}
			setDuration(int(command[2]));
			break;
		}
		case _GoUp: 
		{
			for (int i = 0 ;i<int(command[1]);i++) {
				console.goDown();
			}
			setDuration(int(command[2]));
			break;
		}
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
			/*int index = int(command[2]);
			ListNode* cur = m_head;
			while (cur->getIndex() != index) cur = cur->m_next;
			cur->m_arrow.show = true;*/
			rePosition();
			break;
		}
		case _updateSilent:
		{
			updateSilent(int(command[2]),int(command[1]),int(command[3]));
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
		InsertNextSubCommand({_rePoCur,float(cur->getIndex())});
		InsertNextSubCommand({_choose,float(cur->getIndex()),1});
		InsertNextSubCommand({_GoUp,1,1});
		InsertNextSubCommand({_GoDowm,1,0.75});
		InsertNextSubCommand({_unchoose,float(cur->getIndex()),1});
		cur = cur->m_next;
	}
	InsertNextSubCommand({_GoDowm,1,0.5});
	InsertNextSubCommand({_rePoCur,float(cur->getIndex())});
	InsertNextSubCommand({_choose,float(cur->getIndex()),1});
	InsertNextSubCommand({_unchoose,float(cur->getIndex()),1});
	InsertNextSubCommand({_insertSilent,float(value),float(index)});
	//InsertNextSubCommand({_forRemove,float(cur->getIndex()+1)});
	InsertNextSubCommand({_rePo});
	//InsertNextSubCommand({_showArrow,float(cur->getIndex()+1),1});
	InsertNextSubCommand({_choose,float(cur->getIndex()+1),1});
	InsertNextSubCommand({_unchoose,float(cur->getIndex()+1),1});
}

void SLL::SLLForm::insertSilent(const int& value, const int& index) {
    ListNode* cur = m_head;
    while (cur && cur->getIndex() != index - 1) {
        cur = cur->m_next;
    }
    if (!cur) return; 
    ListNode* newNode = new ListNode(value, index, m_camera);
    newNode->m_next = cur->m_next;
    cur->m_next = newNode;
    newNode->button_setting = &form_setting;
    newNode->text_setting = &form_setting;
    //newNode->setPosition(m_workspace.width,m_workspace.height);
	newNode->setSize(m_node_size,m_node_size);
	//newNode->m_arrow.show = false;
    ListNode* temp = newNode->m_next;
    while (temp) {
        temp->setIndex(temp->getIndex() + 1);
        temp = temp->m_next;
    }
    size++;
}

void SLL::SLLForm::console_add_insert(const int &value)
{
	console.InsertNextMainCommand("Add " + to_string(value));
	console.InsertNextSubCommand("while (cur->next) ");
	console.InsertNextSubCommand("cur=cur->next;");
	console.InsertNextSubCommand("cur->next = new Node(" + to_string(value)+");");
}

void SLL::SLLForm::remove(const int &value,const int& index)
{
	ListNode* cur = m_head->m_next;
	if (index == 0) {
		InsertNextSubCommand({_GoDowm,1,1});
		InsertNextSubCommand({_GoDowm,1,1});
		InsertNextSubCommand({_removeSilent,float(value),float(index)});
		return;
	}
	while (cur && cur->getIndex() != index-1) {
		InsertNextSubCommand({_rePoCur,float(cur->getIndex())});
		InsertNextSubCommand({_choose,float(cur->getIndex()),1});
		InsertNextSubCommand({_GoUp,1,1});
		InsertNextSubCommand({_GoDowm,1,0});
		InsertNextSubCommand({_unchoose,float(cur->getIndex()),1});
		cur = cur->m_next;
	}
	if (cur && cur->m_next) {
		InsertNextSubCommand({_GoDowm,1,1});
		InsertNextSubCommand({_rePoCur,float(cur->getIndex())});
		InsertNextSubCommand({_GoDowm,1,0});
		InsertNextSubCommand({_choose,float(cur->getIndex()),1});
		//InsertNextSubCommand({_moveCorner,float(index)});
		InsertNextSubCommand({_removeSilent,float(value),float(index)});
		InsertNextSubCommand({_rePo});
		InsertNextSubCommand({_unchoose,float(cur->getIndex()),1});
	} else {
		//There is nothing to delete
		InsertNextSubCommand({_GoDowm,3,1});
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

//void SLL::SLLForm::moveCorner(const int &index)
//{
//	ListNode* cur = m_head;
//	while (cur->getIndex() != index) cur = cur->m_next;
//	cur->setDuration(getSpeed());
//	cur->setSlowPosition(m_workspace.width,m_workspace.height);
//}
void SLL::SLLForm::console_add_remove(const int &value)
{
	console.InsertNextMainCommand("Remove " + to_string(value));
	console.InsertNextSubCommand("while (cur->next && cur->next->val != " + to_string(value) +")");
	console.InsertNextSubCommand("cur=cur->next;");
	console.InsertNextSubCommand("if (cur->next)");
	console.InsertNextSubCommand("cur->next = cur->next->next;");
	console.InsertNextSubCommand("return;");
}

void SLL::SLLForm::update(const int &old_value, const int &new_value)
{
	ListNode* cur = m_head->m_next;
	while (cur && cur->getValue() != old_value) 
	{	
		InsertNextSubCommand({_rePoCur,float(cur->getIndex())});
		InsertNextSubCommand({_choose,float(cur->getIndex()),1});
		InsertNextSubCommand({_GoUp,1,1});
		InsertNextSubCommand({_GoDowm,1,0});
		InsertNextSubCommand({_unchoose,float(cur->getIndex()),1});
		cur = cur->m_next;
	}
	if (cur) {
		InsertNextSubCommand({_GoDowm,1,1});
		InsertNextSubCommand({_rePoCur,float(cur->getIndex())});
		InsertNextSubCommand({_GoDowm,1,0});
		InsertNextSubCommand({_choose,float(cur->getIndex()),1});
		InsertNextSubCommand({_updateSilent,float(old_value),float(new_value),float(cur->getIndex())});
		InsertNextSubCommand({_unchoose,float(cur->getIndex()),1});
		InsertNextSubCommand({_rePo});
	} else InsertNextSubCommand({_GoDowm,3,1});
}

void SLL::SLLForm::updateSilent(const int &old_value, const int &new_value, const int &index)
{
	ListNode* cur = m_head;
	while (cur && cur->getIndex() != index) cur = cur->m_next;
	if (cur) cur->setValue(new_value);
}

void SLL::SLLForm::console_add_update(const int &old_value,const int& new_value)
{
	console.InsertNextMainCommand("Update " + to_string(old_value) + " to " + to_string(new_value));
	console.InsertNextSubCommand("while (cur->val != " + to_string(old_value) +")");
	console.InsertNextSubCommand("cur = cur->next");
	console.InsertNextSubCommand("if (cur)");
	console.InsertNextSubCommand("cur->val = " + to_string(new_value) +";");
	console.InsertNextSubCommand("return;");
}

void SLL::SLLForm::search(const int &value)
{
	ListNode* cur = m_head->m_next;
	while (cur && cur->getValue() != value) {
		InsertNextSubCommand({_rePoCur,float(cur->getIndex())});
		InsertNextSubCommand({_choose,float(cur->getIndex()),1});
		InsertNextSubCommand({_GoUp,1,1});
		InsertNextSubCommand({_GoDowm,1,0});
		InsertNextSubCommand({_unchoose,float(cur->getIndex()),1});
		cur=cur->m_next;
	}
	if (cur) {
		InsertNextSubCommand({_GoDowm,1,1});
		InsertNextSubCommand({_GoDowm,1,0});
		InsertNextSubCommand({_rePoCur,float(cur->getIndex())});
		InsertNextSubCommand({_choose,float(cur->getIndex()),1});
		InsertNextSubCommand({_rePo});
	}
}

void SLL::SLLForm::console_add_search(const int &value)
{
	console.InsertNextMainCommand("Search for " + to_string(value));
	console.InsertNextSubCommand("while (cur->val != " + to_string(value) + ")");
	console.InsertNextSubCommand("cur=cur->next;");
	console.InsertNextSubCommand("if (cur)");
	console.InsertNextSubCommand("Hightlight");
	console.InsertNextSubCommand("return;");
}

void SLL::SLLForm::rePoCur(const int& index)
{
	ListNode* cur = m_head;
	while (cur->getIndex() != index) cur=cur->m_next;
	if (cur) {
		showCur = true;
		m_cur->m_next = cur;
		m_cur->setDuration(getSpeed()/2);
		m_cur->setSlowPosition(cur->getPosition().x,cur->getPosition().y+125);
	}

}

void SLL::Arrow::setPosition(Vector2 tail, Vector2 head) {
	m_tail = tail;
	m_head = head;
	Vector2 dir = head-tail;
	float len = sqrt(dir.x*dir.x + dir.y*dir.y);

	if (len == 0) {
		dir = Vector2{1, 0}; 
		len = 1;
	} else {
		dir = dir*1.0f/len;
	}

	float arrowSize = 10.0f;
	float wingSize = 5.0f;

	m_t1 = head - dir*arrowSize;

	Vector2 perp = { -dir.y, dir.x }; 
	perp = perp*wingSize;

	m_t2 = m_t1+perp;
	m_t3 = m_t1-perp;
}

void SLL::Arrow::handle()
{
	
}

void SLL::Arrow::draw()
{
	DrawLineEx(m_tail,m_t1,m_thickness,color);
	DrawTriangle(m_t2,m_head,m_t3,color);
}
