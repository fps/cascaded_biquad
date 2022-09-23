#include "cascaded_biquad.h"
#include <iostream>

// These coefficients were generated with MATLAB:
// f = designfilt('lowpassiir', 'PassbandFrequency', 0.01, 'StopbandFrequency', 0.02, 'StopbandAttenuation', 32);
// f.Coefficients
const float coefficients[] = 
{
   0.000341790148053,   0.000683580296107,   0.000341790148053,   1.000000000000000,  -1.982247725220660,   0.983614885812873,
   0.000336817881561,   0.000673635763122,   0.000336817881561,   1.000000000000000,  -1.953410545448979,   0.954757816975223,
   0.000333460820498,   0.000666921640997,   0.000333460820498,   1.000000000000000,  -1.933940918565828,   0.935274761847821,
   0.018228517368043,   0.018228517368043,                   0,   1.000000000000000,  -0.963542965263913,                   0
};

#define NUM_SAMPLES 1000

int main()
{
  namespace cb = cascaded_biquad;
  float *state = cb::state<4, float>();

  float input[NUM_SAMPLES];

  // Our input is a step function
  for (int index = 0; index < NUM_SAMPLES; ++index) 
  {
    if (index < NUM_SAMPLES/2) input[index] = 0; else input[index] = 1;
  } 

  for (int index = 0; index < NUM_SAMPLES; ++index) 
  {
    std::cout << cb::process<4, float, float, float>(coefficients, state, input[index]) << "\n";
  }

  delete[] state;

  return 0;
}

