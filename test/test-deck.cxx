#include <catch2/catch_all.hpp>
#include <iostream>
#include <random>

import Deck;

TEST_CASE("bruh") {
  std::cout << "Size of `std::vector<Card>::iterator`: "
            << sizeof(std::vector<Card>::iterator) << '\n';
  try {
    Deck deck;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::ranges::shuffle(deck.cards(),mt);
    for (int i = 0; i < 53; ++i) {
      std::cout << deck.top() << '\n';
    }
  } catch (std::out_of_range &err) {
    std::cout << err.what() << '\n';
  }
}
