#include "monster.h"

Monster::Monster()
    : healthy(100), dirty(0), age(0), hungry(0), thirsty(0), happy(100) {}

Monster::~Monster() {}

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
