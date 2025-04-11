#ifndef SLL_H
#define SLL_H

#include "Form.h"
#include "vector"
#include "TextBox.h"
#include "TextButton.h"
#include "SlowMotion.h"
#include "General.h"

namespace SLL {
	class Arrow {
	public:
		Vector2 m_tail;
		float m_length;
		float m_thickness=5;
		Vector2 m_t1;
		Vector2 m_t2;
		Vector2 m_t3;
		Color color;
		void setPosition(Vector2 tail,Vector2 head);
		void handle();
		void draw();
	private:
	};	
	class ListNode : public TextButton, public SlowMotion{
	public:
		ListNode(const int& value,const int& index);
		int getValue() const;
		int getIndex() const;
		void setValue(const int& value);
		void setIndex(const int& index);
		virtual void setPosition(const float& x,const float& y) override;
		ListNode* m_next;
		Arrow m_arrow;
		virtual void draw() override;
		virtual void handle() override;
		virtual Vector2 getCenter() const,
                        getPosition() const override;
	private:
		int m_value;
		int m_index;
		Vector2 m_center;
		
	};
	class SLLForm : public Form {
	public:

		ButtonSetting temp_b_setting;
		TextSetting temp_t_setting;

		enum CommandCode {
			_insert = 0,
			_delete = 5,
			_choose = 1,
			_unchoose = 2,
			_add = 3,
			_update = 6,
			_remove = 4,
			_search = 10,
			_searchSilent = 11,
			_insertSilent = 7,
			_removeSilent = 8,
			_updateSilent = 9,
			_GoUp = 12,
			_GoDowm = 13
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
		void rePosition();
		~SLLForm();
	private:
		int m_node_size;
		int m_node_spacing;
		int size = 0;
		ListNode* m_head = nullptr;
		ListNode* m_dummy = nullptr;

		void insert(const int& value, const int& index);
		void insertSilent(const int& value, const int& index);
		void console_add_insert(const int& value);

		void remove(const int& value, const int& index);
		void removeSilent(const int& value,const int& index);
		void console_add_remove(const int& value);

		void update(const int& old_value, const int& new_value);
		void updateSilent(const int& old_value,const int& new_value,const int& index);
		void console_add_update(const int& old_value,const int& new_value);

		void search(const int& value);
		void console_add_search(const int& value);
	};
}

#endif
