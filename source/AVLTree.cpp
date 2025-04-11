#include "../include/AVLTree.h"
#include "../include/General.h"

AVLTreeForm::AVLTreeForm(const int& index, FormSetting form_setting, const Vector2& window_size) :
	Form(index, form_setting, window_size) {
	m_root = 0;
	vroot = 0;
}
void AVLTreeForm::add(const vector<std::string>& x)
{
	for (int i = x.size() - 1; i >= 0; i--) {
		console.InsertNextMainCommand("Add " + x[i]);
		InsertNextMainCommand({ CommandCode::insert, 1.0f * to_int(x[i]), 1});
	}
}
void AVLTreeForm::update(const string& oldValue, const string& newValue) {
	string log = "Update " + oldValue + " to " + newValue;
	console.InsertNextMainCommand(log);
	InsertNextMainCommand({CommandCode::update, 1.0f*to_int(oldValue), 1.0f*to_int(newValue), 1});
}
void AVLTreeForm::swap(AVLNode* rootA, AVLNode* rootB) {
	if (!rootA || !rootB) return;
	int val = rootA->getValue();
	rootA->setValue(rootB->getValue());
	rootB->setValue(val);
	Vector2 pos = rootA->getPosition();
	rootA->setPosition(rootB->getPosition().x, rootB->getPosition().y);
	rootB->setPosition(pos.x, pos.y);
}
void AVLTreeForm::swap(Node* rootA, Node* rootB) {
	if (!rootA || !rootB) return;
	std::swap(rootA->val, rootB->val);
}
void AVLTreeForm::update(Node*& root, const int& old, const int& x) {
	if (!root) return;
	InsertNextSubCommand({choose, 1.0f*root->index, 0.5});
	InsertNextSubCommand({goDown, 1, 0.2});
	if (old<root->val) {
		Up.push(root);
		InsertNextSubCommand({goDown, 1, 0.2});
		InsertNextSubCommand({goUp, 2, 0.2});
		update(root->left, old, x);
		InsertNextSubCommand({goUp, 6, 0.2});
		InsertNextSubCommand({goDown, 6, 0.2});
	}
	else {
		InsertNextSubCommand({goDown, 2, 0.2});
		if (old>root->val) {
			InsertNextSubCommand({goDown, 1, 0.2});
			InsertNextSubCommand({goUp, 4, 0.2});
			Down.push(root);
			update(root->right, old, x);
			InsertNextSubCommand({goUp, 4, 0.2});
			InsertNextSubCommand({goDown, 4, 0.2});
		}
		else {
			InsertNextSubCommand({goDown, 2, 0.2});
			InsertNextSubCommand({goDown, 1, 0.2});
			InsertNextSubCommand({update_node, 1.0f*root->index, 1.0f*x, 1.0f*root->val, 1});
			InsertNextSubCommand({goDown, 1, 0.2});
			root->val = x;
			update(root, old < x);
			InsertNextSubCommand({goDown, 1, 0.2});
		}
	}
	while (Up.size()) {
		InsertNextSubCommand({CommandCode::unchoose, 1.0f*Up.top()->index, 1});
		Up.pop();
	}
	while (Down.size()) {
		InsertNextSubCommand({CommandCode::unchoose, 1.0f*Down.top()->index, 1});
		Down.pop();
	}
}
void AVLTreeForm::update(Node*& root, const bool& isGreater) {
	if (!root) return;
	if (root->left && !isGreater) {
		Node* tmp = root->left;
		while (tmp) {
			if (Down.empty() || tmp->val > Down.top()->val) {
				InsertNextSubCommand({CommandCode::choose, 1.0f*tmp->index, 1});
				Down.push(tmp);
			}
			tmp = tmp->right;
		}
	}
	if (root->right && isGreater) {
		Node* tmp = root->right;
		while (tmp) {
			if (Up.empty() || tmp->val < Up.top()->val) {
				InsertNextSubCommand({CommandCode::choose, 1.0f*tmp->index, 1});
				Up.push(tmp);
			}
			tmp = tmp->left;
		}
	}
	
	if (Up.size() && root->val > Up.top()->val) {
		InsertNextSubCommand({CommandCode::swap, 1.0f*root->index, 1.0f*Up.top()->index, 1});
		swap(root, Up.top());
		Down.push(root);
		Node* tmp = Up.top();
		Up.pop();
		while (Down.size() && Down.top()->height < tmp->height) {
			InsertNextSubCommand({CommandCode::unchoose, 1.0f*Down.top()->index, 1});
			Down.pop();
		}
		update(tmp, true);
	}
	else if (Down.size() && root->val < Down.top()->val) {
		InsertNextSubCommand({CommandCode::swap, 1.0f*root->index, 1.0f*Down.top()->index, 1});
		swap(root, Down.top());
		Up.push(root);
		Node* tmp = Down.top();
		Down.pop();
		while (Up.size() && Up.top()->height < tmp->height) {
			InsertNextSubCommand({CommandCode::unchoose, 1.0f*Up.top()->index, 1});
			Up.pop();
		}
		update(tmp, false);
	}
	else {
		while (Down.size() && Down.top()->height < root->height) {
			InsertNextSubCommand({CommandCode::unchoose, 1.0f*Down.top()->index, 1});
			Down.pop();
		}
		while (Up.size() && Up.top()->height < root->height) {
			InsertNextSubCommand({CommandCode::unchoose, 1.0f*Up.top()->index, 1});
			Up.pop();
		}
		InsertNextSubCommand({CommandCode::unchoose, 1.0f*root->index, 1});
	}
}
void AVLTreeForm::search(const string& str) {
	console.InsertNextMainCommand("Search" + str);
	InsertNextMainCommand({CommandCode::search, 1.0f*to_int(str), 1});
}
void AVLTreeForm::search(Node* root, const int& val) {
	if (!root) return;
	InsertNextSubCommand({choose, 1.0f*root->index, 0.5});
	InsertNextSubCommand({goDown, 1, 0.2});
	if (root->val<val) {
		InsertNextSubCommand({goDown, 1, 0.2});
		InsertNextSubCommand({goUp, 2, 0.2});
		search(root->right,val);
		InsertNextSubCommand({goDown, 2, 0.2});
		InsertNextSubCommand({goDown, 4, 0.2});
	}
	else {
		InsertNextSubCommand({goDown, 2, 0.2});
		if (root->val>val) {
			InsertNextSubCommand({goDown, 1, 0.2});
			InsertNextSubCommand({goUp, 4, 0.2});
			search(root->left, val);
			InsertNextSubCommand({goDown, 4, 0.2});
			InsertNextSubCommand({goDown, 2, 0.2});
		}
		else {
			InsertNextSubCommand({goDown, 2, 0.2});
			InsertNextSubCommand({wait, 10});
			InsertNextSubCommand({goDown, 1, 0.2});
		}
	}
	InsertNextSubCommand({unchoose, 1.0f*root->index, 0.5});
	InsertNextSubCommand({goUp, 6, 0.2});
}
void AVLTreeForm::insert(Node*& root, Node* parent, const int& x) {
    if (!root) {
        root = new Node(x, 1, logic_node.size());
		root->parent = parent;
        logic_node.push_back(root);
        return ;
    };
	int old_index = root->index;
	InsertNextSubCommand({choose, 1.0f*old_index, 0.5});
    //Go to left if x<root or right when x>root like BST
	int index = 0;
	InsertNextSubCommand({CommandCode::goDown, 3, 1});
    if (x>root->val) {
		InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
		InsertNextSubCommand({CommandCode::goUp, 5, 1});
		InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
		if (!root->right) {
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({CommandCode::add, 1, 1.0f*x, 1.0f*root->index, 0.5});
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({CommandCode::goDown, 16, 1});
		}
        insert(root->right, root, x);
		InsertNextSubCommand({CommandCode::goUp, 14, 1});
		InsertNextSubCommand({CommandCode::goDown, 3, 0.2});
    }
    else {
		InsertNextSubCommand({CommandCode::goDown, 2, 0.2});
		if (x<=root->val) {
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({CommandCode::goUp, 7, 1});
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			if (!root->left) {
				InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
				InsertNextSubCommand({CommandCode::add, 0, 1.0f*x,1.0f*root->index, 0.5});
				InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
				InsertNextSubCommand({CommandCode::goDown, 16, 1});
			}
			insert(root->left, root, x);
			InsertNextSubCommand({CommandCode::goUp, 12, 1});
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
		}
    }
    //After insert, back and check its height of each branch
	int old_height = root->height;
    root->height = max(height(root->right), height(root->left))+1;
	InsertNextSubCommand({update_height, 1.0f*old_index, 1.0f*root->height, 1.0f*old_height, 1});
    //If right branch taller than left branch over 1 unit => Turn Left
	int balance = height(root->right)-height(root->left);
    if (balance>1) {
		InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
        //Check if case right-right or right-left
        if (height(root->right->right)<height(root->right->left)) {
			InsertNextSubCommand({CommandCode::goDown, 2, 0.2});
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->right->index, 0.5});
			InsertNextSubCommand({choose, 1.0f*root->right->left->index, 0.5});
			InsertNextSubCommand({CommandCode::rotateRight, 1.0f*root->right->index, 1});
			InsertNextSubCommand({unchoose, 1.0f*root->right->index, 0.5});
			InsertNextSubCommand({unchoose, 1.0f*root->right->left->index, 0.5});
			rotateRight(root->right);

			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->right->index, 0.5});
			InsertNextSubCommand({CommandCode::rotateLeft, 1.0f*root->index, 1});
			InsertNextSubCommand({CommandCode::goDown, 6, 1});
			InsertNextSubCommand({unchoose, 1.0f*old_index, 0.5});
			InsertNextSubCommand({unchoose, 1.0f*root->right->index, 0.5});
		} else {
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->right->index, 0.5});
			InsertNextSubCommand({CommandCode::rotateLeft, 1.0f*root->index, 1});
			InsertNextSubCommand({CommandCode::goDown, 9, 1});
			InsertNextSubCommand({unchoose, 1.0f*old_index, 0.5});
			InsertNextSubCommand({unchoose, 1.0f*root->right->index, 0.5});
		}
        rotateLeft(root);
    } else
    //If left branch taller than right branch over 1 unit => Turn Right
    if (balance<-1) {
        //Check if case left-left or left-right
        if (height(root->left->left)<height(root->left->right)) {
			InsertNextSubCommand({CommandCode::goDown, 8, 1});
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->left->index, 0});
			InsertNextSubCommand({choose, 1.0f*root->left->right->index, 0.5});
			InsertNextSubCommand({CommandCode::rotateLeft, 1.0f*root->left->index, 1});
			InsertNextSubCommand({unchoose, 1.0f*root->left->index, 0.5});
			InsertNextSubCommand({unchoose, 1.0f*root->left->right->index, 0.5});
			rotateLeft(root->left);

			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->left->index, 0.5});
			InsertNextSubCommand({CommandCode::rotateRight, 1.0f*root->index, 1});
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({unchoose, 1.0f*old_index, 0.5});
			InsertNextSubCommand({unchoose, 1.0f*root->left->index, 0.5});
			rotateRight(root);
		} else {
			InsertNextSubCommand({CommandCode::goDown, 6, 1});
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->left->index, 0.5});
			InsertNextSubCommand({CommandCode::rotateRight, 1.0f*root->index, 1});
			InsertNextSubCommand({CommandCode::goDown, 4, 0.2});
			InsertNextSubCommand({unchoose, 1.0f*old_index, 0.5});
			InsertNextSubCommand({unchoose, 1.0f*root->left->index, 0.5});
			rotateRight(root);
		}
    } else {
		InsertNextSubCommand({CommandCode::goDown, 11, 1});
		InsertNextSubCommand({unchoose, 1.0f*old_index, 0.5});
	}
}
void AVLTreeForm::handle()
{
	Form::handle();
	int index_focus = -1;
	for (int i = 0; i<visual_node.size(); i++) 
		if (visual_node[i]) {
			visual_node[i]->handle(m_camera);
			if (visual_node[i]->isFocus()) index_focus = i;
		}
	if (IsKeyDown(KEY_F2) && index_focus != -1) {
		main_box_show();
		option_box.select(2);
		update_textbox_choice.setText(to_string(visual_node[index_focus]->getValue()));
		update_textbox_value.setFocus(true);
	}
	else if (IsKeyDown(KEY_DELETE) && index_focus != -1) {
		main_box_show();
		option_box.select(4);
		remove_textbox.setText(to_string(visual_node[index_focus]->getValue()));
		remove_textbox.setFocus(true);
	}
	if (skip_button.isPressed()) reFocusCamera();
}

