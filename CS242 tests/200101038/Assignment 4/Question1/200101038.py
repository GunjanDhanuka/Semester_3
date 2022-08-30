import random
import time

player, opponent = "x", "o"

# Function to display the board's state
def displayBoard(board):
    print()
    for row in range(3):
        for col in range(3):
            print(board[row][col], end=" ")
            if col < 2:
                print("|", end=" ")

        print()
        if row < 2:
            print("----------")
    print()


# Returns 0 if game is not over and 1 if it is over
def gameOver(board):

    for row in range(3):
        if (
            board[row][0] == board[row][1]
            and board[row][1] == board[row][2]
            and not board[row][0] == "_"
        ):
            return 1

    for col in range(3):
        if (
            board[0][col] == board[1][col]
            and board[1][col] == board[2][col]
            and not board[0][col] == "_"
        ):
            return 1

    # check diagonals
    if board[0][0] == board[1][1] == board[2][2] and not board[0][0] == "_":
        return 1

    if board[0][2] == board[1][1] == board[2][0] and not board[0][2] == "_":
        return 1

    # Check for Draw game
    flag = True
    for row in range(3):
        for col in range(3):
            if board[row][col] == "_":
                # Empty position present
                return 0
        if not flag:
            break

    # If all cells are full and no one player is winner then game is drawn
    return 1


# Returns scores which help the minimax algorithms to decide the best move
def evaluation(board):
    for row in range(3):
        if board[row][0] == board[row][1] and board[row][1] == board[row][2]:
            if board[row][0] == player:
                return 100
            elif board[row][0] == opponent:
                return -100

    for col in range(3):
        if board[0][col] == board[1][col] and board[1][col] == board[2][col]:
            if board[0][col] == player:
                return 100
            elif board[0][col] == opponent:
                return -100

    # check diagonals
    if board[0][0] == board[1][1] == board[2][2]:
        if board[0][0] == player:
            return 100
        elif board[0][0] == opponent:
            return -100

    if board[0][2] == board[1][1] == board[2][0]:
        if board[0][2] == player:
            return 100
        elif board[0][2] == opponent:
            return -100

    if boardFull(board):
        return 0
    return 0


# Tells if the board is full or not
def boardFull(board):
    for row in range(3):
        for col in range(3):
            if board[row][col] == "_":
                return True

    return False


# Function to implement the MiniMax Algorithm
def minimax(board, depth, maximisingPlayer):
    if gameOver(board) == 1:
        return evaluation(board)

    if maximisingPlayer:
        maxEval = -10000

        for row in range(3):
            for col in range(3):
                if board[row][col] == "_":
                    board[row][col] = player
                    maxEval = max(
                        maxEval, minimax(board, depth + 1, not maximisingPlayer)
                    )
                    board[row][col] = "_"
        return maxEval
    else:
        minEval = +10000

        for row in range(3):
            for col in range(3):
                if board[row][col] == "_":
                    board[row][col] = opponent
                    minEval = min(
                        minEval, minimax(board, depth + 1, not maximisingPlayer)
                    )
                    board[row][col] = "_"
        return minEval


# Based on the minimax algorithm, it finds out the best move from the board
def bestmove(board):
    bestVal = -10000
    move = (-1, -1)

    for row in range(3):
        for col in range(3):
            if board[row][col] == "_":
                board[row][col] = player

                value = minimax(board, 0, False)

                board[row][col] = "_"
                if value > bestVal:
                    bestVal = value
                    move = (row, col)

    return move


# Single Player Tough Game Mode
def singleplayerTough(board):
    # random.seed(time.time())
    print("Randomly selecting the first player....")
    # first = random.choice([0, 1])
    currentPlayer = player
    # if first == 0:
    #     player, opponent = "x", "o"
    #     currentPlayer = player
    #     print("You will have the first turn!")
    # else:
    #     opponent, player = "x", "o"
    #     currentPlayer = opponent
    #     print("The computer will have the first turn!")

    while True:
        displayBoard(board)
        if gameOver(board):
            score = evaluation(board)
            if score == 100:
                print("THE COMPUTER WINS... :)")
            elif score == -100:
                print("YOU, THE HUMAN, WINS... :o")
            else:
                print("THE GAME ENDS IN A DRAW")
            print("Press Enter to continue...")
            trash = input()
            return
        # When human enters a move
        if currentPlayer == opponent:
            print("Enter your move:", end=" ")
            movePosition = input()
            if not validPos(movePosition):
                print("Invalid move! Please enter a number between 1 to 9.")
                continue
            movePosition = int(movePosition)
            if moveAvailable(board, movePosition):
                i, j = coordinates(movePosition)
                print("You moved to position,", movePosition)
                board[i][j] = currentPlayer
                currentPlayer = player
                continue
            else:
                print(
                    "That position is already occupied. Please re-enter new position."
                )
                continue
        else:
            print("It is Computer's turn!")
            i, j = bestmove(board)
            pos = i * 3 + j + 1
            print("Computer moved to position ", pos)
            board[i][j] = currentPlayer
            currentPlayer = opponent
            continue


