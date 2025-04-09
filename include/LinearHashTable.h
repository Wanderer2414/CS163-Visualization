#ifndef LINEARHASHTABLE_H
#define LINEARHASHTABLE_H

#include "Form.h"
#include "TextBox.h"
#include "TextButton.h"
#include "Global.h"

namespace HT {
    class Node : public TextButton {
    public:
        Node();
        int                 getValue() const;
        virtual void        setValue(const int& value),
                            draw()      override,
                            handle()    override,
                            setIndex(const int& index);
        Color               anim_color, found_color;
        bool                is_animating = false, is_found = false;
    private:
        int                 m_value,
                            m_index;
    };

    class HashTable : public Form {
    public:
        enum CommandCode {
            _insert = 0,
            _delete = 5,
            _choose = 1,
            _unchoose = 2,
            _add = 3,
            _remove = 4,
            _search = 6,
            _update = 7,
            _found = 8,
            _goUp = 9,
            _goDown = 10,
            _insert_end_code,
            _search_end_code,
            _remove_end_code,
            _update_end_code
        };
        HashTable(const int& index, FormSetting form_setting, const Vector2& window_size);
        virtual void        add(const vector<std::string>& data) override,
            remove(const std::string& data) override,
            search(const std::string& x) override,
            update(const std::string& old_value, const std::string& new_value),

            draw()              override,
            handle()            override,
            setMemorySize(const int& size),
            FetchNextCommand(const std::vector<float>& command) override,
            FetchPrevCommand(const std::vector<float>& command) override,
            insert_console_add(),
            search_console_add(),
            remove_console_add(),
            update_console_add();
        ~HashTable();
    private:
        int         m_storage_size,
                    max_size,
                    m_node_size,
                    m_node_spacing;

        int         index(const int& value);
        void        insert(const int& value),
                    remove(const int& value),
                    search(const int& value),
                    update(const int& oldvalue, const int& newvalue);
        TextBox     m_memory_sz_textBox;
        std::vector<Node> m_memory;
        bool checkAnimationsComplete();
    };
}

#endif