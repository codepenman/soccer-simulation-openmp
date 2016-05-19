%module example
 %{
 /* Includes the header in the wrapper code */
 #include "Ball.h"
 %}
 
 /* Parse the header file to generate wrappers */
 %include "Ball.h"
 
