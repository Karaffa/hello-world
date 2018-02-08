#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include <string>
#include <iostream>

const std::string NAME = "pkaraff";
const int WIDTH = 640;
const int HEIGHT = 480;

class ShapeGenerator {
public:
  ShapeGenerator(SDL_Color, SDL_Point, SDL_Rect);
  void drawCircle(SDL_Renderer* renderer, int radius);
  void drawRectangle(SDL_Renderer* renderer);
  void drawGradientCircle(SDL_Renderer* renderer, int radius, char hue);
  void setColor(SDL_Color);
  void setCenter(SDL_Point);
  void setCorner(SDL_Rect);
  const std::string overloaded();
private:
  SDL_Color color;
  SDL_Point center;
  SDL_Rect corner;
};

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


std::ostream& operator<<(std::ostream& out, ShapeGenerator Generate) {
  return out << Generate.overloaded();
}


int main(void) {
  SDL_Renderer *renderer;
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

  // Drawing Start

  ShapeGenerator Generate({0, 0, 0, 0}, {0, 0}, {0, 0, 0, 0});

  // Background Color
  Generate.setCorner({0, 0, 640, 480});
  Generate.setColor({0, 0, 0, 0});
  Generate.drawRectangle(renderer);
  
  //Neat blue background orb
  Generate.setCenter({117, 109});
  Generate.setColor({0, 0, 0, 0});
  Generate.drawGradientCircle(renderer, 100, 'b');

  //Neat red background orb
  Generate.setCenter({516, 361});
  Generate.setColor({0, 0, 0, 0});
  Generate.drawGradientCircle(renderer, 100, 'r');

  //Neat yellow background orb
  Generate.setCenter({414, 124});
  Generate.setColor({0, 0, 0, 0});
  Generate.drawGradientCircle(renderer, 100, 'y');

  //Neat green background orb
  Generate.setCenter({175, 347});
  Generate.setColor({0, 0, 0, 0});
  Generate.drawGradientCircle(renderer, 100, 'g');

  //Neat purple background orb
  Generate.setCenter({607, 148});
  Generate.setColor({0, 0, 0, 0});
  Generate.drawGradientCircle(renderer, 100, 'p');

  //Neat orange background orb
  Generate.setCenter({73, 228});
  Generate.setColor({0, 0, 0, 0});
  Generate.drawGradientCircle(renderer, 100, 'o');

  //casette outline shape
  Generate.setCorner({116, 110, 353, 245});
  Generate.setColor({0, 0, 0, 0});
  Generate.drawRectangle(renderer);
  
  //Red interior of the casette
  Generate.setCorner({121,115, 343, 205});
  Generate.setColor({128, 0, 0, 0});
  Generate.drawRectangle(renderer);
  
  //top left corner dot
  Generate.setColor({0, 0, 0, 0});
  Generate.setCenter({133, 128});
  Generate.drawCircle(renderer, 5);
  
  //top right corner dot
  Generate.setCenter ({450, 128});
  Generate.drawCircle(renderer, 5);

  //casette interior window outline
  Generate.setColor({0, 0, 0, 0});
  Generate.setCorner({175, 159, 234, 99});
  Generate.drawRectangle(renderer);
  
  //casette interior window background
  Generate.setColor({60, 0, 9, 0});
  Generate.setCorner({180, 164, 224, 89});
  Generate.drawRectangle(renderer);
  
  //casette tape left roll
  Generate.setColor({0, 0, 0, 0});
  Generate.setCenter({227, 209});
  Generate.drawCircle(renderer, 50);
  
  //casette tape left roll inner circle
  Generate.setColor({37, 37, 37, 0});
  Generate.drawCircle(renderer, 25);
  
  //casette tape right roll 
  Generate.setCenter({360,209});
  Generate.setColor({0, 0, 0, 0});
  Generate.drawCircle(renderer, 46);
  
  //casette tape right roll inner circle
  Generate.setColor({37, 37, 37, 0});
  Generate.drawCircle(renderer, 25);
  
  //castte tape line stretching from left roll to right roll
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0 );
  SDL_RenderDrawLine(renderer, 236, 246, 325, 190);
  SDL_RenderDrawLine(renderer, 235, 246, 324, 190);
  SDL_RenderDrawLine(renderer, 235, 245, 324, 189);
  SDL_RenderDrawLine(renderer, 234, 245, 323, 189);

  //bottom tab top grey line
  Generate.setColor({128, 128, 128, 0});
  Generate.setCorner({177, 320, 234, 25});
  Generate.drawRectangle(renderer);
  
  //hides the rest of the grey rectangle at the bottom
  Generate.setColor({0, 0, 0, 0});
  Generate.setCorner({177, 325, 234, 25});
  Generate.drawRectangle(renderer);
  
  //grey lines at the bottom from the top line at the bottom
  SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0 );
  SDL_RenderDrawLine(renderer, 172, 354, 177, 325);
  SDL_RenderDrawLine(renderer, 173, 354, 178, 325);
  SDL_RenderDrawLine(renderer, 417, 354, 411, 325);
  SDL_RenderDrawLine(renderer, 416, 354, 410, 325);

  //bottom left dot
  Generate.setColor({37, 37, 37, 0});
  Generate.setCenter({220, 340});
  Generate.drawCircle(renderer, 4);
  
  //bottom right dot
  Generate.setCenter({372, 340});
  Generate.drawCircle(renderer, 4);

  // Drawing Complete

  std::cout << Generate << std::endl; //overloaded operator

  SDL_RenderPresent(renderer);
  FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
  frameGen.makeFrame();

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
