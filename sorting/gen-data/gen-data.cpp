#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include "randomc.h"

using ::std::cout;
using ::std::endl;
using ::std::string;
using ::std::stringstream;

int getRandomNumber(uint32_t range_min, uint32_t range_max) {
    uint32_t seed = static_cast<uint32_t>(time(NULL) + rand());
    TRandomMersenne rndgen(seed);
    return rndgen.IRandom(range_min, range_max);
}


void genDataFile(string fname_reversed, string fname_random, uint32_t num_elems) {

    std::ofstream rsfile(fname_reversed.c_str());
    if (rsfile.is_open() && rsfile.good()) {
        for (uint32_t i = num_elems; i > 0; i--) rsfile << i << "  ";
        rsfile << endl;
        rsfile.close();
    }

    rsfile.open(fname_random.c_str());
    if (rsfile.is_open() && rsfile.good()) {
        for (uint32_t i = 0; i < num_elems; i++) rsfile << getRandomNumber(0, num_elems) << " ";
        rsfile.close();
    }

}

int main(int argc, char* argv[]) {

    genDataFile("../data/reverse-sorted-100.dat", "../data/random-100.dat", 100);
    genDataFile("../data/reverse-sorted-1000.dat", "../data/random-1000.dat", 1000);
    genDataFile("../data/reverse-sorted-10K.dat", "../data/random-10Kdat", 10000);
    genDataFile("../data/reverse-sorted-20K.dat", "../data/random-20K.dat", 20000);
    genDataFile("../data/reverse-sorted-50K.dat", "../data/random-50K.dat", 50000);
    genDataFile("../data/reverse-sorted-100K.dat", "../data/random-100K.dat", 100000);
    genDataFile("../data/reverse-sorted-500K.dat", "../data/random-500K.dat", 500000);
    genDataFile("../data/reverse-sorted-1M.dat", "../data/random-1M.dat", 1000000);
    genDataFile("../data/reverse-sorted-10M.dat", "../data/random-10M.dat", 10000000);

    return 0;
}
