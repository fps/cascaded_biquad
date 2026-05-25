#include <cascaded_biquad.h>
#include <iostream>
#include <cmath>

#include <noise.h>
#include <noise_output.h>

int main()
{
  namespace cb = cascaded_biquad;

  cb::direct_form1<4, float, float, float> filter = 
  {
    { { 
    {1.0, 1.2737743779835942, 1.0, -0.9304164090155603, 0.22721104055145627}, 
    {1.0, -0.5709142606604667, 0.9999999999999999, -1.1004204118801604, 0.38089210320292105}, 
    {1.0, -1.2046820069725777, 0.9999999999999999, -1.3412154666010316, 0.6073991164386764}, 
    {1.0, -1.3945444665695719, 1.0000000000000002, -1.5866887686623201, 0.8589758072285574}
    } } ,
    0.002678078649978631 
  };

  float max_difference = 0;

  for (int index = 0; index < noise.size(); ++index)
  {
    float d = fabs(filter.process(noise[index]) - noise_output[index]);
    if (d > max_difference)
    {
      max_difference = d;
    }
  }

  std::cout << max_difference << "\n";

  return 0;
 }
