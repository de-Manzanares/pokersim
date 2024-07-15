#include "Player.h"

#include <algorithm>

void Player::find_hand(const Table &table) {
  _known.clear();
  _known.reserve(7);
  _known = _hole_cards;
  _known.insert(_known.end(), table.cards().begin(), table.cards().end());
  std::sort(_known.begin(), _known.end());
}
