#include "Player.h"

#include <algorithm>
#include <numeric>

void Player::find_hand(const Table &table) {
  count_cards(&table);
  if (find_royal_flush()) { // NOLINT
  } else if (find_straight_flush()) {
  } else if (find_four_oak()) {
  } else if (find_full_house()) {
  } else if (find_flush()) {
  } else if (find_straight()) {
  } else if (find_three_oak()) {
  } else if (find_two_pair()) {
  } else if (find_one_pair()) {
  } else if (find_high_card()) {
  }
}

// TODO rewrite searches to use _card_list_Values

void Player::count_cards(const Table *table) {
  _card_list_Suit.clear();
  _card_list_Suit = std::vector(4, std::vector<value>(13, 0));
  _card_list_Values.clear();
  _card_list_Values = std::vector<value>(13, 0);

  std::vector<Card> known = _hole_cards;
  known.insert(known.end(), table->cards().begin(), table->cards().end());

  for (const auto &card : known) {
    _card_list_Suit[static_cast<value>(card.suit())][card.val() - 1] += 1;
    _card_list_Values[card.val() - 1] += 1;
  }
}

bool Player::find_royal_flush() {
  bool found = false;
  // 10, jack, king, queen, ace, all of same suit
  for (std::size_t suit = 0; suit < 4 && !found; ++suit) {
    if (_card_list_Suit[suit][10 - 1] == 1 &&
        _card_list_Suit[suit][static_cast<value>(Value::jack) - 1] == 1 &&
        _card_list_Suit[suit][static_cast<value>(Value::queen) - 1] == 1 &&
        _card_list_Suit[suit][static_cast<value>(Value::king) - 1] == 1 &&
        _card_list_Suit[suit][static_cast<value>(Value::ace) - 1] == 1) {
      found = true;
      ++_hands.royal_flush;
      // TODO 2,3x counting... what if we hit a royal flush on the flop?
    }
  }
  return found;
}

bool Player::find_straight_flush() {
  bool found = false;
  // TODO more efficient recognition algorithm
  // any five consecutive values of the same suit
  for (std::size_t suit = 0; suit < 4; ++suit) {
    for (auto val = static_cast<value>(Value::king); val > 5 && !found; --val) {
      if (_card_list_Suit[suit][val - 1] == 1 &&
          _card_list_Suit[suit][val - 2] == 1 &&
          _card_list_Suit[suit][val - 3] == 1 &&
          _card_list_Suit[suit][val - 4] == 1 &&
          _card_list_Suit[suit][val - 5] == 1) {
        ++_hands.straight_flush;
        found = true;
        // TODO 2,3x counting... what if we hit a straight flush on the flop?
      }
    }
  }
  return found;
}

bool Player::find_four_oak() {
  bool found = false;
  // TODO more efficient recognition algorithm
  // four of the same value
  for (auto card_val = Value::ace; card_val > Value::four && !found;
       --card_val) {
    if (_card_list_Suit[static_cast<value>(Suit::club)]
                       [static_cast<value>(card_val)] == 1 &&
        _card_list_Suit[static_cast<value>(Suit::diamond)]
                       [static_cast<value>(card_val)] == 1 &&
        _card_list_Suit[static_cast<value>(Suit::heart)]
                       [static_cast<value>(card_val)] == 1 &&
        _card_list_Suit[static_cast<value>(Suit::spade)]
                       [static_cast<value>(card_val)] == 1) {
      found = true;
      ++_hands.four_oak;
    }
  }
  return found;
}

bool Player::find_full_house() {
  bool found = false;
  bool found_3 = false;
  bool found_2 = false;
  Value skip_val{};
  // TODO more efficient recognition algorithm
  // three of the same value and two of another value
  std::vector<std::vector<Suit>> suit_3 = {
      {Suit::club, Suit::diamond, Suit::heart},
      {Suit::spade, Suit::diamond, Suit::heart},
      {Suit::club, Suit::spade, Suit::heart},
      {Suit::club, Suit::diamond, Suit::spade},
  };
  std::vector<std::vector<Suit>> suit_2 = {
      {Suit::club, Suit::diamond},  {Suit::club, Suit::heart},
      {Suit::club, Suit::spade},    {Suit::diamond, Suit::heart},
      {Suit::diamond, Suit::spade}, {Suit::heart, Suit::spade},
  };
  // flag the 3 values and skip them in the 2 search
  for (auto card_val = Value::ace; card_val > Value::three && !found_3;
       --card_val) {
    for (const auto &combo : suit_3) {
      if (_card_list_Suit[static_cast<value>(combo[0])]
                         [static_cast<value>(card_val)] == 1 &&
          _card_list_Suit[static_cast<value>(combo[1])]
                         [static_cast<value>(card_val)] == 1 &&
          _card_list_Suit[static_cast<value>(combo[2])]
                         [static_cast<value>(card_val)] == 1) {
        found_3 = true;
        skip_val = card_val;
      }
    }
  }
  for (auto card_val = Value::ace; card_val > Value::two && found_3 && !found_2;
       --card_val) {
    for (const auto &combo : suit_2) {
      if (card_val != skip_val) {
        if (_card_list_Suit[static_cast<value>(combo[0])]
                           [static_cast<value>(card_val)] == 1 &&
            _card_list_Suit[static_cast<value>(combo[1])]
                           [static_cast<value>(card_val)] == 1) {
          found_2 = true;
        }
      }
    }
  }
  if (found_3 && found_2) {
    found = true;
    ++_hands.full_house;
  }
  return found;
}

