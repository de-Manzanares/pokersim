#include <catch2/catch_all.hpp>
#include <iostream>

import Card;

TEST_CASE("bruh") {
  std::vector<Card> cards;
  cards.reserve(52);
  for (int i = 0; i < 4; ++i) {
    for (int j = 1; j < 14; ++j) {
      cards.emplace_back(j, static_cast<Suit>(i));
    }
  }
  for (auto const &card : cards) {
    std::cout << card << '\n';
  }
}
