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

 
// Matrix Ai has dimension p[i-1] x p[i]
// for i = 1 . . . n
int MatrixChainOrder(int p[], int i, int j)
{
    if (i == j)
        return 0;
    int k;
    int mini = 2147483647; //max int limit
    int count;
 
    // Place parenthesis at different places
    // between first and last matrix, 
    // recursively calculate count of multiplications 
    // for each parenthesis placement 
    // and return the minimum count
    for (k = i; k < j; k++) 
    {
        count = MatrixChainOrder(p, i, k) + MatrixChainOrder(p, k + 1, j) + p[i - 1] * p[k] * p[j];
 
        mini = min(count, mini);
    }
 
    // Return minimum count
    return mini;
}
 
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
    cout << "Minimum number of multiplications is " << MatrixChainOrder(P, 1, size) << endl;

    delete[] P; // for no memory leaks cause using pointers
    return 0;
}