AVLTreeForm::~AVLTreeForm() {
	for (int i = 0; i<visual_node.size(); i++) delete visual_node[i];
	for (int i = 0; i<logic_node.size(); i++) delete logic_node[i];
}

void AVLTreeForm::draw()
{
	BeginMode2D(m_camera);
	BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
	for (int i = 0; i<visual_node.size(); i++)
		if (visual_node[i]) visual_node[i]->draw();
	EndScissorMode();
	EndMode2D();
	Form::draw();
}

void AVLTreeForm::FetchPrevCommand(const std::vector<float>& codes)
{
	float dur = codes.back();
	int code = codes[0];
	switch (code) {
	case CommandCode::insert: {
		int val = codes[1];
		for (int i =0;i<logic_node.size(); i++) {
			delete logic_node[i];
			logic_node[i] = 0;
		}
		logic_node.pop_back();
		m_root = 0;
		clone(m_root, vroot);
		console.goUp();
		setDuration(0.1);
	}
	break;
	case CommandCode::insert_end: {
		console.goUp();
		insert_console_add();
		for (int i = 0; i<20; i++) console.goDown();
		setDuration(dur);
	}
	break;
	case CommandCode::add: {
		bool right = codes[1];
		int value = codes[2], parent = codes[3];

		if (parent!=-1) {
			if (right) visual_node[parent]->right = 0;
			else visual_node[parent]->left = 0;
		} else vroot = 0;
		delete visual_node.back();
		visual_node.pop_back();
		rePosition(dur*getSpeed());
		setDuration(dur);
	}
	break;
	case CommandCode::erase: {
		for (int i =0;i<logic_node.size(); i++) {
			delete logic_node[i];
			logic_node[i] = 0;
		}
		m_root = 0;
		clone(m_root, vroot);
		console.goUp();
		setDuration(dur);
	}
	break;
	case CommandCode::erase_end: {
		console.goUp();
		remove_console_add();
		for (int i = 0; i<33; i++) console.goDown();
		setDuration(dur);
	}
	break;
	case CommandCode::remove_node: {
		int parent = codes[1], index = codes[2], value = codes[3];
		visual_node[index] = new AVLNode(&form_setting, &form_setting, index, value);
		visual_node[index]->height = 1;
		if (parent!=-1) {
			visual_node[index]->parent = visual_node[parent];
			if (value < visual_node[parent]->getValue()) visual_node[parent]->left = visual_node[index];
			else visual_node[parent]->right = visual_node[index];
		}
		rePosition(dur*getSpeed()/2);
		setDuration(dur);
	}
	break;
	case CommandCode::swap: {
		int start = codes[1], end = codes[2];
		swap(visual_node[start], visual_node[end]);
		rePosition(dur*getSpeed());
		setDuration(dur);
	}
	break;
	case CommandCode::update: {
		console.goUp();
		setEnable(false);
		update(m_root, codes[2], codes[1]);
		setDuration(dur);
		setEnable(true);
	}
	break;
	case CommandCode::update_end: {
		console.goUp();
		update_console_add();
		for (int i = 0; i<9; i++) console.goDown();
		setDuration(dur);
	}
	case CommandCode::update_node: {
		visual_node[codes[1]]->setValue(codes[3]);
		setDuration(dur);
	}
	break;
	case CommandCode::search: {
		console.goUp();
		setDuration(dur);
	}
	break;	
	case CommandCode::search_end: {
		console.goUp();
		search_console_add();
		console.goDown();
		setDuration(dur);
	}
	break;
	case CommandCode::update_height: {
		int index = codes[1], height = codes[3];
		visual_node[index]->height = height;
		setDuration(dur);
	}
	break;
	case CommandCode::choose: {
		int index = codes[1];
		visual_node[index]->end_color(dur*getSpeed()/2);
		setDuration(dur);
	}
	break;
	case CommandCode::unchoose: {	
		int index = codes[1];
		visual_node[index]->start(dur*getSpeed()/2, RED);
		setDuration(dur);		
	}
	break;
	case CommandCode::rotateLeft: {
		AVLNode* tmp = visual_node[codes[1]]->parent;
		if (tmp ==vroot) {
			visual_rotateRight(vroot);
		}
		else if (tmp->parent->right == tmp) {
			visual_rotateRight(tmp->parent->right);
		}
		else {
			visual_rotateRight(tmp->parent->left);
		}
		rePosition(dur*getSpeed()*0.5);
		setDuration(dur);
	}
	break;
	case CommandCode::rotateRight: {
		AVLNode* tmp = visual_node[codes[1]]->parent;
		if (tmp ==vroot) visual_rotateLeft(vroot);
		else if (tmp->parent->right == tmp) visual_rotateLeft(tmp->parent->right);
		else visual_rotateLeft(tmp->parent->left);
		rePosition(dur*getSpeed()*0.5);
		setDuration(dur);
	}
	break;
	case CommandCode::wait: {
		setDuration(dur);
	}
	break;
	case CommandCode::goUp: {
		int n = codes[1];
		for (int i= 0; i<n; i++) console.goDown();
		setDuration(dur);
	}
	break;
	case CommandCode::goDown: {
		int n = codes[1];
		for (int i= 0; i<n; i++) console.goUp();
		setDuration(dur);
	}
	break;
	default:
		break;
	}
}

