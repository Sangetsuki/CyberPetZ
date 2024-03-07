#ifndef GUARD_GUI_H
#define GUARD_GUI_H

#include <functional>
#include <raylib.h>
#include <string>

namespace gui {
class Button {
public:
  Button(Rectangle _pos, std::string _text, std::function<void(void)> _onclick);
  void render(void) const;
  bool isPointInside(Vector2 point) const;
  void handleClick(void) const;

private:
  std::string text;
  Rectangle pos;
  std::function<void(void)> onclick;
};

class TextBox {
public:
  TextBox(Rectangle pborder, size_t textsize, std::string title,
          std::function<void(std::string)> onend);
  bool isTyping(void) const;
  void update(void);
  void render(void) const;
  void destroy(void);

private:
  Rectangle border;
  size_t max_size;
  std::string title;
  std::string currentText;
  bool typing;
  bool active;
  std::function<void(std::string)> onend;
};

void RenderVerticalProgressBar(float x, float y, float w, float h,
                               float progress, Color color);

} // namespace gui

#endif
