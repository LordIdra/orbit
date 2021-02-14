#include "numbers.h"




#define float3dp(x) afloat(int(x * 1000 + 0.5))/1000




// Return float(x^y)
afloat power(aint x, int y)
{
    aint n = x;
    for (unsigned int i = 1; i < y; i++) x *= n;
    
    return afloat(n);
}

// Return float(x^y)
afloat power(afloat x, int y)
{
    afloat n = x;
    for (unsigned int i = 1; i < y; i++) n *= x;

    return n;
}



/* https://www.geeksforgeeks.org/square-root-of-a-perfect-square/ */
afloat root(aint value)
{
    afloat n = value.convert_to<afloat>();
    afloat x = n; 
    afloat y = 1; 
    afloat e = 0.000001;

    while (x - y > e) {
        x = (x + y) / 2; 
        y = n / x; 
    }

    return x; 
}

afloat root(afloat n) 
{ 
    afloat x = n; 
    afloat y = 1; 
    afloat e = 0.000001;

    while (x - y > e) {
        x = (x + y) / 2; 
        y = n / x; 
    }
    
    return x; 
} 



int get_length(afloat value) {
    
    float length = 0;
    
    while (-1 >= value || value >= 1 ) {
        length++;
        value /= 10;
    }

    return length;
}

int get_precision(afloat value) {
    
    float precision = 0;
    
    while (-1 <= value || value <= 1 ) {
        precision++;
        value *= 10;
    }

    return precision;
}



inline string create_larger_measurement(afloat value, int zeroes, string suffix) {
    return (float3dp(value/afloat(pow(10, zeroes)))).convert_to<string>() + " " + suffix;
}

inline string create_smaller_measurement(afloat value, int zeroes, string suffix) {
    return (float3dp(value*afloat(pow(10, zeroes)))).convert_to<string>() + " " + suffix;
}




string make_standard_mass(afloat value) {
    // Value goes in in [kg]

    if ((value < 0.0005) && (-0.0005 < value)) {
        // Unit is close to 0
        return create_smaller_measurement(value, 0, "kg");
    }

    if (value < 1) {
        // Unit needs to decrease
        int precision = get_precision(value);

        if (precision < 4)  return create_smaller_measurement(value, 3, "g");
    } 
    

    else {
        // Unit needs to increase
        int length = get_length(value);

        if      (length < 4)  return create_larger_measurement(value, 0,  "kg");
        else if (length < 7)  return create_larger_measurement(value, 3,  "t" );
        else if (length < 10) return create_larger_measurement(value, 6,  "Mg");
        else if (length < 13) return create_larger_measurement(value, 7,  "Gg");
        else if (length < 16) return create_larger_measurement(value, 12, "Tg");
        else if (length < 19) return create_larger_measurement(value, 15, "Pg");
        else if (length < 22) return create_larger_measurement(value, 18, "Eg");
        else if (length < 25) return create_larger_measurement(value, 21, "Zg");
        else if (length < 28) return create_larger_measurement(value, 24, "Yg");
        else if (length < 31) return create_larger_measurement(value, 27, "Rg");   // technically doesn't exist yet
        else if (length < 34) return create_larger_measurement(value, 30, "Qg");   // but we need it because the sun is REALLY, REALLY obese
    }
    
    return "ERROR line" + std::to_string(__LINE__);
}


string make_standard_velocity(afloat value) {
    // Value goes in in [km/s]

    if ((value < 0.0005) && (-0.0005 < value)) {
        // Unit is close to 0
        return create_smaller_measurement(value, 0, "km/s");
    }

    else if (value < 1) {
        // Unit needs to decrease
        int precision = get_precision(value);

        if (precision < 4)  return create_smaller_measurement(value, 3, "m/s");
    } 
    

    else {
        // Unit needs to increase
        int length = get_length(value);

        if (length < 4)  return create_larger_measurement(value, 0, "km/s"); // If it gets any higher than km/s there are more important problems to solve
        if (length < 100)  return create_larger_measurement(value, 0,  "error");
    }
    
    return "ERROR line" + std::to_string(__LINE__);
}


string make_standard_distance(afloat value) {
    // Value goes in in [km]

    if ((value < 0.0005) && (-0.0005 < value)) {
        // Unit is close to 0
        return create_smaller_measurement(value, 0, "km");
    }

    if (value < 1) {
        // Unit needs to decrease
        int precision = get_precision(value);

        if (precision < 4)  return create_smaller_measurement(value, 3, "m");
    } 
    

    else {
        // Unit needs to increase
        int length = get_length(value);

        if      (length < 4)   return create_larger_measurement(value, 0,  "km");
        else if (length < 7)   return create_larger_measurement(value, 3,  "Mm");
        else if (length < 10)  return create_larger_measurement(value, 6,  "Gm");
        else if (length < 13)  return create_larger_measurement(value, 9,  "Tm");
    }
    
    return "ERROR line" + std::to_string(__LINE__);
}


string make_standard_time(afloat value) {
    // Value goes in in [s]
    string current_return = "";
    int current_time_used = 0;
    long input_as_long = value.convert_to<long>();

    if (value > 31540000) {
        // Years
        int years = ((input_as_long % 31540000) - (current_time_used % 31540000));
        current_return += std::to_string(years) + "y";
        current_time_used += years * 31540000;
    
    } if (value > 86400) {
        // Days
        int days = ((input_as_long % 86400) - (current_time_used % 86400));
        current_return += std::to_string(days) + "d";
        current_time_used += days * 86400;
    
    } if (value > 360) {
        // Hours
        int hours = ((input_as_long % 360) - (current_time_used % 360));
        current_return += std::to_string(hours) + "h";
        current_time_used += hours * 360;
    
    } if (value > 60) {
        // Minutes
        int minutes = ((input_as_long % 60) - (current_time_used % 60));
        current_return += std::to_string(minutes) + "m";
        current_time_used += minutes * 60;
    }

    // Seconds
    int seconds = input_as_long - current_time_used;
    current_return += std::to_string(seconds) + "s";

    return current_return;
}