#include "monster.h"

#define ONE_PER 42949672

Monster::Monster()
    : healthy(MIDDLE), dirty(MIDDLE), age(ZEROUT), hungry(MIDDLE),
      thirsty(MIDDLE), happy(MIDDLE) {}

Monster::~Monster() {}

// Might make this a short and just use straight up the percentage
void Monster::step(void) {
  healthy -= ONE_PER;
  dirty += ONE_PER;
  age++;
  happy -= ONE_PER;
  hungry += ONE_PER;
  thirsty += ONE_PER;
}
