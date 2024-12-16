#include <iostream>
#pragma comment(lib, "..\\Debug\\StaticLib1.lib")

extern "C" {
  int __stdcall getmin(int*, int);
  int __stdcall getmax(int*, int);
}

int main()
{
  int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int min = getmin(arr, sizeof(arr) / sizeof(int));
  int max = getmax(arr, sizeof(arr) / sizeof(int));
  std::cout << "getmin+getmax=" << min + max;
}

