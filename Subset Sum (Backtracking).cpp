#include <iostream>
using namespace std;

bool subsetSum(int arr[], int n, int sum) {
    // Base cases
    if (sum == 0)
        return true;
    if (n == 0)
        return false;

    // If current element is greater than sum, skip it
    if (arr[n - 1] > sum)
        return subsetSum(arr, n - 1, sum);

    // Include or exclude the element
    return subsetSum(arr, n - 1, sum) ||
           subsetSum(arr, n - 1, sum - arr[n - 1]);
}

int main() {
    int arr[] = {3, 34, 4, 12, 5, 2};
    int sum = 9;
    int n = sizeof(arr) / sizeof(arr[0]);

    if (subsetSum(arr, n, sum))
        cout << "Subset with given sum exists";
    else
        cout << "No subset found";

    return 0;
}