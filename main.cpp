#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_ttf.h"
#include "Source/RBTree.h"
#include "cmath"
#include "ShapeRenderers.h"
#include "vector"
#include <utility>

int main(int argc, char* argv[]) {
    //RGBA
    SDL_Color TextColor = {255,255,255,255};
    SDL_Color CircleColor = {255,255,0,255};
    SDL_Color LineColor = {0,255,255,255};
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }

    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
        SDL_Quit();
        return -1;
    }
    int window_x = 1600,window_y = 900;
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
    TTF_Font* font = TTF_OpenFont("D:/FONTS/abel/abel-regular.ttf", 24);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Main loop
    bool running = true;
    SDL_Event event;
    while (running) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        //temporally making a complete binary tree from array
        int arr[] = {2, 5, 6, 7, 8, 9, 10,11,12,13,14,15,21,23,25,27,30};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        int level = 0,counter = 1;
        int r = 15, x = window_x / 2, y = r * 2;

        vector<pair<int, int>> Nodes;
        int currentParent = 0;

        for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
            if (i == 0) {
                x = window_x / 2;
                y = r * 2;
            } else {
                x = Nodes[currentParent].first;
                if (i % 2 == 1) x -= window_x / pow(2, level + 1);
                else x += window_x / pow(2, level + 1);  // Right child (move right)
                y = Nodes[currentParent].second + 2 * r;  // Y is always below the parent
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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
