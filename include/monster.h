#ifndef MONSTER_H_GUARD
#define MONSTER_H_GUARD

#define ZEROUT 0x00000000
#define MIDDLE 0x80000000
#define MAXEDOUT 0xFFFFFFFF

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

  // private:
  short unsigned int healthy;
  short unsigned int hungry;
  short unsigned int thirsty;
  short unsigned int dirty;
  short unsigned int age;
  short unsigned int happy;
};

#endif // !MONSTER_H_GUARD
