#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

// Function to convert a string in a given base to a decimal integer
unsigned long long decode(const std::string &value, int base) {
    unsigned long long result = 0;
    for (char digit : value) {
        result = result * base + (isdigit(digit) ? digit - '0' : tolower(digit) - 'a' + 10);
    }
    return result;
}

// Function to calculate the Lagrange interpolation and find the constant term (c)
unsigned long long lagrangeInterpolation(const std::vector<int> &xValues, const std::vector<unsigned long long> &yValues) {
    int k = xValues.size();
    unsigned long long c = 0;

    for (int i = 0; i < k; ++i) {
        unsigned long long term = yValues[i];
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= (0 - xValues[j]) / (xValues[i] - xValues[j]); // Simplified without modular arithmetic
            }
        }
        c += term;
    }
    return c;
}

int main() {
    // Input data directly as a string for testing
    std::string jsonString = R"({
        "keys": {
            "n": 10,
            "k": 7
        },
        "1": {
            "base": "6",
            "value": "13444211440455345511"
        },
        "2": {
            "base": "15",
            "value": "aed7015a346d63"
        },
        "3": {
            "base": "15",
            "value": "6aeeb69631c227c"
        },
        "4": {
            "base": "16",
            "value": "e1b5e05623d881f"
        },
        "5": {
            "base": "8",
            "value": "316034514573652620673"
        },
        "6": {
            "base": "3",
            "value": "2122212201122002221120200210011020220200"
        },
        "7": {
            "base": "3",
            "value": "20120221122211000100210021102001201112121"
        },
        "8": {
            "base": "6",
            "value": "20220554335330240002224253"
        },
        "9": {
            "base": "12",
            "value": "45153788322a1255483"
        },
        "10": {
            "base": "7",
            "value": "1101613130313526312514143"
        }
    })";

    // Manually parse the input
    int n = 10; // Number of roots
    int k = 7;  // Minimum number of roots required
    std::vector<int> xValues;
    std::vector<unsigned long long> yValues;

    // Example parsing - in a real case, you'd loop through keys to extract these values
    for (int i = 1; i <= n; ++i) {
        int x = i; // Key as x
        // Example static values based on your JSON input for demonstration
        std::string baseStr = (i == 1) ? "6" : (i == 2 || i == 3) ? "15" :
                              (i == 4) ? "16" : (i == 5) ? "8" :
                              (i == 6 || i == 7) ? "3" : (i == 8) ? "6" :
                              (i == 9) ? "12" : "7";
        std::string valueStr = (i == 1) ? "13444211440455345511" : (i == 2) ? "aed7015a346d63" :
                               (i == 3) ? "6aeeb69631c227c" : (i == 4) ? "e1b5e05623d881f" :
                               (i == 5) ? "316034514573652620673" : (i == 6) ? "2122212201122002221120200210011020220200" :
                               (i == 7) ? "20120221122211000100210021102001201112121" : (i == 8) ? "20220554335330240002224253" :
                               (i == 9) ? "45153788322a1255483" : "1101613130313526312514143";

        int base = std::stoi(baseStr);
        unsigned long long y = decode(valueStr, base);

        xValues.push_back(x);
        yValues.push_back(y);
    }

    // Calculate the constant term (c) using Lagrange interpolation
    unsigned long long c = lagrangeInterpolation(xValues, yValues);
    std::cout << "The secret (constant term c) is: " << c << std::endl;

    return 0;
}
