#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

#include <boost/cstdint.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

using ::std::vector;
using ::std::cout;
using ::std::endl;
using ::std::ifstream;
using ::std::ofstream;
using ::std::swap;
using ::std::string;
using ::std::ios;
using ::std::setw;

typedef boost::posix_time::ptime Time;
typedef boost::posix_time::time_duration TimeDuration;
typedef vector<uint32_t> VecUInt32;


/**
 * @brief         Selection Sort algorithm implementation
 * @param[in/out] array - STL compatible container object
 *                        which contains initial data to sort
 *                        and will contain sorted data after
 *                        function calling
 */

template <class T> void selection_sort (T &array) {
    size_t idx;
    for (size_t i=0; i < array.size(); i++) {
        idx = i; // keep the index of current item

        for (size_t j = i + 1; j < array.size(); j++)
            // find element with lower value
            if (array[j] < array[idx]) idx = j;
        // if element with lower value exists swap the positions
        if (idx != i) swap(array[i], array[idx]);
    }
}

/**
 * @brief         Insertion Sort algorithm implementation
 * @param[in/out] array - STL compatible container object
 *                        which contains initial data to sort
 *                        and will contain sorted data after
 *                        function calling
 */
template <class T> void insertion_sort (T &array) {
  for (size_t i=1; i < array.size(); i++)
    for (size_t j=i; j > 0 && array[j-1] > array[j]; j--)
      swap(array[j], array[j-1]);
}


void init_vector(VecUInt32 &v, uint32_t num_elems, string fname) {
    v.erase(v.begin(), v.end());
    v.reserve(num_elems);
    uint32_t t;

    ifstream rsfile(fname.c_str());
    if (rsfile) while (rsfile >> t) v.push_back(t);
    rsfile.close();
}

template<class T, class F> TimeDuration timing_function(T &array, F ptrSortFunc) {
    Time start(boost::posix_time::microsec_clock::local_time());
    ptrSortFunc(array);
    Time end(boost::posix_time::microsec_clock::local_time());
    return end - start;
}


template <class F> long run(VecUInt32 &v, string fname, uint32_t num_elems, int num_execs, F ptrSortFunc) {
    long sum_of_total_microsecs = 0;
    long current_microsecs = 0;
    long average = 0;
   // we will run num_execs times and calculate average
    for (int i=0; i < num_execs; i++) {
        init_vector(v, num_elems, fname);
        current_microsecs = timing_function(v, ptrSortFunc).total_microseconds();
        cout << "Current execution time: " << current_microsecs << endl;
        sum_of_total_microsecs += current_microsecs;
    }

    average = (sum_of_total_microsecs / num_execs);
    cout << "Average execution time: " << average << endl;
    return average;
}

