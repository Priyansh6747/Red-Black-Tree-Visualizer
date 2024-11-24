//include SDL2 Library
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_ttf.h"
//c++11 std libraries
#include "bits/stdc++.h"
#include "cmath"
#include "vector"
#include "string"
#include "iostream"
//custom headers
#include "Source/RBTree.h"
#include "Source/ShapeRenderers.h"
#include "Source/UI.h"
#include "Source/Utilities.h"
#include "Source/SaveHeap.h"
#include "Source/SaveManager.h"


using namespace std;


int main(int argc, char* argv[]) {
    //window
    int window_x = 1920,window_y = 1040;
    //RGBA
    SDL_Color TextColor = {0,0,0,255};
    SDL_Color InputFieldColor = {200,200,200,30};
    SDL_Color InputFieldColorActive = {255,255,255,40};
    SDL_Color InsertButtonColor = {0,255,0,30};
    SDL_Color DeleteButtonColor = {255,0,0,255};
    SDL_Color ResetButtonColor = {0,0,250,255};
    SDL_Color SaveBtnColor = {150,255,255,45};
    SDL_Color LoadBtnColor = {150,255,255,45};
    SDL_Color BackGroundColor = {150,150,210,45};
    SDL_Color QuitColor = {255,0,0,255};
    SDL_Color RED = {255,0,0};
    SDL_Color Green = {0,0,0,255};

    SDL_Rect inputField = {50, window_y - 80, 200, 40};  // Input field rectangle
    SDL_Rect button = {300, window_y - 80, 100, 40};     // Button rectangle
    SDL_Rect DeleteBtn = {450, window_y - 80, 100, 40};     // Button rectangle
    SDL_Rect ResetBtn = {600, window_y - 80, 100, 40};
    SDL_Rect SaveBtn = {window_x-80, 0, 60, 40};     // Button rectangle
    SDL_Rect QuitBtn = {window_x-80, window_y-80, 60, 40};     // Button rectangle


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }

    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Tree Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_x, window_y, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Load a font
    TTF_Font* font = TTF_OpenFont("Fonts/Baloo-Regular.ttf", 24);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    //declares
    vector<pair<int,bool>> InputArray; // for bool true mean insert false mean deletion
    string inputText;
    bool bIsInputActive = false;
    SDL_Event event;
    vector<pair<int,bool>> LevelOrder;
    RBTree Tree;
    TreeData CurrentTree;
    SaveManager SM;
    vector<pair<SDL_Rect, TreeData>> savedTreeButtons;

    // Main loop
    bool running = true;
    while (running) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty())inputText.pop_back();
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                for(auto it : savedTreeButtons){
                    if (mouseX > it.first.x && mouseX < it.first.x + it.first.w && mouseY > it.first.y && mouseY < it.first.y + it.first.h){
                        for (auto i : LevelOrder)
                            Tree.deleteValue(i.first);
                        for(auto i : it.second.GetInput()){
                            (i.second)?Tree.insertValue(i.first):Tree.deleteValue(i.first);
                            InputArray.push_back(i);
                        }

                    }
                }
                if (mouseX > button.x && mouseX < button.x + button.w && mouseY > button.y && mouseY < button.y + button.h) {
                    // Button clicked
                    if (!inputText.empty()) {
                        Tree.insertValue(StringToInt(inputText));
                        InputArray.emplace_back(StringToInt(inputText),true);
                        inputText.clear();  // Clear input field
                    }
                }else if (mouseX > inputField.x && mouseX < inputField.x + inputField.w && mouseY > inputField.y && mouseY < inputField.y + inputField.h){
                    {
                        SDL_StartTextInput();
                        bIsInputActive = true;
                    }
                }else if (mouseX > DeleteBtn.x && mouseX < DeleteBtn.x + DeleteBtn.w && mouseY > DeleteBtn.y && mouseY < DeleteBtn.y + DeleteBtn.h){
                    if(!inputText.empty()){
                        InputArray.emplace_back(StringToInt(inputText),false);
                        Tree.deleteValue(StringToInt(inputText));
                        LevelOrder.clear();
                        LevelOrder = Tree.LevelOrder();
                        inputText.clear();
                    }
                }else if (mouseX > ResetBtn.x && mouseX < ResetBtn.x + ResetBtn.w && mouseY > ResetBtn.y && mouseY < ResetBtn.y + ResetBtn.h){
                    for (auto i : LevelOrder)
                        Tree.deleteValue(i.first);
                }else if(mouseX > QuitBtn.x && mouseX < QuitBtn.x + QuitBtn.w && mouseY > QuitBtn.y && mouseY < QuitBtn.y + QuitBtn.h){
                    running = false;
                    break;
                }else if (mouseX > SaveBtn.x && mouseX < SaveBtn.x + SaveBtn.w && mouseY > SaveBtn.y && mouseY < SaveBtn.y + SaveBtn.h){
                    CurrentTree.SetInfo(InputArray, "A", Tree.GetTop());
                    Save(CurrentTree, SM);
                    for (auto i : LevelOrder)
                        Tree.deleteValue(i.first);

                    // Clear the button list and regenerate
                    savedTreeButtons.clear();
                    InputArray.clear();
                    CurrentTree.clear();
                    int i = 0;
                    for (const auto& it : SM.GetAll()) {
                        SDL_Rect loadReact = {window_x - 60, 60 + 50 * i, 40, 40};
                        savedTreeButtons.push_back({loadReact, it});
                        i++;
                    }
                }
                else {
                    SDL_StopTextInput();
                    bIsInputActive = false;
                }
            } else if (event.type == SDL_TEXTINPUT) {
                char currentChar = event.text.text[0];
                if(currentChar == '-') {
                    if (inputText.empty())
                        inputText += currentChar;
                }
                else if(currentChar < '0' || currentChar >'9') continue;
                else inputText += currentChar;
            }

        }
        SDL_SetRenderDrawColor(renderer, BackGroundColor.r, BackGroundColor.g, BackGroundColor.b, BackGroundColor.a);
        SDL_RenderClear(renderer);

        string InputFieldText = inputText.empty()?(bIsInputActive?" ":"Click To Enter"):inputText;

        RenderInputField(renderer,font,inputField,InputFieldText,
                         (bIsInputActive)?InputFieldColorActive:InputFieldColor,TextColor);
        RenderButton(renderer,font,button,"Insert",InsertButtonColor,TextColor);
        RenderButton(renderer,font,DeleteBtn,"Delete",DeleteButtonColor,TextColor);
        RenderButton(renderer,font,ResetBtn,"Reset",ResetButtonColor,TextColor);
        RenderButton(renderer,font,QuitBtn,"Quit",QuitColor,TextColor);
        RenderButton(renderer,font,SaveBtn,"SAVE",SaveBtnColor,TextColor);
        for (auto& Button : savedTreeButtons)
            RenderButton(renderer, font, Button.first, to_string(Button.second.GetTop()), LoadBtnColor, TextColor);


        int level = 0,counter = 1;
        int r = 22, x = window_x / 2, y = r * 2;

        vector<pair<int, int>> Nodes;
        LevelOrder = Tree.LevelOrder();

        int currentParent = 0;
        for (int i = 0; i < LevelOrder.size(); i++) {
            if(LevelOrder[i].first == -99) {
                if (i > 0 && i % 2 == 0)
                    currentParent++;
                if (--counter == 0) {
                    level++;
                    counter = pow(2, level);
                }
                continue;
            }
            if (i == 0) {
                x = window_x / 2;
                y = r * 2;
            } else {
                float widthAdjuster = 1.3;
                x = Nodes[currentParent].first;
                if (i % 2 == 1) x -= window_x / pow(2, level + widthAdjuster);
                else x += window_x / pow(2, level + widthAdjuster );  // Right child (move right)
                y = Nodes[currentParent].second + 4 * r;  // Y is always below the parent
            }
            RenderCircleWithNumber(renderer, font, x, y, r, LevelOrder[i].first, (LevelOrder[i].second)?RED:Green,(LevelOrder[i].second)?RED:Green);
            if (i > 0)
                RenderLine(renderer, Nodes[currentParent].first, Nodes[currentParent].second+r, x, y-r, (LevelOrder[i].second)?RED:Green);
            Nodes.emplace_back(x, y);
            if (i > 0 && i % 2 == 0)
                currentParent++;
            if (--counter == 0) {
                level++;
                counter = pow(2, level);
            }
        }
        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
