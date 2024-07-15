#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Card.hpp"
#include "Table.hpp"

#include <algorithm>
#include <vector>

class Player {
 public:
  std::vector<Card> &cards() { return _hole_cards; }
  [[nodiscard]] std::vector<Card> const &cards() const { return _hole_cards; }
  void find_hand(const Table &table);

 private:
  std::vector<Card> _hole_cards;
  std::vector<Card> _known;
};

inline void Player::find_hand(const Table &table) {
  _known.clear();
  _known.reserve(7);
  _known = _hole_cards;
  _known.insert(_known.end(), table.cards().begin(), table.cards().end());
  std::sort(_known.begin(), _known.end());
}

#endif // PLAYER_HPP
