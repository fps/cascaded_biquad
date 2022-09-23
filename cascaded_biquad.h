#pragma once

namespace cascaded_biquad 
{
  // These coefficients are expected to be normalized, i.e. the fifth column
  // has to be ones. If that is not the case you need to to normalize them
  // beforehand!
  template<int stages, typename coefficient_t, typename state_t, typename sample_t> 
  sample_t process(const coefficient_t *coefficients, state_t* state, sample_t in) 
  {
    sample_t intermediate = in;
    for (int stage = 0; stage < stages; ++stage) 
    {
      const sample_t stage_in = intermediate;
      const sample_t stage_out = stage_in * coefficients[6*stage+0] + state[2*stage+0];
      state[2*stage+0] = state[2*stage+1] + coefficients[6*stage+1] * stage_in - coefficients[6*stage+4] * stage_out;
      state[2*stage+1] = coefficients[6*stage+2] * stage_in - coefficients[6*stage+5] * stage_out;
      intermediate = stage_out;
    }
    return intermediate;
  }

  template<int stages, typename state_t> 
  state_t* state() 
  {
    return new state_t[2*stages];
  }
}
