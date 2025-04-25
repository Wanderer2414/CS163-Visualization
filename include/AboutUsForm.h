#ifndef ABOUTUS_FORM_H
#define ABOUTUS_FORM_H

#include "Bubble.h"
#include "Clock.h"
#include "Controller.h"
#include "Global.h"
#include "LabelExtra.h"
#include "MoveContainer.h"
#include "SettingPackage.h"

class AboutUsForm {
public:
    AboutUsForm(FormSetting form_setting, const Vector2& window_size);
    int             run();
    virtual void    handle(),
                    draw();
private:
    Vector2         m_window_size;
    FormSetting     form_setting;
    MoveContainer   main_container;
    LabelEx         main_letter;
    vector<Controller*> children;
    vector<Bubble>      bubbles;
    Clock               clock;
};
#define main_letter_content "\
\\centerABOUT US\n\
\\rightMonday, April 21st, 2025\n\
\n\
Dear you (and us in the future),\n\
\n\
    Are you a student in the same major and school as us? Or perhaps a fellow computer science student?\n\
    First of all, thank you for taking the time to follow our project!\n\
\n\
    We are students from the Advanced Program in Computer Science (APCS) at the University of Science, Vietnam.\n\
    Our team members are:\n\
            Thien Hoa (K23)\n\
            Duc Thinh (K24)\n\
            Quoc Huy (K24)\n\
            Vi Le (K24)\n\
\n\
    This being our very first project, we poured a lot of heart and effort into it. We would also like to express our gratitude to Thien Hoa for providing us with a wealth of resources and for his helpful introduction to OOP concepts. His support was invaluable in guiding us through this process.\n\
\n\
    This project is about visualizing several data structures, including Singly Linked List, AVL Tree, Hash Table, and Graph. Our goal is to help users - especially students - understand how these structures work through interactive and visual representations.\n\
\n\
    The project was originally planned to be done in semester 3, alongside the Data Structures subject. However, we were required to complete it in semester 2. This was a big challenge for us and a shock when we realized we had to manage the project earlier than expected! =))\n\
\n\
    We know that technology is rapidly advancing, which is why two subjects, CS161 and CS162, were merged into CS160. As a result, we had to self-learn many concepts before they were officially taught in class, such as Object-Oriented Programming (OOP), with an OOP-based project. This was our challenge: teaching ourselves OOP before it was formally taught in class :).\n\
\n\
    Although we followed an object-oriented programming (OOP) structure in this project, we hadn't officially learned OOP before starting it. This project was part of a Data Structures course. Because of this, we understand that some parts of our code may not be as clean or well-organized as we would have liked. We're aware that there are still many opportunities for improvement and some bugs left to fix. Unfortunately, due to time constraints, we couldn't fully develop all the ideas we had in mind or polish everything to perfection.\n\
\n\
    Throughout the process, we faced many obstacles. However, we were able to overcome them together, and this journey has been an incredible learning experience for all of us. In the end, we gained a lot of knowledge and experience from this project - both in coding, group work, and time management. This experience has truly taught us how to work together, manage our time effectively, and improve our technical skills (We spent more than 70% of our time on this project, which only accounts for 15% of our subject's grade) =)).\n\
\n\
    If you are a student at our school and have any questions or find any bugs in this project, please feel free to contact us. We'd be happy to help!\n\
    Once again, thank you for your interest in our work!\n\
    Thanks to each of our team members for their support and dedication.\n\
    And a special thank you to our school for giving us the opportunity to take on this project.\n\
\n\
\\right    With gratitude,      \n\
\\rightFrom APCS students,\n\
\\right     Group 2             \n\
"

#endif