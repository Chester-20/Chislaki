#include <iostream>

using namespace std;

void printTest(int n, double a[][3], double b[]) {
    cout << "\nTest\n";
    for (int i{ 0 }; i < n; ++i) {
        for (int j{ 0 }; j < n; ++j) {
            cout << a[i][j] << "\t";
        }
        cout << "\t| " << b[i] << "\n";
    }
    return;
}

int main() {
    cout << "Hello Gayss!" << endl;

    const int n{ 3 };
    double a[n][n] = {
            {  6,  13, -17 },
            { 13,  29, -38 },
            {-17, -38,  50 }
    };
    double b[n]{ 2, 4, -5 };

    double a0[n][n]{};
    double b0[n]{};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a0[i][j] = a[i][j];
        }
        b0[i] = b[i];
    }

    printTest(n, a, b);
    
    int ior[n]{};	
   
    for (int i = 0; i < n; ++i) ior[i] = i;

  
    int i0{};
    for (int k = 0; k < n; ++k) {
     
        double akk{ 0 }; int m{}; int p{};
        for (int i = k; i < n; ++i) {
            i0 = ior[i];
            if (abs(a[i0][k]) > akk) {
                m = i0;
                p = i;
                akk = abs(a[i0][k]);
            }
        }
        
        swap(ior[p], ior[k]);
      
        ior[k] = m;
        double amain{ a[m][k] };
        if (!amain) {
            cout << "Error: IER = 1" << endl;
            return 0;
        }
        
        for (int j = k; j < n; ++j) {
            a[m][j] /= amain;
        }
        b[m] /= amain;
     
        for (int i = k + 1; i < n; ++i) {
            i0 = ior[i];
            for (int j = k + 1; j < n; ++j) {
                a[i0][j] -= a[i0][k] * a[m][j];
            }
            b[i0] -= a[i0][k] * b[m];
        }
      
    }
    
    if (!(a[i0][n - 1])) {
        cout << "Error: IER = 1" << endl;
        return 0;
    }

    double x[n]{};   
    i0 = ior[n - 1];
    b[i0] /= a[i0][n - 1];
    x[n - 1] = b[i0];

  
    for (int k = n - 2; k >= 0; --k) {
        i0 = ior[k];
        x[k] = b[i0];
        for (int j = n - 1; j > k; --j) {
            x[k] -= a[i0][j] * x[j];
        }
    }

    cout << "\nX:\t";
    for (int i = 0; i < n; ++i) {
        cout << x[i] << "\t";
    }


    double f[n]{ 0 };   
    double bDelta{ 0 }; 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            f[i] += a0[i][j] * x[j];
            a[i][j] = a0[i][j];
        }
        b[i] = f[i];
        f[i] -= b0[i]; 
        bDelta = abs(f[i]) > bDelta ? abs(f[i]) : bDelta;
    }
    cout << "\nF:\t";
    for (int i = 0; i < n; ++i) {
        cout << f[i] << "\t";
    }
    cout << "\nDelta:\t" << bDelta;

   

    for (int i = 0; i < n; ++i) ior[i] = i;

  
    for (int k = 0; k < n; ++k) {
      
        double akk{ 0 }; int m{}; int p{};
        for (int i = k; i < n; ++i) {
            i0 = ior[i];
            if (abs(a[i0][k]) > akk) {
                m = i0;
                p = i;
                akk = abs(a[i0][k]);
            }
        }

        swap(ior[p], ior[k]);

        ior[k] = m;
        double amain{ a[m][k] };
        if (!amain) {
            cout << "Error: IER = 1" << endl;
            return 0;
        }
     
        for (int j = k; j < n; ++j) {
            a[m][j] /= amain;
        }
        b[m] /= amain;
    
        for (int i = k + 1; i < n; ++i) {
            i0 = ior[i];
            for (int j = k + 1; j < n; ++j) {
                a[i0][j] -= a[i0][k] * a[m][j];
            }
            b[i0] -= a[i0][k] * b[m];
        }
 

    }
 
    if (!(a[i0][n - 1])) {
        cout << "Error: IER = 1" << endl;
        return 0;
    }

    double x00[n]{};   
    i0 = ior[n - 1];
    b[i0] /= a[i0][n - 1];
    x00[n - 1] = b[i0];

    for (int k = n - 2; k >= 0; --k) {
        i0 = ior[k];
        x00[k] = b[i0];
        for (int j = n - 1; j > k; --j) {
            x00[k] -= a[i0][j] * x00[j];
        }
    }

    cout << "\nX00:\t";
    for (int i = 0; i < n; ++i) {
        cout << x00[i] << "\t";
    }

 
    double max00{ 0.0 };
    double max{ 0.0 };
    for (int i = 0; i < n; ++i) {
        max00 = abs(x00[i] - x[i]) > max00 ? abs(x00[i] - x[i]) : max00;
        max = x[i] > max ? x[i] : max;
    }
    cout << "\ndelta:\t" << max00 / max;
    cout << "\nGayss itog" << endl;

    return 0;
}

