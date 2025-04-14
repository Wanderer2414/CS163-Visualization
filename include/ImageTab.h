#ifndef IMAGE_TAB_H
#define IMAGE_TAB_H
#include "Controller.h"
#include "GIF.h"
class ImageTab: public Controller, public Move {
public:
    ImageTab();
    virtual void    handle()    override,
                    draw()      override,
                    setSize(const float& x, const float& y) override,
                    setPosition(const float &x, const float &y) override,
                    push(GIF* gif),
                    clearGifs();
    Vector2         getPosition() const override;
    ~ImageTab();
private:
    int gif_pointer;
    vector<GIF*> gifs;
    Clock clock;
};
#endif