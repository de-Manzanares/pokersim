#ifndef TABLE_H
#define TABLE_H

#include "Card.h"
#include "Player.h"
#include <vector>

class Player;

enum class Phase : value { flop, turn, river };

inline Phase &operator++(Phase &p) {
  if (p == Phase::river) {
    p = Phase::flop;
  } else {
    p = static_cast<Phase>(static_cast<value>(p) + 1);
  }
  return p;
}

class Table {
 public:
  explicit Table(std::size_t player_count);
  std::vector<Player> &opponents() { return _opponents; }
  [[nodiscard]] std::vector<Player> const &opponents() const;
  std::vector<Card> &cards() { return _community_cards; }
  [[nodiscard]] std::vector<Card> const &cards() const;
  Phase &phase() { return _phase; }
  [[nodiscard]] Phase const &phase() const { return _phase; }

 private:
  std::vector<Card> _community_cards;
  std::vector<Player> _opponents;
  Phase _phase;
};

#endif // TABLE_H
