#include "Table.h"

#include <vector>

Table::Table(const std::size_t player_count) {
  for (std::size_t i = 0; i < player_count; ++i) {
    _opponents.emplace_back();
  }
  _phase = Phase::flop;
}

std::vector<Player> const &Table::opponents() const { return _opponents; }

std::vector<Card> const &Table::cards() const { return _community_cards; }
