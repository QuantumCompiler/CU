import gymnasium as gym
import torch
import random
import numpy as np
from collections import deque
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
import ale_py
import os
import csv

# Set device
if torch.cuda.is_available():
    device = torch.device("cuda")
elif torch.backends.mps.is_available():
    device = torch.device("mps")
else:
    device = torch.device("cpu")

''' QNetwork Class - Deep Q-Network
    The QNetwork class defines a neural network model that will be used to approximate the Q-value function.
    The model consists of three fully connected layers with ReLU activation functions.
    The input to the model is the state and the output is the Q-value for each action.
    The model is initialized with kaiming_uniform_ weights and zero biases.
    The forward method defines the forward pass of the model.
    The _init_weights method initializes the weights and biases of the model.
'''
class QNetwork(nn.Module):
    ''' Constructor
            Input:
                input_shape: tuple - shape of the input state
                action_size: int - number of actions
                seed: int - random seed
            Algorithm:
                * Initialize the parent class
                * Define the model architecture
                * Initialize the weights and biases of the model
    '''
    def __init__(self, input_shape, action_size, seed):
        super(QNetwork, self).__init__()
        self.seed = torch.manual_seed(seed)
        self.input_shape = input_shape
        flattened_size = np.prod(input_shape)
        self.model = nn.Sequential(
            nn.Flatten(),
            nn.Linear(flattened_size, 64),
            nn.ReLU(),
            nn.Linear(64, 64),
            nn.ReLU(),
            nn.Linear(64, action_size)
        )
        self._init_weights()

    ''' forward - Forward Pass Method
            Input:
                state: tensor - input state
            Algorithm:
                * Flatten the input state
                * Pass the flattened state through the model
            Output:
                tensor - Q-value for each action
    '''
    def forward(self, state):
        state = state.view(-1, *self.input_shape)
        state = state.view(state.size(0), -1)
        return self.model(state)
    
    ''' _init_weights - Initialize Weights Method
            Input:
                None
            Algorithm:
                * Initialize the weights and biases of the model using kaiming_uniform_ and constant_ functions
            Output:
                None
    '''
    def _init_weights(self):
        for layer in self.model:
            if isinstance(layer, nn.Linear):
                nn.init.kaiming_uniform_(layer.weight, nonlinearity='relu')
                nn.init.constant_(layer.bias, 0)

