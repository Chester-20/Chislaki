#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void gaussElimination(vector<vector<double>> A, vector<double> B, vector<double>& x) {
    for (int i = 0; i < 3; i++) {
        int maxRow = i;
        for (int k = i + 1; k < 3; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        swap(A[maxRow], A[i]);
        swap(B[maxRow], B[i]);

        for (int k = i + 1; k < 3; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < 3; j++) {
                A[k][j] -= factor * A[i][j];
            }
            B[k] -= factor * B[i];
        }
    }
    for (int i = 0; i < 3; i++)
    {
        x.push_back(B[i]);
    }
    for (int i = 2; i >= 0; i--) {
        for (int j = i + 1; j < 3; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    cout << "Solution vector:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }
}
void residualVector(vector<vector<double>> A, vector<double> B, vector<double> x)
{
    double residual[3];
    double maxResidual = 0.0;
    for (int i = 0; i < 3; i++) {
        residual[i] = B[i];
        for (int j = 0; j < 3; j++) {
            residual[i] -= A[i][j] * x[j];
        }
        if (abs(residual[i]) > maxResidual) {
            maxResidual = abs(residual[i]);
        }
    }
    cout << "Residual vector:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "residual[" << i << "] = " << residual[i] << endl;
    }
    cout << "max residual = " << maxResidual << endl;
}
void relativeError(vector<vector<double>> A, vector<double> x)
{
    vector<double> b;
    for (int i = 0; i < 3; i++)
    {
        b.push_back(0);
        for (int j = 0; j < 3; j++)
        {
            b[i] += A[i][j] * x[j];
        }
    }
    vector<double> _x;
    gaussElimination(A, b, _x);
    double maxX = 0.0;
    double maxGap = 0.0;
    for (int i = 0; i < 3; i++)
    {
        if (abs(_x[i] - x[i]) > maxGap)
        {
            maxGap = abs(_x[i] - x[i]);
        }
        if (abs(x[i]) > maxX)
        {
            maxX = x[i];
        }
    }
    cout << "Relative error: " << maxGap / maxX << endl;
}
int main() {
    vector<vector<double>> A = { {6, 13, -17},
                                {13, 29, -38},
                                {-17, -38, 50} };
    vector<double> b = { 2, 4, -5};
    vector<double> x;
    gaussElimination(A, b, x);
    residualVector(A, b, x);
    relativeError(A, x);
}
