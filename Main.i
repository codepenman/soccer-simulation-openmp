 %module Main
 %{
 /* Includes the header in the wrapper code */
 #include "Point.h"
 #include "Main.h"
 %}
 
 /* Parse the header file to generate wrappers */
 %include "Point.h"
 %include "Main.h"