#ifndef LINEARHASHTABLE_H
#define LINEARHASHTABLE_H

#include "Form.h"
#include "Label.h"
#include "TextBox.h"
#include "TextButton.h"
#include "Global.h"
#include "TextureButton.h"

namespace HT {
    class Node : public TextButton {
    public:
        Node();
        int                 getValue() const;
        virtual void        setValue(const int& value),
                            draw()      override,
                            handle()    override,
                            setIndex(const int& index);
        Color               anim_color;
        bool                is_animating = false;
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
            _empty = 8,
            _goUp = 9,
            _goDown = 10,
            _insert_end_code = 12,
            _search_end_code = 13,
            _remove_end_code = 14,
            _update_end_code = 15
        };
        HashTable(const int& index, FormSetting form_setting, const Vector2& window_size);
        virtual void        add(const vector<std::string>& data) override,
            remove(const std::string& data) override,
            search(const std::string& x) override,
            update(const std::string& old_value, const std::string& new_value) override,
                
            draw()              override,
            handle()            override,
            setMemorySize(const int& size),
            FetchNextCommand(const std::vector<float>& command) override,
            FetchPrevCommand(const std::vector<float>& command) override,
            insert_console_add(),
            search_console_add(),
            remove_console_add(),
            update_console_add();
        virtual string RandomCreateSize(int _max, int _min);
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
        Label       size_label;
        TextureButton random_size_button;
        std::vector<Node> m_memory;
    };
}

#endif
   