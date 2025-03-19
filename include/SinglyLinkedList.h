#ifndef SLL_H
#define SLL_H

#include "Form.h"
#include "vector"
#include "TextBox.h"
#include "TextButton.h"

namespace SLL {
	class Node : public TextButton {
	public:
		Node(const int& index, const int& val);
		int getIndex() const;
		int getValue() const;
		virtual void	draw()		override,
						handle()	override,
						setPosition(const float& x, const float& y) override;
		Vector2 getCenter() const,
				getPosition() const override;
		~Node();
		Node* next = nullptr;
	private:
		int m_index;
		int m_value;
		Vector2 m_center;
	};
	class SLLForm : public Form {
	public: 
		enum CommandCode {
			_Insert = 0,
			_Delete = 3,
			_Choose = 1,
			_Unchoose = 2,
		};
		SLLForm(const Vector2& window_size);
		virtual void		init()						override,
							add(const std::string& x, const std::string& index = "-1"),
							remove(const std::string& x) override,
							removeAtIndex(const int& index),
							update(const int& x) override,
							search(const int& x) override,
							draw()				 override,
							handle()			 override,
							close()				 override,
							FetchNextCommand(const std::vector<float>& command) override,
							FetchPrevCommand(const std::vector<float>& command)	override;
		~SLLForm();
	private:
		Node*		m_head;
		void		insert(Node*& head, const int& x, const int& index),
					remove(Node*& head, const int& x),
					removeAtIndex(Node*& head, const int& index),
					draw(Node* head),
					handle(Node* head),
					free(Node* head),
					rePosition();
		std::vector<Node*> m_list;
	};
}

#endif