/*
 * File:   main.c
 * Author: bathy
 *
 * Created on July 8, 2015, 9:46 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dilu_c.h"
#include "sgfilter.h"



//#include <iostream>

int main(int argc, char **argv) {
    char file_name[250], file_name2[250];
    FILE *fp2, *fp3;
    long file_size = 0;
    int i = 0, mm = 0, m = 0;
    struct header file_head;
    struct mass mass_list[29999];
    double tic_correction = 1, ret_correction = 0;
    int nl = DEFAULT_NL;
    int nr = DEFAULT_NR;
    int ld = DEFAULT_LD;
    int poly = DEFAULT_M;
    //double start_0 = 0, end_0 = 0;
    double *ret_list, *int_list, *sgfilt_list;
    //printf("%f", Sqrt(123456));

    //strcpy(file_name, "C:\\Users\\7cent\\Documents\\Visual Studio 2012\\Projects\\Project1\\Project1\\L-del_Sal_MK_9291pos.ms1.ims");
    strcpy(file_name, argv[1]);

    if (argc > 1) { tic_correction = atof(argv[2]); }

    //printf("%s",testfile);
    /*
    if (argc>1)
    {
            strcpy(ms1name,remove_three(argv[1]));
            strcat(ms1name,"ms1");
    }
    else
    {
            strcpy(ms1name,remove_three(file_name));
            strcat(ms1name,"ms1");
    }
     */
    fp2 = fopen(file_name, "rb");

    if (!fp2) {
        printf("File not found!\n");
        return 1;
    } else {
        fseek(fp2, 0, SEEK_END);
        file_size = ftell(fp2);
        fseek(fp2, 0, SEEK_SET);

    }
    //printf("%d,%d\n",file_size, ftell(fp2));

    if (i % 3 != 0) {
        return 1;
    };

    while (file_size > ftell(fp2)) {
        //while (m<5){
        fread(&file_head, sizeof(file_head), 1, fp2);
        i = (int) file_head.num_point;
        fread(&mass_list, sizeof(float) * i, 1, fp2);
        //m=ftell(fp2);
        //printf("%.4f %.0f %.4f %d\n", mass_list[1].mz,mass_list[1].intensity,mass_list[1].retention,i);

        if (file_head.log_intensity > 5 && i > 150) {
            itoa((int) (file_head.mass_bin * 10000), file_name2);
            strcat(file_name2, ".mass");
            mm = i / 3;
            ret_list = dvector(1, mm);
            int_list = dvector(1, mm);
            sgfilt_list = dvector(1, mm);
            //yf=dvector(1, mm);

            for (m = 0; m < mm; m++) {
                ret_list[m] = mass_list[m].retention + ret_correction;
                int_list[m] = mass_list[m].intensity * tic_correction;
            }
            ins_sort(ret_list, int_list, mm); //sort by ret_time

            sgfilter(int_list, sgfilt_list, mm, nl, nr, ld, poly);
            sgfilter(sgfilt_list, int_list, mm, nl, nr, ld, poly);
            sgfilter(int_list, sgfilt_list, mm, nl, nr, ld, poly);
            sgfilter(sgfilt_list, int_list, mm, nl, nr, ld, poly);

            triangular_filter(int_list, mm);

            sgfilter(int_list, sgfilt_list, mm, nl, nr, ld, poly);
            sgfilter(sgfilt_list, int_list, mm, nl, nr, ld, poly);
            sgfilter(int_list, sgfilt_list, mm, nl, nr, ld, poly);
            sgfilter(sgfilt_list, int_list, mm, nl, nr, ld, poly);

            fp3 = fopen(file_name2, "w");
            fprintf(fp3, "%.4f\t%.4f\n", ret_list[0], int_list[0]);

            for (m = 1; m < mm; m++) {
                fprintf(fp3, "%.4f\t%.4f\n", ret_list[m], int_list[m]);
            }

            fclose(fp3);
            free_dvector(ret_list, 1, mm);
            free_dvector(int_list, 1, mm);
            free_dvector(sgfilt_list, 1, mm);
            //printf("Mass: %f", file_head.mass_bin);
            //getchar();
            //system("./runproc.m test.txt");
        }
    }

    //sgfilter(yr,yf,mm,nl,nr,ld,m);

    printf("done!\n");
    //getchar();

    fclose(fp2);

    return (EXIT_SUCCESS);
}


