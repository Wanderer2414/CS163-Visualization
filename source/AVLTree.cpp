#include "../include/AVLTree.h"
#include "../include/General.h"

AVLTreeForm::AVLTreeForm(const int& index, FormSetting form_setting, const Vector2& window_size) :
	Form(index, form_setting, window_size) {
	m_root = 0;
	vroot = 0;
	fill_setting = form_setting;
	fill_setting.normal_color = RED;
}
void AVLTreeForm::add(const vector<std::string>& x)
{
	for (int i = x.size() - 1; i >= 0; i--) {
		console.InsertNextMainCommand("Add " + x[i]);
		InsertNextMainCommand({ CommandCode::insert, 1.0f * to_int(x[i]), 1});
	}
}

int AVLTreeForm::insert(Node*& root, Node* parent, const int& x) {
    if (!root) {
        root = new Node(x, 1, logic_node.size());
		root->parent = parent;
        logic_node.push_back(root);
		visual_node.push_back(0);
        return root->index;
    };
	InsertNextSubCommand({choose, 1.0f*root->index, 0.5});
	InsertNextSubCommand({unchoose, 1.0f*root->index, 0});
    //Go to left if x<root or right when x>root like BST
	int index = 0;
    if (x>root->val) {
		if (!root->right) {
			InsertNextSubCommand({CommandCode::add, 1, 1.0f*x, 1.0f*root->index, 1.0f*logic_node.size(), 0.5});
		}
        index = insert(root->right, root, x);
    }
    else if (x<root->val) {
		if (!root->left) {
			InsertNextSubCommand({CommandCode::add, 0, 1.0f*x, 1.0f*root->index,1.0f*logic_node.size(), 0.5});
		}
        index = insert(root->left, root, x);
    }
    else return -1;
    //After insert, back and check its height of each branch
    root->height = max(height(root->right), height(root->left))+1;
    //If right branch taller than left branch over 1 unit => Turn Left
    if (height(root->right)-height(root->left)>1) {
        //Check if case right-right or right-left
        if (height(root->right->right)<height(root->right->left)) {
			InsertNextSubCommand({CommandCode::rotateRight, 1.0f*root->right->index, 1});
			InsertNextSubCommand({wait, 1});
			rotateRight(root->right);
		}
		InsertNextSubCommand({CommandCode::rotateLeft, 1.0f*root->index, 1});
		InsertNextSubCommand({wait, 1});
        rotateLeft(root);
    } else
    //If left branch taller than right branch over 1 unit => Turn Right
    if (height(root->left)-height(root->right)>1) {
        //Check if case left-left or left-right
        if (height(root->left->left)<height(root->left->right)) {
			InsertNextSubCommand({CommandCode::rotateLeft, 1.0f*root->left->index, 1});
			InsertNextSubCommand({wait, 1});
			rotateLeft(root->left);
		}
		InsertNextSubCommand({CommandCode::rotateRight, 1.0f*root->index, 1});
		InsertNextSubCommand({wait, 1});
        rotateRight(root);
    }
	return index;
}
void AVLTreeForm::handle()
{
	Form::handle();
	for (int i = 0; i<visual_node.size(); i++) 
		if (visual_node[i]) visual_node[i]->handle();
}

AVLTreeForm::~AVLTreeForm() {

}

void AVLTreeForm::draw()
{
	BeginMode2D(m_camera);
	BeginScissorMode(m_workspace.x, m_workspace.y, m_workspace.width, m_workspace.height);
	draw(vroot);
	EndScissorMode();
	EndMode2D();
	Form::draw();
}