void AVLTreeForm::FetchNextCommand(const std::vector<float>& codes)
{
	int code = codes[0];
	float dur = codes.back();
	switch (code) {
	case CommandCode::insert: {
		int value = codes[1];
		insert_console_add();
		console.goDown();
		InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
		insert(m_root, 0, value);
		if (!vroot) {
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({CommandCode::add, 0, 1.0f*value, -1, 1});
			InsertNextSubCommand({CommandCode::goDown, 17, 1});
		}
		InsertNextSubCommand({CommandCode::insert_end, 1});
		setDuration(dur);
	}
	break;
	case CommandCode::insert_end: {
		console.goDown();
		setDuration(dur);
	}
	break;
	case CommandCode::search: {
		search_console_add();
		console.goDown();
		search(m_root, codes[1]);
		InsertNextSubCommand({search_end, 1});
		setDuration(dur);
	}
	break;	
	case CommandCode::search_end: {
		for (int i = 0; i<7; i++) console.goDown();
		setDuration(dur);
	}
	break;
	case CommandCode::add: {
		bool right = codes[1];
		int value = codes[2], parent = codes[3];
		visual_node.push_back(new AVLNode(&form_setting, &form_setting, visual_node.size(), value));		
		if (parent!=-1) {
			if (right) visual_node[parent]->right = visual_node.back();
			else visual_node[parent]->left = visual_node.back();
			visual_node.back()->parent = visual_node[parent];
			Vector2 pos = visual_node[parent]->getPosition();
			visual_node.back()->setPosition(pos.x, pos.y);
		} else vroot = visual_node.back();
		rePosition(dur*getSpeed());
		setDuration(dur);
	}
	break;
	case CommandCode::update_height: {
		int index = codes[1], height = codes[2];
		visual_node[index]->height =height;
		setDuration(dur);
	}
	break;
	case CommandCode::swap: {
		int start = codes[1], end = codes[2];
		swap(visual_node[start], visual_node[end]);
		rePosition(dur*getSpeed()/2);
		setDuration(dur);
	}
	break;
	case CommandCode::update: {
		update_console_add();
		console.goDown();
		update(m_root, codes[1], codes[2]);
		InsertNextSubCommand({update_end, 1});
		setDuration(dur);
	}
	break;
	case CommandCode::update_end: {
		console.goDown();
		setDuration(dur);
	}
	break;
	case CommandCode::choose: {
		int index = codes[1];
		visual_node[index]->start(dur*getSpeed()/2, RED);
		setDuration(dur);
	}
	break;
	case CommandCode::update_node: {
		visual_node[codes[1]]->setValue(codes[2]);
		setDuration(dur);
	}
	break;
	case CommandCode::unchoose: {	
		int index = codes[1];
		visual_node[index]->end_color(dur*getSpeed()/2);
		setDuration(dur);		
	}
	break;
	case CommandCode::wait: {
		setDuration(dur);
	}
	break;
	case CommandCode::erase: {
		int x = codes[1];
		remove_console_add();
		console.goDown();
		int index = vroot->getIndex();
		if (vroot) InsertNextSubCommand({choose, 1.0f*index, 1});
		remove(m_root, x);
		rePosition(dur*getSpeed());
		InsertNextSubCommand({erase_end, 1});
		setDuration(dur);
	}
	break;
	case CommandCode::erase_end: {
		console.goDown();
		setDuration(dur);
	}
	break;
	case CommandCode::goDown: {
		int n = codes[1];
		for (int i= 0; i<n; i++) console.goDown();
		setDuration(dur);
	}
	break;
	case CommandCode::goUp: {
		int n = codes[1];
		for (int i= 0; i<n; i++) console.goUp();
		setDuration(dur);
	}
	break;
	case CommandCode::remove_node: {
		int par = codes[1], index = codes[2], value = codes[3];
		if (par!=-1) {
			if (visual_node[par]->left == visual_node[index]) {
				visual_node[par]->left = 0;
			} else visual_node[par]->right = 0;
		}
		delete visual_node[index];
		visual_node[index] = 0;
		setDuration(dur);
	}
	break;
	case CommandCode::rotateLeft: {
		AVLNode* tmp = visual_node[codes[1]];
		if (tmp ==vroot) visual_rotateLeft(vroot);
		else if (tmp->parent->right == tmp) visual_rotateLeft(tmp->parent->right);
		else visual_rotateLeft(tmp->parent->left);
		rePosition(dur*getSpeed()*0.5);
		setDuration(dur);
	}
	break;
	case CommandCode::rotateRight: {
		AVLNode* tmp = visual_node[codes[1]];
		if (tmp ==vroot) visual_rotateRight(vroot);
		else if (tmp->parent->right == tmp) visual_rotateRight(tmp->parent->right);
		else visual_rotateRight(tmp->parent->left);
		rePosition(dur*getSpeed()*0.5);
		setDuration(dur);
	}
	break;
	default:
		break;
	}
}

