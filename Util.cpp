//
//  Util.cpp
//  NeuroEvolution
//

#include "Util.h"
#include <math.h>

//	converts an integer to a string
string itos(int arg)
{
    ostringstream buffer;
    
    //send the int to the ostringstream
    buffer << arg;
    
    //capture the string
    return buffer.str();
}

//	converts a float to a string
string ftos(float arg)
{
    ostringstream buffer;
    
    //send the int to the ostringstream
    buffer << arg;
    
    //capture the string
    return buffer.str();
}

//	clamps the first argument between the second two
void Clamp(double &arg, double min, double max)
{
    if (arg < min)
    {
        arg = min;
    }
    
    if (arg > max)
    {
        arg = max;
    }
}
