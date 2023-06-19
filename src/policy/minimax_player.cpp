#include <cstdlib>
#include <climits>
#include "../state/state.hpp"
#include "./minimax_player.hpp"
using namespace std;

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move minimax_player::get_move(State *state, int depth)
{
  state->get_legal_actions();
  Move bestMove;
  int bestValue = INT_MIN;

  for(const auto &act : state->legal_actions)
  {
    State* childState = state->next_state(act);
    int value = minimax(childState, depth-1, false, INT_MIN, INT_MAX);

    if (value > bestValue)
    {
      bestValue = value;
      bestMove = act;
    }
  }

  return bestMove;
}

int minimax_player::minimax(State* node, int depth, bool maximizingPlayer, int alpha, int beta)
{
  if(depth == 0 ||node->legal_actions.empty())
  {
    return node->evaluate();
  }

  if(maximizingPlayer)
  {
    int bestValue = INT_MIN;
    node->get_legal_actions();

    for(const auto& act : node->legal_actions)
    {
      State *childNode = node->next_state(act);
      int value = minimax(childNode, depth-1, false, alpha, beta);
      bestValue = max(bestValue, value);

    }

    return bestValue;
  }

  else
  {
    int bestValue = INT_MAX;
    node->get_legal_actions();

    for(const auto& act : node->legal_actions)
    {
      State *childNode = node->next_state(act);
      int value = minimax(childNode, depth-1, true, alpha, beta);
      bestValue = min(bestValue, value);

    }

    return bestValue;
  }
};