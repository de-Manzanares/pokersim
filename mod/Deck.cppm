module;

#include <stdexcept>
#include <vector>

export module Deck;
export import Card;

export class Deck {
 public:
  Deck();
  std::vector<Card> &cards() { return _cards; }
  Card top(); ///< return and consume the top card

 private:
  std::vector<Card> _cards;
  std::vector<Card>::iterator _top;
};

Deck::Deck() {
  for (int i = 0; i < 4; ++i) {
    for (int j = 1; j < 14; ++j) {
      _cards.emplace_back(j, static_cast<Suit>(i));
    }
  }
  _top = _cards.begin();
}

Card Deck::top() {
  if (_top == _cards.end()) {
    throw std::out_of_range("Trying to deal from an empty deck.");
  }
  Card const card = *_top;
  ++_top;
  return card;
}
