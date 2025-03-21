#include "../include/SinglyLinkedList.h"
#include "../include/General.h"

namespace SLL {
	Node::Node(const int& index, const int& val) {
		TextButton::init();
		m_value = 0;
		m_index = 0;
		setSize(50, 50);
		setText(std::to_string(m_value));
	}
	int Node::getIndex() const {
		return m_index;
	}
	int Node::getValue() const {
		return m_value;
	}
	void Node::handle() {
		TextButton::handle();
	}
	void Node::setPosition(const float& x, const float& y) {
		m_center = { x, y };
		TextButton::setPosition(x, y);
	}
	Vector2 Node::getPosition() const {
		return m_center;
	}
	Node::~Node() {

	}
	SLLForm::SLLForm(const Vector2& window_size) : Form(window_size) {
		m_head = nullptr;
		setPause(true);
	}
	void SLLForm::add(const vector<std::string>& x) {
		for (auto& i:x) {
			console.InsertNextMainCommand("Add " + i);
			InsertNextMainCommand({ _Insert, 1.0f * to_int(i), 1});
		}
	}
	void SLLForm::insert(Node*& head, const int& x, const int& index) {
		Node* newNode = new Node(m_list.size(), x);
		if (index == 0 || !head) {
			newNode->next = head;
			head = newNode;
		}
		else {
			Node* curr = head;
			int count = 0;
			while (curr->next && count < index - 1) {
				InsertNextSubCommand({ _Choose, (float)curr->getIndex(), 1 });
				InsertNextSubCommand({ _Unchoose, (float)curr->getIndex(), 1 });
				curr = curr->next;
				count++;
			}
			InsertNextSubCommand({ _Choose, (float)curr->getIndex(), 1 });
			InsertNextSubCommand({ _Unchoose, (float)curr->getIndex(), 1 });
			newNode->next = curr->next;
			curr->next = newNode;
		}
		m_list.push_back(newNode);
		rePosition();
	}
	void SLLForm::remove(Node*& head, const int& x) {
		if (!head) return;
		Node* prev = nullptr, * curr = head;
		while (curr && curr->getValue() != x) {
			InsertNextSubCommand({ _Choose, (float)curr->getIndex(), 1 });
			InsertNextSubCommand({ _Unchoose, (float)curr->getIndex(), 1 });
			prev = curr;
			curr = curr->next;
		}
		if (curr) {
			if (prev) prev->next = curr->next;
			else head = curr->next;
			delete curr;
			rePosition();
		}
	}
	void SLLForm::remove(const std::string& x) {
		InsertNextMainCommand({ _Delete, 1.0f * to_int(x) });
	}
	void SLLForm::removeAtIndex(const int& index) {
		InsertNextMainCommand({ _Delete, -1, (float)index });
	}
	void SLLForm::removeAtIndex(Node*& head, const int& index) {
		if (!head) return;
		Node* prev = nullptr, * curr = head;
		int count = 0;
		while (curr && count < index) {
			InsertNextSubCommand({ _Choose, (float)curr->getIndex(), 1 });
			InsertNextSubCommand({ _Unchoose, (float)curr->getIndex(), 1 });
			prev = curr;
			curr = curr->next;
			count++;
		}
		if (curr) {
			if (prev) prev->next = curr->next;
			else head = curr->next;
			delete curr;
			rePosition();
		}
	}
	void SLLForm::FetchNextCommand(const std::vector<float>& command) {
		if (command.empty()) return;


		switch ((int)command[0]) {
		case _Insert:
			insert(m_head, (int)command[1], (int)command[2]);
			setDuration(command[2]);
			break;
		case _Delete:
			if ((int)command[1] != -1) remove(m_head, (int)command[1]);
			else removeAtIndex(m_head, (int)command[2]);
			break;
		case _Choose:
			console.goDown();
			// m_list[(int)command[1]] = RED;
			setDuration(command[2]);
			break;
		case _Unchoose:
			// m_list[(int)command[1]]->m_normal_color = WHITE;
			setDuration(command[2]);
			break;
		default:
			break;
		}
	}
	void SLLForm::init()
	{
		Form::init();
	}
	void SLLForm::search(const int& x)
	{
	}
	void SLLForm::update(const int& x)
	{
	}
	void SLLForm::FetchPrevCommand(const std::vector<float>& command) {
		if (command.empty()) return;
		switch ((int)command[0]) {
		case _Insert:
			removeAtIndex(m_head, (int)command[2]);
			rePosition();
			setDuration((int)command[1]);
			console.goUp();
			break;
		case _Delete:
			insert(m_head, (int)command[1], (int)command[2]);
			rePosition();
			console.goUp();
			break;
		case _Choose:
			// m_list[(int)command[1]]->m_normal_color = WHITE;
			setDuration(command[2]);
			break;
		case _Unchoose:
			// m_list[(int)command[1]]->m_normal_color = RED;
			setDuration(command[2]);
			break;
		default:
			break;
		}
	}
	void SLLForm::rePosition() {
		if (!m_head) return;
		Node* curr = m_head;
		float x = 50, y = 100;
		while (curr) {
			curr->setPosition(x, y);
			x += 100;
			curr = curr->next;
		}
	}
	void SLLForm::draw() {
		Form::draw();
		BeginMode2D(m_camera);
		BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
		EndScissorMode();
		EndMode2D();
	}
	void Node::draw() {
		TextButton::draw();
		Vector2 index_pos = m_text_position;
		index_pos.y -= text_setting->font_size + 5;
		DrawTextEx(text_setting->font, std::to_string(m_index).c_str(), index_pos, text_setting->font_size / 1.5,text_setting->spacing, WHITE);
	}
	void SLLForm::handle() {
		Form::handle();
		handle(m_head);
	}
	void SLLForm::handle(Node* head) {
		Node* curr = head;
		while (curr) {
			curr->handle();
			curr = curr->next;
		}
	}
	void SLLForm::free(Node* head) {
		while (head) {
			Node* tmp = head;
			head = head->next;
			delete tmp;
		}
	}
	void SLLForm::close() {
		Form::close();
		free(m_head);
	}
	SLLForm::~SLLForm() {
		
	}
}
