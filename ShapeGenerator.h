#include <string>
#include <SDL.h>

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