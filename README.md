Sure, here's an example of how you can format the Minimax algorithm in a README.md file on GitHub:

# Minimax Algorithm
The Minimax algorithm is a decision-making algorithm used in game theory and decision theory. It is commonly used in two-player turn-based games to determine the optimal move for a player.

## How it works
The algorithm works by recursively evaluating all possible moves a player can make and their corresponding outcomes. It then selects the move that maximizes the player's chances of winning and minimizes the opponent's chances of winning.

The algorithm works by building a game tree representing all possible moves and their outcomes. It then assigns a score to each node in the tree, representing the expected outcome of that move. The scores are propagated up the tree until the root node is reached, where the optimal move can be selected.

The algorithm is called "minimax" because it alternates between minimizing the opponent's score and maximizing the player's score.

## Complexity
The time complexity of the Minimax algorithm is exponential in the worst case, as it needs to evaluate all possible moves and their outcomes. However, it can be optimized using techniques such as alpha-beta pruning to reduce the search space.

## How to use it
As of right now this implementation of Min-max algorithm is desigend to access whether the position of tic tac toe given on the start of a program as array of:
zeros - if certain space is empty
ones - if a player one ocuppies that place
twos - if a player two ocuppies that place
The outcome of a SOLVE_GAME_STATE command will determine whether one player with optimal play has a chance to win or is it a forced draw


## Conclusion
The Minimax algorithm is a powerful decision-making algorithm that can be used to determine the optimal move in two-player turn-based games. While its time complexity is exponential, it can be optimized using various techniques to reduce the search space.
