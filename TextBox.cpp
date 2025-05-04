#include "include/TextBox.hpp"

TextBox::TextBox(std::string name, Vector2 pos, float w, float h, std::string content)
{
    this-> pos = pos; //set our vector2 struct pos to the one given by the constructor

    //set all our rec component
    rec.x = this-> pos.x;
    rec.y = this-> pos.y;
    rec.width = w;
    rec.height = h;
    rec.color = WHITE;

    this-> content = content; //set our default string displayed into the rec
    offsetX = 11;       
    offsetY = 5;        //set our offset x and y
    offsetUP = 45;

    this -> name = name; //get the contructors name and set it to our var

    isActive = false; //inialize the "has rec has been pressed" var to false;
    fontSize = 30;

}

void TextBox::Update()
{
    mousePos = GetMousePosition(); //store the mouse Position in mouse_pos

    rec.color = MouseEffect(rec); //set the color of the rec dynamicly
    Draw();
    ClickToggle(rec); //Check if user has clicked on the rec

}

void TextBox::Draw()
{
    DrawRectangleRounded(rec, 0.2, 1, rec.color); //draw our rectangle on the screen with rounded edge
    DrawText(content.c_str(), rec.x+offsetX, rec.y+offsetY, 30, BLACK); //Draw our text/content in it with the correct offset for the x and y
    DrawRectangleRoundedLinesEx(rec, 0.2, 1, 3, BLACK); //Draw a black outline for a cleaner UI
    DrawText(name.c_str(), rec.x, rec.y - offsetUP, fontSize+10, BLACK);// drawn name and info
}

bool TextBox::ClickToggle(CRectangle _rec)
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) //if the mouse is over the rec and user has clicked on the lest button of his mouse then:
    {   
        if(RectEqual(rec, _rec)) {isActive = CheckCollisionPointRec(mousePos, rec);} //check if our mouse is on the base rec, if so it has been click
        return CheckCollisionPointRec(mousePos, _rec);
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && CheckCollisionPointRec(mousePos, _rec) && !content.empty() ) //clear content if right click is pressed on the rec
    {
        content.clear();
    }
    return false;
}


Color TextBox::MouseEffect(CRectangle _rec) //Change the color of the rec if the mouse is over it for better UI
{
    bool mouse_on_rec = CheckCollisionPointRec(mousePos, _rec);// check if the mouse on over the _rec
    if(mouse_on_rec || isActive)
    {   
        return {220, 220, 220, 255}; //if the mouse is over the rec set it's color to a very light gray
    }
    else
    {   
        return WHITE;
    }
}

bool TextBox::RectEqual(Rectangle rec1, Rectangle rec2) //return if two itputed Rectangle are equals
{
    return (rec1.x == rec2.x &&
            rec1.y == rec1.y &&
            rec1.width == rec2.width &&
            rec1.height == rec2.height);
}

