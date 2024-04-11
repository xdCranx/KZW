import time
from dataclasses import dataclass
from typing import List

def LoadData(filename):
    with open(filename, 'r') as file:
        rows = file.readlines()

    data = {}
    while rows:
        line = rows.pop(0)
        if line.startswith("data."):
            dataset = line.replace('data.', '').replace(':', '').replace('\n', '')
            data[dataset] = {}

            line_parts = rows.pop(0).split()
            i = int(line_parts[0])
            k = int(line_parts[1])

            data[dataset]["n_of_tasks"] = i
            data[dataset]["n_of_subtasks"] = k
            data[dataset]["tasks"] = {}
            
            for i in range(i):
                data[dataset]["tasks"][i+1] = [int(x) for x in rows.pop(0).split()]
            
            while rows and not line.startswith("neh"):
                line = rows.pop(0)

            if not rows:
                break
            data[dataset].update({"Cmax": int(rows.pop(0)), "NEH": []})

            while rows and line != "\n":
                line = rows.pop(0)
                data[dataset]["NEH"].extend([int(x) for x in line.split()])

    return data

@dataclass
class Task:
    id: int
    processing_times: List[int]

@dataclass
class Node:
    task: int
    machine_index: int
    time_to: int
    time_from: int

def AddTask(graph, index, task):
    prev_node = graph[index-1] if index > 0 else None
    new_node = Node(task, 0, task.processing_times[0], 0)
    if prev_node:
        new_node.time_to += prev_node.time_to
    graph.insert(index, new_node)

def TimeFromPosition(graph):
    n = len(graph)
    for i in range(n):
        graph[i].time_from = sum(graph[i].task.processing_times)
        if i < n - 1:
            graph[i].time_from += graph[i + 1].time_from

def AccNEH(data):
    n = data["n_of_tasks"]
    tasksList = [Task(id, processing_times) for id, processing_times in data["tasks"].items()]
    tasksList.sort(key=lambda x: sum(x.processing_times), reverse=True)

    graph = []
    AddTask(graph, 0, tasksList[0])
    for i in range(1, n):
        best_time = float('inf')
        best_index = 0
        for j in range(i + 1):
            AddTask(graph, j, tasksList[i])
            TimeFromPosition(graph)
            cmax = graph[-1].time_to + graph[-1].time_from
            if cmax < best_time:
                best_time = cmax
                best_index = j
            graph.pop(j)

        AddTask(graph, best_index, tasksList[i])
        TimeFromPosition(graph)

    return graph[-1].time_from

#===================================================================================================

if __name__ == "__main__":
    data = LoadData("data.txt")

    for i, instance_data in list(data.items()):
        
        start = time.time()
        AccNEH(instance_data)
        end = time.time()
        executionTime = end - start
        print(executionTime)