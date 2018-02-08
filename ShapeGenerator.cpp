#include "ShapeGenerator.h"

ShapeGenerator::ShapeGenerator(SDL_Color col, SDL_Point cen, SDL_Rect cor) : 
  color(col), center(cen), corner(cor) {}

void ShapeGenerator::drawCircle(SDL_Renderer* renderer, int radius) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}

void ShapeGenerator::drawRectangle(SDL_Renderer* renderer){
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &corner);
}

void ShapeGenerator::drawGradientCircle(SDL_Renderer* renderer, int radius, char hue){
  for(int i = radius; i > 0; i--){
    if(hue == 'r') color.r++;
    if(hue == 'g') color.g++;
    if(hue == 'b') color.b++;
    if(hue == 'y') {color.r++; color.g++;}
    if(hue == 'p') {color.r+=2; color.b+=2;}
    if(hue == 'o') {color.r+=2; color.g++;}
    drawCircle(renderer, i);
  }
}

void ShapeGenerator::setColor(SDL_Color col){
  color = col;
}

void ShapeGenerator::setCenter(SDL_Point cen){
  center = cen;
}

void ShapeGenerator::setCorner(SDL_Rect cor){
  corner = cor;
}

const std::string ShapeGenerator::overloaded() {
  return "This operator is overloaded";
}