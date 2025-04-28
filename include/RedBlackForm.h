#ifndef RED_BACK_H
#define RED_BACK_H
#include "Form.h"
#include "SettingPackage.h"
#include "raylib.h"
class RedBlackForm: public Form {
public:
    RedBlackForm(const int& index, FormSetting form_setting, const Vector2& window_size);
};
#endif