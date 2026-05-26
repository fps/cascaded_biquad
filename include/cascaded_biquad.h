#pragma once

#include <cstring>
#include <array>

namespace cascaded_biquad 
{
  template<typename coefficient_t>
  struct coefficients
  {
    coefficient_t b0;
    coefficient_t b1;
    coefficient_t b2;

    coefficient_t a0;
    coefficient_t a1;
    coefficient_t a2;
  };

  template<typename coefficient_t>
  struct normalized_coefficients
  {
    coefficient_t b0;
    coefficient_t b1;
    coefficient_t b2;

    coefficient_t a1;
    coefficient_t a2;
  };

  template<typename coefficient_t>
  normalized_coefficients<coefficient_t> normalize_coefficients(coefficients<coefficient_t> const & c)
  {
    return { c.a1 / c.a0, c.a2 / c.a0, c.b0 / c.a0, c.b1 / c.a0, c.b2 / c.a0 };
  };
  
  template<int stages, typename coefficient_t = float, typename state_t = coefficient_t, typename sample_t = coefficient_t>
  struct direct_form1
  {
    const std::array<normalized_coefficients<coefficient_t>, stages> coefficients;
    const coefficient_t gain;

    std::array<std::array<state_t, 2>, stages> previous_inputs;
    std::array<std::array<state_t, 2>, stages> previous_outputs;

    inline sample_t process(float const input)
    {
      sample_t intermediate = input;
      for (int stage = 0; stage < stages; ++stage)
      {
        auto const & c = coefficients[stage];
        auto & pi = previous_inputs[stage];
        auto & po = previous_outputs[stage];

        const sample_t out = c.b0 * intermediate + c.b1 * pi[0] + c.b2 * pi[1] - c.a1 * po[0] - c.a2 * po[1];

        pi[1] = pi[0];
        po[1] = po[0];
        pi[0] = intermediate;
        po[0] = out; 

        intermediate = out;    
      }

      return gain * intermediate;
    }
  };

}
