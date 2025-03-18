#ifndef MODE_H
#define MODE_H

#include "Colors.h"

class Mode {
private:
    ColorScheme currentTheme;

public:
    Mode();  
    void SetTheme(ColorScheme theme);
    ColorScheme GetTheme() const;
};

#endif // MODE_H
