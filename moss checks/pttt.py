import random
import sys
# Defining an empty game board
board = ["_", "_", "_",
         "_", "_", "_",
         "_", "_", "_"]
# Variable which stores the player character
player = ""
# Variable which stores the computer character
comp = ""
# A boolean value that determines if gmae is going on
game_still_going = True
# Variable which stores the winner
winner = None
# variable which tells which playes has the next chance
current_player = "X"

# Functipn to set all varaiables to default value at the start of each game
def reinitialise_var():
  # Defining an empty game board
  global board
  board = ["_", "_", "_",
          "_", "_", "_",
          "_", "_", "_"]
  # Variable which stores the player character
  global player
  player = ""
  # Variable which stores the computer character
  global comp
  comp = ""
  # A boolean value that determines if gmae is going on
  global game_still_going
  game_still_going = True
  # Variable which stores the winner
  global winner
  winner = None
  # variable which tells which playes has the next chance
  global current_player
  current_player = "X"

# function that displays the game board
def display_board():
    print("\n")
    print(board[0] + " | " + board[1] + " | " + board[2] + "     1 | 2 | 3")
    print(board[3] + " | " + board[4] + " | " + board[5] + "     4 | 5 | 6")
    print(board[6] + " | " + board[7] + " | " + board[8] + "     7 | 8 | 9")
    print("\n")

# Function which produces random numbers from 0-8 for the computer's choice
def computer_choice():
    pos = random.randint(0, 8)
    return pos

# Function which handles the user inputs in multiplayer mode
def handle_multi_player_turn(player):
    print(player + "'s turn.")
    position = input("Choose a position from 1-9: ")
    valid = False
    # Run the loop till the user enters a valid input
    while True:
    # Make sure the input is valid
        while True:
            if position in ["1", "2", "3", "4", "5", "6", "7", "8", "9"]:
              break
            position = input("Invalid. Choose a position from 1-9: ")
            
 
    # Get correct index in our board list
        position = int(position) - 1

    # Then also make sure the spot is available on the board
        if (board[position] == "_"):
            valid = True
        else:
            print("That position is already filled")
        if (valid):
           break
    # Change the board character to player character
    board[position] = player
    # Display the changes
    display_board()

# Function to check if game is over 
def check_if_game_over():
    # Check if a player has won the game 
    check_if_win()
    # Check if the games is a tie
    check_if_tie()

# Function to check if a aplayer has one the game
def check_if_win():
    global winner
    # Check if there was a winner anywhere
    row_winner = check_rows()
    column_winner = check_columns()
    diagonal_winner = check_diagonals()
    # Get the winner
    if (row_winner):
        winner = row_winner
    elif (column_winner):
        winner = column_winner
    elif (diagonal_winner):
        winner = diagonal_winner
    else:
        winner = None

# Function to check if there is a row in which all character are same
def check_rows():
  # Set global variables
  global game_still_going
  # Check if any of the rows have all the same value (and is not empty)
  row_1 = board[0] == board[1] == board[2] != "_"
  row_2 = board[3] == board[4] == board[5] != "_"
  row_3 = board[6] == board[7] == board[8] != "_"
  # If any row does have a match, flag that there is a win
  if row_1 or row_2 or row_3:
    game_still_going = False
  # Return the winner
  if (row_1):
    return board[0] 
  elif (row_2):
    return board[3] 
  elif (row_3):
    return board[6] 
  # Or return None if there was no winner
  else:
    return None

# Function to check if there is a row in which all character are same
def check_columns():
  # Set global variables
  global game_still_going
  # Check if any of the columns have all the same value (and is not empty)
  column_1 = board[0] == board[3] == board[6] != "_"
  column_2 = board[1] == board[4] == board[7] != "_"
  column_3 = board[2] == board[5] == board[8] != "_"
  # If any row does have a match, flag that there is a win
  if column_1 or column_2 or column_3:
    game_still_going = False
  # Return the winner
  if column_1:
    return board[0] 
  elif column_2:
    return board[1] 
  elif column_3:
    return board[2] 
  # Or return None if there was no winner
  else:
    return None

