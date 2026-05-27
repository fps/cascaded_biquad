#pragma once

#include <cstring>
#include <array>
#include <ostream>

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
  std::ostream & operator<<(std::ostream & o, coefficients<coefficient_t> const & c)
  {
    o << "{ " << c.b0 << ", " << c.b1 << ", " << c.b2 << ", " << c.a0 << ", " << c.a1 << ", " << c.a2 << " }";
    return o;
  }

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
  std::ostream & operator<<(std::ostream & o, normalized_coefficients<coefficient_t> const & c)
  {
    o << "{ " << c.b0 << " " << c.b1 << " " << c.b2 << " " << c.a1 << " " << c.a2 << " }";
    return o;
  }

  template<typename coefficient_t>
  normalized_coefficients<coefficient_t> normalize_coefficients(coefficients<coefficient_t> const & c)
  {
    return { c.b0 / c.a0, c.b1 / c.a0, c.b2 / c.a0, c.a1 / c.a0, c.a2 / c.a0 };
  };
  
  template<int sections, typename coefficient_t = float, typename state_t = coefficient_t, typename sample_t = coefficient_t>
  struct direct_form1
  {
    const std::array<normalized_coefficients<coefficient_t>, sections> coefficients;
    const coefficient_t gain;

    std::array<std::array<state_t, 2>, sections> previous_inputs;
    std::array<std::array<state_t, 2>, sections> previous_outputs;

    inline sample_t process(sample_t const input)
    {
      sample_t intermediate = input;
      for (int section = 0; section < sections; ++section)
      {
        auto const & c = coefficients[section];

        auto & pi = previous_inputs[section];
        auto & po = previous_outputs[section];

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

  template<int sections, typename coefficient_t = float, typename state_t = coefficient_t, typename sample_t = coefficient_t>
  std::ostream & operator<<(std::ostream & o, direct_form1<sections, coefficient_t, state_t, sample_t> const & f)
  {
    o << "{ ";
    for (int section = 0; section < sections; ++section)
    {
      o << f.coefficients[section] << ", ";
    }
    o << f.gain << " }";
    return o;
  }

  template<int sections, typename coefficient_t = float, typename state_t = coefficient_t, typename sample_t = coefficient_t>
  struct direct_form2
  {
    const std::array<normalized_coefficients<coefficient_t>, sections> coefficients;
    const coefficient_t gain;

    std::array<std::array<state_t, 2>, sections> states;

    inline sample_t process(sample_t const input)
    {
      sample_t intermediate = input;
      for (int section = 0; section < sections; ++section)
      {
        auto const & c = coefficients[section];
        auto & state = states[section];

        const state_t s = intermediate - c.a1 * state[0] - c.a2 * state[1];
        intermediate = c.b0 * s + c.b1 * state[0] + c.b2 * state[1];

        state[1] = state[0];
        state[0] = s;
      }

      return gain * intermediate;
    }
  };

  template<int sections, typename coefficient_t = float, typename state_t = coefficient_t, typename sample_t = coefficient_t>
  std::ostream & operator<<(std::ostream & o, direct_form2<sections, coefficient_t, state_t, sample_t> const & f)
  {
    o << "{ ";
    for (int section = 0; section < sections; ++section)
    {
      o << f.coefficients[section] << ", ";
    }
    o << f.gain << " }";
    return o;
  }
}

