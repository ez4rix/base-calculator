#include "include/Input.hpp"

Input::Input(std::string name ,Vector2 pos, float w, float h, std::string content) : TextBox(name, pos, w, h, content) 
{
    neverClicked = true; 
    authorized = {48,49,50,51,52,53,54,55,56,57}; //initiaz to the unicodes for digit 0 to 9
}


void Input::Update()
{
    mousePos = GetMousePosition(); //store the mouse Position in mouse_pos

    rec.color = MouseEffect(rec);
    ClickToggle(rec);
    SetContent();
    //IsActiveIndicator();
    Draw();
}

int Input::Getkey()
{
    std::map<int, int> map;
    map[97] = 65;
    map[98] = 66;
    map[99] = 67;
    map[100] = 68;
    map[101] = 69;
    map[102] = 70;

    int num = GetCharPressed(); //get the unicode val of the pressed key
    for(int i : authorized) //set i to each element in authorized character
    {
        if(num == i) //check if the user has inputed a number by comparing it's unicode to the one authorized
        {
            if(num >= 97 && num <= 102) {return map[num];}
            return i; //return i if his authorized = correct input
        }
    }
    return 0; //else return a 0
}

void Input::SetContent()
{
    if(isActive) //if user has clicked
    {

        if(neverClicked) //clear the content if it's the first time, since base value was enter
        {
            content.clear();
            neverClicked = false;
        }

        key = Getkey(); //get the input user (0,1) / (0,1,2,3,4,5,6,7,8,9) / (0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F) 
        if(key != 0 && content.size() < 10) //check if it's a correct input and if the display isn't full
        {
            content += key; //append the char
        }        

        if(IsKeyPressed(KEY_BACKSPACE) && !content.empty()) //delete the last charcter when backspace is pressed
        {
            content.pop_back();
        }
    }
}
