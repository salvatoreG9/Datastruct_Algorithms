/*
* Author: Salvador Garza
* Assignment Title: Big Multiply
* Assignment Description: This program reads two numbers from 
* Due Date: 9/22/2023
* Date Created: 9/16/2023
* Date Last Modified: 9/22/2023
*/


/*
* Data Abstraction:
* Print results of 2 Digit multiplication to console
* Input:
* The program reads input from file named numbers.txt. 
* numbers.txt contains 2 lines representing 2 integers per line
* Process:
* Use divide and conquer methadology 
* Run karatsuba algorithm on main algorithm and run on every
* multiplication required until formula is broken down to single digits
* Perform multiplication / shifts / additions to create main result
* 
* Output:
* The answer is printed to the terminal and to output.txt
*
* Assumptions:
* n_x = n_y personal working assumption
* n_x and n_y are even numbers
* numbers.txt has 2 valid integer values 
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

// Function declerations
// We will not be modifying any strings
// All modifications will be performed in function and returned
string karatsuba(const string &x, const string &y);
string shift(const string &input, int n);
string addStrings(const string &num1, const string &num2);
//string subtractStrings(unimplemented)


//************************************************************
// description: shifts the string containing an integer by n number of character '0'
// simulated multiplying the input number by 10^n 
// return: string
// precondition: string is valid and n is a positive integer value
// postcondition: returns string integer with n number of 0's appended to it 
// *
//************************************************************


string shift(const string &input, int n) {
    cout << "shift \n";
    
    string result = input;
    for (int i = 0; i < n; i++) {
        result += '0'; // Append '0' to the string input 
    }
    
    return result;
}

//************************************************************
// description: adds 2  string integers by converting character to integer and performing operations. 
// 
// return: string containing integer
// precondition: strings are varied length. Every value is a valid integer
// postcondition: returns string integer of both string integers added
// *
//************************************************************

string addStrings(const string &num1, const string &num2) {
    cout << "adding strings \n";
    
    // Create 2 index counters starting at the very last character of each string and increment down until it's complete
    int i = num1.size() - 1;
    int j = num2.size() - 1;

    int carry = 0; // If there is a carry unit left at the end set the sum to the carry 

    string result = ""; // Append current sum to result string. Reverse at the very end

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry; // carry initialized at 0 and is determined in this while loop

        if (i >= 0) {
            sum += num1[i] - '0';  // Convert char to int and add to sum 
            i--;
        }
        if (j >= 0) {
            sum += num2[j] - '0';  // Convert char to int and add to sum
            j--;
        }

        carry = sum / 10; // The digit that represents 10s : 42 / 10 = carry digit of 4 
        sum = sum % 10;   // The digit that represents 1s : 42 % 10 = sum digit of 2 

        result = result + to_string(sum);
    }

    reverse(result.begin(), result.end());  // Reverse to get the correct order
    return result;
}



//************************************************************
// description: Takes 2 string integers and performs multiplication through karatsuba algorithm
// called recursively
// return: string containing integer
// precondition: strings are valid integers
// postcondition: returns string integer of both string integers multiplied through karatsuba algorithm
// *
//************************************************************

string karatsuba(const string &x, const string &y) {
    if (x.length() == 1 || y.length() == 1) {
        int result = (x[0] - '0') * (y[0] - '0'); // This has the right idea, but the implementation is off
        // Convert string to integer and multiply
        return to_string(result);
    }

    int n = max(x.length(), y.length()); // Figure out the length of the larger number
    int m = n / 2; // Divide length of number 

    string a = x.substr(0, x.length() - m); // x[0:x.length-m]
    string b = x.substr(x.length() - m);    // x[(x.lenght-m):]
    string c = y.substr(0, y.length() - m); // y[0:y.length-m]
    string d = y.substr(y.length() - m);    // y[(y.lenght-m):]

    // Breaking variables into their karatsuba values 
    string ac = karatsuba(a, c); // a*c
    string bd = karatsuba(b, d); // b*d
    string ad = karatsuba(a,d); // a*d
    string bc = karatsuba(b,c); //b*c

    string num1,num2,num3;
    num1 = shift(ac,2*m); // Portion 1 shifted length n
    num2 = shift(addStrings(ad,bc),m); //portion 2 shifted length m 
    num3 = bd; // portion 3 not shifted

    // karatsuba_formula(a,b,c,d,ac,bd,m)
    cout << "Performing karatsuba\n";
    // Need to implement karatsuba reduction method in future if able
    string kara_result = addStrings(addStrings(num1,num2),num3); // Add portion1,2,3 together and return value
    return kara_result;
}

int main() {


    string x, y; // Will contain the values read from file numbers.txt

    // Read file numbers.txt
    ifstream inputFile("numbers.txt");
    if (!inputFile) {
        cerr << "Error opening numbers.txt for reading." << endl;
        return 1;
    }

    if (getline(inputFile, x) && getline(inputFile, y)) {
        string result = karatsuba(x, y);
        cout << "The product of " << x << " and " << y << " is: " << result << endl;
    } else {
        cerr << "Error reading numbers from numbers.txt." << endl;
        return 2;
    }

    inputFile.close();

    
    return 0;
}
