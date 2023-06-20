#include <cstdlib>
#include <climits>
#include "../state/state.hpp"
#include "./alphabeta.hpp"
using namespace std;

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int alphabeta::pruning(State* node, int depth, int alpha, int beta, bool maximizingPlayer)
{
  if(depth == 0 ||node->legal_actions.empty())
  {
    return node->evaluate();
  }

  if(maximizingPlayer)
  {
    int bestValue = INT_MIN;
    if(!node->legal_actions.size())
    node->get_legal_actions();

    for(const auto& act : node->legal_actions)
    {
      State *childNode = node->next_state(act);
      int value = pruning(childNode, depth-1, alpha, beta, false);
      bestValue = max(bestValue, value);
      alpha = max(alpha, bestValue);
      if(alpha >= beta)
      {
        break;
      }
    }

    return alpha;
  }

  else
  {
    int bestValue = INT_MAX;
    if(!node->legal_actions.size())
    node->get_legal_actions();

    for(const auto& act : node->legal_actions)
    {
      State *childNode = node->next_state(act);
      int value = pruning(childNode, depth-1, alpha, beta, true);
      bestValue = min(bestValue, value);
      beta = min(beta, bestValue);
      if(alpha >= beta)
      {
        break;
      }
    }

    return beta;
  }
};

Move alphabeta::get_move(State *state, int depth)
{
  if(!state->legal_actions.size())
    state->get_legal_actions();

  Move bestMove;

  if(!state->player)
  {
    int bestValue = INT_MIN;

  for(const auto &act : state->legal_actions)
  {
    State* childState = state->next_state(act);
    int value = pruning(childState, depth-1, INT_MIN, INT_MAX, false);

    if (value > bestValue)
    {
      bestValue = value;
      bestMove = act;
    }
  }
  return bestMove;

  }
  
  else
  {
    int bestValue = INT_MAX;
    for(const auto &act : state->legal_actions)
  {
    State* childState = state->next_state(act);
    int value = pruning(childState, depth-1, INT_MIN, INT_MAX, true);

    if (value < bestValue)
    {
      bestValue = value;
      bestMove = act;
    }
  }
  return bestMove;

  }
}