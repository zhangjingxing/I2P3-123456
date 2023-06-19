#include <cstdlib>
#include <climits>

#include "../state/state.hpp"
#include "./value_player.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move value_player::get_move(State *state){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int bestvalue = INT_MIN;
  Move bestmove;

  for(auto act : actions)
  {
    State* new_state = state->next_state(act);
    int value = new_state->evaluate();

    if(value > bestvalue)
    {
        bestvalue = value;
        bestmove = act;
    }

  }

  return bestmove;
}