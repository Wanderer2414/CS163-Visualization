#ifndef HEAPVISUAL_H
#define HEAPVISUAL_H

#include "CommandLists.h"
#include "Controller.h"
#include "MinHeap.h"
#include "SettingPackage.h"
#include "SlowMotion.h"

class HeapBlock: public Controller, public SlowMotion {
public:
    HeapBlock(ButtonSetting* button_setting, TextSetting* text_setting);
    ButtonSetting       *button_setting;
    TextSetting         *text_setting;
    virtual void        setSize(const float& width, const float& height) override,
                        setPosition(const float& x, const float& y)      override,
                        draw()                                           override,
                        handle()                                         override,
                        setValue(const int& start, const int& end, const int& weight);
    Vector2             getPosition() const override;
private:
    string              des_text, weight_text;
    Vector2             m_des_position, m_weight_position;
};

class HeapVisual: public Controller, public MinHeap {
public:
    HeapVisual(FormSetting* form_setting);
    FormSetting         *form_setting;

    bool                isVisible() const;
    virtual void        handle() override,
                        draw()   override,

                        setPosition(const float &x, const float &y)         override,
                        setSize(const float &width, const float &height)    override,
                        setVisible(const bool& visible),
                        Insert(const Path& path)                            override,
                        erase(const int &index)                             override,
                        clear()                                             override;
    Path                pop()                    override;
private:
    enum HeapCode {
        swap_code, pop_code, add_code, fill, pop_back
    };
    ButtonSetting       choose_setting;
    bool                m_visible;
    vector<HeapBlock>   heap;
    virtual void        swap(Path& a, Path& b) override;
};

#endif