# valueIterationAgents.py
# -----------------------
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


# valueIterationAgents.py
# -----------------------
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


import mdp, util

from learningAgents import ValueEstimationAgent
import collections

class ValueIterationAgent(ValueEstimationAgent):
    """
        * Please read learningAgents.py before reading this.*

        A ValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100):
        """
            Your value iteration agent should take an mdp on
            construction, run the indicated number of iterations
            and then act according to the resulting policy.

            Some useful mdp methods you will use:
                mdp.getStates()
                mdp.getPossibleActions(state)
                mdp.getTransitionStatesAndProbs(state, action)
                mdp.getReward(state, action, nextState)
                mdp.isTerminal(state)
        """
        self.mdp = mdp
        self.discount = discount
        self.iterations = iterations
        self.values = util.Counter() # A Counter is a dict with default 0
        self.runValueIteration()

    ''' runValueIteration - Runs the value iteration algorithm for a given number of iterations.
            Input:
                self - The ValueIterationAgent object
            Algorithm:
                * For each iteration in the range of the number of iterations, do:
                    * Get the list of states from the MDP.
                    * Initialize a temporary counter.
                    * For each state in the list of states, do:
                        * Initialize the maximum value to negative infinity.
                        * For each action in the possible actions for the state, do:
                            * Compute the Q-value of the state-action pair.
                            * If the Q-value is greater than the maximum value, update the maximum value.
                        * Set the value of the state in the temporary counter to the maximum value.
                    * Update the values of the states to the values in the temporary counter.
            Output:
                Updates the values of the states in the MDP.s
    '''
    def runValueIteration(self):
        # Write value iteration code here
        "*** YOUR CODE HERE ***"
        for i in range(self.iterations):
            states = self.mdp.getStates()
            temp_counter = util.Counter()
            for state in states:
                maxVal = float("-inf")
                for action in self.mdp.getPossibleActions(state):
                    q = self.computeQValueFromValues(state, action)
                    if q > maxVal:
                        maxVal = q
                    temp_counter[state] = maxVal
            self.values = temp_counter


    def getValue(self, state):
        """
            Return the value of the state (computed in __init__).
        """
        return self.values[state]

    ''' computeQValueFromValues - Computes the Q-value of a state-action pair based on the values computed in the value iteration.
            Input:
                self - The ValueIterationAgent object
                state - The state for which the Q-value is to be computed
                action - The action for which the Q-value is to be computed
            Algorithm:
                * Get the transition states and probabilities for the state-action pair.
                * Initialize the total to 0.
                * For each next state and probability in the transition states and probabilities, do:
                    * Get the reward for the state-action pair.
                    * Add the product of the probability, reward, and the discount factor to the total.
                * Return the total.
            Output:
                The Q-value of the state-action pair based on the values computed in the value iteration.
    '''
    def computeQValueFromValues(self, state, action):
        """
            Compute the Q-value of action in state from the
            value function stored in self.values.
        """
        "*** YOUR CODE HERE ***"
        action_prob_pairs = self.mdp.getTransitionStatesAndProbs(state, action)
        total = 0
        for next_state, prob in action_prob_pairs:
            reward = self.mdp.getReward(state, action, next_state)
            total += prob * (reward + self.discount * self.values[next_state])
        return total

    ''' computeActionFromValues - Returns the best action for a state based on the values computed in the value iteration.
            Input:
                self - The ValueIterationAgent object
                state - The state for which the best action is to be computed
            Algorithm:
                * Initialize the best action to None and the maximum value to negative infinity.
                * For each action in the possible actions for the state, do:
                    * Compute the Q-value of the state-action pair.
                    * If the Q-value is greater than the maximum value, update the maximum value and the best action.
                * Return the best action.
            Output:
                The best action for the state based on the values computed in the value iteration.
    '''
    def computeActionFromValues(self, state):
        """
            The policy is the best action in the given state
            according to the values currently stored in self.values.

            You may break ties any way you see fit.  Note that if
            there are no legal actions, which is the case at the
            terminal state, you should return None.
        """
        "*** YOUR CODE HERE ***"
        bestAction = None
        maxVal = float("-inf")
        for action in self.mdp.getPossibleActions(state):
            q = self.computeQValueFromValues(state, action)
            if q > maxVal:
                maxVal = q
                bestAction = action
        return bestAction

    def getPolicy(self, state):
        return self.computeActionFromValues(state)

    def getAction(self, state):
        "Returns the policy at the state (no exploration)."
        return self.computeActionFromValues(state)

    def getQValue(self, state, action):
        return self.computeQValueFromValues(state, action)

class AsynchronousValueIterationAgent(ValueIterationAgent):
    """
        * Please read learningAgents.py before reading this.*

        An AsynchronousValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs cyclic value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 1000):
        """
            Your cyclic value iteration agent should take an mdp on
            construction, run the indicated number of iterations,
            and then act according to the resulting policy. Each iteration
            updates the value of only one state, which cycles through
            the states list. If the chosen state is terminal, nothing
            happens in that iteration.

            Some useful mdp methods you will use:
                mdp.getStates()
                mdp.getPossibleActions(state)
                mdp.getTransitionStatesAndProbs(state, action)
                mdp.getReward(state)
                mdp.isTerminal(state)
        """
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    ''' runValueIteration - Runs the cyclic value iteration algorithm for a given number of iterations.
            Input:
                self - The AsynchronousValueIterationAgent object
            Algorithm:
                * Get the list of states from the MDP.
                * For each iteration in the range of the number of iterations, do:
                    * Get the state at the current iteration.
                    * If the state is not a terminal state, do:
                        * Initialize an empty list values.
                        * For each action in the possible actions for the state, do:
                            * Compute the Q-value of the state-action pair.
                            * Add the Q-value to the values list.
                        * Set the value of the state to the maximum value in the values list.
            Output:
                Updates the values of the states in the MDP.
    '''
    def runValueIteration(self):
        "*** YOUR CODE HERE ***"
        states = self.mdp.getStates()
        num_states = len(states)
        for i in range(self.iterations):
            state = states[i % num_states]
            if not self.mdp.isTerminal(state):
                values = []
                for action in self.mdp.getPossibleActions(state):
                    q = self.computeQValueFromValues(state, action)
                    values.append(q)
                self.values[state] = max(values)

