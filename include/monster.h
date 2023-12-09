#ifndef MONSTER_H_GUARD
#define MONSTER_H_GUARD

enum MonsterID { MONID_PENGU = 0, MONID_PIDOL };

// TODO: A good class
class Monster {
public:
  Monster();
  Monster(Monster &&) = default;
  Monster(const Monster &) = default;
  Monster &operator=(Monster &&) = default;
  Monster &operator=(const Monster &) = default;
  ~Monster();

  void step(void);
  bool writeToFile(void);
  bool readFromFile(void);
  // private:
  MonsterID species;
  short unsigned int healthy;
  short unsigned int hungry;
  short unsigned int thirsty;
  short unsigned int dirty;
  short unsigned int age;
  short unsigned int happy;
};

#endif // !MONSTER_H_GUARD
