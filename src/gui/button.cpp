#include "gui.h"

gui::Button::Button(Rectangle _pos, std::string _text,
                    std::function<void(void)> _onclick)
    : pos(_pos), text(_text), onclick(_onclick){

                              };

void gui::Button::render(void) const {
  DrawRectangleRec(pos, RAYWHITE);
  DrawRectangleLinesEx(pos, 1.0, BLACK);
  DrawText(text.c_str(), pos.x + pos.height / 5, pos.y + 2 * pos.height / 25,
           4 * pos.height / 5, BLACK);
}

bool gui::Button::isPointInside(Vector2 point) const {
  return CheckCollisionPointRec(point, pos);
}

void gui::Button::handleClick(void) const {
  if (isPointInside(GetMousePosition()) &&
      IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    onclick();
}
