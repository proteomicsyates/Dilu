//
// Created by 7cent on 8/5/2015.
//

#ifndef DILU_CLION_DILU_C_H
#define DILU_CLION_DILU_C_H

#endif //DILU_CLION_DILU_C_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct mass {
    float mz;
    float intensity;
    float retention;
};

struct header {
    float mass_bin;
    float num_point;
    float log_intensity;
};

char *remove_three(const char *filename) {
    size_t len = strlen(filename);
    char *newfilename = malloc(len - 2);
    memcpy(newfilename, filename, len - 3);
    newfilename[len - 3] = 0;
    return newfilename;
}

float InvSqrt(float x) {
    float xhalf = 0.5f * x;
    int i = *(int *) &x; // store floating-point bits in integer
    i = 0x5f3759df - (i >> 1); // initial guess for Newton's method
    x = *(float *) &i; // convert new bits into float
    x = x * (1.5f - xhalf * x * x); // One round of Newton's method
    return x;
}

float Sqrt(float val) {
    long tmp = *(long *) &val;
    tmp -= 127L << 23; /* Remove IEEE bias from exponent (-2^23) */
    /* tmp is now an appoximation to logbase2(val) */
    tmp = tmp >> 1; /* divide by 2 */
    tmp += 127L << 23; /* restore the IEEE bias from the exponent (+2^23) */
    return *(float *) &tmp;
}

/*
double *dvector(long nl, long nh) {
    double*v;
    long k;
    v = (double*) malloc((size_t) ((nh - nl + 2) * sizeof (double)));
    if (!v) {
        printf("Error: Allocation failure.");
        exit(1);
    }
    for (k = nl; k <= nh; k++)v[k] = 0.0;
    return v - nl + 1;
}

void free_dvector(double*v, long nl, long nh) {
    free((char*) (v + nl - 1));
}
*/
float *fvector(int nl, int nh) {
    float *v;
    int k;
    v = (float *) malloc((size_t) ((nh - nl + 2) * sizeof(float)));
    if (!v) {
        printf("Error: Allocation failure.");
        exit(1);
    }
    for (k = nl; k <= nh; k++)v[k] = 0.0;
    return v - nl + 1;
}

void free_fvector(float *v, int nl, int nh) {
    free((char *) (v + nl - 1));
}

void ins_sort(double *pointer, double *pointer2, int n) { //sort fvector 1 and fvector 2 based on fvector1's value
    int c, d;
    double t;

    for (c = 0; c < n; c++) {
        d = c;

        while (d > 0 && *(pointer + d) < *(pointer + d - 1)) {
            t = *(pointer + d);
            *(pointer + d) = *(pointer + d - 1);
            *(pointer + d - 1) = t;
            t = *(pointer2 + d);
            *(pointer2 + d) = *(pointer2 + d - 1);
            *(pointer2 + d - 1) = t;

            d--;
        }
    }
}

void triangular_filter(double *pointer, int n) { //sort fvector 1 and fvector 2 based on fvector1's value
    int i;
    double t[n], t11=0;
    for (i = 0; i < n; i++) {
        t[i] = *(pointer + i);
    }
    for(i=0;i<49;i++){t11+=t[i];}
    *(pointer + 24) = t11 / 49;
    for (i = 25; i < n-25; i++) {
        *(pointer + i) = *(pointer + i - 1) - t[i - 25] / 49 + t[i + 24] / 49;
    }

    for (i = 0; i < n; i++) {
        t[i] = *(pointer + i);
    }
    t11=0;
    for(i=0;i<49;i++){t11+=t[i];}
    *(pointer + 24) = t11 / 49;
    for (i = 25; i < n-25; i++) {
        *(pointer + i) = *(pointer + i - 1) - t[i - 25] / 49 + t[i + 24] / 49;
    }


}


char *itoa(int value, char *result) {

    char *ptr = result, *ptr1 = result, tmp_char;
    int tmp_value, base = 10;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 +
                                                                                           (tmp_value - value * base)];
    } while (value);

    // Apply negative sign
    //if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}
