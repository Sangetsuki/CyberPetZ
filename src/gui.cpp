#include "gui.h"

void RenderVerticalProgressBar(float x, float y, float w, float h,
                               float progress, Color color) {
  const Rectangle border = {x, y, w, h};
  const Rectangle content = {x + 1, y + (1 - progress) * h, w - 2,
                             progress * h};

  DrawRectangleRec(content, color);
  DrawRectangleLinesEx(border, 1.0, BLACK);
}
