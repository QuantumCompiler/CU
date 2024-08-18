from agent import *

# Evaluation function
def play_game(env, agent, n_episodes=100, agent_name="New_Agent.pth"):
    agent.qnetwork_local.eval()
    scores = []
    scores_window = deque(maxlen=100)
    if not os.path.exists('../Evaluation Results'):
        os.makedirs('../Evaluation Results')
    results_file = f'../Evaluation Results/{agent_name}_Eval_Results.csv'
    with open(results_file, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['Episode', 'Episode Score', 'Running Average'])
        for i_episode in range(1, n_episodes + 1):
            state, info = env.reset(seed=42)
            score = 0
            print(f"\nPlaying episode {i_episode}")
            while True:
                action = agent.act(state, eps=None)
                next_state, reward, terminated, truncated, info = env.step(action)
                done = terminated or truncated
                state = next_state
                score += reward
                if done:
                    print(f"Episode {i_episode} finished with total reward: {score}\n")
                    break
            scores_window.append(score)
            scores.append(score)
            running_average = np.mean(scores)
            writer.writerow([i_episode, score, running_average])

if __name__ == "__main__":
    agent_name = input("Enter the name for agent you'd like to evaluate: ")
    if agent_name == "":
        agent_name = "New_Agent"
    env = gym.make("ALE/Asteroids-v5")
    input_shape = env.observation_space.shape
    agent = DQNAgent(input_shape=input_shape, action_size=env.action_space.n, seed=0)
    checkpoint = torch.load(f'../Agents/{agent_name}.pth', map_location=torch.device('cpu'), weights_only=True)
    agent.qnetwork_local.load_state_dict(checkpoint)
    play_game(env, agent, agent_name=agent_name)
    env.close()