# qlearningAgents.py
# ------------------
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


from game import *
from learningAgents import ReinforcementAgent
from featureExtractors import *

import random,util,math

class QLearningAgent(ReinforcementAgent):
    """
      Q-Learning Agent

      Functions you should fill in:
        - computeValueFromQValues
        - computeActionFromQValues
        - getQValue
        - getAction
        - update

      Instance variables you have access to
        - self.epsilon (exploration prob)
        - self.alpha (learning rate)
        - self.discount (discount rate)

      Functions you should use
        - self.getLegalActions(state)
          which returns legal actions for a state
    """
    def __init__(self, **args):
        "You can initialize Q-values here..."
        ReinforcementAgent.__init__(self, **args)

        "*** YOUR CODE HERE ***"
        self.qValues = util.Counter()

    ''' getQValue - This function is called by the parent class to get the Q-Value of a state-action pair
          Input:
            state - The current state
            action - The action taken in the current state
          Algorithm:
            * Return the Q-Value of the state-action pair
          Output:
            Q-Value of the state-action pair
    '''
    def getQValue(self, state, action):
        """
          Returns Q(state,action)
          Should return 0.0 if we have never seen a state
          or the Q node value otherwise
        """
        "*** YOUR CODE HERE ***"
        return self.qValues[(state, action)]

    ''' computeValueFromQValues - This function is called by the parent class to compute the maximum Q-Value in a state
          Input:
            state - The current state
          Algorithm:
            * Get the legal actions in the current state
            * If there are no legal actions, return 0.0
            * Get the Q-Values of all the legal actions
            * Return the maximum Q-Value
          Output:
            maxQValue - The maximum Q-Value in the current state
    '''
    def computeValueFromQValues(self, state):
        """
          Returns max_action Q(state,action)
          where the max is over legal actions.  Note that if
          there are no legal actions, which is the case at the
          terminal state, you should return a value of 0.0.
        """
        "*** YOUR CODE HERE ***"
        legalActions = self.getLegalActions(state)
        if len(legalActions) == 0:
            return 0.0
        qValues = [self.getQValue(state, action) for action in legalActions]
        return max(qValues)

    ''' computeActionFromQValues - This function is called by the parent class to compute the best action to take in a state
          Input:
            state - The current state
          Algorithm:
            * Get the legal actions in the current state
            * If there are no legal actions, return None
            * Get the Q-Values of all the legal actions
            * Get the maximum Q-Value
            * Get the best actions with the maximum Q-Value
            * Return a random action from the best actions
          Output:
            action - The best action to take in the current state
    '''
    def computeActionFromQValues(self, state):
        """
          Compute the best action to take in a state.  Note that if there
          are no legal actions, which is the case at the terminal state,
          you should return None.
        """
        "*** YOUR CODE HERE ***"
        legalActions = self.getLegalActions(state)
        if len(legalActions) == 0:
            return None
        qValues = [self.getQValue(state, action) for action in legalActions]
        maxQValue = max(qValues)
        bestActions = [action for action in legalActions if self.getQValue(state, action) == maxQValue]
        return random.choice(bestActions)

    ''' getAction - This function is called by the parent class to get the action to take in the current state
          Input:
            state - The current state
          Algorithm:
            * Get the legal actions in the current state
            * If there are no legal actions, return None
            * If the coin flip is less than epsilon, return a random action
            * Else, return the action with the maximum Q-Value
          Output:
            action - The action to take in the current state
    '''
    def getAction(self, state):
        """
          Compute the action to take in the current state.  With
          probability self.epsilon, we should take a random action and
          take the best policy action otherwise.  Note that if there are
          no legal actions, which is the case at the terminal state, you
          should choose None as the action.

          HINT: You might want to use util.flipCoin(prob)
          HINT: To pick randomly from a list, use random.choice(list)
        """
        # Pick Action
        legalActions = self.getLegalActions(state)
        action = None
        "*** YOUR CODE HERE ***"
        if len(legalActions) == 0:
            return None
        if util.flipCoin(self.epsilon):
            action = random.choice(legalActions)
        else:
            action = self.computeActionFromQValues(state)
        return action

    ''' update - This function is called by the parent class to observe a state = action => nextState and reward transition
          Input:
            state - The current state
            action - The action taken in the current state
            nextState - The next state
            reward - The reward received after taking the action in the current state
          Algorithm:
            * Get the Q-Value of the current state and action
            * Get the Q-Value of the next state
            * Calculate the sample value using the reward and the Q-Value of the next state
            * Update the Q-Value of the current state and action using the sample value
          Output:
            None
    '''
    def update(self, state, action, nextState, reward):
        """
          The parent class calls this to observe a
          state = action => nextState and reward transition.
          You should do your Q-Value update here

          NOTE: You should never call this function,
          it will be called on your behalf
        """
        "*** YOUR CODE HERE ***"
        qValue = self.getQValue(state, action)
        nextQValue = self.computeValueFromQValues(nextState)
        sample = reward + self.discount * nextQValue
        self.qValues[(state, action)] = (1 - self.alpha) * qValue + self.alpha * sample

    def getPolicy(self, state):
        return self.computeActionFromQValues(state)

    def getValue(self, state):
        return self.computeValueFromQValues(state)


