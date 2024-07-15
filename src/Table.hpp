#ifndef TABLE_H
#define TABLE_H

#include <vector>

class Player;
typedef uint64_t value;

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

inline Table::Table(const std::size_t player_count) {
  for (auto i = 0; i < player_count; ++i) {
    _opponents.emplace_back();
  }
  _phase = Phase::flop;
}

inline std::vector<Player> const &Table::opponents() const {
  return _opponents;
}

inline std::vector<Card> const &Table::cards() const {
  return _community_cards;
}

#endif // TABLE_H
