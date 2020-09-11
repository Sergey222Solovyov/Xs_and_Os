# My tic-tac-toe game 
Tic-tac-toe game with AI that can't lose.

A game of tic-tac-toe, realized with interactive movement on the board. The game also has a mode that allows you to play with an AI whose logic based on MiniMax algoritm.

# MiniMax algoritm

Minimax is a kind of backtracking algorithm that is used in decision making and game theory to find the optimal move for a player, assuming that your opponent also plays optimally. 
In Minimax the two players are called maximizer and minimizer. The maximizer tries to get the highest score possible while the minimizer tries to do the opposite and get the lowest score possible. Every board state has a value associated with it. In a given state if the maximizer has upper hand then, the score of the board will tend to be some positive value. 

# How is it implemented in my project 

Firs of all we have a function evaluate. The basic idea behind the evaluation function is to give a high value for a board if maximizer‘s turn or a low value for the board if minimizer‘s turn. For example let us consider X as the maximizer and O as the minimizer. If X wins on the board we give it a positive value of +10 If O wins it a negative value of -10. and value of +0 in case of a draw. 

To check whether or not the current move is better than the best move we take the help of minimax() function which will consider all the possible ways the game can go and returns the best value for that move.

And last but not least findBestPosition() function. This function evaluates all the available moves using minimax(). Minimax returns a value that is written to the moveVal variable. The position on the board when moveVal had the greatest value becomes final. 




Source: https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/?ref=lbp
