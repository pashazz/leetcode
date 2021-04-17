from typing import List


def permutations(array : List):
    stack = [(i, ) for i in array]
    results = []
    while stack:
        elem = stack.pop() # pop(0) for BFS, pop() for DFS
        if len(elem) == len(array):
            results.append(elem)
        else:
            for remaining in filter(lambda item: item not in elem, array):
                stack.append((*elem, remaining,))

    return results

print(permutations([1,2,3]))
