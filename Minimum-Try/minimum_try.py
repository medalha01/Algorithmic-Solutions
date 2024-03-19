from typing import List
import time


def min_operations_to_make_permutation(arr: List[int]) -> int:
    """
    Calculate the minimum number of operations needed to rearrange the elements
    of the given array `arr` such that it becomes a permutation of the first
    n natural numbers, where n is the length of `arr`.

    An operation consists of replacing an element in the array with a missing number
    to form a continuous range from 1 to n.

    :param arr: List[int] - The input array to be transformed into a permutation.
    :return: int - The minimum number of operations required.
    """
    array_size = len(arr)
    expected_numbers = set(range(1, array_size + 1))
    missing_numbers = sorted(expected_numbers.difference(set(arr)))

    # Sort and identify numbers that exceed the expected range
    exceeding_numbers = sorted(arr)
    for number in expected_numbers:
        if number in exceeding_numbers:
            exceeding_numbers.remove(number)

    total_operations = 0

    # Pair each exceeding number with the closest missing number
    for exceeding_number in exceeding_numbers:
        min_difference = None
        chosen_missing_number = None

        # Find the missing number that is closest to the current exceeding number
        for missing_number in missing_numbers:
            difference = abs(exceeding_number - missing_number)

            if min_difference is None or difference < min_difference:
                chosen_missing_number = missing_number
                min_difference = difference

            # Break early if we find the smallest possible difference
            if difference <= 1 or difference > min_difference:
                break

        total_operations += min_difference
        missing_numbers.remove(chosen_missing_number)

    return total_operations


# Do not modify the code below; it is used for evaluation purposes.
if __name__ == "__main__":
    timer_start = time.time()
    test_array = [
        1,
        2,
        3,
        4,
        6,
        7,
        8,
        3,
        2,
        10,
        12,
        20,
        34,
        15,
        3,
        1,
        7,
        15,
        16,
        16,
        35,
        34,
    ]
    print(
        f"Minimum number of operations: {min_operations_to_make_permutation(test_array)}"
    )
    timer_end = time.time()

    execution_time = timer_end - timer_start
    print(f"Execution time: {execution_time} seconds")
