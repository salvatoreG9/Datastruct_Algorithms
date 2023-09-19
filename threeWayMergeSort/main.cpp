/*
* Author: Salvador Garza
* Assignment Title: Three Way Merge Sort 
* Assignment Description: This program contains a threeWayMergeSort algorithm implementation and demonstration
* Due Date: 9/15/2013
* Date Created: 9/6/2023
* Date Last Modified: 9/12/2023
*/

#include <iostream>
#include <fstream>
#include <string>	// Using <string> when reading the input file and pushing the values into numbers array
#include <vector>	// Using <vector> to contain our unsorted and sorted list of numbers
using namespace std;


/*
* Data Abstraction:
* Input:
* Program prompts user to enter a file name 
* Filename contains an unsorted list of numbers
* Process:
* Function threeWayMergeSort takes an unsorted vector, and the vector range 
* function divides the vector into 3 roughly equal segments and passes those segments back into threeWayMergeSort 
* function breaks vector down into smallest value and completes a merge 
* function merges subarrays into main array and result is a vector of sorted numbers
* Output:
* The sorted list is printed to the .txt file named 
'output.txt'
* Assumptions:
* The input file is valid and contains a list of numbers
* It is assumed that, having been prompted to do so, the user will
correctly input data
*/



//************************************************************
// description: merge 3 segments of vectors and sort the values in numerical order*
// return: void 
// precondition: the vector being merged either has a length of 2, or the vector contains sub arrays from a certain range that have already been merged 
// inputs left, firstDivision, secondDivison, right contain the parameters that divide the vector into segments that we are merging and sorting 
// this function is not called in main. It is called at the end of parent function threeWayMergeSort 
// postcondition: vector1 is modified and sorted from the range left-right 
//************************************************************

void threeWayMerge(vector<int>& vector1, int left, int firstDivision, int secondDivision, int right) {
    cout << "Merging from indices " << left << " to " << right << "\n";

    
    int sizeLeft = firstDivision - left + 1;			// Size of left vector
    int sizeMiddle = secondDivision - firstDivision;	// Size of middle vector
    int sizeRight = right - secondDivision;				// Size of right vector

    
    vector<int> leftVector(vector1.begin() + left, vector1.begin() + firstDivision + 1);					// LeftVector temporary data 
    vector<int> middleVector(vector1.begin() + firstDivision + 1, vector1.begin() + secondDivision + 1);	// middleVector temporary data
    vector<int> rightVector(vector1.begin() + secondDivision + 1, vector1.begin() + right + 1);				// rightVector temporary data

	
    int leftIdx = 0, middleIdx = 0, rightIdx = 0; // Iterate through each subarray and merge the arrray 
    int mergePos = left;						  // We will be finding the smallest value starting from left of the vector to the right 


    while (leftIdx < sizeLeft || middleIdx < sizeMiddle || rightIdx < sizeRight) {	// While there are items that have not been determined to be smallest value 
        int smallestValue;

        if (leftIdx < sizeLeft &&	// if leftVector still has data 
	
           (middleIdx == sizeMiddle || leftVector[leftIdx] <= middleVector[middleIdx]) &&		// if middleVector is complete or the current value is larger than the leftVector
           (rightIdx == sizeRight || leftVector[leftIdx] <= rightVector[rightIdx])) {			// if rightVector is complete or the current value of rightVector is larger than leftVector
			
            smallestValue = leftVector[leftIdx]; // leftVector is smallest value
			leftIdx++;

        } else if (middleIdx < sizeMiddle &&	// if middleVector still has data 
                   (rightIdx == sizeRight || middleVector[middleIdx] <= rightVector[rightIdx])) { //if rightVector is empty or the current value of rightVector is larger than middleVector
            smallestValue = middleVector[middleIdx];	// middleVector is smallest value
			middleIdx++;

        } else {
            smallestValue = rightVector[rightIdx]; // rightVector current position contains smallest value 
			rightIdx++;
        }

		// Merge and iterate to next vector value to find the next smallest value
        vector1[mergePos] = smallestValue;
		mergePos++;
    }

    cout << "After merging: ";
    for (int i = left; i <= right; i++)
        cout << vector1[i] << " ";
    cout << "\n\n";
}


//************************************************************
// description: this function is called to facilitate a 3 way merge sort 
// return: void 
// precondition: Vector passed in is unsorted and composed of integer values
// inputs vector, left, and right to determine the vector boundries
// this function does NOT perform the merge. The function facilitates recursive calls that divide the vector into smallest segments and passes them 
// into the function that performs the merge 'threeWayMerge
// postcondition: vector1 is modified and sorted in ascending order
//************************************************************


void threeWayMergeSort(vector<int>& vector1, int left, int right) {

	// if left < right no need to merge or further divide vector into subvectors
    if (left < right) {

        int firstDivision = left + (right - left) / 3; 			 // first division point
        int secondDivision = firstDivision + (right - left) / 3; // second division point

		// Segments will be 
		// left - firstDivision 
		// (firstDivision+1) - secondDivision
		// (secondDivision+1) - 

        cout << "\nDividing indices " << left << "-" << right;
        cout << " into: " << left << "-" << firstDivision << ", ";
        cout << (firstDivision + 1) << "-" << secondDivision << ", and " << (secondDivision + 1) << "-" << right << "\n";

		// Recursive calls 
        threeWayMergeSort(vector1, left, firstDivision);
        threeWayMergeSort(vector1, firstDivision + 1, secondDivision);
        threeWayMergeSort(vector1, secondDivision + 1, right);

		// This is where the merge is performed 
		// Merge is performed multiple times in recursive calls 
        threeWayMerge(vector1, left, firstDivision, secondDivision, right);
    }
}

int main() {

	vector<int> numbers; // Empty vector. Will contain unsorted vector of numbers read from file
	// originally this was done with arrays but too tricky reading files into an array

	string filename;	 // User inputs into filename we will read data from

	//Prompt for filename 
	cout << "Enter the name of your file: ";
	cin >> filename; 

	//open file name 
	ifstream inFile(filename);

    if (!inFile.is_open()) {
        cerr << "Failed to open the file " << filename << "." << endl;
        return 1;
    }

	string line;	// Current line being read
    while (getline(inFile, line)) {
        
       numbers.push_back(stoi(line)); //stoi string to integer // pushes back to vector
    }

    inFile.close();

    int size = numbers.size();	// Size of vector numbers

    cout << "Given array is: ";
    for (int i = 0; i <= size; i++)
        cout << numbers[i] << " ";
    cout << "\n-------------------------\n";

	// Function call to perform 3 way merge sort
    threeWayMergeSort(numbers, 0, size-1);

	// Prints output
    cout << "-------------------------\n";
    cout << "Sorted array is: ";
    for (int i = 0; i < size; i++)
        cout << numbers[i] << " ";
    cout << "\n";


	// Write text to output file
	ofstream outFile("output.txt");

	if(!outFile.is_open()){
		cerr << "Failed to create or open output.txt for writing" << endl;
		return 1;
	}

	for(int num : numbers){
		outFile << num << endl;
	}

	outFile.close();
	cout << "Values have been written to output.txt" << endl;

    return 0;
}
