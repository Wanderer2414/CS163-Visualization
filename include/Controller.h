#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Global.h"
#include "SettingPackage.h"

class Controller {
public:
    Controller();
    virtual bool    isHovered() const,
                    isFocus() const;
    virtual void    handle()    ,
                    draw()      ,
                    setPosition(const float& x, const float& y),
                    setSize(const float& width, const float& height);
    virtual Vector2 getSize() const,
                    getPosition() const;
    virtual void    update();
    ~Controller();
protected:
    Vector2         m_position,
                    m_size;
};

#endif //CONTROLLER_H