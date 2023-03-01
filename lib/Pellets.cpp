#include "Pellets.hpp"
#include <algorithm>


namespace pacman {

Pellets::Pellets()
  : positions(initialPelletPositions()) {}

bool Pellets::isPellet(GridPosition p) const {
 auto gridPositionIT = std::find(positions.begin(), positions.end(), p);
 return(gridPositionIT != positions.end());
}

bool Pellets::eatPelletAtPosition(GridPosition p) {
    // for(auto it = positions.begin(); it != positions.end(); ++it) {
    //     if(*it == p) {
    //         positions.erase(it);
    //         return true;
    //     }
    // }
    // return false;
    auto gridPositionIT = std::find(positions.begin(), positions.end(), p);
 if(gridPositionIT != positions.end()){
positions.erase(gridPositionIT);
return true;
 }
 return false;
}

} // namespace pacman
