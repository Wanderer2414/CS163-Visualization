#include <iostream>

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

class SinglyLinkedList {
	private:
		ListNode* head;
		ListNode* tail;
		int size;
	public:
		void add(int val);
		void update(int index, int val);
		void remove(int index);
		ListNode* search(int val);
};

