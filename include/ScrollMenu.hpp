#ifndef SCROLLMENU_HPP
#define SCROLLMENU_HPP

#include "TextBox.hpp"

class ScrollMenu : public TextBox
{
public:

    struct Choice
    {
        CRectangle recChoice;
        std::string nameChoice;
    };
    
    Choice choice1, choice2, choice3, choice4, choice5; //declare all our possible choices (5 max)
    std::deque<Choice> allChoices; //deque that'll store all our choices
    int nChoice; //our number of choice

    ScrollMenu(std::string name, Vector2 pos, float w, float h, std::string content, std::deque<std::string> choices);

    void Update() override;
    bool ClickToggle(CRectangle _rec) override;
    void OpenMenu();
    void SetSelection();
    Color MouseEffect(CRectangle rec) override;


};


#endif