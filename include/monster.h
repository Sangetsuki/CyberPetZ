#ifndef MONSTER_H_GUARD
#define MONSTER_H_GUARD

// TODO: A good class
class Monster {
public:
  Monster();
  Monster(Monster &&) = default;
  Monster(const Monster &) = default;
  Monster &operator=(Monster &&) = default;
  Monster &operator=(const Monster &) = default;
  ~Monster();

  // private:
  unsigned int healthy;
  unsigned int hungry;
  unsigned int thirsty;
  unsigned int dirty;
  unsigned int age;
  unsigned int happy;
};

#endif // !MONSTER_H_GUARD
