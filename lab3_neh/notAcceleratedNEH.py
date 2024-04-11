import time

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

def CalcCmax(data, schedule):
    n = data["n_of_tasks"]
    m = data["n_of_subtasks"]
    tasks = data["tasks"]
    cmax = 0

    time_matrix = [[0 for _ in range(m)] for _ in range(n)]

    for i, task in enumerate(schedule):
        for j in range(m):
            if i == 0:
                time_matrix[i][j] = (tasks[task][j] + time_matrix[i][j-1]) if j > 0 else tasks[task][j]
            else:
                time_matrix[i][j] = max(time_matrix[i-1][j], time_matrix[i][j-1]) + tasks[task][j]
        cmax = max(cmax, time_matrix[i][m-1])

    
    return cmax

def NEH(data):
    n_of_tasks = data["n_of_tasks"]
    tasks = data["tasks"]

    tasks = sorted(tasks.items(), key=lambda x: sum(x[1]), reverse=True)

    pi = [tasks[0][0]]
    time_schedule = [CalcCmax(data, pi)]

    for i in range(1, n_of_tasks):
        best_time = float('inf')
        best_index = 0

        for j in range(i + 1):
            new_schedule = pi[:j] + [tasks[i][0]] + pi[j:]
            new_time = CalcCmax(data, new_schedule)

            if new_time < best_time:
                best_time = new_time
                best_index = j

        pi.insert(best_index, tasks[i][0])
        time_schedule.append(best_time)

    return pi, time_schedule[-1]

#===================================================================================================

if __name__ == "__main__":
    data = LoadData("data.txt")

    for i, dataset in data.items():
        print(f"|Dataset {i}|")

        time_start = time.time()
        schedule, cmax = NEH(dataset)
        time_end = time.time()

        print("Time:", time_end - time_start)
        # print("Cmax:", cmax, dataset["Cmax"])
        
        if dataset["Cmax"] != cmax:
            print("Wrong schedule")
            input("Press any key to continue")
        print()

            