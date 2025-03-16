#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Form.h"
#include "TextBox.h"
#include "TextButton.h"
#include <vector>
namespace HT {
    class Node: public TextButton {
    public:
        Node();
        int                 getValue() const;
        virtual void        setValue(const int& value),
                            draw()      override,
                            handle()    override,
                            setIndex(const int& index);
    private:
        int                 m_value,
                            m_index;
    };

    class HashTable: public Form {
    public:
        enum CommandCode {
            _insert = 0,
            _delete = 5,
            _choose = 1,
            _unchoose = 2,
            _add = 3,
            _remove = 4

        };
        HashTable(const Vector2& window_size);
        virtual void        init()              override,
                            add(const std::string& data) override,
                            remove(const std::string& data) override,
                            draw()              override,
                            handle()            override,
                            setMemorySize(const int& size),
                            FetchNextCommand(const std::vector<float>& command) override,
                            FetchPrevCommand(const std::vector<float>& command) override;
        ~HashTable();
    private:
        int         m_storage_size,
                    max_size,
                    m_node_size,
                    m_node_spacing;
    
        int         index(const int& value);
        void        insert(const int& value),
                    remove(const int& value, const bool& isShow = true);
        
        TextBox     m_memory_sz_textBox;
        std::vector<Node> m_memory;
    
    };
    
}
#endif