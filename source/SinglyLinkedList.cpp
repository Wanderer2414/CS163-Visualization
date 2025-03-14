#include "../include/SinglyLinkedList.h"

void SinglyLinkedList::add(int val)
{
	if (!head) {
		head = new ListNode(val);
		tail = head;
	}
	else {
		tail->next = new ListNode(val);
		tail = tail->next;
	}
}

void SinglyLinkedList::update(int index, int val)
{
	ListNode* temp = head;
	for (int i = 1; i <= index; i++) {
		if (temp->next) {
			temp = temp->next;
		}
	}
	temp->val = val;
}

void SinglyLinkedList::remove(int index)
{
	if (index == 1 && head) {
		ListNode* del = head;
		head = head->next;
		delete del;
	}
	else {
		ListNode* temp = head;
		for (int i = 1; i < index; i++) {
			if (temp->next) {
				temp = temp->next;
			}
		}
		ListNode* del = temp->next;
		temp->next = temp->next->next;
		delete del;
	}
}

ListNode* SinglyLinkedList::search(int val)
{
	ListNode* temp = head;
	while (temp) {
		if (temp->val == val) return temp;
		else temp = temp->next;
	}
    return nullptr;
}
