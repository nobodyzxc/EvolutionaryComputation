#!/bin/python3.6
import sys
import matplotlib.pyplot as plt

# https://matplotlib.org/2.1.1/api/_as_gen/matplotlib.pyplot.plot.html

records = {}
config = {
        3: {'cc': 'k', 'label': 'problem 3'},
        4: {'cc': 'b', 'label': 'problem 4'},
        6: {'cc': 'r', 'label': 'problem 6'},
        7: {'cc': 'g', 'label': 'problem 7'},
}

for fidx in config.keys():
    with open(str(fidx) + '.csv', 'r') as data:
        rounds = [[int(f) for f in r.split(',')] for r in data.read().split()]
        avg = [sum(r) / len(r) for r in zip(*rounds)]
        records[fidx] = avg

records[4] = [d - 800 for d in records[4]]
records[7] = [d - 800 for d in records[7]]

def plot(idxs, fn):
    lines = [plt.plot(records[idx], 
                      config[idx]['cc'],
                      label=config[idx]['label'])
                for idx in idxs]

    plt.legend(loc='best')
    plt.ylabel('fitness')
    plt.xlabel('generation')
    plt.savefig(fn)
    plt.close()

plot([3], '3.png')
plot([4], '4.png')
plot([3, 4], '3n4.png')
plot([6], '6.png')
plot([7], '7.png')
plot([6, 7], '6n7.png')
plot(config.keys(), 'summary.png')
