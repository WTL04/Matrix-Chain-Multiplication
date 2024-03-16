#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

// print matrix
void printMatrix(const vector<vector<int>> &matrix) {
  cout << "Matrix: " << endl;
  for (const auto &row : matrix) {
    for (int element : row) {
      cout << element << " ";
    }
    cout << endl;
  }
}

// print row
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


vector<vector<int>> parseFile(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "Failed to open file: " << filename << endl;
    exit(1);
  }

  vector<vector<int>> matrix;
  string line;

  while (getline(file, line)) {

    stringstream ss(line);
    char ch;
    int num;
    vector<int> row;

    while (ss >> ch) {
      if (isdigit(ch) || ch == '-') {

        ss.putback(ch);
        ss >> num;
        row.push_back(num);

      } else if (ch == ',' || ch == '{') {

        continue; // skip commas and {

      } else if (ch == '}') {

        matrix.push_back(row);
        row.clear();

        // if consecutive closing brackets --> break
        char next_char;
        if (ss >> next_char && next_char == '}') {
          break;
        }
      }
    }
  }
  file.close();
  return matrix;
}

int * getPArray(vector<vector<int>> matrix)
{
    int size = matrix.size();
    int* result = new int[size+1]; // Allocate memory for the array

    for (int i = 0; i < size; i++)
    {
        result[i] = matrix[i][0];
    }
    result[size] = matrix.back().back(); // Assign the last item

    return result;
}

// int MatrixChainOrder(int p[], int size)
// {
//     int table[size][size];

//     // Set k[i][i] = 0 since no multiplications are needed for a single matrix
//     for (int i = 0; i < size; i++) {
//         table[i][i] = 0;
//     }

//     // Iterate over the chain length
//     for (int len = 2; len <= size; len++) 
//     {
//         // Iterate over the start index of the chain

//         for (int i = 1; i <= size - len + 1; i++) 
//         {
//             int j = i + len - 1; // Calculate the end index of the chain
//             table[i][j] = 2147483647 ;

//             // Iterate over the partition point
//             for (int k = i; k < j; k++) 
//             {
//                 // Calculate the cost of multiplying matrices from i to j
//                 int cost = table[i][k] + table[k+1][j] + p[i-1] * p[k] * p[j];
//                 // Update the minimum cost
//                 table[i][j] = min(table[i][j], cost);
//             }
//         }
//     }
//     // Return the minimum number of multiplications needed for the entire chain
//     return table[0][size-1];
    
// }
 
int main()
{
    string filename;
    cout << "Enter file name (.txt): ";
    cin >> filename;
    cout << endl;

    auto matrix = parseFile(filename); 
    int* P = getPArray(matrix);

    int size = matrix.size();
 
    // Function call
    //cout << "Minimum number of multiplications is " << MatrixChainOrder(P, size) << endl;

    delete[] P; // for no memory leaks cause using pointers
    return 0;
}