bool Player::find_flush() {
  bool found = false;
  // five cards of the same suit
  for (auto suit = 0; suit < 4; ++suit) {
    if (std::accumulate(_card_list_Suit[suit].begin(),
                        _card_list_Suit[suit].end(), value{0}) >= value{5}) {
      found = true;
      ++_hands.flush;
    }
  }
  return found;
}
// TODO ace is both 1 and 14 ...

// TODO rethink loop limits, are we checking everything?

bool Player::find_straight() {
  bool found = false;
  for (auto card_val = Value::ace; card_val > Value::four && !found;
       --card_val) {
    if (card_val == Value::ace) {
      if (_card_list_Values[static_cast<value>(card_val) - 1] > 0 &&
          _card_list_Values[static_cast<value>(Value::king) - 1] > 0 &&
          _card_list_Values[static_cast<value>(Value::queen) - 1] > 0 &&
          _card_list_Values[static_cast<value>(Value::jack) - 1] > 0 &&
          _card_list_Values[static_cast<value>(Value::ten) - 1] > 0) {
        found = true;
        ++_hands.straight;
      }
    } else if (_card_list_Values[static_cast<value>(card_val) - 1] > 0 &&
               _card_list_Values[static_cast<value>(card_val) - 2] > 0 &&
               _card_list_Values[static_cast<value>(card_val) - 3] > 0 &&
               _card_list_Values[static_cast<value>(card_val) - 4] > 0 &&
               _card_list_Values[static_cast<value>(card_val) - 5] > 0) {
      found = true;
      ++_hands.straight;
    }
  }
  return found;
}

bool Player::find_three_oak() {
  bool found = false;
  for (int i = 12; i >= 0 && !found; --i) {
    if (_card_list_Values[i] >= 3) {
      found = true;
      ++_hands.three_oak;
    }
  }
  return found;
}

bool Player::find_two_pair() {
  bool found = false;
  bool found_1 = false;
  bool found_2 = false;
  int skip_val{};
  for (int i = 12; i >= 0 && !found_1; --i) {
    if (_card_list_Values[i] == 2) {
      found_1 = true;
      skip_val = i;
    }
  }
  for (int i = 12; i >= 0 && !found_2; --i) {
    if (i != skip_val) {
      if (_card_list_Values[i] == 2) {
        found_2 = true;
      }
    }
  }
  if (found_1 && found_2) {
    found = true;
    ++_hands.two_pair;
  }
  return found;
}

bool Player::find_one_pair() {
  bool found = false;
  for (int i = 12; i >= 0 && !found; --i) {
    if (_card_list_Values[i] == 2) {
      found = true;
      ++_hands.one_pair;
    }
  }
  return found;
}

bool Player::find_high_card() {
  bool found = false;
  if (_card_list_Values[static_cast<value>(Value::ace) - 1] == 1) {
    found = true;
    ++_hands.high_card;
  } else {
    for (int i = 12; i > 0 && !found; --i) {
      if (_card_list_Values[i] == 1) {
        found = true;
        ++_hands.high_card;
      }
    }
  }
  return found;
}

std::ostream &Player::print_report(std::ostream &strm, const Player *player) {
  // TODO separate flop, turn, river
  strm << "Royal flush     : " << player->_hands.royal_flush << '\n';
  strm << "Straight flush  : " << player->_hands.straight_flush << '\n';
  strm << "Four of a kind  : " << player->_hands.four_oak << '\n';
  strm << "Full house      : " << player->_hands.full_house << '\n';
  strm << "Flush           : " << player->_hands.flush << '\n';
  strm << "Straight        : " << player->_hands.straight << '\n';
  strm << "Three of a kind : " << player->_hands.three_oak << '\n';
  strm << "Two pair        : " << player->_hands.two_pair << '\n';
  strm << "One pair        : " << player->_hands.one_pair << '\n';
  strm << "High card       : " << player->_hands.high_card << std::endl;
  return strm;
}