class PacmanQAgent(QLearningAgent):
    "Exactly the same as QLearningAgent, but with different default parameters"

    def __init__(self, epsilon=0.05,gamma=0.8,alpha=0.2, numTraining=0, **args):
        """
        These default parameters can be changed from the pacman.py command line.
        For example, to change the exploration rate, try:
            python pacman.py -p PacmanQLearningAgent -a epsilon=0.1

        alpha    - learning rate
        epsilon  - exploration rate
        gamma    - discount factor
        numTraining - number of training episodes, i.e. no learning after these many episodes
        """
        args['epsilon'] = epsilon
        args['gamma'] = gamma
        args['alpha'] = alpha
        args['numTraining'] = numTraining
        self.index = 0  # This is always Pacman
        QLearningAgent.__init__(self, **args)

    def getAction(self, state):
        """
        Simply calls the getAction method of QLearningAgent and then
        informs parent of action for Pacman.  Do not change or remove this
        method.
        """
        action = QLearningAgent.getAction(self,state)
        self.doAction(state,action)
        return action


class ApproximateQAgent(PacmanQAgent):
    """
        ApproximateQLearningAgent

        You should only have to overwrite getQValue
        and update.  All other QLearningAgent functions
        should work as is.
    """
    def __init__(self, extractor='IdentityExtractor', **args):
        self.featExtractor = util.lookup(extractor, globals())()
        PacmanQAgent.__init__(self, **args)
        self.weights = util.Counter()

    def getWeights(self):
        return self.weights

    ''' getQValue - This function is called by the parent class to get the Q-Value of a state-action pair
          Input:
            state - The current state
            action - The action taken in the current state
          Algorithm:
            * Get the feature vector of the current state and action
            * Calculate the Q-Value of the state-action pair
          Output:
            qValue - The Q-Value of the state-action pair
    '''
    def getQValue(self, state, action):
        """
          Should return Q(state,action) = w * featureVector
          where * is the dotProduct operator
        """
        "*** YOUR CODE HERE ***"
        featureVector = self.featExtractor.getFeatures(state, action)
        qValue = 0
        for feature in featureVector:
            qValue += self.weights[feature] * featureVector[feature]
        return qValue

    ''' update - This function is called by the parent class to observe a state = action => nextState and reward transition
          Input:
            state - The current state
            action - The action taken in the current state
            nextState - The next state
            reward - The reward received after taking the action in the current state
          Algorithm:
            * Get the feature vector of the current state and action
            * Calculate the difference between the reward and the Q-Value of the current state and action
            * Update the weights of the feature vector using the difference
          Output:
            None
    '''
    def update(self, state, action, nextState, reward):
        """
            Should update your weights based on transition
        """
        "*** YOUR CODE HERE ***"
        featureVector = self.featExtractor.getFeatures(state, action)
        difference = (reward + self.discount * self.computeValueFromQValues(nextState)) - self.getQValue(state, action)
        for feature in featureVector:
            self.weights[feature] += self.alpha * difference * featureVector[feature]

    def final(self, state):
        "Called at the end of each game."
        # call the super-class final method
        PacmanQAgent.final(self, state)

        # did we finish training?
        if self.episodesSoFar == self.numTraining:
            # you might want to print your weights here for debugging
            "*** YOUR CODE HERE ***"
            pass