void AVLTreeForm::remove(const std::string& x)
{
	console.InsertNextMainCommand("Remove " + x);
	InsertNextMainCommand({ CommandCode::erase, 1.0f * to_int(x), 1 });
}
void AVLTreeForm::clone(Node*& rootA, AVLNode*& rootB) {
	if (!rootB) return;
	rootA = new Node(rootB->getValue(), rootB->height, rootB->getIndex());
	if (rootB->parent) rootA->parent = logic_node[rootB->parent->getIndex()];
	logic_node[rootA->index] = rootA;
	clone(rootA->left, rootB->left);
	clone(rootA->right, rootB->right);
}
void AVLTreeForm::visual_rotateLeft(AVLNode*& root)
{
    AVLNode* tmp = root;
    root = root->right;
    root->parent = tmp->parent;
    tmp->right = 0;
    //Set a height of root again
    tmp->height = height(tmp->left)+1;
    //If new root node has left branch, combine it with old root to new left branch
    if (root->left) {
        tmp->right = root->left;
        root->left->parent = tmp;
        //Re-Calculate height
        tmp->height = max(height(tmp->right), height(tmp->left)) + 1;
    }
    root->left = tmp;
    tmp->parent = root;
    //Re-Cal height of new root
    root->height = max(height(root->right), height(root->left)) + 1;
}

