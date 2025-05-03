#include "include/TextBox.hpp"
#include "include/Input.hpp"
#include "include/ScrollMenu.hpp"

#include <algorithm>
#include <math.h>


const Color BACKGROUND = {240, 240, 240, 255};
Vector2 mousPos;
std::deque<std::string> choices{"DEC", "BIN", "HEX"}; //max 5
std::deque<std::string> op{"+", "-", "*", "/"}; // Possible operation to perform on our Input

std::string curSelecBase1 = "BASE";
std::string curSelecBase2 = "BASE";

bool canProcessG = false;

int intBase1;
int intBase2;
int result1;
int result2;
std::string final;

//GUI---------------------------------------------------------------------------
bool StrEquals(std::string str1, std::string str2)
{
    return str1 == str2;
}

//------------------------------------------------------------------------------------------


// INPUT PROCESSING --------------------------------------------------------------------------------

std::deque<int> InputToDequeInt(std::string num) 
{
    std::deque<int> store{0};
    if(num.empty()) {return store;}
    store.pop_back();
  
    for (char ch : num)
    {
        if (std::isdigit(ch)) {
            store.push_back(ch - '0');
        } else {
            ch = std::toupper(ch);
            store.push_back(ch - 'A' + 10);
        }
    }
    return store;
}


int BaseCompute(int base, std::deque<int> store)
{
    int awns = 0;
    for(size_t i = 0; i < store.size(); i++)
    {
        int x;
        x = store[i] * pow(base, store.size()-i-1);
        awns += x;
    }
    return awns;
}

int InputProssessing(std::string input, int base)
{
    std::deque<int> intDeque = InputToDequeInt(input);
    int decNum = BaseCompute(base, intDeque);
    return decNum;
}

// -------------------------------------------------------------------------------------------------

//OUTPUT PROCESSING---------------------------------------------------------------------------------

float Rounding(float x) {
    double large = static_cast<double>(x) * 1'000'000.0;
    double largeRounded = round(large);
    double final = largeRounded / 1'000'000.0;
    return static_cast<float>(final);
}

float OpOnInput(int a, int b, std::string op) {
    float result;
    if (op == "+") { result = static_cast<float>(a + b); }
    else if (op == "-") { result = static_cast<float>(a - b); }
    else if (op == "*") { result = static_cast<float>(a * b); }
    else if (op == "/") {
        if (b == 0) { return -1.0f; }
        float divide = static_cast<float>(a) / static_cast<float>(b);
        result = Rounding(divide);
    } else {
        result = static_cast<float>(a + b); // default case
    }
    return result;
}

std::string DecToBase(double number, int base, int precision = 6)
{
    if (base < 2 || base > 36)
        return "Invalid base";

    bool isNegative = number < 0;
    number = std::fabs(number);

    // Split number into integer and fractional parts
    long long intPart = static_cast<long long>(number);
    double fracPart = number - intPart;

    // Convert integer part
    std::string intStr;
    do {
        int digit = intPart % base;
        intStr += (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
        intPart /= base;
    } while (intPart > 0);
    std::reverse(intStr.begin(), intStr.end());

    // Convert fractional part
    std::string fracStr;
    if (precision > 0 && fracPart > 0.0) {
        fracStr += '.';
        for (int i = 0; i < precision; ++i) {
            fracPart *= base;
            int digit = static_cast<int>(fracPart);
            fracStr += (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
            fracPart -= digit;
            if (fracPart == 0.0)
                break;
        }
    }

    return (isNegative ? "-" : "") + intStr + fracStr;
}


std::string OutputPrecessing(int a, int b, std::string op, int base)
{
    float result = OpOnInput(a, b, op);
    std::string temp = DecToBase(result, base);
    return temp;
}

//--------------------------------------------------------------------------------------------------


int main()
{
    int screenWidth = 700;
    int screenHeight = 700;

    std::map<std::string, int> baseMap;
    baseMap["DEC"] = 10;
    baseMap["BIN"] = 2;
    baseMap["HEX"] = 16;

    std::map<int, std::deque<int>> authorizedMap;
    authorizedMap[10] = {48,49,50,51,52,53,54,55,56,57}; //0 to 9
    authorizedMap[2] = {48,49}; // 0 and 1
    authorizedMap[16] = {48,49,50,51,52,53,54,55,56,57,  65,66,67,68,69,70,  97,98,99,100,101,102};//0 to 9, A to F and a to f

    InitWindow(screenWidth, screenHeight, "Binary Calculator");
    SetTargetFPS(60);


    //OBJECT CREATION -------------------------------------------------------------------------------------------------------------------------

    //create our Input 1 and 2 object
    Input Input1("Input 1:", {100, 100}, 200, 35, "Enter");
    Input Input2("Input 2:", {400, 100}, 200, 35, "Enter");

    //create our scroll object wit hthe correct choices and offset for better UI
    ScrollMenu Scroll1("select a base: ", {100, 175}, 100, 35, "DEC", choices);
    ScrollMenu Scroll2("select a base: ", {400, 175}, 100, 35, "DEC", choices);
    Scroll1.fontSize = Scroll2.fontSize = 10;
    Scroll1.offsetUP = Scroll2.offsetUP = 25;
    
    //creates the scroll to select our operation
    ScrollMenu ScrollOp("", {330, 100}, 40, 35, "+", op);
    ScrollOp.offsetX += 2;

    //create both of the base selector for our input
    ScrollMenu ScrollOut("select output base: ", {250, 470}, 100, 35, "DEC", choices);
    ScrollOut.fontSize = 11;
    ScrollOut.offsetUP = 25;

    //create our output object using the super class TextBox but we'll only allowed it's draw method to avoid all the other effect
    TextBox Output1("Output :", {250, 395}, 200, 35, "...");

    //-------------------------------------------------------------------------------------------------------------------------------

    while (!WindowShouldClose())
    {

        //Draw update all the object
        BeginDrawing();

            ClearBackground(BACKGROUND);

            //Rec1.Update();
            Input1.Update();
            Input2.Update();
            Scroll1.Update();
            Scroll2.Update();
            ScrollOp.Update();
            ScrollOut.Update();

            Output1.Clean(); //clean 0
            Output1.Draw();

        EndDrawing();

        //Map the base to it's correspondant int base
        intBase1 = baseMap[Scroll1.content];
        intBase2 = baseMap[Scroll2.content];
        int intBaseOut = baseMap[ScrollOut.content];

        //Set the authorized digit to the corresponding base number
        Input1.authorized = authorizedMap[intBase1];
        Input2.authorized = authorizedMap[intBase2];

        // Clear when base change
        if(curSelecBase1 != Scroll1.content) {Input1.content.clear();   curSelecBase1 = Scroll1.content; }
        if(curSelecBase2 != Scroll2.content) {Input2.content.clear();   curSelecBase2 = Scroll2.content; }

        // Check if the Users Input are correct and not the initial one
        bool canProcess1 = !(Scroll1.content == "BASE" || Input1.content == "Enter");
        bool canProcess2 = !(Scroll2.content == "BASE" || Input2.content == "Enter");

        if(canProcess1 && canProcess2) {canProcessG = true;}
        else {canProcessG = false;}

        // Process all the Inputs
        if(canProcessG)
        {
            result1 = InputProssessing(Input1.content, intBase1);
            result2 = InputProssessing(Input2.content, intBase2);

            std::string awns = OutputPrecessing(result1, result2, ScrollOp.content, intBaseOut);
            std::cout << awns << std::endl;
            Output1.content = awns;

        }
    }
    CloseWindow();
    return 0;
}