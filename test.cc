#include "cascaded_biquad.h"
#include <iostream>

// These coefficients were generated with MATLAB:
// f = designfilt('lowpassiir', 'PassbandFrequency', 0.01, 'StopbandFrequency', 0.02, 'StopbandAttenuation', 32);
// f.Coefficients(:,[1 2 3 5 6])
#if 0
const float coefficients[] = 
{
   0.000341790148053,   0.000683580296107,   0.000341790148053,   -1.982247725220660,   0.983614885812873,
   0.000336817881561,   0.000673635763122,   0.000336817881561,   -1.953410545448979,   0.954757816975223,
   0.000333460820498,   0.000666921640997,   0.000333460820498,   -1.933940918565828,   0.935274761847821,
   0.018228517368043,   0.018228517368043,                   0,    -0.963542965263913,                   0
};


const float coefficients[] =
{
 0.0011064,   0.00146455 ,  0.0011064,  -0.00136294,  0.000436528,
 0.0011064,  -0.000486232,  0.0011064,  -0.00142182,  0.000584152,
 0.0011064,  -0.00118574 ,  0.0011064,  -0.00149734,  0.000772222,
 0.0011064,  -0.00143236 ,  0.0011064,  -0.00155831,  0.000920688,
 0.0011064,  -0.00152968 ,  0.0011064,  -0.00160096,  0.00101711,
 0.0011064,  -0.00156524 ,  0.0011064,  -0.00163502,  0.00108005
};
#endif

const float coefficients[] = {
  1.00000000000000000000000000000000, 1.32370651424032437226685487985378, 0.99999999999999977795539507496869, -1.23186615451241943119953248242382, 0.39454855580901848632890960288933,
  1.00000000000000000000000000000000, -0.43947298797902079048327550481190, 1.00000000000000000000000000000000, -1.28508795525736618792222998308716, 0.52797554616923736414690893070656,
  1.00000000000000000000000000000000, -1.07171112587677774818928355671233, 0.99999999999999966693309261245304, -1.35334477257660634741398553160252, 0.69795977693816424469730463897577,
  1.00000000000000000000000000000000, -1.29461065699227506620161420869408, 1.00000000000000000000000000000000, -1.40845586574345693620102792920079, 0.83214833401569621162963130700518,
  1.00000000000000000000000000000000, -1.38257647054952670373495493549854, 1.00000000000000000000000000000000, -1.44700473087661229953937436221167, 0.91930043677839590188227703038137,
  1.00000000000000000000000000000000, -1.41471341047715126748585134919267, 0.99999999999999988897769753748435, -1.47778935891814988679016096284613, 0.97618547901300722902107054324006,
};
const float gain = 0.00110639888678778879060882189833;

#define NUM_SAMPLES 10000

int main()
{
  namespace cb = cascaded_biquad;
  float *state = cb::state<6, float>();

  float input[NUM_SAMPLES];

  // Our input is a step function
  for (int index = 0; index < NUM_SAMPLES; ++index) 
  {
    if (index < NUM_SAMPLES/2) input[index] = 0; else input[index] = 1;
  } 

  for (int index = 0; index < NUM_SAMPLES; ++index) 
  {
    std::cout << index << ": " << cb::process<6, float, float, float>(coefficients, state, gain, input[index]) << "\n";
  }

  delete[] state;

  return 0;
}

