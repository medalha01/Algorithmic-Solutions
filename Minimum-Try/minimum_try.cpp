#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <climits>

// Check if a number exists in a given vector.
// Parameters:
// vec: Reference to the vector in which the number is searched.
// number: The number to search for in the vector.
// Returns true if the number is found, false otherwise.
bool is_number_in_vector(const std::vector<int> &vec, int number)
{
    // Utilize std::find to search for 'number' in 'vec'.
    if (std::find(vec.begin(), vec.end(), number) != vec.end())
    {
        return true; // The number is present in the vector.
    }
    else
    {
        return false; // The number is not present in the vector.
    }
}

// Calculate the minimum number of operations needed to transform a given array into a permutation.
// Parameters:
// original_array: Pointer to the original array of integers.
// Returns the minimum number of operations required.
int min_operations_to_make_permutation(const std::vector<int> *original_array)
{
    int array_size = original_array->size(); // Determine the size of the original array.
    std::vector<int> missing_numbers;        // Store numbers that are missing to form a perfect permutation.

    // Identify missing numbers in the range [1, array_size].
    for (int i = 1; i <= array_size; i++)
    {
        if (!is_number_in_vector(*original_array, i))
        {
            missing_numbers.push_back(i); // Add missing numbers to the vector.
        }
    }

    // Initialize a vector with elements from the original array to identify exceeding numbers.
    std::vector<int> exceeding_numbers = std::vector<int>(original_array->begin(), original_array->end());
    // Sort the vector to facilitate the removal of duplicates and identification of exceeding numbers.
    std::sort(exceeding_numbers.begin(), exceeding_numbers.end());

    // Remove one instance of each valid number to leave only exceeding numbers in the vector.
    for (int i = 1; i <= array_size; i++)
    {
        auto it = std::find(exceeding_numbers.begin(), exceeding_numbers.end(), i);
        if (it != exceeding_numbers.end())
        {
            exceeding_numbers.erase(it); // Remove the first occurrence of number 'i'.
        }
    }

    // For debugging: Print out the exceeding and missing numbers.
    for (int exceeding_number : exceeding_numbers)
    {
        std::cout << "Exceeding number: " << exceeding_number << std::endl;
    }
    for (int missing_number : missing_numbers)
    {
        std::cout << "Missing number: " << missing_number << std::endl;
    }

    // Compute the total number of operations needed to transform exceeding numbers into missing ones.
    int total_operations = 0;
    for (int exceeding_number : exceeding_numbers)
    {
        int min_difference = INT_MAX;
        int chosen_missing_number = -1;

        // Find the missing number that is closest to the current exceeding number.
        for (int missing_number : missing_numbers)
        {
            int difference = std::abs(exceeding_number - missing_number);
            if (difference < min_difference)
            {
                chosen_missing_number = missing_number;
                min_difference = difference;
            }

            // Break the loop early if an ideal pair is found or no better match is possible.
            if (difference <= 1 || difference > min_difference)
            {
                break;
            }
        }

        // Accumulate the operation cost and remove the chosen missing number from further consideration.
        total_operations += min_difference;
        auto it = std::find(missing_numbers.begin(), missing_numbers.end(), chosen_missing_number);
        if (it != missing_numbers.end())
        {
            missing_numbers.erase(it);
        }
    }

    return total_operations; // Return the total operation count required for transformation.
}

int main()
{
    // Measure the execution time of the min_operations_to_make_permutation function.
    auto timer_start = std::chrono::high_resolution_clock::now();

    // Define a test array with arbitrary values.
    const std::vector<int> test_array = {1, 2, 3, 4, 6, 7, 8, 3, 2, 10, 12, 20, 34, 15, 3, 1, 7, 15, 16, 16, 35, 34};
    // Print the minimum number of operations required to transform the test array into a permutation.
    std::cout << "Minimum number of operations: " << min_operations_to_make_permutation(&test_array) << std::endl;

    // Measure and print the execution time.
    auto timer_end = std::chrono::high_resolution_clock::now();
    auto execution_time = std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer_start).count();
    std::cout << "Execution time: " << execution_time << " milliseconds" << std::endl;

    return 0;
}
