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
		//InsertNextMainCommand({ CommandCode::add, 1.0f * to_int(x[i]), 1 });
		/*InsertNextMainCommand({ CommandCode::choose, 1.0f * to_int(x[i]), 1 });
		InsertNextMainCommand({ CommandCode::unchoose, 1.0f * to_int(x[i]), 1 });
		*/
		InsertNextMainCommand({ CommandCode::insert, 1.0f * to_int(x[i])});
		rePosition();
		//console.goDown();
	}
}
AVLNode* AVLTreeForm::insert(AVLNode*& root, const Vector2& par, const int& x)
{
	if (!root) {
		InsertNextSubCommand({ CommandCode::choose, 1.0f * m_list.size(), 1 });
		InsertNextSubCommand({ CommandCode::redraw, 1.0f });

		console.InsertNextSubCommand("Insert " + std::to_string(x));
		root = new AVLNode(m_list.size(), x);
		root->button_setting = &form_setting;
		root->text_setting = &form_setting;
		root->setPosition(par.x, par.y);
		m_list.push_back(root);

		InsertNextSubCommand({ CommandCode::unchoose, 1.0f * root->getIndex(), 0 });
		return root;
	}
	InsertNextSubCommand({ CommandCode::choose, 1.0f * root->getIndex(), 1 });
	console.InsertNextSubCommand("Compare with " + std::to_string(root->getValue()));
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
			console.InsertNextSubCommand("LL Case: Rotate Right ");
			return rotateRight(root); // LL case
		}
		else {
			console.InsertNextSubCommand("LR Case: Rotate Left ");
			root->left = rotateLeft(root->left); // LR case
			return rotateRight(root);
		}
	} // Right Heavy
	else if (balance < -1) {
		if (x > root->right->getValue()) {
			console.InsertNextSubCommand("RR Case: Rotate Left ");
			return rotateLeft(root); // RR case
		}
		else {
			console.InsertNextSubCommand("RL Case: Rotate Right ");
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
		AVLNode*& node = findNode(m_root, (int)codes[1]);
		if (node) {
			node = rotateRight(node);
			rePosition();
		}
		break;
	}
	case CommandCode::rotateRight: {
		AVLNode*& node = findNode(m_root, (int)codes[1]);
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
	case CommandCode::insert: {
		insert(m_root, { 400, 100 }, (int)codes[1]);
		rePosition();
		setDuration(0);
		console.goDown();
		break;
	}
	case CommandCode::add: {
		insert(m_root, { 400, 100 }, (int)codes[1]);
		rePosition();
		setDuration((int)codes[1]);
		console.goDown();
		break;
	}
	case CommandCode::choose: {
		console.goDown();
		setDuration((int)codes[2]);
		int nodeIndex = (int)codes[1];
		m_list[nodeIndex]->anim_color = RED;


		m_list[nodeIndex]->is_animating = true;
		break;
	}
	case CommandCode::unchoose: {
		setDuration((int)codes[2]);
		int nodeIndex = (int)codes[1];
		m_list[nodeIndex]->is_animating = false;
		break;
	}
	case CommandCode::erase: {
		remove(m_root, (int)codes[1]);
		rePosition();
		break;
	}
	case CommandCode::rotateLeft: {
		AVLNode*& node = findNode(m_root, (int)codes[1]);
		if (node) {
			node = rotateLeft(node);
			setDuration((int)codes[1]);
			rePosition();
		}
		break;
	}
	case CommandCode::rotateRight: {
		AVLNode*& node = findNode(m_root, (int)codes[1]);
		if (node) {
			node = rotateRight(node);
			setDuration((int)codes[1]);
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

AVLNode* AVLTreeForm::rotateLeft(AVLNode* root)
{
	if (!root || !root->right) return root;

	AVLNode* newRoot = root->right;
	root->right = newRoot->left;
	if (newRoot->left) newRoot->left->parent = root;

	newRoot->left = root;
	newRoot->parent = root->parent;
	root->parent = newRoot;

	if (newRoot->parent == nullptr) this->m_root = newRoot;
	else {
		if (newRoot->parent->left == root)
			newRoot->parent->left = newRoot;
		else
			newRoot->parent->right = newRoot;
	}
	root->updateHeight();
	newRoot->updateHeight();

	return newRoot;
}

AVLNode* AVLTreeForm::rotateRight(AVLNode* root)
{
	if (!root || !root->left) return root;

	AVLNode* newRoot = root->left;
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

	return newRoot;
}

void AVLTreeForm::remove(AVLNode*& root, const int& x)
{
	if (!root) return;
	if (x < root->getValue()) remove(root->left, x);
	else if (x > root->getValue()) remove(root->right, x);
	else {
		if (!root->left || !root->right) {
			AVLNode* tmp = root->left ? root->left : root->right;
			if (tmp) tmp->parent = root->parent;
			if (root->parent) {
				if (root->parent->left == root) root->parent->left = tmp;
				else root->parent->right = tmp;
			}
			delete root;
			root = tmp;
		}
		else {
			AVLNode* tmp = root->right;
			AVLNode* parentTmp = root;
			while (tmp->left) {
				parentTmp = tmp;
				tmp = tmp->left;
			}
			root->setValue(tmp->getValue());
			if (parentTmp->left == tmp) parentTmp->left = tmp->right;
			else parentTmp->right = tmp->right;

			if (tmp->right) tmp->right->parent = parentTmp;
			if (root == tmp) root = tmp->right ? tmp->right : tmp->left;

			delete tmp;
			tmp = nullptr; // M
		}
	}
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
	if (root->left) root->left->parent = root;
	if (root->right) root->right->parent = root;
}

AVLNode*& AVLTreeForm::findNode(AVLNode*& root, int value)
{
	if (!root) return root; // Return reference
	if (root->getValue() == value) return root;
	if (value < root->getValue()) return findNode(root->left, value);
	return findNode(root->right, value);
}

int AVLTreeForm::rePosition(AVLNode* root, const int& level, float index, std::map<std::pair<float, int>, bool>& board)
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

int AVLTreeForm::getHeight(AVLNode* root)
{
	return root ? root->getHeight() : 0;
}

int AVLTreeForm::getBalanceFactor(AVLNode* root)
{
	if (!root) return 0;
	int leftHeight = root->left ? root->left->getHeight() : 0;
	int rightHeight = root->right ? root->right->getHeight() : 0;
	return leftHeight - rightHeight;
}


void AVLTreeForm::free(AVLNode* root)
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

void AVLTreeForm::handle(AVLNode* root)
{
	if (!root) return;
	root->handle();
	if (root->left) handle(root->left);
	if (root->right) handle(root->right);
}

void AVLTreeForm::draw(AVLNode* root)
{
	if (!root) return;
	if (root->left) {
		DrawLineEx(root->getCenter(), root->left->getCenter(), 2.0f, root->button_setting->hover_color);
		draw(root->left);
	}
	if (root->right) {
		DrawLineEx(root->getCenter(), root->right->getCenter(), 2.0f, root->button_setting->hover_color);
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

