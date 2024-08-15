# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """


    def getAction(self, gameState):
      """
      You do not need to change this method, but you're welcome to.

      getAction chooses among the best options according to the evaluation function.

      Just like in the previous project, getAction takes a GameState and returns
      some Directions.X for some X in the set {North, South, West, East, Stop}
      """
      # Collect legal moves and successor states
      legalMoves = gameState.getLegalActions()

      # Choose one of the best actions
      scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
      bestScore = max(scores)
      bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
      chosenIndex = random.choice(bestIndices) # Pick randomly among the best

      "Add more of your code here if you want to"

      return legalMoves[chosenIndex]

    """ evaluationFunction is the function that evaluates the current state of the game and returns a score
        Input:
          self - The object pointer
          currentGameState - The current state of the game
          action - The action to be taken
        Algorithm:
          * Get the current position of the pacman
          * Get the food, ghosts and capsules from the current state
          * Calculate the distance of the pacman from the food
          * Iterate over the total number of ghosts
            * If the ghost is scared, add the score
            * If the ghost is not scared, subtract the score
          * Calculate the distance of the pacman from the capsules
          * If the capsule distances are not empty
            * Get the minimum distance of the pacman from the capsules
            * Calculate the score
          * Get the remaining food
          * Subtract the remaining food from the score
          * Calculate the final score
            * Add the score of the current state
            * Add the food score
            * Add the ghost score
            * Add the capsule score
            * Add the food count score
          * Return the final score
        Output:
          finalScore - The score of the current state
    """
    def evaluationFunction(self, currentGameState, action):
      """
      Design a better evaluation function here.

      The evaluation function takes in the current and proposed successor
      GameStates (pacman.py) and returns a number, where higher numbers are better.

      The code below extracts some useful information from the state, like the
      remaining food (newFood) and Pacman position after moving (newPos).
      newScaredTimes holds the number of moves that each ghost will remain
      scared because of Pacman having eaten a power pellet.

      Print out these variables to see what you're getting, then combine them
      to create a masterful evaluation function.
      """
      "*** YOUR CODE HERE ***"
      # Useful information you can extract from a GameState (pacman.py)
      successorGameState = currentGameState.generatePacmanSuccessor(action)
      pacmanPos = successorGameState.getPacmanPosition()
      food = successorGameState.getFood()
      ghosts = successorGameState.getGhostStates()
      capsules = currentGameState.getCapsules()
      # Initialize the variables
      foodScore = 0
      ghostScore = 0
      capsuleScore = 0
      foodDistances = [manhattanDistance(pacmanPos, foodPos) for foodPos in food.asList()]
      # If the food distances are not empty
      if foodDistances:
          nearestFoodDist = min(foodDistances)  # Get the minimum distance of the pacman from the food
          foodScore = 1.0 / nearestFoodDist # Calculate the score
      # Iterate over the total number of ghosts
      for ghost in ghosts:
          ghostDist = manhattanDistance(pacmanPos, ghost.getPosition()) # Calculate the distance of the pacman from the ghosts
          # If the ghost is scared, add the score
          if ghost.scaredTimer > 0:
              ghostScore += 2.0 / (ghostDist + 1)
          # Otherwise, subtract the score
          else:
              ghostScore -= 1.0 / (ghostDist + 1)
      # Calculate the distance of the pacman from the capsules
      capsuleDistances = [manhattanDistance(pacmanPos, capsule) for capsule in capsules]
      # If the capsule distances are not empty
      if capsuleDistances:
          nearestCapsuleDist = min(capsuleDistances)  # Get the minimum distance of the pacman from the capsules
          capsuleScore = 1.0 / (nearestCapsuleDist + 1) # Calculate the score
      # Get the remaining food
      remainingFood = len(food.asList())
      # Subtract the remaining food from the score
      foodCountScore = -remainingFood
      # Calculate the final score
      finalScore = (
          successorGameState.getScore() +
          foodScore * 10 +                 
          ghostScore * 20 +                
          capsuleScore * 10 +              
          foodCountScore * 5               
      )
      return finalScore

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """
    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
          Returns a list of legal actions for an agent
          agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
          Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
          Returns the total number of agents in the game
        """
        "*** YOUR CODE HERE ***"
        """ minimax - Calculates the minimax value of the current state
              Input:
                agentIndex - The index of the agent
                depth - The depth of the search
                gameState - The current state of the game
              Algorithm:
                * If the game is won or lost or the depth is reached
                  * Return the evaluation function of the current state
                * If the agent index is 0
                  * Return the max value
                * Otherwise
                  * Return the min value
              Output:
                The minimax value of the current state
        """
        def minimax(agentIndex, depth, gameState):
            # If the game is won or lost or the depth is reached
            if gameState.isWin() or gameState.isLose() or depth == self.depth:
                return self.evaluationFunction(gameState), None
            # If the agent index is 0
            if agentIndex == 0:
                return maxValue(agentIndex, depth, gameState)
            # Otherwise
            else:
                return minValue(agentIndex, depth, gameState)
        """ maxValue - Calculates the max value of the current state
              Input:
                agentIndex - The index of the agent
                depth - The depth of the search
                gameState - The current state of the game
              Algorithm:
                * Initialize the variables
                * Iterate over the legal actions of the agent
                  * Get the successor of the current state
                  * Calculate the value of the successor
                  * If the value is greater than the max value
                    * Update the max value
                    * Update the best action
                * If the depth is 0
                  * Return the max value and the best action
                * Otherwise
                  * Return the max value
              Output:
                The max value of the current state
        """
        def maxValue(agentIndex, depth, gameState):
            # Initialize the variables
            v = float("-inf")
            bestAction = None
            # Iterate over the legal actions of the agent
            for action in gameState.getLegalActions(agentIndex):
                # Get the successor of the current state
                successor = gameState.generateSuccessor(agentIndex, action)
                # Calculate the value of the successor
                value, _ = minimax((agentIndex + 1) % gameState.getNumAgents(), depth + ((agentIndex + 1) // gameState.getNumAgents()), successor)
                # If the value is greater than the max value
                if value > v:
                    v = value
                    bestAction = action
            # If the depth is 0
            if depth == 0:
                return v, bestAction
            # Otherwise
            else:
                return v, None
        """ minValue - Calculates the min value of the current state
              Input:
                agentIndex - The index of the agent
                depth - The depth of the search
                gameState - The current state of the game
              Algorithm:
                * Initialize the variables
                * Iterate over the legal actions of the agent
                  * Get the successor of the current state
                  * Calculate the value of the successor
                  * If the value is less than the min value
                    * Update the min value
                * Return the min value
              Output:
                The min value of the current state
        """
        def minValue(agentIndex, depth, gameState):
            # Initialize the variables
            v = float("inf")
            # Iterate over the legal actions of the agent
            for action in gameState.getLegalActions(agentIndex):
                # Get the successor of the current state
                successor = gameState.generateSuccessor(agentIndex, action)
                # Calculate the value of the successor
                value, _ = minimax((agentIndex + 1) % gameState.getNumAgents(), depth + ((agentIndex + 1) // gameState.getNumAgents()), successor)
                # If the value is less than the min value
                if value < v:
                    v = value
            return v, None
        # Initialize the variables
        _, action = minimax(0, 0, gameState)
        # Return the action
        return action

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """
    def getAction(self, gameState):
        """
          Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        """ alphaBeta - Calculates the alpha-beta value of the current state
              Input:
                agentIndex - The index of the agent
                depth - The depth of the search
                gameState - The current state of the game
                alpha - The alpha value
                beta - The beta value
              Algorithm:
                * If the game is won or lost or the depth is reached
                  * Return the evaluation function of the current state
                * If the agent index is 0
                  * Return the max value
                * Otherwise
                  * Return the min value
              Output:
                The alpha-beta value of the current state
        """
        def alphaBeta(agentIndex, depth, gameState, alpha, beta):
            # If the game is won or lost or the depth is reached
            if gameState.isWin() or gameState.isLose() or depth == self.depth:
                return self.evaluationFunction(gameState), None
            # If the agent index is 0
            if agentIndex == 0:
                return maxValue(agentIndex, depth, gameState, alpha, beta)
            # Otherwise
            else:
                return minValue(agentIndex, depth, gameState, alpha, beta)
        """ maxValue - Calculates the max value of the current state
              Input:
                agentIndex - The index of the agent
                depth - The depth of the search
                gameState - The current state of the game
                alpha - The alpha value
                beta - The beta value
              Algorithm:
                * Initialize the variables
                * Iterate over the legal actions of the agent
                  * Get the successor of the current state
                  * Calculate the value of the successor
                  * If the value is greater than the max value
                    * Update the max value
                    * Update the best action
                  * If the value is greater than beta
                    * Return the max value and the best action
                  * Update the alpha value
                * If the depth is 0
                  * Return the max value and the best action
                * Otherwise
                  * Return the max value
              Output:
                The max value of the current state
        """
        def maxValue(agentIndex, depth, gameState, alpha, beta):
            # Initialize the variables
            v = float("-inf")
            bestAction = None
            # Iterate over the legal actions of the agent
            for action in gameState.getLegalActions(agentIndex):
                # Get the successor of the current state
                successor = gameState.generateSuccessor(agentIndex, action)
                # Calculate the value of the successor
                value, _ = alphaBeta((agentIndex + 1) % gameState.getNumAgents(), depth + ((agentIndex + 1) // gameState.getNumAgents()), successor, alpha, beta)
                # If the value is greater than the max value
                if value > v:
                    v = value
                    bestAction = action
                # If the value is greater than beta
                if v > beta:
                    return v, bestAction
                # Update the alpha value
                alpha = max(alpha, v)
            # If the depth is 0
            if depth == 0:
                return v, bestAction
            # Otherwise
            else:
                return v, None
        """ minValue - Calculates the min value of the current state
              Input:
                agentIndex - The index of the agent
                depth - The depth of the search
                gameState - The current state of the game
                alpha - The alpha value
                beta - The beta value
              Algorithm:
                * Initialize the variables
                * Iterate over the legal actions of the agent
                  * Get the successor of the current state
                  * Calculate the value of the successor
                  * If the value is less than the min value
                    * Update the min value
                  * If the value is less than alpha
                    * Return the min value
                  * Update the beta value
                * Return the min value
              Output:
                The min value of the current state
        """
        def minValue(agentIndex, depth, gameState, alpha, beta):
            # Initialize the variables
            v = float("inf")
            bestAction = None
            # Iterate over the legal actions of the agent
            for action in gameState.getLegalActions(agentIndex):
                # Get the successor of the current state
                successor = gameState.generateSuccessor(agentIndex, action)
                # Calculate the value of the successor
                value, _ = alphaBeta((agentIndex + 1) % gameState.getNumAgents(), depth + ((agentIndex + 1) // gameState.getNumAgents()), successor, alpha, beta)
                # If the value is less than the min value
                if value < v:
                    v = value
                    bestAction = action
                # If the value is less than alpha
                if v < alpha:
                    return v, bestAction
                # Update the beta value
                beta = min(beta, v)
            return v, None
        # Initialize the variables
        _, action = alphaBeta(0, 0, gameState, float("-inf"), float("inf"))
        # Return the action
        return action


class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """
    def getAction(self, gameState):
        """
          Returns the expectimax action using self.depth and self.evaluationFunction

          All ghosts should be modeled as choosing uniformly at random from their
          legal moves.
        """
        "*** YOUR CODE HERE ***"
        """ expectimax - Calculates the expectimax value of the current state
              Input:
                agentIndex - The index of the agent
                depth - The depth of the search
                gameState - The current state of the game
              Algorithm:
                * If the game is won or lost or the depth is reached
                  * Return the evaluation function of the current state
                * If the agent index is 0
                  * Return the max value
                * Otherwise
                  * Return the exp value
              Output:
                The expectimax value of the current state
        """
        def expectimax(agentIndex, depth, gameState):
            # If the game is won or lost or the depth is reached
            if gameState.isWin() or gameState.isLose() or depth == self.depth:
                return self.evaluationFunction(gameState), None
            # If the agent index is 0
            if agentIndex == 0:
                return maxValue(agentIndex, depth, gameState)
            # Otherwise
            else:
                return expValue(agentIndex, depth, gameState)
        """ maxValue - Calculates the max value of the current state
              Input:
                agentIndex - The index of the agent
                depth - The depth of the search
                gameState - The current state of the game
              Algorithm:
                * Initialize the variables
                * Iterate over the legal actions of the agent
                  * Get the successor of the current state
                  * Calculate the value of the successor
                  * If the value is greater than the max value
                    * Update the max value
                    * Update the best action
                * If the depth is 0
                  * Return the max value and the best action
                * Otherwise
                  * Return the max value
              Output:
                The max value of the current state
        """
        def maxValue(agentIndex, depth, gameState):
            # Initialize the variables
            v = float("-inf")
            bestAction = None
            # Iterate over the legal actions of the agent
            for action in gameState.getLegalActions(agentIndex):
                # Get the successor of the current state
                successor = gameState.generateSuccessor(agentIndex, action)
                # Calculate the value of the successor
                value, _ = expectimax((agentIndex + 1) % gameState.getNumAgents(), depth + ((agentIndex + 1) // gameState.getNumAgents()), successor)
                # If the value is greater than the max value
                if value > v:
                    v = value
                    bestAction = action
            # If the depth is 0
            if depth == 0:
                return v, bestAction
            # Otherwise
            else:
                return v, None
        """ expValue - Calculates the exp value of the current state
              Input:
                agentIndex - The index of the agent
                depth - The depth of the search
                gameState - The current state of the game
              Algorithm:
                * Initialize the variables
                * Iterate over the legal actions of the agent
                  * Get the successor of the current state
                  * Calculate the value of the successor
                  * Add the value to the total value
                * Return the total value
              Output:
                The exp value of the current state
        """
        def expValue(agentIndex, depth, gameState):
            # Initialize the variables
            v = 0
            actions = gameState.getLegalActions(agentIndex)
            p = 1.0 / len(actions)
            # Iterate over the legal actions of the agent
            for action in actions:
                # Get the successor of the current state
                successor = gameState.generateSuccessor(agentIndex, action)
                # Calculate the value of the successor
                value, _ = expectimax((agentIndex + 1) % gameState.getNumAgents(), depth + ((agentIndex + 1) // gameState.getNumAgents()), successor)
                v += p * value
            return v, None
        # Initialize the variables
        _, action = expectimax(0, 0, gameState)
        # Return the action
        return action

""" betterEvaluationFunction - Calculates the better evaluation function of the current state
      Input:
        currentGameState - The current state of the game
      Algorithm:
        * Useful information from the game state
        * Base score is the current game state score
        * Calculate the reciprocal of the distance to the nearest food
        * Calculate the reciprocal of the distance to the nearest ghost
        * Calculate the reciprocal of the distance to the nearest capsule
        * Calculate remaining food score (negative because more food is worse)
        * Combine all the scores with appropriate weights
        * Return the final score
      Output:
        finalScore - The score of the current state
"""
def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: This evaluation function balances the immediate need to avoid
      ghosts, collect food, and consume power pellets. It uses the distances to
      the nearest food, ghost, and power pellet, and the number of remaining food
      pellets to compute a score. The function prioritizes food collection while
      avoiding ghosts, and it seeks power pellets to turn ghosts into vulnerable targets.
    """
    # Useful information from the game state
    pacmanPos = currentGameState.getPacmanPosition()
    food = currentGameState.getFood()
    ghosts = currentGameState.getGhostStates()
    capsules = currentGameState.getCapsules()
    # Base score is the current game state score
    score = currentGameState.getScore()
    # Calculate the reciprocal of the distance to the nearest food
    foodDistances = [manhattanDistance(pacmanPos, foodPos) for foodPos in food.asList()]
    if foodDistances:
        nearestFoodDist = min(foodDistances)
        foodScore = 1.0 / nearestFoodDist
    else:
        foodScore = 0
    # Calculate the reciprocal of the distance to the nearest ghost
    ghostScore = 0
    for ghost in ghosts:
        ghostDist = manhattanDistance(pacmanPos, ghost.getPosition())
        if ghost.scaredTimer > 0:
            ghostScore += 2.0 / (ghostDist + 1)  # Incentivize approaching scared ghosts
        else:
            ghostScore -= 1.0 / (ghostDist + 1)  # Discourage approaching active ghosts
    # Calculate the reciprocal of the distance to the nearest capsule
    capsuleDistances = [manhattanDistance(pacmanPos, capsule) for capsule in capsules]
    if capsuleDistances:
        nearestCapsuleDist = min(capsuleDistances)
        capsuleScore = 1.0 / (nearestCapsuleDist + 1)
    else:
        capsuleScore = 0
    # Calculate remaining food score (negative because more food is worse)
    remainingFood = len(food.asList())
    foodCountScore = -remainingFood
    # Combine all the scores with appropriate weights
    finalScore = (
        score +               
        foodScore * 10 +      
        ghostScore * 20 +     
        capsuleScore * 10 +   
        foodCountScore * 5
    )
    return finalScore

# Abbreviation
better = betterEvaluationFunction

# python pacman.py -p ExpectimaxAgent -a evalFn=better -l smallClassic