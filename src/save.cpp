#include "save.h"
#include <cstdio>

std::unique_ptr<Save> gSaveData = std::make_unique<Save>();
bool gSaveExists = false;

bool Save::readFile(void) {
  FILE *file = fopen("save.bin", "rb");
  if (!file) {
    gSaveExists = false;
    return false;
  }

  fread(gSaveData.get(), sizeof(Save), 1, file);

  fclose(file);
  gSaveExists = true;
  return true;
}

bool Save::writeFile(void) {
  FILE *file = fopen("save.bin", "wb+");
  if (!file) {
    return false;
  }

  fwrite(gSaveData.get(), sizeof(Save), 1, file);
  fclose(file);
  return true;
}
