#ifndef INCLUDE_CARD_H_
#define INCLUDE_CARD_H_

#include <ostream>

typedef uint64_t value;

enum class Suit : value { club, diamond, heart, spade };
enum class Value : value {
  ace = 1,
  two,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine,
  ten,
  jack = 11,
  queen,
  king
};

inline Value &operator--(Value &val) { // NOLINT
  if (val == Value::ace) {
    val = Value::king;
  } else {
    val = static_cast<Value>(static_cast<value>(val) - 1);
  }
  return val;
}

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

#endif // INCLUDE_CARD_H_
