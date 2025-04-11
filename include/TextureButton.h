#ifndef TEXTUREBUTTON_H 
#define TEXTUREBUTTON_H 

#include "Button.h"
#include "SettingPackage.h"
#include "Global.h"

class TextureButton : public Button {
public:
    TextureButton();
    int             getStage() const;
    bool            isFocus() const override;
    virtual void    handle()                                            override,
                    draw()                                              override,
                    setSize(const float& width, const float& height)    override,
                    setButtonStage(const int& index, const string& source, const string& hover_source);

    void            next(), back(), go(const int& index);
    ~TextureButton();
protected:
    bool              m_is_focus;
    int               source_pointer;
    vector<Texture2D> m_sources;
    vector<Texture2D> m_sources_hover;
};

#endif