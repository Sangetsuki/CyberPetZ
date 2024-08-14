#ifndef SAVE_H_GUARD
#define SAVE_H_GUARD

#include "monster.h"
#include <ctime>
#include <memory>

struct Save {
  Monster monster;
  std::time_t closed;
  int chips;

  bool readFile(void);
  bool writeFile(void);
};

extern bool gSaveExists;
extern std::unique_ptr<Save> gSaveData;

#endif // !SAVE_H_GUARD
