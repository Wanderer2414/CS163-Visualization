#include "../include/AVLTree.h"
#include "../include/General.h"
#include <iostream>
#include <cmath>

AVLTreeForm::AVLTreeForm(const int& index, FormSetting form_setting, const Vector2& window_size) :
	Form(index, form_setting, window_size) {
	m_root = 0;
}

void AVLTreeForm::add(const vector<std::string>& x)
{
	for (int i = x.size() - 1; i >= 0; i--) {
		console.InsertNextMainCommand("Add " + x[i]);
		InsertNextMainCommand({ CommandCode::add, 1.0f * to_int(x[i]), 1 });
		rePosition();
		console.goDown();
	}
}
Node* AVLTreeForm::insert(Node*& root, const Vector2& par, const int& x)
{
	if (!root) {
		root = new Node(m_list.size(), x);
		root->button_setting = &form_setting;
		root->text_setting = &form_setting;
		root->setPosition(par.x, par.y);
		root->setSize(40, 40);
		root->setValue(x);
		m_list.push_back(root);

		InsertNextSubCommand({ CommandCode::redraw, 1.0f });
		return root;
	}
	console.InsertNextSubCommand("Compare with " + std::to_string(root->getValue()));
	InsertNextSubCommand({ CommandCode::choose, 1.0f * root->getIndex(), 1 });
	InsertNextSubCommand({ CommandCode::unchoose, 1.0f * root->getIndex(), 0 });

	if (x < root->getValue()) {
		root->left = insert(root->left, root->getCenter(), x);
		root->left->parent = root;
	}
	else if (x > root->getValue()) {
		root->right = insert(root->right, root->getCenter(), x);
		root->right->parent = root;
	}
	else return root;

	root->updateHeight();
	int balance = getBalanceFactor(root);
	// Left heavy
	if (balance > 1) {
		if (x < root->left->getValue()) {
			return rotateRight(root); // LL case
		}
		else {
			root->left = rotateLeft(root->left); // LR case
			return rotateRight(root);
		}
	} // Right Heavy
	else if (balance < -1) {
		if (x > root->right->getValue()) {
			return rotateLeft(root); // RR case
		}
		else {
			root->right = rotateRight(root->right); // RL case
			return rotateLeft(root);
		}
	}
	// recheck
	root->updateHeight();
	balance = getBalanceFactor(root);

	if (root->parent == nullptr) m_root = root;
	std::map<std::pair<float, int>, bool> board;
	rePosition(root, 0, 0, board);
	adjustPositions();
	return root;
}
void AVLTreeForm::handle()
{
	Form::handle();
	handle(m_root);
}

AVLTreeForm::~AVLTreeForm()
{
}

void AVLTreeForm::draw()
{
	Form::draw();
	BeginMode2D(m_camera);
	BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
	draw(m_root);
	EndScissorMode();
	EndMode2D();
}

void AVLTreeForm::FetchPrevCommand(const std::vector<float>& codes)
{
	if (codes.empty()) return;
	switch ((int)codes[0]) {
	case CommandCode::add: {
		remove(m_root, (int)codes[1]);
		rePosition();
		setDuration(0);
		console.goUp();
		break;
	}
	case CommandCode::erase: {
		insert(m_root, { 400, 100 }, (int)codes[1]);
		rePosition();
		console.goUp();
		break;
	}
	case CommandCode::rotateLeft: {
		Node*& node = findNode(m_root, (int)codes[1]);
		if (node) {
			node = rotateRight(node);
			rePosition();
		}
		break;
	}
	case CommandCode::rotateRight: {
		Node*& node = findNode(m_root, (int)codes[1]);
		if (node) {
			node = rotateLeft(node);
			rePosition();
		}
		break;
	}
	default:
		break;
	}
}

