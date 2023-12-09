#include "monster.h"
#include <cassert>
#include <cstdio>
#include <unistd.h>

Monster::Monster()
    : healthy(100), dirty(0), age(0), hungry(0), thirsty(0), happy(100),
      species(MONID_PENGU) {}

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

bool Monster::writeToFile(void) {
  FILE *file = fopen("monster.bin", "wb+");
  assert(file != nullptr);

  fwrite(this, sizeof(*this), 1, file);

  fclose(file);

  return true;
}

bool Monster::readFromFile(void) {
  FILE *file = fopen("monster.bin", "rb");
  if (file == nullptr) {
    return false;
  }
  assert(file != nullptr);
  fread(this, sizeof(*this), 1, file);
  fclose(file);
  return true;
}
