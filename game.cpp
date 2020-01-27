#include "game.hpp"

Game::Game(int n, int m)
{
  set_n(n);
  set_m(m);
  this->game_over = false;
  this->player_one_turn = true;
}

void Game::generate_board()
{
  std::cout << "Generating board..." << std::endl;

  //resizing the board based off of n
  this->game_board.resize(this->n);
  for(long unsigned int i = 0; i < this->game_board.size(); ++i)
  {
    this->game_board[i].resize(this->n);
  }

  //populating the board with filler 0s
  for(int i = 0; i < this->n; ++i)
  {
    for(int j = 0; j < this->n; ++j)
    {
      this->game_board[i][j] = 0;
    }
  }
}

void Game::print_board()
{
  std::string board_state;

  board_state.append("\n");

  for(int i = 0; i < this->n; ++i)
  {
    for(int j = 0; j < this->n; ++j)
    {
      board_state.append("+---");
    }
    board_state.append("+");
    board_state.append("\n");

    for(int j = 0; j < this->n; ++j)
    {
      board_state.append("| ");

      if(this->game_board[i][j] == 1)
      {
          board_state.append("X");
      }
      else if(this->game_board[i][j] == 2)
      {
        board_state.append("O");
      }
      else
      {
        board_state.append("_");
      }

      board_state.append(" ");
    }
    board_state.append("|");
    board_state.append("\n");
  }

  for(int j = 0; j < this->n; ++j)
  {
    board_state.append("+---");
  }
  board_state.append("+");
  board_state.append("\n");

  std::cout << board_state << std::endl;
}

void Game::print_int_board()
{
  for(int i = 0; i < this->n; ++i)
  {
    for(int j = 0; j < this->n; ++j)
    {
        std::cout << this->game_board[i][j] << " ";
    }

    std::cout << std::endl;
  }
}

bool Game::is_game_over()
{
  if(this->num_disks == (this->n * this-> n))
  {
    return true;
  }

  return this->game_over;
}

bool Game::check_vertical_win(int j)
{
  int consectutive = 1;

  for(int i = this->i; i <= this->n-1; ++i)
  {
    if(i != this->n - 1)
    {
      if(this->game_board[i][j] == this->game_board[i+1][j])
      {
        consectutive++;

        if(consectutive == this->m)
        {
          return true;
        }
      }
      else
      {
        return false;
      }
    }
  }

  return false;
}

bool Game::check_horizontal_win(int j)
{
  int current_column = j;
  int consectutive = 1;

  for(int left_j = current_column; left_j >= 0; --left_j)
  {
    //std::cout << "[" << this->i << ", " << left_j << "] checked" << std::endl;
    for(int right_j = left_j + 1; right_j < this->n; right_j++)
    {
      //std::cout << "[" << this->i << ", " << right_j << "] checked" << std::endl;
      if(this->game_board[this->i][left_j] == this->game_board[this->i][right_j] && this->game_board[this->i][left_j] != 0)
      {
        consectutive++;
        //std::cout << consectutive << std::endl;
        if(consectutive == this->m)
        {
          return true;
        }
      }
      else
      {
        break;
      }
    }
    consectutive = 1;
  }

  return false;
}

bool Game::check_diagonal_win(int j)
{
  int current_column = j;
  int current_row;
  int consectutive = 1;

  //diagonally bottom right
  for(int i = this->i; i > 0; --i)
  {
    current_row = i;

    for(int j = current_column; j < this->n - 1; ++j)
    {
      if(current_row + 1 < this-> n && j < this->n)
      {
        //std::cout << "Compared [" << current_row << ", " << j << "] with [" << current_row + 1 << ", " << j + 1 << "]" << std::endl;
        if(this->game_board[current_row][j] == this->game_board[current_row + 1][j + 1] && this->game_board[current_row][j] != 0)
        {
          ++consectutive;
          ++current_row;

          if(consectutive == this->m)
          {
            //std::cout << "You won diagonally to the bottom right!" << std::endl;
            return true;
          }
        }
        else
        {
          break;
        }
      }
    }
    --current_column;
    consectutive = 1;
  }

  consectutive = 1;
  current_column = j;

  //diagonally bottom left
  for(int i = this->i; i > 0; --i)
  {
    current_row = i;

    for(int j = current_column; j >= 0; --j)
    {
      if(current_row + 1 < this-> n && j < this->n)
      {
        //std::cout << "Compared [" << current_row << ", " << j << "] with [" << current_row + 1 << ", " << j - 1 << "]" << std::endl;
        if(this->game_board[current_row][j] == this->game_board[current_row + 1][j - 1] && this->game_board[current_row][j] != 0)
        {
          ++consectutive;
          ++current_row;

          if(consectutive == this->m)
          {
            //std::cout << "You won diagonally to the bottom left!" << std::endl;
            return true;
          }
        }
        else
        {
          break;
        }
      }
    }
    ++current_column;
    consectutive = 1;
  }

  return false;
}

bool Game::check_all_wins(int j)
{
  if(check_vertical_win(j) == true)
  {
    std::cout << "You win vertically!" << std::endl;
    return true;
  }
  else if(check_horizontal_win(j) == true)
  {
    std::cout << "You win horizontally!" << std::endl;
    return true;
  }
  else if(check_diagonal_win(j) == true)
  {
    std::cout << "You win diagonally!" << std::endl;
    return true;
  }

  return false;
}

void Game::add_disk_to_column(int j)
{
  //so normies do not have to use 0 as first column
  --j;

  if(j >= 0 && j < this->n)
  {
    for(int i = this->n-1; i >= 0; --i)
    {
      if(this->game_board[i][j] == 0)
      {
        if(player_one_turn == true)
        {
          this->game_board[i][j] = 1;
          player_one_turn = !player_one_turn;
          this->num_disks++;
          this->i = i;

          if(check_all_wins(j) == true)
          {
            this->game_over = true;
            return;
          }
          break;
        }
        else
        {
          this->game_board[i][j] = 2;
          player_one_turn = !player_one_turn;
          this->num_disks++;
          this-> i = i;

          if(check_all_wins(j) == true)
          {
            this->game_over = true;
            return;
          }
          break;
        }
      }
    }
  }
  else
  {
    std::cout << "Invalid column: out of range" << std::endl;
  }

}

void Game::set_n(int n)
{
  if(n >= 3 && n <= 10)
  {
    this->n = n;
  }
  else
  {
    int new_n = 0;

    std::cout << "Enter valid 'n' (3 - 10): ";
    std::cin >> new_n;
    std::cout << std::endl;

    set_n(new_n);
  }
}

void Game::set_m(int m)
{
  if(m > 1 &&  m <= this->n)
  {
    this->m = m;
  }
  else
  {
    int new_m = 0;

    std::cout << "Please enter valid 'm' (2 - n): ";
    std::cin >> new_m;
    std::cout << std::endl;

    set_m(new_m);
  }
}



/*
privatize methods that are only ever called within the class (win checks)

getters and setters for:

int num_disks;
bool player_one_turn;

vector<vector<int>> game_board;
*/