void AVLTreeForm::FetchNextCommand(const std::vector<float>& codes)
{
	if (codes.empty()) return;
	switch ((int)codes[0]) {
	case CommandCode::add: {
		insert(m_root, { 400, 100 }, (int)codes[1]);
		rePosition();
		setDuration(0);
		console.goDown();
		break;
	}
	case CommandCode::erase: {
		remove(m_root, (int)codes[1]);
		rePosition();
		break;
	}
	case CommandCode::rotateLeft: {
		Node*& node = findNode(m_root, (int)codes[1]);
		if (node) {
			node = rotateLeft(node);
			rePosition();
		}
		break;
	}
	case CommandCode::rotateRight: {
		Node*& node = findNode(m_root, (int)codes[1]);
		if (node) {
			node = rotateRight(node);
			rePosition();
		}
		break;
	}
	case CommandCode::redraw: {
		console.goDown();
		rePosition();
		setDuration(codes[1]);
		break;
	}
	default:
		break;
	}
}

void AVLTreeForm::remove(const std::string& x)
{
	console.InsertNextMainCommand("Remove " + x);
	InsertNextMainCommand({ CommandCode::erase, 1.0f * to_int(x) });
	remove(m_root, std::stoi(x));
	rePosition();
}

Node* AVLTreeForm::rotateLeft(Node* root)
{
	if (!root || !root->right) return root;
	
	Node* newRoot = root->right;
	root->right = newRoot->left;
	if (newRoot->left) newRoot->left->parent = root;

	newRoot->left = root;
	newRoot->parent = root->parent;
	root->parent = newRoot;
	std::cout << "Rotate Left at " << root->getValue() << ", New Root: " << newRoot->getValue() << std::endl;

	if (newRoot->parent == nullptr) this->m_root = newRoot;
	else {
		if (newRoot->parent->left == root)
			newRoot->parent->left = newRoot;
		else
			newRoot->parent->right = newRoot;
	}
	root->updateHeight();
	newRoot->updateHeight();

	//InsertNextSubCommand({ CommandCode::rotateLeft, 1.0f * root->getValue() });
	//rePosition();
	return newRoot;
}

Node* AVLTreeForm::rotateRight(Node* root)
{
	if (!root || !root->left) return root;

	Node* newRoot = root->left;
	root->left = newRoot->right;
	if (newRoot->right) newRoot->right->parent = root;

	newRoot->right = root;
	newRoot->parent = root->parent;
	root->parent = newRoot;

	if (newRoot->parent == nullptr)
		this->m_root = newRoot;
	else {
		if (newRoot->parent->left == root)
			newRoot->parent->left = newRoot;
		else
			newRoot->parent->right = newRoot;
	}

	root->updateHeight();
	newRoot->updateHeight();

	//InsertNextSubCommand({ CommandCode::rotateRight, 1.0f * root->getValue() });
	//rePosition();

	return newRoot;
}

void AVLTreeForm::remove(Node*& root, const int& x)
{
	if (!root) return;
	if (x < root->getValue()) remove(root->left, x);
	else if (x > root->getValue()) remove(root->right, x);
	else {
		if (!root->left || !root->right) {
			Node* tmp = root->left ? root->left : root->right;
			if (tmp) tmp->parent = root->parent;
			/*auto it = std::find(m_list.begin(), m_list.end(), root);
			if (it != m_list.end()) m_list.erase(it);*/
			delete root;
			root = tmp;
		}
		else {
			Node* tmp = root->right;
			while (tmp->left) tmp = tmp->left;
			root->setValue(tmp->getValue());
			remove(root->right, tmp->getValue());
			if (root->right) root->right->parent = root;
		}
	}
	if (!root) return;
	root->updateHeight();
	int balance = getBalanceFactor(root);

	// Left Heavy
	if (balance > 1) {
		if (getBalanceFactor(root->left) >= 0) {
			root = rotateRight(root);
		}
		else {
			root->left = rotateLeft(root->left);
			root = rotateRight(root);
		}
	}
	// Right Heavy
	else if (balance < -1) {
		if (getBalanceFactor(root->right) <= 0) {
			root = rotateLeft(root);
		}
		else {
			root->right = rotateRight(root->right);
			root = rotateLeft(root);
		}
	}
}

