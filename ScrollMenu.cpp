#include "include/ScrollMenu.hpp"

ScrollMenu::ScrollMenu(std::string name, Vector2 pos, float w, float h, std::string content, std::deque<std::string> choices) : TextBox(name, pos, w, h, content)
{  
    rec.x = pos.x;
    rec.y = pos.y;

    allChoices = {choice1, choice2, choice3, choice4, choice5};
    nChoice = choices.size();

    for(int i = 0; i < nChoice; i++)
    {
        allChoices[i].recChoice = {pos.x, pos.y + h*(i+1) + 10, w, h+2}; //set all of our choices' rectangle attribute, + h*(i+1) to                                                                   
        allChoices[i].nameChoice = choices[i];                              //ensure all rec are at differents height and +10 tp separate                        
        allChoices[i].recChoice.color = WHITE;
    }
}

void ScrollMenu::Update()
{
    mousePos = GetMousePosition(); //store the mouse Position in mouse_pos

    MouseEffect(rec);
    for(int i = 0; i < nChoice; i++) //change the color of the rec if the mouse is over it for better UI
    {
        allChoices[i].recChoice.color = MouseEffect(allChoices[i].recChoice);
    }
    SetSelection();
    ClickToggle(rec);
    OpenMenu();
    Draw(); 
}

bool ScrollMenu::ClickToggle(CRectangle _rec)
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) //if the mouse is over the rec and user has clicked on the lest button of his mouse then:
    {   
        if(RectEqual(rec, _rec)) {isActive = CheckCollisionPointRec(mousePos, rec);} //check if our mouse is on the base rec, if so it has been click
        return CheckCollisionPointRec(mousePos, _rec);
    }
    return false;
}

void ScrollMenu::OpenMenu()
{
    if(isActive)
    {
        for(int i = 0; i < nChoice; i++)
        {
            DrawRectangleRec(allChoices[i].recChoice, allChoices[i].recChoice.color);
            DrawRectangleLinesEx(allChoices[i].recChoice, 2, BLACK);
            DrawText(allChoices[i].nameChoice.c_str(), allChoices[i].recChoice.x + offsetX, allChoices[i].recChoice.y + offsetY, 30, BLACK);
        }
    }
}

void ScrollMenu::SetSelection()
{
    if(isActive) 
    {
        for(int i = 0; i < nChoice; i++)
        {
            if(ClickToggle(allChoices[i].recChoice)) {content = allChoices[i].nameChoice;}
        }
    }
}

Color ScrollMenu::MouseEffect(CRectangle _rec) //Change the color of the rec if the mouse is over it for better UI
{
    bool mouse_on_rec = CheckCollisionPointRec(mousePos, _rec);// check if the mouse on over the _rec
    if(mouse_on_rec)
    {   
        return {220, 220, 220, 255}; //if the mouse is over the rec set it's color to a very light gray
    }
    else
    {   
        return WHITE;
    }
}