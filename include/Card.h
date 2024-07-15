#ifndef CARD_H
#define CARD_H

#include <ostream>

typedef uint64_t value;

enum class Suit : value { club, diamond, heart, spade };
enum class Value : value { ace = 1, jack = 11, queen, king };

class Card {
 public:
  Card(const Suit suit, const value val) : _suit(suit), _val(val) {}
  Suit &suit() { return _suit; }
  [[nodiscard]] Suit const &suit() const { return _suit; }
  value &val() { return _val; }
  [[nodiscard]] value const &val() const { return _val; }
  friend std::ostream &operator<<(std::ostream &strm, const Card &card);
  friend bool operator<(const Card &lhs, const Card &rhs);

 private:
  Suit _suit;
  value _val;
};

#endif // CARD_H
