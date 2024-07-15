#include "Deck.h"
#include "Table.h"
#include <iostream>

int main() {
  constexpr std::size_t SIM_SIZE = 1;
  constexpr std::size_t N_OPPONENTS = 3;

  Deck deck;
  Player player;
  Table table(N_OPPONENTS); // N opponents at the table

  deck.shuffle();
  deck.deal_to(&player); // hole cards
  Deck deck_copy = deck;

  for (std::size_t i = 0; i < SIM_SIZE; ++i) {
    deck.deal_to(&table.opponents()); // deal to opponents
    deck.deal_to(&table);             // deal the flop
    player.find_hand(table);          // record player hand
    deck.deal_to(&table);             // deal the turn
    player.find_hand(table);          // record player hand
    deck.deal_to(&table);             // record player hand
    player.find_hand(table);          // deal the river
    // TODO clever deck-reuse
    // TODO reset deck when empty
  }

  Player::print_report(std::cout, &player);

  return 0;
}