# Function to check if there is a row in which all character are same
def check_diagonals():
  # Set global variables
  global game_still_going
  # Check if any of the columns have all the same value (and is not empty)
  diagonal_1 = board[0] == board[4] == board[8] != "_"
  diagonal_2 = board[2] == board[4] == board[6] != "_"
  # If any row does have a match, flag that there is a win
  if diagonal_1 or diagonal_2:
    game_still_going = False
  # Return the winner
  if diagonal_1:
    return board[0] 
  elif diagonal_2:
    return board[2]
  # Or return None if there was no winner
  else:
    return None

# Function to check if the game ended in a tie
def check_if_tie():
    # Set global variables
  global game_still_going
  # If board is full
  if "_" not in board:
    game_still_going = False
    return True
  # Else there is no tie
  else:
    return False

# Function to change the player in multiplayer mode
def flip_player():
  # Global variables we need
  global current_player
  # If the current player was X, make it O
  if current_player == "X":
    current_player = "O"
  # Or if the current player was O, make it X
  elif current_player == "O":
    current_player = "X"

# Function which carries out a multiplayer game
def play_multiplayer():
    display_board()
    # Loop which takes inputs from users in an alternate manner till the game doesn't end
    while True:
        handle_multi_player_turn(current_player)
        # Check if the game is over
        check_if_game_over()
        # Change the player
        flip_player()
        # Break the loop if the game_still_going boolean variable changes to False
        if game_still_going == False:
            break
    # Display the winner 
    if winner == "X" or winner == "O":
        print(winner + " won. :)")
    # Else tell there was a tie
    elif winner == None:
        print("Tie.")
    # Back to main menu
    main_menu()

# Function which handles turns in the easy single player game
def handle_single_player_turn():
    
    print("Player's turn:")
    # Take input from the player
    position = input("Choose a position from 1-9: ")
    valid = False
    # Run the loop till the user enters a valid input
    while True:
    # Make sure the input is valid
        while True:
            if position in ["1", "2", "3", "4", "5", "6", "7", "8", "9"]:
              break
            position = input("Invalid. Choose a position from 1-9: ")
            
 
    # Get correct index in our board list
        position = int(position) - 1

    # Then also make sure the spot is available on the board
        if (board[position] == "_"):
            valid = True
        else:
            print("That position is already filled")
        if (valid):
           break
    
    board[position] = player
    # Display the changes and check if the game is over
    display_board()
    check_if_game_over()
    
    # If the game is still going on find the position the computer will choose
    if (game_still_going == True):
        print("computer's turn:")
        # Check if the position chosen is empty and change the character accordingly
        while board[position] != "_":
            position = computer_choice()
        board[position] = comp
        # Display the chnages and check if the game is over
        display_board()
        check_if_game_over()

# Function which handles turns in the hard single player game
def handle_hard_single_player_turn():
    print("Player's turn:")
    # Take input from the player
    position = input("Choose a position from 1-9: ")
    valid = False
    # Run the loop till the user enters a valid input
    while True:
    # Make sure the input is valid
        while True:
            if position in ["1", "2", "3", "4", "5", "6", "7", "8", "9"]:
              break
            position = input("Invalid. Choose a position from 1-9: ")
            
 
    # Get correct index in our board list
        position = int(position) - 1

    # Then also make sure the spot is available on the board
        if (board[position] == "_"):
            valid = True
        else:
            print("That position is already filled")
        if (valid):
           break
    board[position] = player
    # Display the changes and check if the game is over
    display_board()
    check_if_game_over()
    
    # If the game is still going on find the position the computer will choose
    if (game_still_going == True):
        print("computer's turn:")
        # Initialise with a very low score 
        bestScore = -800
        bestMove = 0
        number = 1
        # For each cell in the board, if it is empty check if the computercan win through it and choose the best possible operation
        while number < 10:
            if (board[number-1] == '_'):
                board[number-1] = comp
                score = minimax(board, 0, False)
                board[number-1] = '_'
                if (score > bestScore):
                    bestScore = score
                    bestMove = number-1
            number = number + 1
        # For the best posssible position enter the character of the computer
        board[bestMove] = comp
        # Display the changes and check if the game is over
        display_board()
        check_if_game_over()

