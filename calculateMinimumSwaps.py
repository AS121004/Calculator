def calculateMinimumSwaps(fileSize, affinity):
    # Count the number of conflicts and their frequency
    conflict_count = 0
    frequency = {}

    for i in range(len(fileSize)):
        if fileSize[i] == affinity[i]:
            conflict_count += 1
            frequency[affinity[i]] = frequency.get(affinity[i], 0) + 1

    # If all files are in conflict and are the same, return -1
    if conflict_count == len(fileSize) and len(frequency) == 1:
        return -1

    # Determine the maximum frequency of any affinity value in conflicts
    max_count = max(frequency.values(), default=0)
    # Calculate the number of pairs that can be fixed by swaps
    pairs = min(conflict_count // 2, conflict_count - max_count)
    # Minimum operations needed
    min_operations = conflict_count - pairs

    return min_operations