int main(void) {
    int num_execs = 5;
    uint32_t num_elems;
    VecUInt32 v;

    long sel_rev_microsecs;
    long sel_rnd_microsecs;
    long ins_rev_microsecs;
    long ins_rnd_microsecs;


    ofstream outfile("result-cpp.dat");

    //outfile << std::setiosflags(ios::right);
    //outfile << resetiosflags(ios::right);
    outfile << "#Number-of-elements Selection-Sort-Reverse Selection-Sort-Random Insertion-Sort-Reverse Insertion-Sort-Random" << endl;

    // warm up
    init_vector(v, 100, "../data/reverse-sorted-100.dat");
    timing_function(v, selection_sort<VecUInt32>);


    num_elems = 100;
    cout << "Running on " << num_elems << " elements" << endl;
    sel_rev_microsecs = run(v, "../data/reverse-sorted-100.dat", num_elems, num_execs, selection_sort<VecUInt32>);
    sel_rnd_microsecs = run(v, "../data/random-100.dat", num_elems, num_execs, selection_sort<VecUInt32>);
    ins_rev_microsecs = run(v, "../data/reverse-sorted-100.dat", num_elems, num_execs, insertion_sort<VecUInt32>);
    ins_rnd_microsecs = run(v, "../data/random-100.dat", num_elems, num_execs, insertion_sort<VecUInt32>);

    outfile << num_elems
            << " " << sel_rev_microsecs
            << " " << sel_rnd_microsecs
            << " " << ins_rev_microsecs
            << " " << ins_rnd_microsecs << endl;


    num_elems = 1000;
    cout << "Running on " << num_elems << " elements" << endl;
    sel_rev_microsecs = run(v, "../data/reverse-sorted-1000.dat", num_elems, num_execs, selection_sort<VecUInt32>);
    sel_rnd_microsecs = run(v, "../data/random-1000.dat", num_elems, num_execs, selection_sort<VecUInt32>);
    ins_rev_microsecs = run(v, "../data/reverse-sorted-1000.dat", num_elems, num_execs, insertion_sort<VecUInt32>);
    ins_rnd_microsecs = run(v, "../data/random-1000.dat", num_elems, num_execs, insertion_sort<VecUInt32>);

    outfile << num_elems
            << " " << sel_rev_microsecs
            << " " << sel_rnd_microsecs
            << " " << ins_rev_microsecs
            << " " << ins_rnd_microsecs << endl;


    num_elems = 10000;
    cout << "Running on " << num_elems << " elements" << endl;
    sel_rev_microsecs = run(v, "../data/reverse-sorted-10K.dat", num_elems, num_execs, selection_sort<VecUInt32>);
    sel_rnd_microsecs = run(v, "../data/random-10K.dat", num_elems, num_execs, selection_sort<VecUInt32>);
    ins_rev_microsecs = run(v, "../data/reverse-sorted-10K.dat", num_elems, num_execs, insertion_sort<VecUInt32>);
    ins_rnd_microsecs = run(v, "../data/random-10K.dat", num_elems, num_execs, insertion_sort<VecUInt32>);

    outfile << num_elems
            << " " << sel_rev_microsecs
            << " " << sel_rnd_microsecs
            << " " << ins_rev_microsecs
            << " " << ins_rnd_microsecs << endl;



    num_elems = 20000;
    cout << "Running on " << num_elems << " elements" << endl;
    sel_rev_microsecs = run(v, "../data/reverse-sorted-20K.dat", num_elems, num_execs, selection_sort<VecUInt32>);
    sel_rnd_microsecs = run(v, "../data/random-20K.dat", num_elems, num_execs, selection_sort<VecUInt32>);
    ins_rev_microsecs = run(v, "../data/reverse-sorted-20K.dat", num_elems, num_execs, insertion_sort<VecUInt32>);
    ins_rnd_microsecs = run(v, "../data/random-20K.dat", num_elems, num_execs, insertion_sort<VecUInt32>);

    outfile << num_elems
            << " " << sel_rev_microsecs
            << " " << sel_rnd_microsecs
            << " " << ins_rev_microsecs
            << " " << ins_rnd_microsecs << endl;


    num_elems = 50000;
    cout << "Running on " << num_elems << " elements" << endl;
    sel_rev_microsecs = run(v, "../data/reverse-sorted-50K.dat", num_elems, num_execs, selection_sort<VecUInt32>);
    sel_rnd_microsecs = run(v, "../data/random-50K.dat", num_elems, num_execs, selection_sort<VecUInt32>);
    ins_rev_microsecs = run(v, "../data/reverse-sorted-50K.dat", num_elems, num_execs, insertion_sort<VecUInt32>);
    ins_rnd_microsecs = run(v, "../data/random-50K.dat", num_elems, num_execs, insertion_sort<VecUInt32>);

    outfile << num_elems
            << " " << sel_rev_microsecs
            << " " << sel_rnd_microsecs
            << " " << ins_rev_microsecs
            << " " << ins_rnd_microsecs << endl;


    num_elems = 100000;
    cout << "Running on " << num_elems << " elements" << endl;
    sel_rev_microsecs = run(v, "../data/reverse-sorted-100K.dat", num_elems, num_execs, selection_sort<VecUInt32>);
    sel_rnd_microsecs = run(v, "../data/random-100K.dat", num_elems, num_execs, selection_sort<VecUInt32>);
    ins_rev_microsecs = run(v, "../data/reverse-sorted-100K.dat", num_elems, num_execs, insertion_sort<VecUInt32>);
    ins_rnd_microsecs = run(v, "../data/random-100K.dat", num_elems, num_execs, insertion_sort<VecUInt32>);

    outfile << num_elems
            << " " << sel_rev_microsecs
            << " " << sel_rnd_microsecs
            << " " << ins_rev_microsecs
            << " " << ins_rnd_microsecs << endl;


    outfile.close();


    return 0;
}
