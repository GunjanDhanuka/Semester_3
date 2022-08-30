## QUESTION 1 in CS242 ASSIGNMENT 4
## SUBMITTED BY: GUNJAN DHANUKA
## ROLL: 200101038
## DATE: 17/11/2021

Write a PYTHON program to play the game of TIC-TAC-TOE on a 3×3 board with alternate inputs from user and computer.

---------------------------------------------

Steps to execute:
Open Terminal in the directory where 200101038.py file is present.

Type: $ python3 200101038.py

-----------------------------------------------
This will launch the game in the command line interface.

You have 3 options:-

1. User vs Computer - EASY
    In this Easy difficulty, the computer simply picks a random move from the available moves.
    Thus the user may win if he plays optimally.

1. User vs Computer - MEDIUM
    In this Medium difficulty, there is equal chance that the computer will play random or will play optimally.
    Hence, this is between the Easy and Hard difficulties.

3. User vs Computer - HARD
    In this Hard difficulty, the computer uses the Minimax algorithm heuristic to perform the best move possible.
    It also looks ahead for a certain depth till the end of game and forsees all possibilites.
    The evaluation of a board state is done on the basis that which player wins on that state.
    In this difficulty, it is impossible to win against the computer even if you play optimally. (As tested by me a number of times)

4. User1 vs User2   
    In this mode, you can play a local match with another human user with alternate turns.


When you want to exit, enter 0 as choice on the main menu.
-----------------------------------------------