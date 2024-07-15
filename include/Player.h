#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_

#include "Table.h"
#include <vector>

class Table;

struct Hands {
  value royal_flush{};
  value straight_flush{};
  value four_oak{};
  value full_house{};
  value flush{};
  value straight{};
  value three_oak{};
  value two_pair{};
  value one_pair{};
  value high_card{};
};

class Player {
 public:
  std::vector<Card> &cards() { return _hole_cards; }
  [[nodiscard]] std::vector<Card> const &cards() const { return _hole_cards; }
  void find_hand(const Table &table);
  static std::ostream &print_report(std::ostream &strm, const Player *player);

 private:
  std::vector<Card> _hole_cards;
  std::vector<std::vector<value>> _card_list_Suit;
  std::vector<value> _card_list_Values;
  Hands _hands;
  void count_cards(const Table *table);
  bool find_royal_flush();
  bool find_straight_flush();
  bool find_four_oak();
  bool find_full_house();
  bool find_flush();
  bool find_straight();
  bool find_three_oak();
  bool find_two_pair();
  bool find_one_pair();
  bool find_high_card();
};

#endif // INCLUDE_PLAYER_H_
