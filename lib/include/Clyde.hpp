#pragma once

#include "Ghost.hpp"

namespace pacman {

class Clyde final : public Ghost {
public:
  Clyde();
  void setTarget(Position pacManPos);

protected:
  double speed() const override;
  Position initialPosition() const override;

private:
  Position scatterTarget() const;
  static constexpr Position initial_position = { 15.5, 14 };
  static constexpr Position scatter_target = { 0, 30 };
};

} // namespace pacman