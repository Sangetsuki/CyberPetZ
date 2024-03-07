#include "gui.h"

void gui::RenderVerticalProgressBar(float x, float y, float w, float h,
                                    float progress, Color color) {
  const Rectangle border = {x, y, w, h};
  const Rectangle content = {x + 1, y + (1 - progress) * h, w - 2,
                             progress * h};

  DrawRectangleRec(content, color);
  DrawRectangleLinesEx(border, 1.0, BLACK);
}

gui::Button::Button(Rectangle _pos, std::string _text,
                    std::function<void(void)> _onclick)
    : pos(_pos), text(_text), onclick(_onclick){

                              };

void gui::Button::render(void) const {
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

gui::TextBox::TextBox(Rectangle pborder, size_t max, std::string _title,
                      std::function<void(std::string)> callback)
    : border(pborder), max_size(max), title(_title), onend(callback) {
  currentText.reserve(max);
}

void gui::TextBox::update(void) {
  int key = GetCharPressed();

  while (key > 0) {
    if ((key >= 32) && (key <= 125) && currentText.size() < 12)
      currentText.push_back(key);

    key = GetCharPressed();
  }

  if (IsKeyPressed(KEY_BACKSPACE) && currentText.size() > 0) {
    currentText.pop_back();
  } else if (IsKeyPressed(KEY_ENTER) && currentText.size() != 0) {
    typing = false;
    onend(currentText);
    currentText.clear();
  }
}

void gui::TextBox::render(void) const {
  Rectangle titlebox = {border.x, border.y - 4 * border.height / 5,
                        border.width, 4 * border.height / 5};
  DrawRectangleRec(titlebox, WHITE);
  DrawRectangleLinesEx(titlebox, 1.0, BLACK);
  DrawText(title.c_str(), titlebox.x + 1, titlebox.y + 1,
           4 * titlebox.height / 5, BLACK);
  DrawRectangleRec(border, WHITE);
  DrawRectangleLinesEx(border, 1.0, BLACK);
  DrawText(currentText.c_str(), border.x + 2, border.y + 2,
           4 * border.height / 5, BLACK);
}

void gui::TextBox::destroy(void) {
  typing = false;
  currentText.clear();
}
