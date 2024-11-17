//include SDL2 Library
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_ttf.h"
//c++11 std libraries
#include "cmath"
#include "vector"
#include "string"
#include "iostream"
//custom headers
#include "Source/RBTree.h"
#include "Source/ShapeRenderers.h"
#include "Source/UI.h"
#include "Source/Utilities.h"


using namespace std;


int main(int argc, char* argv[]) {
    //window
    int window_x = 1920,window_y = 1040;
    //RGBA
    SDL_Color TextColor = {0,0,255,255};
    SDL_Color CircleColor = {255,255,0,255};
    SDL_Color LineColor = {0,255,255,255};
    SDL_Color InputFieldColor = {255,255,255,255};
    SDL_Color InsertButtonColor = {150,200,190,255};

    SDL_Rect inputField = {50, window_y - 80, 200, 40};  // Input field rectangle
    SDL_Rect button = {300, window_y - 80, 100, 40};     // Button rectangle


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
    TTF_Font* font = TTF_OpenFont("Fonts/abel-regular.ttf", 24);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }
    string inputText;
    // Main loop
    bool running = true;
    SDL_Event event;
    vector<int> arr = {};
    while (running) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty())inputText.pop_back();
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                if (mouseX > button.x && mouseX < button.x + button.w && mouseY > button.y && mouseY < button.y + button.h) {
                    // Button clicked
                    if (!inputText.empty()) {
                        arr.emplace_back(StringToInt(inputText));
                        inputText.clear();  // Clear input field
                    }
                }else if (mouseX > inputField.x && mouseX < inputField.x + inputField.w && mouseY > inputField.y && mouseY < inputField.y + inputField.h){
                    SDL_StartTextInput();
                }else SDL_StopTextInput();
            } else if (event.type == SDL_TEXTINPUT) {
                inputText += event.text.text[0];
                cout <<event.text.text[0]<<" ";
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        string InputFieldText = inputText.empty()?"Enter":inputText;
        RenderInputField(renderer,font,inputField,InputFieldText,TextColor,InputFieldColor);
        RenderButton(renderer,font,button,"Insert",InsertButtonColor,TextColor);

        int level = 0,counter = 1;
        int r = 22, x = window_x / 2, y = r * 2;

        vector<pair<int, int>> Nodes;
        int currentParent = 0;

        for (int i = 0; i < arr.size(); i++) {
            if (i == 0) {
                x = window_x / 2;
                y = r * 2;
            } else {
                x = Nodes[currentParent].first;
                if (i % 2 == 1) x -= window_x / pow(2, level +1.3 );
                else x += window_x / pow(2, level + 1.3 );  // Right child (move right)
                y = Nodes[currentParent].second + 4 * r;  // Y is always below the parent
            }
            RenderCircleWithNumber(renderer, font, x, y, r, arr[i], CircleColor, TextColor);
            if (i > 0)
                RenderLine(renderer, Nodes[currentParent].first, Nodes[currentParent].second, x, y, LineColor);
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
