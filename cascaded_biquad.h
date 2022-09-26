#pragma once

#include <cstring>

namespace cascaded_biquad 
{
  // The coefficients are expected to be normalized, i.e. the fifth column
  // has to be ones. If that is not the case you need to to normalize them
  // beforehand!
  // Additionally they are stored as a 1-D array in row-major order. I.e. 
  // the first 5 elements are the entries in the first row.
  template<int stages, typename coefficient_t, typename state_t, typename sample_t> 
  sample_t process(const coefficient_t *coefficients, state_t* state, coefficient_t gain, const sample_t in) 
  {
    sample_t intermediate = in;
    for (int stage = 0; stage < stages; ++stage) 
    {
      const sample_t stage_in = intermediate;
      const sample_t stage_out = stage_in * coefficients[5*stage+0] + state[2*stage+0];
      state[2*stage+0] = state[2*stage+1] + coefficients[5*stage+1] * stage_in - coefficients[5*stage+3] * stage_out;
      state[2*stage+1] = coefficients[5*stage+2] * stage_in - coefficients[5*stage+4] * stage_out;
      intermediate = stage_out;
    }
    return gain * intermediate;
  }

  // Produce an array suitable as filter state for a filter consisting of 
  // number_of_stages stages.  Delete the array with delete[] instead of delete.
  template<int number_of_stages, typename state_t> 
  state_t* state() 
  {
    state_t *state = new state_t[2*number_of_stages];
    memset(state, 0, sizeof(state_t)*2*number_of_stages);
    return state;
  }
}
