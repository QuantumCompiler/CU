#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Filter.h"

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

class Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  } else {
    cerr << "Bad input in readFilter:" << filename << endl;
    exit(-1);
  }
}

/* Improvements compared to original code
    * Reordering of loop so that less cache locality and chache misses are improved
    * Parallel processing (pragma omp parallel for) - Allows for simultaneous computation decreasing the time needed to process values
    * Filter values are pre-computed and not computed inside the loop, decreases the number of function calls for the same value
    * Width, height, and divisor are calculated one time, instead of multiple times
    * Output pixel is calculated directly instead of with nested loops
    * Conditional checks are node inline with the max function, clamping the values between 0 and 255
*/
double
applyFilter(class Filter *filter, cs1300bmp *input, cs1300bmp *output)
{
    long long cycStart, cycStop;

    cycStart = rdtscll();

    output -> width = input -> width;
    output -> height = input -> height;

    int f00 = filter -> get(0,0);
    int f01 = filter -> get(0,1);
    int f02 = filter -> get(0,2);
    int f10 = filter -> get(1,0);
    int f11 = filter -> get(1,1);
    int f12 = filter -> get(1,2);
    int f20 = filter -> get(2,0);
    int f21 = filter -> get(2,1);
    int f22 = filter -> get(2,2);
    
    int width = input -> width - 1;
    int height = input -> height - 1;

    int divisor = filter -> getDivisor();
    
    #pragma omp parallel for
    for (int plane = 0; plane < 3; plane++) {
      for (int row = 1; row < height; row++) {
        for (int col = 1; col < width; col++) {
          output -> color[plane][row][col] = 0;
          int t00 = (input -> color[plane][row - 1][col - 1] * f00);
          int t01 = (input -> color[plane][row - 1][col] * f01);
          int t02 = (input -> color[plane][row - 1][col + 1] * f02);
          int t10 = (input -> color[plane][row][col - 1] * f10);
          int t11 = (input -> color[plane][row][col] * f11);
          int t12 = (input -> color[plane][row][col + 1] * f12);
          int t20 = (input -> color[plane][row + 1][col - 1] * f20);
          int t21 = (input -> color[plane][row + 1][col] * f21);
          int t22 = (input -> color[plane][row + 1][col + 1] * f22);
          int sum = t00 + t01 + t02 + t10 + t11 + t12 + t20 + t21 + t22;
          int result = sum / divisor;
          result = std::max(0, std::min(result, 255));
          output -> color[plane][row][col] = result;
        }
      }
    }
    
  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}