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


vector<vector<int>> parseFile(const string & filename) {
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

vector<int> getP(vector<vector<int>> matrix)
{
  int size = matrix.size();
  vector<int> result;

  for (int i = 0; i < size; i++)
    {
      result.push_back(matrix[i][0]);
    }
  result.push_back(matrix.back().back()); // get last element

  return result;
}

int MatrixChainOrder(vector<int> & p, int n)
{
  
  n += 1; // because arrays are 0 to num
  
  // Create a 2D vectors initialized with zeros
  int rows = n; 
  int cols = n;
  vector<vector<int>> m(rows, vector<int>(cols, 0)); 
  vector<vector<int>> s(rows, vector<int>(cols, 0));

  int j , min, q;

  for (int d = 1; d < n; d++) //computes distance between i and j
    {
      for (int i = 1; i < n - d; i++) // for rows of tables m and s
        {
          j = i + d;
          min = 2147483647; //MAX int in c++

          for (int k = i; k <= j - 1; k++) // loop to find minimum using formula
            {

              q = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j]; // recursive formula
              
              if (q < min)
              {
                min = q;
                s[i][j] = k; // update s array
                
              }
              
            }
          m[i][j] = min; // update m array
        }
    }

  return m[1][n-1];
}

int main()
{
    string filename;
    cout << "Enter file name (.txt): ";
    cin >> filename;
    cout << endl;

    vector<vector<int>> matrix = parseFile(filename); 
    vector<int> P = getP(matrix);
    int n = matrix.size();
    

    // Function call
    cout << "Minimum number of multiplications is " << MatrixChainOrder(P, n) << endl;
    return 0;
}