void AVLTreeForm::FetchPrevCommand(const std::vector<float>& codes)
{
	float dur = codes.back();
	int code = codes[0];
	cout << "in" << endl;
	switch (code) {
	case CommandCode::insert: {
		int val = codes[1];
		int index = remove(m_root, val);
		if (index<visual_node.size() && visual_node[index]) {
			if (visual_node[index]==vroot) vroot = 0;
			if (visual_node[index]->parent) {
				if (visual_node[index]->parent->right == visual_node[index]) {
					visual_node[index]->parent->right = 0;
				} else visual_node[index]->parent->left = 0;
			}
			delete visual_node[index];
			visual_node[index] = 0;
		}
		setDuration(0.1);
	}
	break;
	case CommandCode::add: {
		bool right = codes[1];
		int value = codes[2], parent = codes[3], index = codes[4];

		if (right) visual_node[parent]->right = 0;
		else visual_node[parent]->left = 0;

		delete visual_node[index];
		visual_node[index] = 0;

		rePosition(dur*getSpeed());
		setDuration(dur);
	}
	break;
	case CommandCode::erase: {
		// insert(m_root, { 400, 100 }, (int)codes[1]);
		// rePosition();
		console.goUp();
		break;
	}
	case CommandCode::choose: {
		int index = codes[1];
		visual_node[index]->button_setting = &form_setting;
		setDuration(dur);
	}
	break;
	case CommandCode::unchoose: {	
		int index = codes[1];
		visual_node[index]->button_setting = &fill_setting;
		setDuration(0.1);		
	}
	break;
	case CommandCode::rotateLeft: {
		cout << "Left" << endl;
		AVLNode* tmp = visual_node[codes[1]]->parent;
		Node* cur = logic_node[codes[1]]->parent;
		cout <<"T: " <<  tmp->getValue() << endl;
		if (tmp ==vroot) {
			cout <<"T: " <<  tmp->getValue() << endl;
			rotateRight(m_root);
			cout <<"T: " <<  tmp->getValue() << endl;
			visual_rotateRight(vroot);
			cout << "T" << endl;
		}
		else if (tmp->parent->right == tmp) {
			rotateRight(cur->parent->right);
			visual_rotateRight(tmp->parent->right);
		}
		else {
			rotateRight(cur->parent->left);
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
		setDuration(1);
	}
	break;
	default:
		break;
	}
	cout << "out" << endl;
}

void AVLTreeForm::FetchNextCommand(const std::vector<float>& codes)
{
	int code = codes[0];
	float dur = codes.back();
	switch (code) {
	case CommandCode::insert: {
		int value = codes[1];
		int index =insert(m_root, 0, value);
		if (!vroot) {
			visual_node[index] = new AVLNode(&form_setting, &form_setting, 0, value);
			vroot = visual_node[index];
			rePosition(dur*getSpeed());
		}
		setDuration(dur);
	}
	break;
	case CommandCode::add: {
		bool right = codes[1];
		int value = codes[2], parent = codes[3], index = codes[4];
		visual_node[index] = new AVLNode(&form_setting, &form_setting, visual_node.size(), value);

		if (right) visual_node[parent]->right = visual_node[index];
		else visual_node[parent]->left = visual_node[index];

		visual_node[index]->parent = visual_node[parent];
		Vector2 pos = visual_node[parent]->getPosition();
		visual_node[index]->setPosition(pos.x, pos.y);
		rePosition(dur*getSpeed());
		cout << "out" << endl;
		setDuration(dur);
	}
	break;
	case CommandCode::choose: {
		int index = codes[1];
		visual_node[index]->button_setting = &fill_setting;
		setDuration(dur);
	}
	break;
	case CommandCode::unchoose: {	
		int index = codes[1];
		visual_node[index]->button_setting = &form_setting;
		setDuration(codes.back());		
	}
	break;
	case CommandCode::wait: {
		setDuration(1);
	}
	break;
	case CommandCode::erase: {
		remove(m_root, (int)codes[1]);
		rePosition(dur*getSpeed());
		break;
	}
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
	case CommandCode::redraw: {
		console.goDown();
		rePosition(dur*getSpeed());
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
        tmp->right->height = max(height(tmp->right->right), height(tmp->right->left)) + 1;
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
        tmp->right->height = max(height(tmp->right->right), height(tmp->right->left)) + 1;
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
        tmp->left->height = max(height(tmp->left->left), height(tmp->left->right))+1;
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
	cout << "here " << endl;
    root->parent = tmp->parent;
    tmp->left = 0;
    //Reset it height
    tmp->height = height(tmp->right)+1;
    //Check if exists old right branch
    if (root->right) {
        tmp->left = root->right;
        root->right->parent = tmp;
        //Re-Cal the height
        tmp->left->height = max(height(tmp->left->left), height(tmp->left->right))+1;
    }
    root->right = tmp;
	tmp->parent = root;
    //Re-Cal the height of new root
    root->height = max(height(root->right), height(root->left))+1;
}

int AVLTreeForm::remove(Node*& root, const int& x)
{
	if (!root) return -1;
	if (x < root->val) return remove(root->left, x);
	else if (x > root->val) return remove(root->right, x);
	else {
		if (!root->left && !root->right) {
			int index = root->index;
			logic_node[root->index] = 0;
			delete root;
			root = 0;
			return index;
		}
	}
	return -1;
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
	if (root->left) right = rePosition(root->left, left, level+1) + 100;
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

void AVLTreeForm::handle(AVLNode* root)
{
	if (!root) return;
	root->handle();
	if (root->left) handle(root->left);
	if (root->right) handle(root->right);
}
void AVLEdgeDraw(AVLNode* start, AVLNode* end) {
	Vector2 pos = end->getPosition(), delta = end->getPosition()-start->getPosition();
	Vector2 u = delta/abs(delta), n = {u.y, -u.x};
	pos = pos - u*max(end->getSize().x, end->getSize().y)/2;
	Vector2 start_point = pos - u*10;
	DrawLineEx(start->getPosition(), pos, 2.5f, end->button_setting->normal_color);
	DrawLineEx(start_point-5*n, pos, 2.5f, end->button_setting->normal_color);
	DrawLineEx(start_point+5*n, pos, 2.5f, end->button_setting->normal_color);
}
void AVLTreeForm::draw(AVLNode* root)
{
	if (!root) return;
	if (root->left) {
		draw(root->left);
		AVLEdgeDraw(root, root->left);
	}
	if (root->right) {
		AVLEdgeDraw(root, root->right);
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

