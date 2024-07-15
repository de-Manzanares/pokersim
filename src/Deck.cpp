#include "Deck.h"
#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

Deck::Deck() {
  for (auto suit :
       std::vector{Suit::club, Suit::diamond, Suit::heart, Suit::spade}) {
    for (auto val = 1; val < 14; ++val) {
      _cards.emplace_back(suit, val);
    }
  }
  _it = _cards.begin();
}

void Deck::shuffle() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::ranges::shuffle(_cards, mt);
}

Card Deck::deal() {
  assert(_it != _cards.end());
  const Card card = *_it;
  ++_it;
  return card;
}
