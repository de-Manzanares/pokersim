#include "Card.h"
#include <ostream>

std::ostream &operator<<(std::ostream &strm, const Suit &suit) {
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

std::ostream &operator<<(std::ostream &strm, const Card &card) {
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

bool operator<(const Card &lhs, const Card &rhs) {
  return lhs.val() < rhs.val();
}