void AVLTreeForm::rotateLeft(Node*& root)
{
    Node* tmp = root;
    root = root->right;
    root->parent = tmp->parent;
    tmp->right = 0;
    //Set a height of root again
    tmp->height = height(tmp->left)+1;
    //If new root node has left branch, combine it with old root to new left branch
    if (root->left) {
        tmp->right = root->left;
        root->left->parent = tmp;
        //Re-Calculate height
        tmp->height = max(height(tmp->right), height(tmp->left)) + 1;
    }
    root->left = tmp;
    tmp->parent = root;
    //Re-Cal height of new root
    root->height = max(height(root->right), height(root->left)) + 1;
}

void AVLTreeForm::visual_rotateRight(AVLNode*& root)
{
    //Save a root, turn the left child to root
    AVLNode* tmp = root;
    root = root->left;
    root->parent = tmp->parent;
    tmp->left = 0;
    //Reset it height
    tmp->height = height(tmp->right)+1;
    //Check if exists old right branch
    if (root->right) {
        tmp->left = root->right;
        root->right->parent = tmp;
        //Re-Cal the height
        tmp->height = max(height(tmp->left), height(tmp->right))+1;
    }
    root->right = tmp;
	tmp->parent = root;
    //Re-Cal the height of new root
    root->height = max(height(root->right), height(root->left))+1;
}

