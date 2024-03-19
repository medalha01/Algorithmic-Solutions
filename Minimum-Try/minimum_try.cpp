#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <climits>
#include <algorithm> // For std::find

bool is_number_in_vector(const std::vector<int> &vec, int number)
{
    // Using the std::find algorithm to check for the presence of 'number' in 'vec'
    if (std::find(vec.begin(), vec.end(), number) != vec.end())
    {
        // Number is found
        return true;
    }
    else
    {
        // Number is not found
        return false;
    }
}

int min_operations_to_make_permutation(const std::vector<int> *original_array)
{
    int array_size = original_array->size();
    std::vector<int> missing_numbers;

    for (int i = 1; i <= array_size; i++)
    {
        if (!is_number_in_vector(*original_array, i))
        {
            missing_numbers.push_back(i);
        }
    }

    std::vector<int> exceeding_numbers = std::vector<int>(original_array->begin(), original_array->end());
    std::sort(exceeding_numbers.begin(), exceeding_numbers.end());

    for (int i = 1; i <= array_size; i++)
    {
        auto it = std::find(exceeding_numbers.begin(), exceeding_numbers.end(), i);
        if (it != exceeding_numbers.end())
        {
            exceeding_numbers.erase(it);
        }
    }

    for (int exceeding_number : exceeding_numbers)
    {
        std::cout << "Exceeding number: " << exceeding_number << std::endl;
    }
    for (int missing_number : missing_numbers)
    {
        std::cout << "Missing number: " << missing_number << std::endl;
    }
    int total_operations = 0;

    for (int exceeding_number : exceeding_numbers)
    {
        int min_difference = INT_MAX;
        int chosen_missing_number = -1;

        for (int missing_number : missing_numbers)
        {
            int difference = std::abs(exceeding_number - missing_number);

            if (difference < min_difference)
            {
                chosen_missing_number = missing_number;
                min_difference = difference;
            }

            if (difference <= 1 or difference > min_difference)
            {
                break;
            }
        }

        total_operations += min_difference;
        auto it = std::find(missing_numbers.begin(), missing_numbers.end(), chosen_missing_number);
        if (it != missing_numbers.end())
        {
            missing_numbers.erase(it);
        }
    }

    return total_operations;
}

#include <chrono> // Include the <chrono> header file

int main()
{
    auto timer_start = std::chrono::high_resolution_clock::now(); // Add the namespace qualifier

    const std::vector<int> test_array = {1, 2, 3, 4, 6, 7, 8, 3, 2, 10, 12, 20, 34, 15, 3, 1, 7, 15, 16, 16, 35, 34};
    std::cout << "Minimum number of operations: " << min_operations_to_make_permutation(&test_array) << std::endl;

    auto timer_end = std::chrono::high_resolution_clock::now();
    auto execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(timer_end - timer_start).count();

    std::cout << "Execution time: " << execution_time << " milliseconds" << std::endl;

    return 0;
}
