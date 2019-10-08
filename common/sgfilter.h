//
// Created by bathy on 8/5/2015.
//

#ifndef DILU_CLION_SGFILTER_H
#define DILU_CLION_SGFILTER_H

#endif //DILU_CLION_SGFILTER_H


#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define DEFAULT_NL (15)
#define DEFAULT_NR (15)
#define DEFAULT_M (4)
#define DEFAULT_LD (0)
#define EPSILON ((double)(1.0e-20))
#define NCHMAX (256)
#define CONVOLVE_WITH_NR_CONVLV (0)



#if defined(_CYGWIN_SIGNAL_H)||defined(__APPLE__)||defined(__unix__)||defined(__linux)
#define UNIX_LIKE_OS (1)
#endif


int*ivector(long nl, long nh) {
    int*v;
    v = (int*) malloc((size_t) ((nh - nl + 2) * sizeof (int)));
    if (!v) {
        //log("Error: Allocation failure.");
        exit(1);
    }
    return v - nl + 1;
}

double*dvector(long nl, long nh) {
    double*v;
    long k;
    v = (double*) malloc((size_t) ((nh - nl + 2) * sizeof (double)));
    if (!v) {
        //log("Error: Allocation failure.");
        exit(1);
    }
    for (k = nl; k <= nh; k++)v[k] = 0.0;
    return v - nl + 1;
}

double**dmatrix(long nrl, long nrh, long ncl, long nch) {
    long i, nrow = nrh - nrl + 1, ncol = nch - ncl + 1;
    double**m;
    m = (double**) malloc((size_t) ((nrow + 1) * sizeof (double*)));
    if (!m) {
        //log("Allocation failure 1 occurred.");
        exit(1);
    }
    m += 1;
    m -= nrl;
    m[nrl] = (double*) malloc((size_t) ((nrow * ncol + 1) * sizeof (double)));
    if (!m[nrl]) {
        //log("Allocation failure 2 occurred.");
        exit(1);
    }
    m[nrl] += 1;
    m[nrl] -= ncl;
    for (i = nrl + 1; i <= nrh; i++)m[i] = m[i - 1] + ncol;
    return m;
}

void free_ivector(int*v, long nl, long nh) {
    free((char*) (v + nl - 1));
}

void free_dvector(double*v, long nl, long nh) {
    free((char*) (v + nl - 1));
}

void free_dmatrix(double**m, long nrl, long nrh, long ncl, long nch) {
    free((char*) (m[nrl] + ncl - 1));
    free((char*) (m + nrl - 1));
}

void lubksb(double**a, int n, int*indx, double b[]) {
    int i, ii = 0, ip, j;
    double sum;

    for (i = 1; i <= n; i++) {
        ip = indx[i];
        sum = b[ip];
        b[ip] = b[i];
        if (ii)
            for (j = ii; j <= i - 1; j++)sum -= a[i][j] * b[j];
        else if (sum)ii = i;
        b[i] = sum;
    }
    for (i = n; i >= 1; i--) {
        sum = b[i];
        for (j = i + 1; j <= n; j++)sum -= a[i][j] * b[j];
        b[i] = sum / a[i][i];
    }
}

void ludcmp(double**a, int n, int*indx, double*d) {
    int i, imax = 0, j, k;
    double big, dum, sum, temp;
    double*vv;

    vv = dvector(1, n);
    *d = 1.0;
    for (i = 1; i <= n; i++) {
        big = 0.0;
        for (j = 1; j <= n; j++)
            if ((temp = fabs(a[i][j])) > big)big = temp;
        if (big == 0.0) {
            //log("Error: Singular matrix found in routine ludcmp()");
            exit(1);
        }
        vv[i] = 1.0 / big;
    }
    for (j = 1; j <= n; j++) {
        for (i = 1; i < j; i++) {
            sum = a[i][j];
            for (k = 1; k < i; k++)sum -= a[i][k] * a[k][j];
            a[i][j] = sum;
        }
        big = 0.0;
        for (i = j; i <= n; i++) {
            sum = a[i][j];
            for (k = 1; k < j; k++)
                sum -= a[i][k] * a[k][j];
            a[i][j] = sum;
            if ((dum = vv[i] * fabs(sum)) >= big) {
                big = dum;
                imax = i;
            }
        }
        if (j != imax) {
            for (k = 1; k <= n; k++) {
                dum = a[imax][k];
                a[imax][k] = a[j][k];
                a[j][k] = dum;
            }
            *d = -(*d);
            vv[imax] = vv[j];
        }
        indx[j] = imax;
        if (a[j][j] == 0.0)a[j][j] = EPSILON;
        if (j != n) {
            dum = 1.0 / (a[j][j]);
            for (i = j + 1; i <= n; i++)a[i][j] *= dum;
        }
    }
    free_dvector(vv, 1, n);
}

