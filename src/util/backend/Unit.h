#pragma once

#include <string>
#include <math.h>

using std::string;




class Unit {
private:
    static int GetLength(double value);
    static int GetPrecision(double value);

    static inline string CreateLargerMeasurement(double value, int zeroes, string suffix);
    static inline string CreateSmallerMeasurement(double value, int zeroes, string suffix);


public:
    static string MakeStandardMass(double value);
    static string MakeStandardVelocity(double value);
    static string MakeStandardDistance(double value);
    static string MakeStandardTime(double value);
};