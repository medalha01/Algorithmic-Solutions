import time
from itertools import permutations


def min_operations_to_form_sequence(lst):
    """
    Calculate the minimum number of operations needed to transform a given list into a sequence
    where all operations involve replacing elements to minimize their absolute differences.

    The function determines the minimum sum of absolute differences between each pair of elements
    in the given list and a sorted sequence of unique numbers from 1 to the length of the list.

    :param lst: List[int] - The input list to be transformed into a sequential form.
    :return: Tuple[int, int] - The minimum number of operations and the direct sum difference.
    """
    array_size = len(lst)

    # Identify the numbers that should be in the list to make it a proper sequence
    expected_numbers = set(range(1, array_size + 1))
    missing_numbers = sorted(expected_numbers.difference(set(lst)))
    exceeding_numbers = lst.copy()

    # Remove numbers that are already in their correct place
    for number in expected_numbers:
        if number in exceeding_numbers:
            exceeding_numbers.remove(number)

    # Sort and reverse for permutation generation
    exceeding_numbers.sort()

    # Log the missing and exceeding numbers
    for i in missing_numbers:
        print(f"Missing number: {i}")
    for i in exceeding_numbers:
        print(f"Exceeding number: {i}")

    min_operations = float("inf")

    # Check each permutation to find the one with the minimum operations needed
    for permuted_list in permutations(exceeding_numbers):
        current_operations = 0

        # Calculate the sum of absolute differences for this permutation
        for i, number in enumerate(permuted_list):
            current_operations += abs(missing_numbers[i] - number)

            # Early exit if the current sum exceeds the minimum found so far
            if current_operations > min_operations:
                break

        min_operations = min(min_operations, current_operations)

    return min_operations


# Test the function with a sample list
lst = [1, 2, 3, 4, 6, 7, 8, 3, 2, 10, 12, 20, 34, 15, 3, 1, 7, 15, 16, 16, 35, 34]

timer_start = time.time()
operations = min_operations_to_form_sequence(lst)
timer_end = time.time()

execution_time = timer_end - timer_start

print(f"Execution time: {execution_time} seconds")
print(f"Minimum operations required: {operations}")
