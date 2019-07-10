%module my_string
%{
  #include "my_string.h"
%}

%include "std_vector.i"

namespace std {
   %template(vector_ms) vector<MyString>;
}

%include "my_string.h"
