#Basic Algorithm
inputState = "32748552"

def printBoard(board):
    for i in range(0, 7):
        for j in range(0, 7):
            print(board[i][j] , end=" ")
        print()

def createBoard(state):
    board=[['0']*8 for i in range(8)]
    printBoard(board)
    for col in range(0, len(state)):
        row=int(state[col])-1
        print(row, ",", col)
        board[row][col] = 'Q'
    printBoard(board)



def fitness(state):
    createBoard(state)

fitness(inputState)