# Function which handles turns in the medium single player game
def handle_med_single_player_turn():
    print("Player's turn:")
    # Take input from the player
    position = input("Choose a position from 1-9: ")
    valid = False
    # Run the loop till the user enters a valid input
    while True:
    # Make sure the input is valid
        while True:
            if position in ["1", "2", "3", "4", "5", "6", "7", "8", "9"]:
              break
            position = input("Invalid. Choose a position from 1-9: ")
            
 
    # Get correct index in our board list
        position = int(position) - 1

    # Then also make sure the spot is available on the board
        if (board[position] == "_"):
            valid = True
        else:
            print("That position is already filled")
        if (valid):
           break
    board[position] = player
    # Display the changes and check if the game is over
    display_board()
    check_if_game_over()
    
    # If the game is still going on find the position the computer will choose
    if (game_still_going == True):
        print("computer's turn:")
        temp = random.randint(0, 3)
        # if temp is 1 make a move using the minimax approach
        if temp == 1:
            # Initialise with a very low score 
            bestScore = -800
            bestMove = 0
            number = 1
            # For each cell in the board, if it is empty check if the computercan win through it and choose the best possible operation
            while number < 10:
                if (board[number-1] == '_'):
                    board[number-1] = comp
                    score = minimax(board, 0, False)
                    board[number-1] = '_'
                    if (score > bestScore):
                        bestScore = score
                        bestMove = number-1
                number = number + 1
            # For the best posssible position enter the character of the computer
            board[bestMove] = comp
            display_board()
            check_if_game_over()
        # Else make a random move
        else:
          while board[position] != "_":
              position = computer_choice()
          board[position] = comp
          # Display the changes and check if the game is over
          display_board()
          check_if_game_over()

# Function which carries out a easy single player game
def play_easy_single_player():
    # Ask the user which character they want to play with
    character = input("\nChoose whether you want to play as O or X: ")
    global comp
    # validity checks for the user input
    while character != "X" and character != "O":
        character = input(
            "Invalid input. Choose whether you want to play as O or X: ")
    # Set the computer character according to the user input
    if character == "X":
        comp = "O"
    else:
        comp = "X"
    global player
    player = character
    # displaying the board
    display_board()

    # Loop which takes user input till the game is over
    while True:
        handle_single_player_turn()
        # Break the loop if the game_still_going boolean variable changes to False
        if game_still_going == False:
            break 

    # Display the winner 
    if (winner == player):
        print( "You won. :)\n")
    elif (winner == comp):
        print( "You lost.\n")
    # Else tell there was a tie
    elif (winner == None):
        print("Tie.\n")
    # Back to main menu
    main_menu()

# Function which carries out a hard level single player game   
def play_hard_single_player():
    # Ask the user which character they want to play with
    character = input("\nChoose whether you want to play as O or X: ")
    global comp
    # validity checks for the user input
    while character != "X" and character != "O":
        character = input("Invalid input. Choose whether you want to play as O or X: ")
     # Set the computer character according to the user input
    if character == "X":
        comp = "O"
    else:
        comp = "X"
    global player
    player = character
    # displaying the board
    display_board()

    # Loop which takes user input till the game is over
    while True:
        handle_hard_single_player_turn()
        # Break the loop if the game_still_going boolean variable changes to False
        if game_still_going == False:
            break 

    # Display the winner 
    if (winner == player):
        print( "You won. :)\n")
    elif (winner == comp):
        print( "You lost. :)\n")
    # Else tell there was a tie
    elif (winner == None):
        print("Tie.\n")
    # Back to main menu
    main_menu()

