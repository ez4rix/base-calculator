#ifndef INPUT_HPP
#define INPUT_HPP

#include "TextBox.hpp"

class Input : public TextBox
{
public:

    std::string name;
    int key;
    bool neverClicked;

    std::deque<int> authorized;

    Input(std::string name, Vector2 pos, float w, float h, std::string content);

    int Getkey(); //return the unicode of the key pressed and ensre it's a number
    void SetContent(); //add to the content var the pressed key

    
    void Update() override;
};

#endif