#pragma once

#include <string.h>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;
using std::string;


typedef cpp_int             aint;       // Arbitrary Integer
typedef cpp_dec_float_50    afloat;     // Arbitrary Float

const afloat GRAVITATIONAL_CONSTANT = 0.000000000066742;


afloat power(aint x, int y);
afloat power(afloat x, int y);

afloat root(aint x_in);
afloat root(afloat x);

int get_length(afloat value);
int get_precision(afloat precision);

string create_measurement(afloat value, int zeroes, string suffix);

string make_standard_mass(afloat value);
string make_standard_velocity(afloat value);
string make_standard_distance(afloat value);
string make_standard_time(afloat value);