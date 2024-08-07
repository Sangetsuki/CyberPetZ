#include "gui.h"

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
