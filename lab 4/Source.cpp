#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
double approxFunction(double a, double b, double h) {
    return a * pow(10, b * h);
}
void drawGraph(vector<double> X, double a, double b, int n) {
    ofstream dataFile("data.txt");
    if (!dataFile.is_open()) {
        cerr << "Unable to open data file" << endl;
        return;
    }
    for (int i = 0; i < n; i++)
    {
        double Y = a * pow(10, X[i] * b);
        dataFile << X[i] << " " << Y << endl;
    }
    dataFile.close();
    ofstream scriptFile("script.plt");
    if (!scriptFile.is_open()) {
        cerr << "Unable to open script file" << endl;
        return;
    }
    scriptFile << "set term png\n";
    scriptFile << "set output 'graph.png'\n";
    scriptFile << "set multiplot\n";
    scriptFile << "plot 'data.txt' with lines\n";
    scriptFile << "plot 'oldData.txt' with lines\n";
    scriptFile << "unset multiplot";
    scriptFile.close();
    system("gnuplot script.plt");
}
int main() {
    vector<double> X = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    vector<double> Y = { 760.0, 674.8, 598.0, 528.9, 466.6, 410.6, 360.2 };

    double sumH = 0.0, sumLogP = 0.0, sumHLogP = 0.0, sumH2 = 0.0;
    for (int i = 0; i < X.size(); i++) {
        sumH += X[i];
        sumLogP += log10(Y[i]);
        sumHLogP += X[i] * log10(Y[i]);
        sumH2 += pow(X[i], 2);
    }

    double b = (X.size() * sumHLogP - sumH * sumLogP) / (X.size() * sumH2 - pow(sumH, 2));
    double a = pow(10, (sumLogP - b * sumH) / X.size());
    double dispertion = 0;
    for (int i = 0; i < X.size(); i++) {
        double approximatedPressure = approxFunction(a, b, X[i]);
        dispertion += pow(Y[i] - approximatedPressure, 2);
    }
    dispertion /= X.size();

    cout << "Dispertion: " << sqrt(dispertion) << endl;

    drawGraph(X, a, b, X.size());
}