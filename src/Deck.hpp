#ifndef DECK_HPP
#define DECK_HPP

#include "Player.hpp"
#include "Table.hpp"

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

class Deck {
 public:
  Deck();
  Deck &operator=(const Deck &rhs);
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

inline Deck::Deck() {
  for (auto suit :
       std::vector{Suit::club, Suit::diamond, Suit::heart, Suit::spade}) {
    for (auto val = 1; val < 14; ++val) {
      _cards.emplace_back(suit, val);
    }
  }
  _it = _cards.begin();
}

inline Deck &Deck::operator=(const Deck &rhs) {
  if (this != &rhs) {
    this->_cards = rhs._cards;
    _it = _cards.end() - 1;
  }
  return *this;
}

inline void Deck::shuffle() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::ranges::shuffle(_cards, mt);
}

inline Card Deck::deal() {
  assert(_it != _cards.end());
  const Card card = *_it;
  ++_it;
  return card;
}

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
  for (auto i = 0; i < n_cards; ++i) {
    table->cards().emplace_back(this->deal());
  }
  ++table->phase();
}

#endif // DECK_HPP
