#define ZEROUT 0x00000000
#define MIDDLE 0x80000000
#define MAXEDOUT 0xFFFFFFFF

#include "monster.h"

Monster::Monster()
    : healthy(MIDDLE), dirty(MIDDLE), age(ZEROUT), hungry(MIDDLE),
      thirsty(MIDDLE), happy(MIDDLE) {}

Monster::~Monster() {}
