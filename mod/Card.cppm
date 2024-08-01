module;

#include <map>
#include <ostream>

export module Card;

export enum class Suit { club, diamond, heart, spade };

export enum class FaceValue { T = 10, J, Q, K, A };

std::map<int, char> card_val_to_char{
    {1, 'A'}, {10, 'T'}, {11, 'J'}, {12, 'Q'}, {13, 'K'}, {14, 'A'},
};

std::map<Suit, char> suit_to_char{
    {Suit::club, 'c'},
    {Suit::diamond, 'd'},
    {Suit::heart, 'h'},
    {Suit::spade, 's'},
};

export class Card {
 public:
  explicit Card(int const value, Suit const suit)
      : _value{value}, _suit{suit} {}
  [[nodiscard]] int value() const { return _value; }
  [[nodiscard]] Suit suit() const { return _suit; }
  friend std::ostream &operator<<(std::ostream &os, Card const &card);

 private:
  int const _value;
  Suit const _suit;
};

std::ostream &operator<<(std::ostream &os, Card const &card) {
  if (card._value > 9 || card._value == 1) {
    os << card_val_to_char[card._value];
  } else {
    os << std::to_string(card._value);
  }
  os << suit_to_char[card._suit];
  return os;
}
