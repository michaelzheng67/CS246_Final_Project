#include "outputhelpers.h"

// helper function for outputting cards
std::string Outputhelpers::InttoSymbol(int value) {
    std::string temp;
    if (value <= 10 && value >= 2) {
        temp = std::to_string(value);
    } else if (value == 11) {
        temp = "J";
    } else if (value == 12) {
        temp = "Q";
    } else if (value == 13) {
        temp = "K";
    } else if (value == 1) {
        temp = "A";
    }
    return temp;

}