void AVLTreeForm::adjustPositions()
{
	if (m_list.empty()) return;

	// Collect all current positions to find bounds
	float min_x = INFINITY, max_x = -INFINITY;
	float min_y = INFINITY, max_y = -INFINITY;
	for (auto* node : m_list)
	{
		float x = node->getCenter().x;
		float y = node->getCenter().y;
		if (x < min_x) min_x = x;
		if (x > max_x) max_x = x;
		if (y < min_y) min_y = y;
		if (y > max_y) max_y = y;
	}

	// Calculate total width and height needed, considering node size (50x50)
	float total_width = max_x - min_x;
	float total_height = max_y - min_y;

	// Calculate scaling factors to fit within workspace, leaving space for node size
	float scaling_factor_x = 1.0f;
	if (total_width > 0)
	{
		scaling_factor_x = (m_workspace.width - 50) / total_width;
	}
	float scaling_factor_y = 1.0f;
	if (total_height > 0)
	{
		scaling_factor_y = (m_workspace.height - 50) / total_height;
	}
	float scaling_factor = std::min(scaling_factor_x, scaling_factor_y);
	if (scaling_factor > 1.0f) scaling_factor = 1.0f; // No scaling up

	// Calculate starting positions to center the scaled tree
	float scaled_width = total_width * scaling_factor;
	float scaled_height = total_height * scaling_factor;
	float starting_x = (m_workspace.width - scaled_width) / 2;
	float starting_y = (m_workspace.height - scaled_height) / 2;

	// Adjust each node's position
	for (auto* node : m_list)
	{
		float original_x = node->getCenter().x;
		float original_y = node->getCenter().y;
		float new_x = starting_x + (original_x - min_x) * scaling_factor;
		float new_y = starting_y + (original_y - min_y) * scaling_factor;
		node->setSlowPosition(new_x, new_y);
	}
}

Node*& AVLTreeForm::findNode(Node*& root, int value)
{
	if (!root) return root; // Return reference
	if (root->getValue() == value) return root;
	if (value < root->getValue()) return findNode(root->left, value);
	return findNode(root->right, value);
}

int AVLTreeForm::rePosition(Node* root, const int& level, float index, std::map<std::pair<float, int>, bool>& board)
{
	if (!root) return index;
	// set parent references
	if (root->left) root->left->parent = root;
	if (root->right) root->right->parent = root;
	if (board[{index, level}]) {
		while (board[{index, level}]) index += 2;
	}
	float left = rePosition(root->left, level + 1, index - 1, board) + 1;
	float right = rePosition(root->right, level + 1, left + 1, board) - 1;

	index = (left + right) / 2;
	board[{index, level}] = true;

	root->setDuration(getSpeed() / 2);

	float xPos = index * 50;
	float yPos = level * 50;
	root->setSlowPosition(xPos, yPos);

	return right;
}

int AVLTreeForm::getHeight(Node* root)
{
	return root ? root->getHeight() : 0;
}

int AVLTreeForm::getBalanceFactor(Node* root)
{
	if (!root) return 0;
	int leftHeight = root->left ? root->left->getHeight() : 0;
	int rightHeight = root->right ? root->right->getHeight() : 0;
	return leftHeight - rightHeight;
}


void AVLTreeForm::free(Node* root)
{
	if (!root) return;
	free(root->left);
	free(root->right);
	delete root;
}

void AVLTreeForm::free()
{
	free(m_root);
	m_root = nullptr;
	m_list.clear();
}

void AVLTreeForm::handle(Node* root)
{
	if (!root) return;
	root->handle();
	if (root->left) handle(root->left);
	if (root->right) handle(root->right);
}

void AVLTreeForm::draw(Node* root)
{
	if (!root) return;
	if (root->left) {
		DrawLineEx(root->getCenter(), root->left->getCenter(), 2.0f, BLACK);
		draw(root->left);
	}
	if (root->right) {
		DrawLineEx(root->getCenter(), root->right->getCenter(), 2.0f, BLACK);
		draw(root->right);
	}
 	root->draw();
}

void AVLTreeForm::rePosition()
{
	if (!m_root) return;
	std::map<std::pair<float, int>, bool> board;
	rePosition(m_root, 0, 0, board);

}

