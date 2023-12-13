#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double calculateRoot(double param) {
    return sqrt(1 + pow(param, 3));
}

double calculateFormula(double paramX, double paramY) {
    return paramX * paramX + 2 * paramY;
}

vector<double> createInterval(double start, double end, int divisions) {
    vector<double> intervalPoints(divisions + 1);
    double step = (end - start) / divisions;
    for (int i = 0; i <= divisions; ++i) {
        intervalPoints[i] = start + i * step;
    }
    return intervalPoints;
}

double calculateTrapezoidal(const vector<double>& intervalPoints) {
    double total = 0.0;
    double stepSize = intervalPoints[1] - intervalPoints[0];
    int count = intervalPoints.size() - 1;

    for (int i = 0; i <= count; ++i) {
        if (i == 0 || i == count) {
            total += calculateRoot(intervalPoints[i]);
        }
        else {
            total += 2 * calculateRoot(intervalPoints[i]);
        }
    }

    return stepSize / 2 * total;
}

double calculateSimpson(const vector<double>& intervalPoints) {
    double total = 0.0;
    double stepSize = intervalPoints[1] - intervalPoints[0];
    int count = intervalPoints.size() - 1;

    for (int i = 0; i <= count; ++i) {
        if (i == 0 || i == count) {
            total += calculateRoot(intervalPoints[i]);
        }
        else if (i % 2 == 0) {
            total += 2 * calculateRoot(intervalPoints[i]);
        }
        else {
            total += 4 * calculateRoot(intervalPoints[i]);
        }
    }

    return stepSize / 3 * total;
}

double preciseIntegration(double start, double end, double precision, double (*integrationMethod)(const vector<double>&)) {
    int divisions = 2;
    double currentResult = 0.0; 
    double lastResult;

    do {
        vector<double> interval = createInterval(start, end, divisions);
        lastResult = currentResult;
        currentResult = integrationMethod(interval);
        divisions *= 2;
    } while (fabs(currentResult - lastResult) > precision);

    return currentResult;
}

double advancedSimpsonIntegration(double xStart, double xEnd, double yStart, double yEnd, int xDivisions, int yDivisions) {
    double xStep = (xEnd - xStart) / (2 * xDivisions);
    double yStep = (yEnd - yStart) / (2 * yDivisions);
    double result = 0;

    for (int i = 0; i < xDivisions; i++) {
        for (int j = 0; j < yDivisions; j++) {
            double x0 = xStart + 2 * i * xStep;
            double x1 = xStart + (2 * i + 1) * xStep;
            double x2 = xStart + (2 * i + 2) * xStep;
            double y0 = yStart + 2 * j * yStep;
            double y1 = yStart + (2 * j + 1) * yStep;
            double y2 = yStart + (2 * j + 2) * yStep;

            result += calculateFormula(x0, y0) + 4 * calculateFormula(x1, y0) + calculateFormula(x2, y0) +
                4 * calculateFormula(x0, y1) + 16 * calculateFormula(x1, y1) + 4 * calculateFormula(x2, y1) +
                calculateFormula(x0, y2) + 4 * calculateFormula(x1, y2) + calculateFormula(x2, y2);
        }
    }

    return xStep * yStep / 9 * result;
}

int main() {
    double startX = 0.8, endX = 1.762;
    double precision = 10e-4;
    cout << "Precision: " << precision << endl;
    cout << "Trapezoidal Method: " << preciseIntegration(startX, endX, precision, calculateTrapezoidal) << endl;
    cout << "Simpson Method: " << preciseIntegration(startX, endX, precision, calculateSimpson) << endl;

    precision = 10e-5;
    cout << "Precision: " << precision << endl;
    cout << "Trapezoidal Method: " << preciseIntegration(startX, endX, precision, calculateTrapezoidal) << endl;
    cout << "Simpson Method: " << preciseIntegration(startX, endX, precision, calculateSimpson) << endl;

    cout << "Advanced Simpson Integration: " << advancedSimpsonIntegration(0, 2, 0, 1, 1000, 1000) << endl;
}
