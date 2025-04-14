#ifndef GIF_H
#define GIF_H
#include "Clock.h"
#include "Controller.h"
#include "Move.h"
class GIF: public Controller, public Move {
public:
    GIF();
    Vector2 getPosition() const override;
    virtual void    setSize(const float& x, const float& y) override,
                    setPosition(const float &x, const float &y) override,
                    handle()    override,
                    draw()      override,
                    setDuration(const float& duration),
                    push(const string& str);
    ~GIF();
private:
    int image_pointer = 0;
    vector<Texture2D> image_list;
    Clock   clock;
};
#endif