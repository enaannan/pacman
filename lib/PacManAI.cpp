#include "PacManAI.hpp"

#include "Board.hpp"
#include "Random.hpp"
#include <iostream>

namespace pacman {

void PacManAI::reset() {
  pos = {};
  suggested_direction = Direction::RIGHT;
}

// This function is not yet implemented.
// You will implement it as part of module 24.
GridPosition PacManAI::pelletClosestToPacman(GridPosition pacmanGridPosition  [[maybe_unused]],
                                             std::vector<GridPosition> & pellets [[maybe_unused]]) {
  
   GridPosition closestPellet ={0,0};
  double closestDistance = std::numeric_limits<double>::infinity();
 

  for(const auto & pellet : pellets){
    const auto distance = positionDistance(pacmanGridPosition, pellet);
  if (distance < closestDistance) {
    closestPellet = pellet;
    closestDistance = distance;
  }
  }
  
  return closestPellet;
}

// This function is not yet implemented.
// You will implement it as part of module 21.
bool PacManAI::isValidMove(const Move & move [[maybe_unused]]) {
  if(move.direction == oppositeDirection(suggested_direction))
  return false;

  return isWalkableForPacMan(move.position);
}

// This function is not yet implemented.
// You will implement it as part of module 21. and 24.
Direction PacManAI::optimalDirection(const std::array<Move, 4> & moves [[maybe_unused]]) {
double shortestDistance =  std::numeric_limits<double>::infinity();
Direction optimalDirection = Direction::LEFT;

for (const auto move : moves){
 if (move.distanceToTarget < shortestDistance){
  shortestDistance = move.distanceToTarget;
  optimalDirection= move.direction;
 }
}
return optimalDirection;
}

// This function is not yet implemented.
// You will implement it as part of module 25.
Direction PacManAI::chooseNewDirectionForPacMan(const PacMan & pacMan [[maybe_unused]],
                                               const Pellets & pellets [[maybe_unused]]) {

  const GridPosition pacManGridPos = pacMan.positionInGrid();
  auto pelletPositions = pellets.allPellets();
  if (pelletPositions.empty()) {
    return Direction::NONE;
  }

  const GridPosition targetPos = pelletClosestToPacman(pacManGridPos, pelletPositions);

  const GridPosition currentPosition = pacMan.positionInGrid();
  const auto [x, y] = currentPosition;
  std::array<Move, 4> possibleMoves = {
    Move{ Direction::UP, { x, y - 1 } },
    Move{ Direction::LEFT, { x - 1, y } },
    Move{ Direction::DOWN, { x, y + 1 } },
    Move{ Direction::RIGHT, { x + 1, y } }
  };

  for (auto & move : possibleMoves) {
    if (!isValidMove(move))
      continue;
    move.distanceToTarget = positionDistance(move.position, targetPos);
  }
  return optimalDirection(possibleMoves);
}

void PacManAI::update(const PacMan & pacMan, const Pellets & pellets [[maybe_unused]]) {

  const GridPosition pacManGridPos = pacMan.positionInGrid();
  const GridPosition currentGridPos = positionToGridPosition(pos);

  if (!isIntersection(pacManGridPos) || currentGridPos == pacManGridPos) {
    return;
  }

  suggested_direction = chooseNewDirectionForPacMan(pacMan, pellets);
  pos = pacMan.position();
}
} // namespace pacman
