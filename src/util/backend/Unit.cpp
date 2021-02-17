#include "Unit.h"




// This place is a huge mess, but it works
// Refactor in order sometimes in the future if absolutely necessary,
// but little needs to be done in terms of optimization or interfacing,
// and if it ain't broke, don't fix it...

inline string to3dp(double x) {

    int before_decimal_point = floor(x);
    int after_decimal_point = (x * 1000) - (floor(x) * 1000);

    string zeroes_before;

    if      (after_decimal_point < 10) zeroes_before = "00";
    else if (after_decimal_point < 100) zeroes_before = "0";

    return std::to_string(before_decimal_point) + "." + zeroes_before + std::to_string(after_decimal_point);
}



int Unit::GetLength(double value) {
    
    float length = 0;
    
    while (-1 >= value || value >= 1 ) {
        length++;
        value /= 10;
    }

    return length;
}

int Unit::GetPrecision(double value) {
    
    float precision = 0;
    
    while (-1 <= value || value <= 1 ) {
        precision++;
        value *= 10;
    }

    return precision;
}



inline string Unit::CreateLargerMeasurement(double value, int zeroes, string suffix) {
    return to3dp(value/pow(10, zeroes)) + " " + suffix;
}

inline string Unit::CreateSmallerMeasurement(double value, int zeroes, string suffix) {
    return to3dp(value*pow(10, zeroes)) + " " + suffix;
}




string Unit::MakeStandardMass(double value) {
    // Value goes in in [g]

    if ((value < 0.0005) && (-0.0005 < value)) {
        // Unit is close to 0, probably a floating point error
        return CreateSmallerMeasurement(value, 0, "g");
    }

    if (value < 1) {
        // Unit needs to decrease
        int precision = GetPrecision(value);

        if (precision < 4)  return CreateSmallerMeasurement(value, 3, "mg");
    } 
    

    else {
        // Unit needs to increase
        int length = GetLength(value);

        if      (length < 4)  return CreateLargerMeasurement(value, 0,  "g");
        else if (length < 7)  return CreateLargerMeasurement(value, 3,  "kg" );
        else if (length < 10) return CreateLargerMeasurement(value, 6,  "t");
        else if (length < 13) return CreateLargerMeasurement(value, 7,  "Mg");
        else if (length < 16) return CreateLargerMeasurement(value, 12, "Gg");
        else if (length < 19) return CreateLargerMeasurement(value, 15, "Tg");
        else if (length < 22) return CreateLargerMeasurement(value, 18, "Pg");
        else if (length < 25) return CreateLargerMeasurement(value, 21, "Eg");
        else if (length < 28) return CreateLargerMeasurement(value, 24, "Zg");
        else if (length < 31) return CreateLargerMeasurement(value, 27, "Yg");   
        else if (length < 34) return CreateLargerMeasurement(value, 30, "Rg");    // technically doesn't exist yet
        else if (length < 37) return CreateLargerMeasurement(value, 33, "Qg");    // but we need these two because the sun is REALLY, REALLY fat
    }
    
    return "ERROR line" + std::to_string(__LINE__);
}


string Unit::MakeStandardVelocity(double value) {
    // Value goes in in [m/s]

    if ((value < 0.0005) && (-0.0005 < value)) {
        // Unit is close to 0, probably a floating point error
        return CreateSmallerMeasurement(value, 0, "m/s");
    }

    else if (value < 1) {
        // Unit needs to decrease
        int precision = GetPrecision(value);

        if (precision < 4)  return CreateSmallerMeasurement(value, 3, "mm/s");
    }
    

    else {
        // Unit needs to increase
        int length = GetLength(value);

        if (length < 4)    return CreateLargerMeasurement(value, 0, "m/s"); // If it gets any higher than km/s there are more important problems to solve
        if (length < 7)    return CreateLargerMeasurement(value, 3, "km/s");
    }
    
    return "ERROR line" + std::to_string(__LINE__);
}


string Unit::MakeStandardDistance(double value) {
    // Value goes in in [m]

    if ((value < 0.0005) && (-0.0005 < value)) {
        // Unit is close to 0, probably a floating point error
        return CreateSmallerMeasurement(value, 0, "m");
    }

    if (value < 1) {
        // Unit needs to decrease
        int precision = GetPrecision(value);

        if (precision < 4)  return CreateSmallerMeasurement(value, 3, "mm");
    } 
    

    else {
        // Unit needs to increase
        int length = GetLength(value);

        if      (length < 4)   return CreateLargerMeasurement(value, 0,  "m");
        else if (length < 7)   return CreateLargerMeasurement(value, 3,  "km");
        else if (length < 10)  return CreateLargerMeasurement(value, 6,  "Mm");
        else if (length < 13)  return CreateLargerMeasurement(value, 9,  "Gm");
        else if (length < 16)  return CreateLargerMeasurement(value, 12, "Tm");
    }
    
    return "ERROR line" + std::to_string(__LINE__);
}


string Unit::MakeStandardTime(double value) {
    // Value goes in in [s]
    string current_return = "";
    int current_time_used = 0;
    long input_as_long = value;

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