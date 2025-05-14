#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Global.h"
#include "SettingPackage.h"

class Controller {
public:
    Controller();
    ~Controller();
    virtual bool    isHovered()     const,
                    isFocus()       const;
    virtual Vector2 getSize()       const,
                    getPosition()   const;
    virtual bool    setHover(const Vector2& position),
                    setHover(const bool& hover),
                    contains(const Vector2& position) const,
                    beforeHandle(),
                    handle(),
                    afterHandle();
    virtual void    draw()          const,
                    setSize(const float& width, const float& height),
                    setSize(const Vector2& size),
                    setPosition(const float& x, const float& y),
                    setPosition(const Vector2& position),
                    setFocus(const bool& focus);
    virtual void    update();
private:
    bool            pIsFocus,
                    pIsHovered,
                    pIsPress,
                    pIsRelease;
    Vector2         pPosition,
                    pSize;
};

#endif