class PrioritizedSweepingValueIterationAgent(AsynchronousValueIterationAgent):
    """
        * Please read learningAgents.py before reading this.*

        A PrioritizedSweepingValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs prioritized sweeping value iteration
        for a given number of iterations using the supplied parameters.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100, theta = 1e-5):
        """
            Your prioritized sweeping value iteration agent should take an mdp on
            construction, run the indicated number of iterations,
            and then act according to the resulting policy.
        """
        self.theta = theta
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    ''' runValueIteration - Runs the prioritized sweeping value iteration algorithm for a given number of iterations.
            Input:
                self - The PrioritizedSweepingValueIterationAgent object
            Algorithm:
                * Initialize an empty priority queue.
                * Initialize an empty dictionary predecessors.
                * For each state in the MDP, do:
                    * If the state is not a terminal state, do:
                        * For each action in the possible actions for the state, do:
                            * For each possible next state and probability in the transition function for the state and action, do:
                                * If the next state is already in predecessors, add the state to the predecessors of the next state.
                                * Else, create a new key for the next state in predecessors and set its value to a set containing the state.
                * For each state in the MDP, do:
                    * If the state is not a terminal state, do:
                        * Initialize an empty list values.
                        * For each action in the possible actions for the state, do:
                            * Compute the Q-value of the state-action pair.
                            * Add the Q-value to the values list.
                        * Compute the absolute difference between the maximum value in the values list and the current value of the state.
                        * Push the state into the priority queue with a priority of -diff.
                * For each iteration in the range of the number of iterations, do:
                    * If the priority queue is empty, break.
                    * Pop the state with the highest priority from the priority queue.
                    * If the state is not a terminal state, do:
                        * Initialize an empty list values.
                        * For each action in the possible actions for the state, do:
                            * Compute the Q-value of the state-action pair.
                            * Add the Q-value to the values list.
                        * Set the value of the state to the maximum value in the values list.
                    * For each predecessor of the state, do:
                        * If the predecessor is not a terminal state, do:
                            * Initialize an empty list values.
                            * For each action in the possible actions for the predecessor, do:
                                * Compute the Q-value of the predecessor-action pair.
                                * Add the Q-value to the values list.
                                * Compute the absolute difference between the maximum value in the values list and the current value of the predecessor.
                                * If the difference is greater than theta, push the predecessor into the priority queue with a priority of -diff.
            Output:
                Updates the values of the states in the MDP.s
    '''
    def runValueIteration(self):
        "*** YOUR CODE HERE ***"
        # Initialize priority queue and predecessors dictionary
        priorityQueue = util.PriorityQueue()
        predecessors = {}
        # Compute predecessors for each state
        for state in self.mdp.getStates():
            if not self.mdp.isTerminal(state):
                for action in self.mdp.getPossibleActions(state):
                    for nextState, prob in self.mdp.getTransitionStatesAndProbs(state, action):
                        if prob > 0:
                            if nextState not in predecessors:
                                predecessors[nextState] = set()
                            predecessors[nextState].add(state)
        # Initialize the priority queue with the states
        for state in self.mdp.getStates():
            if not self.mdp.isTerminal(state):
                maxQValue = float('-inf')
                for action in self.mdp.getPossibleActions(state):
                    qValue = self.computeQValueFromValues(state, action)
                    maxQValue = max(maxQValue, qValue)
                diff = abs(self.values[state] - maxQValue)
                priorityQueue.update(state, -diff)
        # Perform the prioritized sweeping value iteration
        for i in range(self.iterations):
            if priorityQueue.isEmpty():
                break
            state = priorityQueue.pop()
            if not self.mdp.isTerminal(state):
                maxQValue = float('-inf')
                for action in self.mdp.getPossibleActions(state):
                    qValue = self.computeQValueFromValues(state, action)
                    maxQValue = max(maxQValue, qValue)
                self.values[state] = maxQValue
            for pred in predecessors[state]:
                if not self.mdp.isTerminal(pred):
                    maxQValue = float('-inf')
                    for action in self.mdp.getPossibleActions(pred):
                        qValue = self.computeQValueFromValues(pred, action)
                        maxQValue = max(maxQValue, qValue)
                    diff = abs(self.values[pred] - maxQValue)
                    if diff > self.theta:
                        priorityQueue.update(pred, -diff)
