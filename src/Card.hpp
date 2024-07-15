#ifndef CARD_HPP
#define CARD_HPP
#include <cstdint>
#include <ostream>

typedef uint64_t value;

enum class Suit : value { club, diamond, heart, spade };
enum class Value : value { ace = 1, jack = 11, queen, king };

inline std::ostream &operator<<(std::ostream &strm, const Suit &suit) {
  switch (suit) {
  case Suit::club:
    strm << 'c';
    break;
  case Suit::diamond:
    strm << 'd';
    break;
  case Suit::heart:
    strm << 'h';
    break;
  case Suit::spade:
    strm << 's';
    break;
  }
  return strm;
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

inline std::ostream &operator<<(std::ostream &strm, const Card &card) {
  if (card.val() > 1 && card.val() < 11) {
    strm << card.val();
  } else {
    switch (card.val()) {
    case static_cast<value>(Value::jack):
      strm << 'J';
      break;
    case static_cast<value>(Value::queen):
      strm << 'Q';
      break;
    case static_cast<value>(Value::king):
      strm << 'K';
      break;
    case static_cast<value>(Value::ace):
      strm << 'A';
      break;
    default:;
    }
  }
  strm << card.suit();
  return strm;
}

inline bool operator<(const Card &lhs, const Card &rhs) {
  return lhs.val() < rhs.val();
}

#endif // CARD_HPP
