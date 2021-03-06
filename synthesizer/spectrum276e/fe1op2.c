#include <math.h>
#include <errno.h>
#include "spectrum.h"
double partfn(double code, double T, double Ne);

double fe1op(nu, model, j)
double nu;
atmosphere *model;
int j;
{
    double hckt, A, H, waveno, x, u, xsect;
    int i;
    float g[48] = { 25.0, 35.0, 21.0, 15.0, 9.0, 35.0, 33.0, 21.0,
        27.0, 49.0, 9.0, 21.0, 27.0, 9.0, 9.0, 25.0,
        33.0, 15.0, 35.0, 3.0, 5.0, 11.0, 15.0, 13.0,
        15.0, 9.0, 21.0, 15.0, 21.0, 25.0, 35.0, 9.0,
        5.0, 45.0, 27.0, 21.0, 15.0, 21.0, 15.0, 25.0,
        21.0, 35.0, 5.0, 15.0, 45.0, 35.0, 55.0, 25.0
    };
    float E[48] = { 500.0, 7500.0, 12500.0, 17500.0, 19000.0, 19500.0,
        19500.0, 21000.0, 22000.0, 23000.0, 23000.0, 24000.0,
        24000.0, 24500.0, 24500.0, 26000.0, 26500.0, 26500.0,
        27000.0, 27500.0, 28500.0, 29000.0, 29500.0, 29500.0,
        29500.0, 30000.0, 31500.0, 31500.0, 33500.0, 33500.0,
        34000.0, 34500.0, 34500.0, 35000.0, 35500.0, 37000.0,
        37000.0, 37000.0, 38500.0, 40000.0, 40000.0, 41000.0,
        41000.0, 43000.0, 43000.0, 43000.0, 43000.0, 44000.0
    };
    float WNO[48] = { 63500.0, 58500.0, 53500.0, 59500.0, 45000.0, 44500.0,
        44500.0, 43000.0, 58000.0, 41000.0, 54000.0, 40000.0,
        40000.0, 57500.0, 55500.0, 38000.0, 57500.0, 57500.0,
        37000.0, 54500.0, 53500.0, 55000.0, 34500.0, 34500.0,
        34500.0, 34000.0, 32500.0, 32500.0, 32500.0, 32500.0,
        32000.0, 29500.0, 29500.0, 31000.0, 30500.0, 29000.0,
        27000.0, 54000.0, 27500.0, 24000.0, 47000.0, 23000.0,
        44000.0, 42000.0, 42000.0, 21000.0, 42000.0, 42000.0
    };

    u = partfn(26.0, model->T[j], model->Ne[j]);
    waveno = 3.335641e-11 * nu;
    hckt = 1.438832 / model->T[j];

    A = 0.0;

    if (waveno < 21000.0)
        return (A);

    for (i = 0; i < 48; i++) {
        if (WNO[i] >= waveno)
            continue;
        xsect = 3.0e-18 / (1.0 + pow((WNO[i] + 3000.0 - waveno) / WNO[i] / 0.1, 4.0));
        A += xsect * g[i] * exp(-E[i] * hckt);
    }

    A *= model->stim[j];

    return (A / u);
}
