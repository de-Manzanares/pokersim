#ifndef INCLUDE_DECK_H_
#define INCLUDE_DECK_H_

#include "Card.h"
#include "Player.h"
#include <vector>

class Deck {
 public:
  Deck();
  void shuffle();
  Card deal();
  template <typename T> void deal_to(T *);
  std::size_t size() { return _cards.size() - (_it - _cards.begin()); }
  std::vector<Card> &cards() { return _cards; }
  [[nodiscard]] std::vector<Card> const &cards() const { return _cards; }

 private:
  std::vector<Card> _cards;
  std::vector<Card>::iterator _it;
};

template <typename T> void Deck::deal_to(T *) {
  static_assert(std::is_same_v<T, Player> ||
                std::is_same_v<T, std::vector<Player>> ||
                std::is_same_v<T, Table>);
}

template <> inline void Deck::deal_to<Player>(Player *player) {
  for (auto i = 0; i < 2; ++i) {
    player->cards().emplace_back(this->deal());
    _cards.erase(_cards.begin());
  }
}

template <>
inline void Deck::deal_to<std::vector<Player>>(std::vector<Player> *players) {
  for (auto &player : *players) {
    for (auto i = 0; i < 2; ++i) {
      player.cards().emplace_back(this->deal());
    }
  }
}

template <> inline void Deck::deal_to<Table>(Table *table) {
  std::size_t n_cards;
  table->phase() == Phase::flop ? n_cards = 3 : n_cards = 1;
  for (std::size_t i = 0; i < n_cards; ++i) {
    table->cards().emplace_back(this->deal());
  }
  ++table->phase();
}

#endif // INCLUDE_DECK_H_
