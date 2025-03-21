#ifndef TEXTUREBUTTON_H 
#define TEXTUREBUTTON_H 

#include "Button.h"
#include "../raylib/raylib.h"
#include "SettingPackage.h"
#include <vector>
#include <string>
using namespace std;

class TextureButton : public Button {
public:
    TextureButton();
    ButtonSetting* button_setting;
    int             getStage() const;
    virtual void    init()                                              override,
        handle()                                            override,
        draw()                                              override,
        setSize(const float& width, const float& height)    override,
        setButtonStage(const int& index, const string& source, const string& hover_source);

    void            next(), back(), go(const int& index);
    ~TextureButton();
protected:
    int             source_pointer;
    vector<Texture2D> m_sources;
    vector<Texture2D> m_sources_hover;
};

#endif