char sgcoeff(double c[], int np, int nl, int nr, int ld, int m) {
    void lubksb(double**a, int n, int*indx, double b[]);
    void ludcmp(double**a, int n, int*indx, double*d);
    int imj, ipj, j, k, kk, mm, *indx;
    double d, fac, sum, **a, *b;

    if (np < nl + nr + 1 || nl < 0 || nr < 0 || ld > m || nl + nr < m) {
        return (1);
    }

    indx = ivector(1, m + 1);
    a = dmatrix(1, m + 1, 1, m + 1);
    b = dvector(1, m + 1);
    for (ipj = 0; ipj <= (m << 1); ipj++) {
        sum = (ipj ? 0.0 : 1.0);
        for (k = 1; k <= nr; k++)sum += pow((double) k, (double) ipj);
        for (k = 1; k <= nl; k++)sum += pow((double) -k, (double) ipj);
        mm = (ipj < 2 * m - ipj ? ipj : 2 * m - ipj);
        for (imj = -mm; imj <= mm; imj += 2)a[1 + (ipj + imj) / 2][1 + (ipj - imj) / 2] = sum;
    }
    ludcmp(a, m + 1, indx, &d);
    for (j = 1; j <= m + 1; j++)b[j] = 0.0;
    b[ld + 1] = 1.0;
    lubksb(a, m + 1, indx, b);
    for (kk = 1; kk <= np; kk++)c[kk] = 0.0;
    for (k = -nl; k <= nr; k++) {
        sum = b[1];
        fac = 1.0;
        for (mm = 1; mm <= m; mm++)sum += b[mm + 1]*(fac *= k);
        kk = ((np - k) % np) + 1;
        c[kk] = sum;
    }
    free_dvector(b, 1, m + 1);
    free_dmatrix(a, 1, m + 1, 1, m + 1);
    free_ivector(indx, 1, m + 1);
    return (0);
}

char sgfilter(double yr[], double yf[], int mm, int nl, int nr, int ld, int m) {
    int np = nl + 1 + nr;
    double*c;
    char retval;

    int j;
    long int k;
    c = dvector(1, nl + nr + 1);
    retval = sgcoeff(c, np, nl, nr, ld, m);
    if (retval == 0) {
        for (k = 1; k <= nl; k++) {
            for (yf[k] = 0.0, j = -nl; j <= nr; j++) {
                if (k + j >= 1) {
                    yf[k] += c[(j >= 0 ? j + 1 : nr + nl + 2 + j)] * yr[k + j];
                }
            }
        }
        for (k = nl + 1; k <= mm - nr; k++) {
            for (yf[k] = 0.0, j = -nl; j <= nr; j++) {
                yf[k] += c[(j >= 0 ? j + 1 : nr + nl + 2 + j)] * yr[k + j];
            }
        }
        for (k = mm - nr + 1; k <= mm; k++) {
            for (yf[k] = 0.0, j = -nl; j <= nr; j++) {
                if (k + j <= mm) {
                    yf[k] += c[(j >= 0 ? j + 1 : nr + nl + 2 + j)] * yr[k + j];
                }
            }
        }
    }
    free_dvector(c, 1, nr + nl + 1);
    return (retval);
}
