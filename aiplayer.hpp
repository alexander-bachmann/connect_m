/*
AI_Player

	boolean isTurn
	int takeTurn(vector[][]) - returns an int of the selected column - set !isTurn
		- will call other methods such as alpha-beta pruning methods
*/


/*
create tree for game state - tree is rebuilt after each move
tree is generated by placing a tile in all possible slots

maybe may tree all nodes just ints - indicating the number of possible winning paths
  node(int depth, vector game_board, ....), pass the game_board down through the tree.. USE THE SAME GAME_STATE VECTOR


every node will have n children
make move in vector then revert moves as the tree is traversed back upwards

each layer of depth does the same thing
board_state 4 x 4 board
  - 4 game states - 1 state for each tile selected - (turn 1)
    - 4 * 4 game states - 4 options for each possible choices from turn 1 - (turn 2)
      - 4 * 4 * 4 game states
        - etc

must decide how deep - only moving a few levels down in the game tree would be faster but likely will result in a weaker move than if allowed to explore for a longer period of time

a < b - no pruning

*/


/*

TO DO

create a general tree structure to simply hold the evaluation int's

void generate_tree(depth) - depth determines the size and number of children for the tree
  given board dimension aka n = 4, and depth = 3
    current game_board will have 4 children, those children will each have 4 children, and those children will each have 4 children

    meaning that there will be at most 4 * 4 * 4 = 64 game_boards that need to be analyzed


heuristic_evaluation() - count the number of possible winning paths based on that move and check if a move results in a winning state for either player

max() --- simple max function

min() --- simple min function

minimax() - minimizing the possible loss for a worst case (maximum loss) scenario.
initial call: minimax(game_board, 3, true) //make a decision looking 3 turns in the future based off current game_board, and it's true that it is AI's turn when minimax is called


int minimax(vector[][] game_board, int depth, bool maximizing_player)
    if depth == 0 || is_game_over in game_board
      return static evaluation of game_board -- CALL heuristic_evaluation() HERE - must factor in whose turn it is when counting, probably just base it off player_one_turn

    if maximizing_player (is AIs turn to move)
      max_eval = -INF
      for each child (all future game_boards one turn from now, stemming from current game_board) - columns 1 through N
        //this is where piece is placed in each successive column

        eval = minimax(child_game_board, depth - 1, false)
        max_eval = max_value(max_eval, eval)

        //this is where previous piece is popped

      return max_eval


    else (is human's turn to move)
      min_eval = +INF
      for each child (all future game_boards one turn from now, stemming from current game_board)
        //this is where piece is placed in each sucessive column

        eval = minimax(child_game_board, depth - 1, true)
        min_eval = min(minEval, eval)

        //this is where previous piece is popped

      return min_eval
*/
