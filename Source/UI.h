#ifndef RED_BLACK_TREE_VISUALIZER_UI_H
#define RED_BLACK_TREE_VISUALIZER_UI_H
#include "../src/include/SDL2/SDL.h"
#include "../src/include/SDL2/SDL_ttf.h"

#include <string>
#include <vector>
#include <cmath>
#include <iostream>

void RenderButton(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect rect, const std::string& label, SDL_Color bgColor, SDL_Color textColor) {
    // Draw the button background
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &rect);

    // Render the label text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, label.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {rect.x + (rect.w - textSurface->w) / 2, rect.y + (rect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
void RenderInputField(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect rect, const std::string& inputText, SDL_Color bgColor, SDL_Color textColor) {
    // Draw the input field background
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &rect);

    // Render the input text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {rect.x + 5, rect.y + (rect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
#endif //RED_BLACK_TREE_VISUALIZER_UI_H
