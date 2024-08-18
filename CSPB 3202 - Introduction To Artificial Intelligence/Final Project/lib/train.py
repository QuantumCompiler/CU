from agent import *

def dqn(n_episodes=2000, max_t=1000, eps_start=1.0, eps_end=0.01, eps_decay=0.995, agent_name="New_Agent"):
    env = gym.make("ALE/Asteroids-v5")
    input_shape = env.observation_space.shape
    agent = DQNAgent(input_shape=input_shape, action_size=env.action_space.n, seed=0)
    scores = []
    scores_window = deque(maxlen=100)
    eps = eps_start
    if not os.path.exists('../Agents'):
        os.makedirs('../Agents')
    if not os.path.exists('../Training Results'):
        os.makedirs('../Training Results')
    results_file = f'../Training Results/{agent_name}_Train_Results.csv'
    with open(results_file, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['Episode', 'Episode Score', 'Running Average'])
        for i_episode in range(1, n_episodes + 1):
            state, info = env.reset(seed=42)
            score = 0
            print(f"\nEpisode {i_episode}")
            for t in range(max_t):
                action = agent.act(state, eps)
                next_state, reward, terminated, truncated, info = env.step(action)
                done = terminated or truncated
                agent.step(state, action, reward, next_state, done)
                state = next_state
                score += reward
                if done:
                    break
            scores_window.append(score)
            scores.append(score)
            eps = max(eps_end, eps_decay * eps)
            running_average = np.mean(scores_window)
            print(f'\rEpisode {i_episode}\tAverage Score: {running_average:.2f}', end="")
            writer.writerow([i_episode, score, running_average])
            torch.save(agent.qnetwork_local.state_dict(), f'../Agents/{agent_name}.pth')
    env.close()
    return scores

if __name__ == "__main__":
    agent_name = input("Enter the name for this agent: ")
    scores = dqn(agent_name=agent_name)