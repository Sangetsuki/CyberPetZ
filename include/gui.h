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

void RenderVerticalProgressBar(float x, float y, float w, float h,
                               float progress, Color color);

} // namespace gui

#endif
