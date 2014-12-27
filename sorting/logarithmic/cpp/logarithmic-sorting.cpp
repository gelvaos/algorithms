#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>

using ::std::swap;
using ::std::vector;
using ::std::cout;
using ::std::endl;



//////////////////////////////////
//  HEAP SORT
//////////////////////////////////

/**
 * @brief         Add element and restore heap structure as binary heap
 * @param[in/out] array - STL compatible container object
 *                        which contains initial data to sort
 *                        and will contain elements in binary heap format
 *                        i.e. array[0] will be root of the tree
 * @param[in]     k - element to add to heap
 * @param[in]     n - size of heap
 */
template <class T> void heapify (T &array, size_t k, size_t n) {

  if (n == 0) return;

  // typename std::iterator_traits<typename T::const_iterator>::value_type tmp_value = array[k];

  while (k <= n/2) {
    // take left child
    size_t child = 2 * k + 1;
    // if it is out of array break
    if (child >= n) break;
    // compare with right child and keep the max one
    if ((child < n) && (array[child] < array[child + 1])) child++;
    // compare parent node with child and if it is higher stop the loop
    if (array[k] >= array[child]) break;
    // otherwise we need to swap them
    swap(array[k], array[child]);
    // and process the same procedure for swapped child
    k = child;
  }
  //  array[k] = tmp_value;
}

/**
 * @brief         Heap Sort algorithm implementation
 * @param[in/out] array - STL compatible container object
 *                        which contains initial data to sort
 *                        and will contain sorted data after
 *                        function calling
 */
template <class T> void heapsort (T &array) {

  typename T::size_type n = array.size();
  int i;

  for (i = n/2 - 1; i >= 0; i--)
    heapify(array, i, n - 1);

  for (i=n-1; i >= 1; i--) {
    swap(array[0], array[i]);
    heapify(array, 0, i-1);
  }
}

//////////////////////////////////
//  MERGE SORT
//////////////////////////////////

/**
 * @brief         Merge Sort algorithm implementation
 * @param[in/out] array - STL compatible container object
 *                        which contains initial data to sort
 *                        and will contain sorted data
 *                        function calling
 */
template <class T> void mergesort (T &array) {

  typename T::size_type n = array.size();

  size_t m = 1;
  size_t i = 0;
  size_t left_begin, left_end, right_begin, right_end;
  while (m < n) {
    i = 0;
    cout << "m=" << m << endl;
    while (i < n - m) {
      left_begin = i;
      left_end = i + m - 1;
      right_begin = i + m;
      right_end = std::min (i + 2 * m - 1, n - 1);
      // cout << "i=" << i << endl;
      cout << "left_begin="<< left_begin << " left_end=" << left_end << " right_begin=" << right_begin << " right_end=" << right_end << endl;
      merge (array, left_begin, left_end, right_begin, right_end);
      i += 2 * m;
    }
    m *= 2;
  }
}

// template <class T> void merge (T &array, int l, int m, int r)
// {
//   T buffer(r - l + 1); // результирующий массив
//   int pos1 = l;  // начальная позициция первого подмассива
//   int pos2 = m+1; // начальная позиция второго подмассива
//   int posB = 0;  // начальная позиция результирующего массива

//   while (pos1<=m && pos2<=r)
//   {
//     if (mas[pos1]<mas[pos2])
//       buffer[posB++] = mas[pos1++];
//     else
//       buffer[posB++] = mas[pos2++];
//   }
//   while (pos1<=m)
//     buffer[posB++] = mas[pos1++];
//   while (pos2<=r)
//     buffer[posB++] = mas[pos2++];

//   copy(buffer.begin(),buffer.end(),mas.begin() + l);
//   buffer.clear();
// }

template <class T> void merge(T &array, size_t left_begin, size_t left_end, size_t right_begin, size_t right_end) {
  for (; left_begin < right_begin; left_begin++) {
    if (array[right_begin] < array[left_begin]) {
      typename std::iterator_traits<typename T::const_iterator>::value_type v = array[left_begin];
      swap (array[left_begin], array[right_begin]);
      print_array(array);
      insert (array, right_begin, array.size() - 1, v);
      print_array(array);
    }
  }
}

template <typename T, typename VT> void insert(T &array, size_t begin, size_t end, VT &v) {
  while ((begin < end) && (array[begin + 1] < v)) {
    // cout << "begin=" << begin << " end=" << end << endl;
    // cout << "swap (array[begin], array[begin + 1]): " << array[begin] << " " << array[begin+1] << endl;
    swap (array[begin], array[begin + 1]);
    // print_array(array);
    ++begin;
  }
  swap (array[begin], v);
}

//////////////////////////////////
//  QUICK SORT
//////////////////////////////////

/**
 * @brief         Quick Sort algorithm implementation
 * @param[in/out] array - STL compatible container object
 *                        which contains initial data to sort
 *                        and will contain sorted data after
 *                        function calling
 */
template <class T> void quicksort (T &array) {}



/**************************************************
 *        HELPER FUNCTIONS
 **************************************************/

template <class T> void print_array(T &array) {
  typename T::const_iterator it;
  for (it = array.begin(); it != array.end(); it++) cout << *it << " ";
  cout << endl;
}

template <class T> void init_array(T &array) {
  array.erase(array.begin(), array.end());
  for (int i=10; i > 0; i--) array.push_back(i);
}

int main(void) {
  vector<int> testvec;
  vector<int>::const_iterator it;

  cout << "Selection sort" << endl;
  init_array(testvec);
  print_array(testvec);
  selectionsort(testvec);
  print_array(testvec);

  cout << "Insertion sort" << endl;
  init_array(testvec);
  print_array(testvec);
  insertionsort(testvec);
  print_array(testvec);

  vector<int> ttt;
  ttt.push_back(22);
  ttt.push_back(100);
  ttt.push_back(44);
  ttt.push_back(15);
  ttt.push_back(2);
  ttt.push_back(36);
  ttt.push_back(53);
  ttt.push_back(23);
  ttt.push_back(82);
  ttt.push_back(5);

  cout << "Heap sort" << endl;
  print_array(ttt);
  heapsort(ttt);
  print_array(ttt);

  init_array(testvec);
  print_array(testvec);
  heapsort(testvec);
  print_array(testvec);


  cout << "Merge sort" << endl;
  init_array(testvec);
  print_array(testvec);
  mergesort(testvec);
  print_array(testvec);

  return 0;
}
