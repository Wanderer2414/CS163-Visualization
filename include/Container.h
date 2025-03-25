#ifndef CONTAINER_H
#define CONTAINER_H
#include "../include/Controller.h"
#include "SettingPackage.h"
#include <vector>
class Container: public Controller {
public:
    Container(FormSetting* form_setting);
    FormSetting         *form_setting;
    virtual bool        isHovered() const override;
    virtual void        draw()      override,
                        handle()    override,
                        setVisible(const bool& visible),
                            
                        setPosition(const float& x, const float& y) override;
    
    virtual void        push_back(Controller* i),
                        pop(Controller* i),
                        reLocate(Controller* i);
    ~Container();
private:
    bool                m_is_hover,
                        m_is_visible;
    std::vector<Controller*> children;
};
#endif