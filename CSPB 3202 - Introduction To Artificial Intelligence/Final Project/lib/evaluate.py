import matplotlib.pyplot as plt
import numpy as np
import os
import csv

def evalSingle(agent, type):
    if not isinstance(agent, list):
        agent = [agent]
    vals = [{} for _ in agent]
    for i, agent_name in enumerate(agent):
        vals[i] = {
            'episode_num': [],
            'episode_score': [],
            'running_average': []
        }
        if type == 1:
            with open(f'../Training Results/{agent_name}_Train_Results.csv', 'r') as file:
                doc = csv.reader(file)
                next(doc)
                for row in doc:
                    vals[i]['episode_num'].append(int(row[0]))
                    vals[i]['episode_score'].append(float(row[1]))
                    vals[i]['running_average'].append(float(row[2]))
        elif type == 2:
            with open(f'../Evaluation Results/{agent_name}_Eval_Results.csv', 'r') as file:
                doc = csv.reader(file)
                next(doc)
                for row in doc:
                    vals[i]['episode_num'].append(int(row[0]))
                    vals[i]['episode_score'].append(float(row[1]))
                    vals[i]['running_average'].append(float(row[2]))
    width = 0.25
    fig, ax = plt.subplots(figsize=(8, 5))
    for i, agent_name in enumerate(agent):
        episode_num = vals[i]['episode_num']
        episode_score = vals[i]['episode_score']
        running_average = vals[i]['running_average']
        ax.bar(episode_num, running_average, width, label=f'{agent_name} Running Average')
        ax.bar([x + width for x in episode_num], episode_score, width, label=f'{agent_name} Episode Score')
    ax.set_xlabel('Episode Number')
    ax.set_ylabel('Score')
    if type == 1:
        ax.set_title(f'Training Results For {agent[0]} - Avg. {running_average[-1]:.2f}, Min. {min(episode_score)}, Max. {max(episode_score)}')
    elif type == 2:
        ax.set_title(f'Evaluation Results For {agent[0]} - Avg. {running_average[-1]:.2f}, Min. {min(episode_score)}, Max. {max(episode_score)}')
    ax.legend()
    plt.show()

def evalCompareSingle(agent):
    if not isinstance(agent, list):
        agent = [agent]
    trainVals = [{} for _ in agent]
    evalVals = [{} for _ in agent]
    for i, agent_name in enumerate(agent):
        trainVals[i] = {
            'episode_num': [],
            'episode_score': [],
            'running_average': []
        }    
    for i, agent_name in enumerate(agent):
        evalVals[i] = {
            'episode_num': [],
            'episode_score': [],
            'running_average': []
        }
    with open(f'../Training Results/{agent_name}_Train_Results.csv', 'r') as file:
        doc = csv.reader(file)
        next(doc)
        for row in doc:
            trainVals[i]['episode_num'].append(int(row[0]))
            trainVals[i]['episode_score'].append(float(row[1]))
            trainVals[i]['running_average'].append(float(row[2]))
    with open(f'../Evaluation Results/{agent_name}_Eval_Results.csv', 'r') as file:
        doc = csv.reader(file)
        next(doc)
        for row in doc:
            evalVals[i]['episode_num'].append(int(row[0]))
            evalVals[i]['episode_score'].append(float(row[1]))
            evalVals[i]['running_average'].append(float(row[2]))
    width = 0.75
    fig, ax = plt.subplots(figsize=(8, 5))
    ax.bar(0.5, trainVals[-1]['running_average'][-1], width, label=f'{agent[0]} Training Average')
    ax.bar(1.5, evalVals[-1]['running_average'][-1], width, label=f'{agent[0]} Testing Average')
    ax.bar(2.5, min(trainVals[i]['episode_score']), width, label=f'{agent[0]} Training Min')
    ax.bar(3.5, min(evalVals[i]['episode_score']), width, label=f'{agent[0]} Testing Min')
    ax.bar(4.5, max(trainVals[i]['episode_score']), width, label=f'{agent[0]} Training Max')
    ax.bar(5.5, max(evalVals[i]['episode_score']), width, label=f'{agent[0]} Testing Max')
    ax.set_xticks([])
    ax.set_xlabel('Evaluation Type')
    ax.set_ylabel('Score')
    ax.set_title(f'Comparison of Training and Evaluation Results For {agent[0]}')
    ax.legend()
    plt.show()

if __name__ == "__main__":
    eval_typ = input("Enter the type of evaluation you'd like to perform (1 for training, 2 for evaluation): ")
    if (eval_typ == "1"):
        # evalSingle("Agent 10", 1)
        # evalSingle("Agent 20", 1)
        # evalSingle("Agent 30", 1)
        # evalSingle("Agent 40", 1)
        # evalSingle("Agent 50", 1)
        # evalSingle("Agent 100", 1)
        # evalSingle("Agent 200", 1)
        # evalSingle("Agent 300", 1)
        # evalSingle("Agent 400", 1)
        # evalSingle("Agent 500", 1)
        evalSingle("Agent 2000", 1)
    elif (eval_typ == "2"):
        # evalSingle("Agent 10", 2)
        # evalSingle("Agent 20", 2)
        # evalSingle("Agent 30", 2)
        # evalSingle("Agent 40", 2)
        # evalSingle("Agent 50", 2)
        # evalSingle("Agent 100", 2)
        # evalSingle("Agent 200", 2)
        # evalSingle("Agent 300", 2)
        # evalSingle("Agent 400", 2)
        # evalSingle("Agent 500", 2)
        # evalSingle("Agent 1000", 2)
        evalSingle("Agent 2000", 2)
    elif (eval_typ == "3"):
        # evalCompareSingle("Agent 10")
        # evalCompareSingle("Agent 20")
        # evalCompareSingle("Agent 30")
        # evalCompareSingle("Agent 40")
        # evalCompareSingle("Agent 50")
        # evalCompareSingle("Agent 100")
        # evalCompareSingle("Agent 200")
        # evalCompareSingle("Agent 300")
        # evalCompareSingle("Agent 400")
        # evalCompareSingle("Agent 500")
        # evalCompareSingle("Agent 1000")
        evalCompareSingle("Agent 2000")
    else:
        print('Invalid input. Please enter 1 or 2.')
        exit()