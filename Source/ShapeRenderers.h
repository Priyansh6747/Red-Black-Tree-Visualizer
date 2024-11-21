#ifndef RED_BLACK_TREE_VISUALIZER_SHAPERENDERERS_H
#define RED_BLACK_TREE_VISUALIZER_SHAPERENDERERS_H
#include "../src/include/SDL2/SDL.h"
#include "../src/include/SDL2/SDL_ttf.h"
#include "string"
#include "cmath"
// Function to render a circle with a number in its center
void RenderCircleWithNumber(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int radius, int number, SDL_Color circleColor, SDL_Color textColor) {
    // Draw the circle
    SDL_SetRenderDrawColor(renderer, circleColor.r, circleColor.g, circleColor.b, circleColor.a);
    float thickness = 3;
    for(int t = 0;t <= thickness ; t++)
        for (int angle = 0; angle < 360; angle++) {
            double rad = angle * M_PI / 180.0; // Convert degrees to radians
            int px = x + (radius + t) * cos(rad);   // X position
            int py = y + (radius + t) * sin(rad);   // Y position
            SDL_RenderDrawPoint(renderer, px, py);
        }

    // Convert the number to a string
    std::string text = std::to_string(number);

    // Render the number at the center of the circle
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Get text dimensions
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    // Free the surface, we don't need it anymore
    SDL_FreeSurface(textSurface);

    // Calculate the rectangle to position the text at the center of the circle
    SDL_Rect textRect = { x - textWidth / 2, y - textHeight / 2, textWidth, textHeight };

    // Render the text
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Clean up the texture
    SDL_DestroyTexture(textTexture);
}

void RenderLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color LineColor) {
    SDL_SetRenderDrawColor(renderer, LineColor.r, LineColor.g, LineColor.b, LineColor.a);
    int thickness = 2;
    for (int t = -thickness / 2; t <= thickness / 2; t++) {
        if (x1 == x2) { // Vertical line
            SDL_RenderDrawLine(renderer, x1 + t, y1, x2 + t, y2);
        } else if (y1 == y2) { // Horizontal line
            SDL_RenderDrawLine(renderer, x1, y1 + t, x2, y2 + t);
        } else { // Diagonal line
            SDL_RenderDrawLine(renderer, x1 + t, y1, x2 + t, y2);
            SDL_RenderDrawLine(renderer, x1, y1 + t, x2, y2 + t);
        }
    }
}


#endif //RED_BLACK_TREE_VISUALIZER_SHAPERENDERERS_H
