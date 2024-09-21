#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//___________________hint_________________
int reference()
{
    printf("-h - to get help for example <-h>.\n");
    printf("-f - statistics for the year or month; for example year - <-s file_name.csv> or month - <-s file_name.csv xx -m>; xx - month number.\n");
    printf("-m - Statistics for the entered month, format: MMYYYY; for example <-m xx>; xx - month number.\n");
    printf("-e - show errors in the file for example <-e>.\n");
    printf("-r - read the file for example <-r file_name>.\n");
    printf("-d - delete entries in a file <-d file_name>.\n");
    return 0;
}
//----------------------------------------

//-----------------| FOR KEY -r |---------
int print_Reading(FILE *f, char *fileName)
{
    f = fopen(fileName, "r");
    if (!f)
    {
        perror("Error opening file");
        return 1;
    }
    char **eror = (char **)malloc(sizeof(char *) * N);
    int len = 0;
    eror = read_File_in_Err1(eror, f, &len);
    printf("# -------- Readed---------\n");
    for (size_t i = 1; i < len; i++)
    {
        printf("%d \t%s", i, eror[i]); /* code */
    }
    fclose(f);
    free(eror);
}
//--------------| For Key -e |-------------------
int reint_arr_Error(FILE *file, char *FileName)
{
    struct sensor *in = malloc(N * sizeof(struct sensor));
    char **eror = (char **)malloc(sizeof(char *) * 1024);
    int arr[100];
    int *ar = arr;
    int s = 0, c = 0;
    file = fopen(FileName, "r");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }
    eror = read_File_in_Err1(eror, file, &c);
    fclose(file);
    file = fopen(FileName, "r");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }
    ar = Read_Csv_Error_Buff(in, file, &s);
    print_Error(eror, ar, c, s);
    fclose(file);
    free(in);
    free(eror);
}
void print_Error(char **err, int *arr, int n_err, int n_arr)
{
    printf("#     Lain        Erors list_");
    printf("\n-------------------------------------------\n");
    // ==================================
    for (int i = 0; i < n_arr; i++)
    {
        for (size_t j = 1; j < n_err; j++)
        {
            if (arr[i] == j)
            {
                printf("%d\t%d\t Errors - %s", i + 1, arr[i], err[j]);
            }
        }
    }
}

// --------------------| FOR KEY -f  |-------
int print_Statistic_Year(FILE *file, char *fileName)
{
    char Month[12][10] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"};
    file = fopen(fileName, "r");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }
    int month = 0;
    struct sensor *in = malloc(N * sizeof(struct sensor));
    int numb = Read_Csv_Error_Outstruct(in, file);
    struct st starr;
    starr.arrmax = (int *)malloc(monN * sizeof(int));
    if (starr.arrmax == 0)
    {
        puts("Not memore");
        return 1;
    }
    starr.arrmin = (int *)malloc(monN * sizeof(int));
    if (starr.arrmax == 0)
    {
        puts("Not memore");
        return 1;
    }
    starr.arrmidl = (float *)malloc(monN * sizeof(int));
    if (starr.arrmax == 0)
    {
        puts("Not memore");
        return 1;
    }
    if (Asc() == 1)
    {
        printf("Start_Sort\n");
        SortByDate_Compe(in, numb);
        printf("Finish_Sort\n");
    }

    //  print(in, numb);

    starr.arrmax = staticM_Year_max2(in, numb, monN); // test str
    starr.arrmin = staticM_Year_min2(in, numb, monN, &month);
    starr.arrmidl = staticM_Year_midl(in, numb, monN);

    if (month == 12)
    {
        printf("\n\t\t=======| STATISTIC for YEAR |============\n");

        printf("\n  #     YEAR    MONTH             Max_Tem        Min_Tem        Average\n");
        printf("=========================================================================\n");
        for (size_t i = 0; i < 12; i++)
        {
            // printf("  %d\t%4d\t%-8s\t  %3d\t\t %3d\t\t%.2f\n", i + 1, in[i].year, Month[i], arr4[i], arr3[i], arr5[i]);
            printf("  %d\t%4d\t%-8s\t  %3d\t\t %3d\t\t%.2f\n", i + 1, in[i].year, Month[i], starr.arrmax[i], starr.arrmin[i], starr.arrmidl[i]);
        }
        printf("\n===================| General statistics for the year |=========================\n");
        max_Tem(in, numb);
        min_Tem(in, numb);
        midl_Tem(in, numb);
    }
    else
    {
        printf("\nNo information available for print fuull statictic \n\n");

        printf("\n===================/ General statistics for the year |=========================\n");
        max_Tem(in, numb);
        min_Tem(in, numb);
        midl_Tem(in, numb);
    }

    fclose(file);
    free(in);
}

// _______________________________________________

//_______________| ERRORS_MASSEG |________________
int mesag_Errors(FILE *file, char *filename)
{
    file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }
    struct sensor *in = malloc(N * sizeof(struct sensor));

    file = fopen("D:/PRO_G/VsCode/CURS_PROJECT/temperature_sma_E.csv", "r");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }
    printf("========================================\n");
    if (Read_Csv_Error_Maseg(in, file) == 1)
        printf("\tThe file contains errors \n");
    else
        printf("\tThe file does not contain an error\n");

    printf("=========================================\n");

    fclose(file);
}

//__________| GENERAL STATISTIC MONTH |______________
int prpint_Month(FILE *file, char *fileName, int numbr)
{
    char Month[12][10] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"};
    file = fopen(fileName, "r");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }

    struct sensor *in = malloc(N * sizeof(struct sensor));
    int numb = Read_Csv_Error_Outstruct(in, file);
     if (Asc() == 1)
    {
        printf("\nStart_Sort\n");
        SortByDate_Compe(in, numb);
        printf("Finish_Sort\n");
        printf("\n__________________________________________________________________________________________________\n");
    }
    printf("\n===================| General statistics for the month |=========================\n");
    printf("\t%-8s ", Month[numbr - 1]);
    printf("\n________________________________________________________________________________\n");
        min_Tem_mons(in, numb, 2021, numbr);
        max_Tem_mons(in, numb, 2021, numbr);
        midl_Tem_mons(in, numb, 2021, numbr);
        fclose(file);
    free(in);

}

int del_Error_p(FILE *file, char *fileName, int index)
{
    struct sensor *in = malloc(N * sizeof(struct sensor));
    char **eror = NULL;
    eror = (char **)malloc(sizeof(char *) * N);
    if (eror == NULL)
        printf("Not memore\n");

    int s = 0, d = 0;
    file = fopen(fileName, "r");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }
   
    eror = read_File_in_Err1(eror, file, &s);
    printf("\n=================Dell_Error=====================\n");
    // printf("\n Enter number lain for dellete\n");
    // scanf(" %d", &d);
    Del_Error(eror, s, index);
    fclose(file);
     file = fopen(fileName, "w");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }
    for (size_t i = 1; i < s - 1; i++)
    {
        fprintf(file, "%s", eror[i]);
    }
    fclose(file);

}