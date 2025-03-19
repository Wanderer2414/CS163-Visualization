#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../raylib/raylib.h"
#include "SettingPackage.h"
class Controller {
public:
    Controller();
    virtual void    init()      ,
                    handle()    ,
                    draw()      ,
                    setPosition(const float& x, const float& y),
                    setSize(const float& width, const float& height);
    virtual Vector2 getSize() const,
                    getPosition() const;
    ~Controller();
protected:
    Vector2         m_position,
                    m_size;
};

#endif //CONTROLLER_H