void AVLTreeForm::rotateRight(Node*& root)
{
    //Save a root, turn the left child to root
    Node* tmp = root;
    root = root->left;
    root->parent = tmp->parent;
    tmp->left = 0;
    //Reset it height
    tmp->height = height(tmp->right)+1;
    //Check if exists old right branch
    if (root->right) {
        tmp->left = root->right;
        root->right->parent = tmp;
        //Re-Cal the height
        tmp->height = max(height(tmp->left), height(tmp->right))+1;
    }
    root->right = tmp;
	tmp->parent = root;
    //Re-Cal the height of new root
    root->height = max(height(root->right), height(root->left))+1;
}

int AVLTreeForm::remove(Node*& root, const int& x)
{
	if (!root) return -1;
	InsertNextSubCommand({goDown, 1, 0.2});
	if (x < root->val) {
		InsertNextSubCommand({goDown, 1, 0.2});
		InsertNextSubCommand({goUp, 2, 0.2});
		InsertNextSubCommand({choose, 1.0f*root->left->index, 0.5});
		remove(root->left, x);
		InsertNextSubCommand({goUp, 30, 1});
		InsertNextSubCommand({goDown, 19, 1});
	}
	else {
		InsertNextSubCommand({goDown, 2, 0.2});
		if (x > root->val) {
			InsertNextSubCommand({goDown, 1, 0.2});
			InsertNextSubCommand({goUp, 4, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->right->index, 0.5});
			remove(root->right, x);
			InsertNextSubCommand({goUp, 28, 0.2});
			InsertNextSubCommand({goDown, 17, 1});
		}
		else {
			InsertNextSubCommand({goDown, 2, 0.2});
			InsertNextSubCommand({goDown, 1, 0.2});
			if (!root->left && !root->right) {
				InsertNextSubCommand({goDown, 1, 0.2});
				int index = root->index, par = -1;
				if (root->parent) par = root->parent->index;
				logic_node[index] = 0;
				delete root;
				root = 0;
				InsertNextSubCommand({CommandCode::remove_node, 1.0f*par, 1.0f*index, 1.0f*x, 1});
				InsertNextSubCommand({goDown, 25, 1});
				return index;
			} 
			else {
				InsertNextSubCommand({goDown, 2, 0.2});
				if (root->left && root->right) {
					InsertNextSubCommand({goDown, 1, 0.2});
					int balance = root->left->height - root->right->height;
					if (balance>0) {
						InsertNextSubCommand({choose, 1.0f*root->left->index, 0.5});
						InsertNextSubCommand({goDown, 1, 0.2});
						InsertNextSubCommand({CommandCode::rotateRight, 1.0f*root->index, 1});
						rotateRight(root);
						InsertNextSubCommand({goDown, 1, 0.2});
						InsertNextSubCommand({goUp, 11, 1});
						remove(root->right, x);
						InsertNextSubCommand({goUp, 21, 1});
						InsertNextSubCommand({goDown, 10, 0.2});
					} else {
						InsertNextSubCommand({goDown, 3, 0.2});
						InsertNextSubCommand({choose, 1.0f*root->right->index, 0.5});
						InsertNextSubCommand({goDown, 1, 0.2});
						InsertNextSubCommand({CommandCode::rotateLeft, 1.0f*root->index, 1});
						rotateLeft(root);
						InsertNextSubCommand({goDown, 1, 0.2});
						InsertNextSubCommand({goUp, 14, 1});
						remove(root->left, x);
						InsertNextSubCommand({goUp, 18, 1});
						InsertNextSubCommand({goDown, 7, 0.2});
					}
				}
				else {
					InsertNextSubCommand({goDown, 7, 1});
					if (root->left) {
						InsertNextSubCommand({goDown, 1, 0.2});
						InsertNextSubCommand({choose, 1.0f*root->left->index, 0.5});
						InsertNextSubCommand({CommandCode::rotateRight, 1.0f*root->index, 1});
						rotateRight(root);
						InsertNextSubCommand({goDown, 1, 0.2});
						InsertNextSubCommand({goUp, 17, 1});
						remove(root->right, x);
						InsertNextSubCommand({goUp, 15, 1});
						InsertNextSubCommand({goDown, 4, 1});
					}
					else if (root->right) {
						InsertNextSubCommand({goDown, 3, 0.2});
						InsertNextSubCommand({goDown, 1, 0.2});
						InsertNextSubCommand({choose, 1.0f*root->right->index, 0.5});
						InsertNextSubCommand({CommandCode::rotateLeft, 1.0f*root->index, 1});
						rotateLeft(root);
						InsertNextSubCommand({goDown, 1, 0.2});
						InsertNextSubCommand({goUp, 20, 1});
						remove(root->left, x);
						InsertNextSubCommand({goUp, 12, 1});
						InsertNextSubCommand({goDown, 1, 0.2});
					}
				}
			}
		}
	}
	int old_height = root->height;
    root->height = max(height(root->right), height(root->left))+1;
	InsertNextSubCommand({update_height, 1.0f*root->index, 1.0f*root->height, 1.0f*old_height, 1});
    //If right branch taller than left branch over 1 unit => Turn Left
	int balance = height(root->right)-height(root->left);
    if (balance>1) {
		InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
        //Check if case right-right or right-left
        if (height(root->right->right)<height(root->right->left)) {
			InsertNextSubCommand({CommandCode::goDown, 2, 0.2});
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->right->index, 0.5});
			InsertNextSubCommand({choose, 1.0f*root->right->left->index, 0.5});
			InsertNextSubCommand({CommandCode::rotateRight, 1.0f*root->right->index, 1});
			InsertNextSubCommand({unchoose, 1.0f*root->right->index, 0.5});
			InsertNextSubCommand({unchoose, 1.0f*root->right->left->index, 0.5});
			rotateRight(root->right);

			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->right->index, 0.5});
			InsertNextSubCommand({CommandCode::rotateLeft, 1.0f*root->index, 1});
			InsertNextSubCommand({CommandCode::goDown, 6, 1});
			InsertNextSubCommand({unchoose, 1.0f*root->index, 0.5});
			InsertNextSubCommand({unchoose, 1.0f*root->right->index, 0.5});
		} else {
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->right->index, 0.5});
			InsertNextSubCommand({CommandCode::rotateLeft, 1.0f*root->index, 1});
			InsertNextSubCommand({CommandCode::goDown, 9, 1});
			InsertNextSubCommand({unchoose, 1.0f*root->index, 0.5});
			InsertNextSubCommand({unchoose, 1.0f*root->right->index, 0.5});
		}
        rotateLeft(root);
    } else
    //If left branch taller than right branch over 1 unit => Turn Right
    if (balance<-1) {
        //Check if case left-left or left-right
        if (height(root->left->left)<height(root->left->right)) {
			InsertNextSubCommand({CommandCode::goDown, 8, 1});
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->left->index, 0});
			InsertNextSubCommand({choose, 1.0f*root->left->right->index, 0.5});
			InsertNextSubCommand({CommandCode::rotateLeft, 1.0f*root->left->index, 1});
			InsertNextSubCommand({unchoose, 1.0f*root->left->index, 0.5});
			InsertNextSubCommand({unchoose, 1.0f*root->left->right->index, 0.5});
			rotateLeft(root->left);

			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->left->index, 0.5});
			InsertNextSubCommand({CommandCode::rotateRight, 1.0f*root->index, 1});
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({unchoose, 1.0f*root->index, 0.5});
			InsertNextSubCommand({unchoose, 1.0f*root->left->index, 0.5});
			rotateRight(root);
		} else {
			InsertNextSubCommand({CommandCode::goDown, 6, 1});
			InsertNextSubCommand({CommandCode::goDown, 1, 0.2});
			InsertNextSubCommand({choose, 1.0f*root->left->index, 0.5});
			InsertNextSubCommand({CommandCode::rotateRight, 1.0f*root->index, 1});
			InsertNextSubCommand({CommandCode::goDown, 4, 0.2});
			InsertNextSubCommand({unchoose, 1.0f*root->index, 0.5});
			InsertNextSubCommand({unchoose, 1.0f*root->left->index, 0.5});
			rotateRight(root);
		}
    } else {
		InsertNextSubCommand({CommandCode::goDown, 11, 1});
		InsertNextSubCommand({unchoose, 1.0f*root->index, 0.5});
	}
	return -1;
}
void AVLTreeForm::remove_console_add() {
	console.InsertNextSubCommand("f(&root, x) {");
	console.InsertNextSubCommand("if root->val > x");
	console.InsertNextSubCommand("		f(root->left, x)");
	console.InsertNextSubCommand("else if root->val < x");
	console.InsertNextSubCommand("		f(root->right, x)");
	console.InsertNextSubCommand("else	");
	console.InsertNextSubCommand("		if root doesn't have child");
	console.InsertNextSubCommand("			remove root");
	console.InsertNextSubCommand("		else if root has both left and right child");
	console.InsertNextSubCommand("			if left node is heavier");
	console.InsertNextSubCommand("				Rotate right");
	console.InsertNextSubCommand("				f(root->right, x)");
	console.InsertNextSubCommand("			else");
	console.InsertNextSubCommand("				Rotate left");
	console.InsertNextSubCommand("				f(root->left, x)");
	console.InsertNextSubCommand("		else if root has left child");
	console.InsertNextSubCommand("			Rotate right");
	console.InsertNextSubCommand("			f(root->right, x)");
	console.InsertNextSubCommand("		else if root has right child");
	console.InsertNextSubCommand("			Rotate left");
	console.InsertNextSubCommand("			f(root->left, x)");
	console.InsertNextSubCommand("if root is not balance");
	console.InsertNextSubCommand("		if root->right and root->right->right are heavier");
	console.InsertNextSubCommand("			RR: Rotate left");
	console.InsertNextSubCommand("		if root->right and root->right->left are heavier");
	console.InsertNextSubCommand("			RL: Rotate right (root->right)");
	console.InsertNextSubCommand("			RL: Rotate left");
	console.InsertNextSubCommand("		if root->left and root->left->left are heavier");
	console.InsertNextSubCommand("			LL: Rotate right");
	console.InsertNextSubCommand("		if root->left and root->left->right are heavier");
	console.InsertNextSubCommand("			LR: Rotate left (root->left)");
	console.InsertNextSubCommand("			LR: Rotate right");
	console.InsertNextSubCommand("}");
}
void AVLTreeForm::search_console_add() {
	console.InsertNextSubCommand("f(root, x) {");
	console.InsertNextSubCommand("	  if root->val < x");
	console.InsertNextSubCommand("		f(root->right, x)");
	console.InsertNextSubCommand("   else	if root->val > x");
	console.InsertNextSubCommand("		f(root->left, x)");
	console.InsertNextSubCommand("   else return root");
	console.InsertNextSubCommand("}");
}
void AVLTreeForm::insert_console_add() {
	console.InsertNextSubCommand("f(&root, x) {");
	console.InsertNextSubCommand("if root is null");
	console.InsertNextSubCommand("		root = new Node(x)");
	console.InsertNextSubCommand("		return");
	console.InsertNextSubCommand("else	if root->val < x");
	console.InsertNextSubCommand("		f(root->right, x)");
	console.InsertNextSubCommand("else	if root->val >= x");
	console.InsertNextSubCommand("		f(root->left, x)");
	console.InsertNextSubCommand("if root is not balance");
	console.InsertNextSubCommand("		if root->right and root->right->right are heavier");
	console.InsertNextSubCommand("			RR: Rotate left");
	console.InsertNextSubCommand("		if root->right and root->right->left are heavier");
	console.InsertNextSubCommand("			RL: Rotate right (root->right)");
	console.InsertNextSubCommand("			RL: Rotate left");
	console.InsertNextSubCommand("		if root->left and root->left->left are heavier");
	console.InsertNextSubCommand("			LL: Rotate right");
	console.InsertNextSubCommand("		if root->left and root->left->right are heavier");
	console.InsertNextSubCommand("			LR: Rotate left (root->left)");
	console.InsertNextSubCommand("			LR: Rotate right");
	console.InsertNextSubCommand("}");
}
void AVLTreeForm::update_console_add() {
	console.InsertNextSubCommand("f(&root, x, new) {");
	console.InsertNextSubCommand("if root->val > x");
	console.InsertNextSubCommand("		f(root->left, x)");
	console.InsertNextSubCommand("else if root->val < x");
	console.InsertNextSubCommand("		f(root->right, x)");
	console.InsertNextSubCommand("else	");
	console.InsertNextSubCommand("		Update its value");
	console.InsertNextSubCommand("		Update its position");
	console.InsertNextSubCommand("}");
}
void AVLTreeForm::reFocusCamera() {
	if (!vroot) return ;
	AVLNode* right = vroot, *left=vroot;
	while (right->right) right = right->right;
	while (left->left) left = left->left;
	float middle = (right->getEndPoint().x + left->getEndPoint().x)/2;
	float zoom = m_workspace.width/(right->getEndPoint().x-left->getEndPoint().x + 100);
	if (zoom < m_camera.zoom) m_camera.zoom	 = zoom;
	middle*=m_camera.zoom;
	m_camera.offset.x = m_workspace.x-middle+m_workspace.width/2;

}
void AVLTreeForm::show(Node* root, const int& indent) {
	if (!root) return;
	for (int i = 0; i<indent; i++) cout << " ";
	cout << root->val << endl;
	show(root->right, indent + 3);
	show(root->left, indent + 3);
}