''' DQNAgent Class - Deep Q-Network Agent
    The DQNAgent class defines an agent that uses a Deep Q-Network to learn the Q-value function.
    The agent interacts with the environment, stores experiences in a replay buffer, and updates the Q-network.
    The agent uses an epsilon-greedy policy to select actions during training.
    The agent uses a target network to stabilize learning.
    The agent uses a replay buffer to store experiences and sample mini-batches for training.
    The agent uses a soft update to update the target network.
    The agent uses a mean squared error loss function to update the Q-network.
    The agent uses an Adam optimizer to update the Q-network.
    The agent uses a discount factor to balance immediate and future rewards.
    The agent uses a tau parameter to control the rate of target network updates.
    The agent uses a batch size to control the number of experiences used for training.
    The agent uses an update frequency to control how often the Q-network is updated.
    The agent uses an epsilon decay parameter to control the rate of exploration.
    The agent uses an epsilon minimum parameter to control the minimum exploration rate.
    The agent uses a random seed to control the randomness of the agent.
    The agent uses a device to control whether to use a GPU or CPU.
    The agent uses a memory buffer to store experiences.
'''
class DQNAgent:
    ''' Constructor
            Input:
                input_shape: tuple - shape of the input state
                action_size: int - number of actions
                seed: int - random seed
            Algorithm:
                * Initialize the input_shape, action_size, and seed
                * Initialize the local and target Q-networks
                * Initialize the optimizer
                * Initialize the memory buffer
                * Initialize the batch size
                * Initialize the discount factor
                * Initialize the tau parameter
                * Initialize the update frequency
                * Initialize the epsilon
                * Initialize the epsilon decay
                * Initialize the epsilon minimum
    '''
    def __init__(self, input_shape, action_size, seed):
        self.input_shape = input_shape
        self.action_size = action_size
        self.seed = random.seed(seed)
        self.qnetwork_local = QNetwork(input_shape, action_size, seed).to(device)
        self.qnetwork_target = QNetwork(input_shape, action_size, seed).to(device)
        self.optimizer = optim.Adam(self.qnetwork_local.parameters(), lr=1e-3)
        self.memory = deque(maxlen=int(1e5))
        self.batch_size = 64
        self.gamma = 0.99
        self.tau = 1e-3
        self.update_every = 4
        self.t_step = 0
        self.eps = 1.0
        self.eps_min = 0.01
        self.eps_decay = 0.995

    ''' step - Step Method
            Input:
                state: array - input state
                action: int - action taken
                reward: float - reward received
                next_state: array - next state
                done: bool - episode termination flag
            Algorithm:
                * Store the experience in the memory buffer
                * Update the Q-network
                * Decay the epsilon
            Output:
                None
    '''
    def step(self, state, action, reward, next_state, done):
        self.memory.append((state, action, reward, next_state, done))
        self.t_step = (self.t_step + 1) % self.update_every
        if self.t_step == 0:
            if len(self.memory) > self.batch_size:
                experiences = self.sample()
                self.learn(experiences, self.gamma)

    ''' act - Decides the action to take
            Input:
                state: array - input state
                eps: float - epsilon value
            Algorithm:
                * Evaluate the Q-values using the local Q-network
                * Choose the action using an epsilon-greedy policy
            Output:
                int - action to take
    '''
    def act(self, state, eps=None):
        if eps is None:
            eps = self.eps
        state = torch.from_numpy(state).float().unsqueeze(0).to(device)
        self.qnetwork_local.eval()
        with torch.no_grad():
            action_values = self.qnetwork_local(state)
        self.qnetwork_local.train()
        if np.random.rand() > eps:
            return np.argmax(action_values.cpu().data.numpy())
        else:
            return np.random.choice(np.arange(self.action_size))
        
    ''' sample - Samples with replacement from the memory buffer
            Input:
                None
            Algorithm:
                * Sample experiences from the memory buffer
                * Convert the experiences to tensors
    '''
    def sample(self):
        experiences = random.sample(self.memory, k=self.batch_size)
        states, actions, rewards, next_states, dones = zip(*experiences)
        states = torch.from_numpy(np.vstack(states)).float().to(device)
        actions = torch.from_numpy(np.vstack(actions)).long().to(device)
        rewards = torch.from_numpy(np.vstack(rewards)).float().to(device)
        next_states = torch.from_numpy(np.vstack(next_states)).float().to(device)
        dones = torch.from_numpy(np.vstack(dones).astype(np.uint8)).float().to(device)
        return (states, actions, rewards, next_states, dones)

    ''' learn - Updates the Q-network
            Input:
                experiences: tuple - batch of experiences
                gamma: float - discount factor
            Algorithm:
                * Compute the Q-values for the next states using the target Q-network
                * Compute the Q-targets using the rewards and Q-values
                * Compute the Q-values for the current states using the local Q-network
                * Compute the loss using the Q-values and Q-targets
                * Update the Q-network using the loss
                * Soft update the target Q-network
            Output:
                None
    '''
    def learn(self, experiences, gamma):
        states, actions, rewards, next_states, dones = experiences
        Q_targets_next = self.qnetwork_target(next_states).detach().max(1)[0].unsqueeze(1)
        Q_targets = rewards + (gamma * Q_targets_next * (1 - dones))
        Q_expected = self.qnetwork_local(states).gather(1, actions)
        loss = F.mse_loss(Q_expected, Q_targets)
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()
        self.soft_update(self.qnetwork_local, self.qnetwork_target, self.tau)

    ''' soft_update - Soft Updates the target Q-network
            Input:
                local_model: QNetwork - local Q-network
                target_model: QNetwork - target Q-network
                tau: float - tau parameter
            Algorithm:
                * Update the target Q-network using the local Q-network
            Output:
                None
    '''
    def soft_update(self, local_model, target_model, tau):
        for target_param, local_param in zip(target_model.parameters(), local_model.parameters()):
            target_param.data.copy_(tau * local_param.data + (1.0 - tau) * target_param.data)

    ''' decay_epsilon - Decays the epsilon value
            Input:
                None
            Algorithm:
                * Decay the epsilon value
            Output:
                None
    '''
    def decay_epsilon(self):
        self.eps = max(self.eps_min, self.eps_decay * self.eps)