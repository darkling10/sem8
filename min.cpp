#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>

using namespace std;

void min(int *arr, int n)
{
    double min_val = 1000000;
    cout << endl;
#pragma omp parallel reduction(min : min_val)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min_val)
        {
            /* code */
            min_val = arr[i];
        }
    }

    cout << "Minimum element is : " << min_val << endl;
}

void max(int *arr, int n)
{
    double max_val = 0.0;
    cout << endl;
#pragma omp parallel reduction(max : max_val)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_val)
        {
            /* code */
            max_val = arr[i];
        }
    }

    cout << "Maximum element is : " << max_val << endl;
}

int main()
{
    int n, i;

    cout << "Enter the number of elements in the array: ";
    cin >> n;
    int arr[n];

    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 100;
    }

    cout << "\nArray elements are: ";
    for (i = 0; i < n; i++)
    {
        cout << arr[i] << ",";
    }

    min(arr, n);
    return 0;
}
