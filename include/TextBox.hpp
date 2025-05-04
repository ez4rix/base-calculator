#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <iostream>
#include <deque>
#include "raylib.h"
#include "raymath.h"
#include <sstream>
#include <map>

class TextBox
{
public:

    //Color MYLIGHTGRAY;

    struct CRectangle : Rectangle //Add the color attribut to a new CRectangle struct from the base raylib Rectangle one
    {
        Color color; // Color attribute added to the Rectangle structinclude/TextBox.hpp
    };

    Vector2 pos; //Pos x and y to use int the Rectangle struct
    CRectangle rec;
    Color recColor; //Color of the rec

    Vector2 mousePos;

    std::string content; //what's displayed into the rectangle, by default "None"
    int offsetX, offsetY, offsetUP; //offset for the text/content
    std::string name; //declare our name for the object
    int fontSize;

    bool isActive; //has the rectangle been clicked ?

    TextBox(std::string name, Vector2 pos, float w, float h, std::string content); //constructor that take the pos x and y to put in the rectangle and what will be displayed in the rec (can be changed)

    virtual void Update(); //method that will update our object
    void Draw(); //will draw all the correct ellement

    // void Clean();

    virtual bool ClickToggle(CRectangle _rec); //will check if the user has clicked ont he rec

    bool RectEqual(Rectangle rec1, Rectangle rec2);
    
    virtual Color MouseEffect(CRectangle _rec); //Set the Color of the rec in func of the state and the mous pos

};

#endif