# Single Player Easy game mode
def singleplayerEasy(board):
    # random.seed(time.time())
    print("Randomly selecting the first player....")
    # first = random.choice([0, 1])
    currentPlayer = player
    # if first == 0:
    #     player, opponent = "x", "o"
    #     currentPlayer = player
    #     print("You will have the first turn!")
    # else:
    #     opponent, player = "x", "o"
    #     currentPlayer = opponent
    #     print("The computer will have the first turn!")

    while True:
        displayBoard(board)
        if gameOver(board):
            score = evaluation(board)
            if score == 100:
                print("THE COMPUTER WINS... :)")
            elif score == -100:
                print("YOU, THE HUMAN, WINS...:o")
            else:
                print("THE GAME ENDS IN A DRAW")
            print("Press Enter to continue...")
            trash = input()
            return
        # When human enters a move
        if currentPlayer == opponent:
            print("Enter your move:", end=" ")
            movePosition = input()
            if not validPos(movePosition):
                print("Invalid move! Please enter a number between 1 to 9.")
                continue
            movePosition = int(movePosition)
            if moveAvailable(board, movePosition):
                i, j = coordinates(movePosition)
                print("You moved to position,", movePosition)
                board[i][j] = currentPlayer
                currentPlayer = player
                continue
            else:
                print(
                    "That position is already occupied. Please re-enter new position."
                )
                continue
        else:
            print("It is Computer's turn!")
            pos = random.choice(availablePos(board))
            i, j = coordinates(pos)
            print("Computer moved to position ", pos)
            board[i][j] = currentPlayer
            currentPlayer = opponent
            continue


# Single Player Medium game mode
def singleplayerMedium(board):
    random.seed(int(time.time()))
    toss = random.choice([0, 1])

    if toss == 1:
        singleplayerEasy(board)
    else:
        singleplayerTough(board)


# Returns the list of empty positions on the board
def availablePos(board):
    ans = []
    for row in range(3):
        for col in range(3):
            if board[row][col] == "_":
                ans.append(row * 3 + col + 1)
    return ans


# Tells if a position is valid integer between 1 to 9
def validPos(position):
    if position.isdigit():
        if int(position) > 0 and int(position) < 10:
            return True
    return False


# Multiplayer Game Mode
def multiplayer(board):
    print("Enter name of Player 1:")
    p1 = input()
    print("Enter name of Player 2:")
    p2 = input()
    # random.seed(int(time.time()))
    print("Randomly selecting the first player....")
    # first = random.choice([0, 1])
    currentPlayer = player

    # if first == 0:
    #     player, opponent = "x", "o"
    #     currentPlayer = player
    #     print("You will have the first turn!")
    # else:
    #     opponent, player = "x", "o"
    #     currentPlayer = opponent
    #     print("The computer will have the first turn!")

    while True:
        displayBoard(board)
        if gameOver(board):
            score = evaluation(board)
            if score == 100:
                print("PLAYER 1 WINS... :)")
            elif score == -100:
                print("PLAYER 2 WINS... :)")
            else:
                print("THE GAME ENDS IN A DRAW")
            print("Press Enter to continue...")
            trash = input()
            return
        # When human enters a move
        if currentPlayer == opponent:
            print("PLAYER 2 - Enter your move:", end=" ")
            movePosition = input()
            if not validPos(movePosition):
                print("PLAYER 2 - Invalid move! Please enter a number between 1 to 9.")
                continue
            movePosition = int(movePosition)
            if moveAvailable(board, movePosition):
                i, j = coordinates(movePosition)
                print("PLAYER 2 - You moved to position,", movePosition)
                board[i][j] = currentPlayer
                currentPlayer = player
                continue
            else:
                print(
                    "PLAYER 2 - That position is already occupied. Please re-enter new position."
                )
                continue
        else:
            print("PLAYER 1 - Enter your move:", end=" ")
            movePosition = input()
            if not validPos(movePosition):
                print("PLAYER 1 - Invalid move! Please enter a number between 1 to 9.")
                continue
            movePosition = int(movePosition)
            if moveAvailable(board, movePosition):
                i, j = coordinates(movePosition)
                print("PLAYER 1 - You moved to position,", movePosition)
                board[i][j] = currentPlayer
                currentPlayer = opponent
                continue
            else:
                print(
                    "PLAYER 1 - That position is already occupied. Please re-enter new position."
                )
                continue


# Returns the pair of co-ordinates from the position from 1 to 9
def coordinates(position):
    position -= 1
    row = int(position / 3)
    col = position % 3
    return row, col


# Tells if move is valid on particular position
def moveAvailable(board, position):
    row, col = coordinates(position)

    if board[row][col] == "_":
        return True
    return False


# Resets the board
def resetBoard(board):
    board = [["_", "_", "_"], ["_", "_", "_"], ["_", "_", "_"]]
    return board


# Prints the guide for the nine cells
def printNumbers():
    print("1 | 2 | 3")
    print("---------")
    print("4 | 5 | 6")
    print("---------")
    print("7 | 8 | 9")


# driver function
def main():
    board = [["_", "_", "_"], ["_", "_", "_"], ["_", "_", "_"]]

    while True:
        print()
        print()
        print("Welcome to Tic-Tac-Toe game...")
        print("Developed by Gunjan Dhanuka!")
        print()
        print("Here the numbers for respective cells")
        printNumbers()
        print()
        print("GAME MODES: ")
        print("1. User vs Computer - EASY")
        print("2. User vs Computer - MEDIUM")
        print("3. User vs Computer - TOUGH")
        print("4. User1 vs User2")
        print("0. Quit")
        print()
        print("Enter your choice: ", end=" ")
        choice = int(input())
        if choice == 1:
            singleplayerEasy(board)
        elif choice == 2:
            singleplayerMedium(board)
        elif choice == 3:
            singleplayerTough(board)
        elif choice == 4:
            multiplayer(board)
        elif choice == 0:
            print("Thanks for playing!")
            break
        else:
            print("Invalid Choice!")
        board = resetBoard(board)


main()