void AVLTreeForm::show(AVLNode* root, const int& indent) {
	if (!root) return;
	for (int i = 0; i<indent; i++) cout << " ";
	cout << root->getValue() << endl;
	show(root->right, indent + 3);
	show(root->left, indent + 3);
}
float AVLTreeForm::rePosition(AVLNode* root, float left, const int& level)
{
	if (!root) return 0;
	float right = left+100, right_right = left;
	if (root->left) right_right = right = rePosition(root->left, left, level+1) + 100;
	if (root->right) right_right = rePosition(root->right, right, level+1);
	float middle;
	if (!root->left && !root->right) middle = left;
	else if (root->left && root->right) {
		middle = (root->left->getEndPoint().x + root->right->getEndPoint().x)/2;
	} else if (root->left) {
		middle = (root->left->getEndPoint().x + 50);
	} else if (root->right) {
		middle = root->right->getEndPoint().x - 50;
	}
	root->setDuration(1);
	root->setSlowPosition(middle, 100*level);
	return right_right;
}

void AVLTreeForm::free(AVLNode* root)
{
	if (!root) return;
	free(root->left);
	free(root->right);
	delete root;
}

void AVLTreeForm::free() {
	for (int i = 0; i<logic_node.size(); i++) delete logic_node[i];
	m_root = nullptr;
	logic_node.clear();
}

void AVLTreeForm::draw(AVLNode* root)
{
	if (!root) return;
	if (root->left) {
		draw(root->left);
	}
	if (root->right) {
		draw(root->right);
	}
	root->draw();
}

void AVLTreeForm::rePosition(const float& dur) {
	if (visual_node.empty()) return;
	rePosition(vroot, 0, 0);
	float delta = vroot->getEndPoint().x;
	for (int i = 0; i<visual_node.size(); i++) 
		if (visual_node[i]) {
			Vector2 pos = visual_node[i]->getEndPoint();
			pos.x -= delta;
			visual_node[i]->setDuration(dur);
			visual_node[i]->setSlowPosition(pos.x, pos.y);
		}	
}
