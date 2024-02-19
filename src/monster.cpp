#include "monster.h"
#include <raylib.h>

Monster::Monster()
    : healthy(100), dirty(0), age(0), hungry(0), thirsty(0), happy(100),
      species(MONID_NONE) {}

Monster::~Monster() {}

Monster::Monster(const char n[12])
    : healthy(100), dirty(0), age(0), hungry(0), thirsty(0), happy(100),
      species(MONID_NONE) {
  TextCopy(name, n);
}

void Monster::step(void) {
  if (healthy > 0)
    healthy--;

  if (hungry < 100)
    hungry++;

  if (thirsty < 100)
    thirsty++;

  // dirty++;
  // age++;
  // happy--;
}
