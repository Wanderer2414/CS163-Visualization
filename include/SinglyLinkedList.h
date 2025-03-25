#ifndef SLL_H
#define SLL_H

#include "Form.h"
#include "vector"
#include "TextBox.h"
#include "TextButton.h"

namespace SLL {
	class ListNode : public TextButton {
	public:
		ListNode(const int& value,const int& index);
		int getValue() const;
		int getIndex() const;
		void setValue(const int& value);
		void setIndex(const int& index);
		ListNode* m_next;
		virtual void draw() override;
		virtual void handle() override;
	private:
		int m_value;
		int m_index;
	};
	class SLLForm : public Form {
	public:
		enum CommandCode {
			_insert = 0,
			_delete = 5,
			_choose = 1,
			_unchoose = 2,
			_add = 3,
			_remove = 4
		};
		SLLForm(const int& index, FormSetting form_setting, const Vector2& window_size);
		virtual void    add(const vector<string>& str) override,
						remove(const std::string& str) override,
						draw() override,
						update(const std::string& old_value, const std::string& new_value) override,
						search(const std::string& x) override,
						FetchNextCommand(const std::vector<float>& command) override,
                        FetchPrevCommand(const std::vector<float>& command) override,
						handle() override;
		~SLLForm();
	private:
		int m_node_size;
		int m_node_spacing;
		int size = 0;
		ListNode* m_head = nullptr;
		void insert(const int& value,const int& index);
		void remove(const int& value);
	};
}

#endif
