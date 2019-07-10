#include "tcl.h"
#include "my_string.h"
#include <iostream>

int My_string_SafeInit(Tcl_Interp *interp);
int main()
{
  Tcl_Interp* interp = Tcl_CreateInterp();
  Tcl_Init(interp);
  My_string_SafeInit(interp);
  Tcl_ResetResult(interp);
  Tcl_EvalFile(interp, "./test.tcl");
  return 0;
}
