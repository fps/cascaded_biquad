A simple header only library implementing cascaded biquad filters as second order sections.

# How to use the library

Just include the header "cascaded_biquad.h" and instantiate one of the `direct_form1`, `direct_form2` or `transposed_direct_form2` templates with your desired number of stages, sample type, coefficient type and state type. See the included test.cc for an example.