# Function which carries out a medium level single player game
def play_med_single_player():
    # Ask the user which character they want to play with
    character = input("\nChoose whether you want to play as O or X: ")
    global comp
    # validity checks for the user input
    while character != "X" and character != "O":
        character = input(
            "Invalid input. Choose whether you want to play as O or X: ")
     # Set the computer character according to the user input
    if character == "X":
        comp = "O"
    else:
        comp = "X"
    global player
    player = character
    # displaying the board
    display_board()

    # Loop which takes user input till the game is over
    while True:
        handle_med_single_player_turn()
        # Break the loop if the game_still_going boolean variable changes to False
        if game_still_going == False:
            break 

    # Display the winner 
    if (winner == player):
        print( "You won. :)\n")
    elif (winner == comp):
        print( "You lost. :)\n")
    # Else tell there was a tie
    elif (winner == None):
        print("Tie.\n")
    # Back to main menu
    main_menu()

# Function for performing minimax operation
def minimax(board, depth, isMaximizing):
    # Check if the gameis over and edit the score accordingly
    if (checkWhichMarkWon(comp)):
        return 1
    elif (checkWhichMarkWon(player)):
        return -1
    elif (checkDraw()):
        return 0
    
    # If we want to maximise the score find the best score
    if (isMaximizing):
        bestScore = -800
        number = 1
        while number < 10:
          if (board[number-1] == '_'):
                board[number-1] = comp
                score = minimax(board, depth + 1, False)
                board[number-1] = '_'
                if (score > bestScore):
                    bestScore = score
          number = number + 1
        return bestScore
    # Else If we want to minimise the score find the best score
    else:
        bestScore = 800
        number = 1
        while number < 10:
          if (board[number-1] == '_'):
                board[number-1] = player
                score = minimax(board, depth + 1, True)
                board[number-1] = '_'
                if (score < bestScore):
                    bestScore = score
          number = number + 1
        return bestScore

# Function to check if a character has won the game 
def checkWhichMarkWon(mark):
    #  Check through all rows, columns and diagonals if the given character is present in the required pattern
    if board[0] == board[1] and board[0] == board[2] and board[0] == mark:
        return True
    elif (board[3] == board[4] and board[3] == board[5] and board[3] == mark):
        return True
    elif (board[6] == board[7] and board[6] == board[8] and board[6] == mark):
        return True
    elif (board[0] == board[3] and board[0] == board[6] and board[0] == mark):
        return True
    elif (board[1] == board[4] and board[1] == board[7] and board[1] == mark):
        return True
    elif (board[2] == board[5] and board[2] == board[8] and board[2] == mark):
        return True
    elif (board[0] == board[4] and board[0] == board[8] and board[0] == mark):
        return True
    elif (board[6] == board[4] and board[6] == board[2] and board[6] == mark):
        return True
    else:
        return False

# Function to check Draw
def checkDraw():
  # Check if the empty character is missing on the board to see if the game has ended in a tie
    for number in range(9):
        if (board[number] == '_'):
            return False
    return True

# Function which starts a game
def play_game():
    # Ask the user if they want to play a multiplayer or a single player game
    number = input("Enter 1 for single player and 2 for multiplayer 3 for exit: ")
    while number != "1" and number != "2" and number != "3":
          number = input("Invalid input. Enter 1 for single player and 2 for multiplayer: ")
    number = int(number)
    if (number == 1):
        print("\nSingle Player game:\n")
        # Ask the user for the level of difficulty they want in the game and proceed accordingly
        level = input("Enter 1 for easy and 2 for medium and 3 for hard: ")
        # validity checks for the user input
        while level != "1" and level != "2" and level != "3":
          level = input("Invalid input. Enter 1 for easy and 2 for medium and 3 for hard: ")
        level = int(level)
        
        if (level == 1):
          play_easy_single_player()
        elif (level == 2):
          play_med_single_player()
        else:
          play_hard_single_player()
    elif number == 2:
        print("Multiplayer game:")
        play_multiplayer()
    else:
        print("Thankyou for playing :)\nTic Tac Toe by Pranjal Singh")
        sys.exit()

# Function to call the main menu
def main_menu():
  print("Main menu:\n")
  # Reinitialize all variables to default value
  reinitialise_var()
  # Calling the play_game() function
  play_game()

# Calling the main menu
main_menu()