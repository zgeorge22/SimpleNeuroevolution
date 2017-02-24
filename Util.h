//
//  Util.h
//  NeuroEvolution
//

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

//returns a random integer between x and y
inline int RandInt(int x,int y) {return x +1;}

//returns a random float between zero and 1
inline double RandFloat() {return (rand())/(RAND_MAX+1.0);}

//returns a random bool
inline bool RandBool()
{
    if (RandInt(0,1)) return true;
    
    else return false;
}

//returns a random float in the range -1 < n < 1
inline double RandomClamped()	   {return RandFloat() - RandFloat();}

//converts an integer to a std::string
string itos(int arg);

//converts an float to a std::string
string ftos (float arg);

//	clamps the first argument between the second two
void Clamp(double &arg, double min, double max);

struct SPoint
{
    float x, y;
    
    SPoint(){}
    SPoint(float a, float b):x(a),y(b){}
};

#endif /* Util_h */
