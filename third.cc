// ln2_estimate.cc
//    usage:
//      ./ln2_estimate.cc [<N> [<seed>]]

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

// Random value of x
#define ranx() \
  (((double)rand()/RAND_MAX)+1.0) // Uniform from interval [1, 2]

// Random value of y
#define rany() \
  (((double)rand()/RAND_MAX)) // Uniform from interval [0, 1]

float round(float var) {
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

int main(int argc, char* argv[]) {
  // Integral of (1/x)dx from x=1 to x=2 gives ln2 - ln1 = ln2
  // Hence, area under 1/x curve from x =1 to x =2 gives ln2
  // Find x in range [1, 2], y in range [0, 1]

  int outcome, N=10000, count_in=0, seed=123;
  double fraction_in;

  // If more than 1 argument (first argument is always program name)
  if(argc>1) {
    // 'Second' argument (argument at index 1) should be the value of N (optional)
    // sscanf extracts the first encountered type in second argument from first argument, and stores in third
    sscanf( argv[1], "%d", &N ); // put first command-line argument in N
  }

  if(argc>2) {
    sscanf( argv[2], "%d", &seed); //put second argument in seed
  }

  // Summary of parameters
  cout << "#" << argv[0] << " N = " << N << " seed = " << seed << endl;

  // Initialise random number generator
  srandom(seed);

  // Perform N experiments
  for(int n=1; n <= N; n++) {
    double x = ranx();
    double y = rany();
    outcome = ( (1.0/x) > y )  ? 1 : 0;   // Does (x, y) lie under the y = 1/x graph?
    count_in += outcome;

    fraction_in = static_cast<double>(count_in)/n;  // fraction of points that lies under y = 1/x graph
    // Since square defined by corners (1, 0) and (2, 1) has area of 1, fraction_in = area under y = 1/x graph
    // cout << "Current estimate of ln2 = " << fraction_in << endl;
    // previous line commented as it significantly increased lag time
  }

  cout << "Final stimate of ln2 = " << fraction_in << endl;
  return 0;
}
