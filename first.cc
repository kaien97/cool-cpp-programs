#include <iostream>
using namespace std;

int partition(int* arr, int low, int high)
{

  int pivot = arr[high];
  int i = (low - 1);

  for (int j=low; j<=high - 1; j++) {
    if (arr[j] < pivot)
        {
            i++;    // increment index of smaller element
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
  }
  int temp = arr[i+1];
  arr[i+1] = arr[high];
  arr[high] = temp;
  return (i + 1);
}

int* quickSort(int* arr, int low, int high)
{
  if (low < high) {
    // pi is partitioning index
    int pi = partition(arr, low, high);

    arr = quickSort(arr, low, pi - 1);
    arr = quickSort(arr, pi + 1, high);
  } else {
    return arr;
  }
}

int main()
{

  int count;

  cout << "How many numbers do you want to enter? " << endl;
  cin >> count;

  int *a, *result;
  for (int i = 0; i < count; i++) {
    cout << "Enter a number here: " << endl;
    cin >> a[i];
  }

  result = quickSort(a, 0, count - 1);
  cout << "The sorted array is " << a << endl;

  return 0;
}
