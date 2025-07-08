#ifndef TEXTUREBUTTON_H 
#define TEXTUREBUTTON_H 

#include "Button.h"
#include "SettingPackage.h"
#include "Global.h"

class TextureButton : public Button {
public:
    TextureButton();
    int             getStage() const;
    virtual void    handle()                                            override,
                    draw()                                              override,
                    setSize(const float& width, const float& height)    override,
                    setButtonStage(const int& index, const string& source, const string& hover_source),
                    Hover();

    void            next(), back(), go(const int& index);
    ~TextureButton();
protected:
    int               source_pointer,
                      hover_remain_time;
    vector<Texture2D> m_sources;
    vector<Texture2D> m_sources_hover;
};

#endif