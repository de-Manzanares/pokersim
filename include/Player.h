#ifndef PLAYER_H
#define PLAYER_H

#include "Table.h"
#include <vector>

class Table;

class Player {
 public:
  std::vector<Card> &cards() { return _hole_cards; }
  [[nodiscard]] std::vector<Card> const &cards() const { return _hole_cards; }
  void find_hand(const Table &table);

 private:
  std::vector<Card> _hole_cards;
  std::vector<Card> _known;
};

#endif // PLAYER_H
