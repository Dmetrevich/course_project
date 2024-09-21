 #include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define N 10000000
#define monN 12 

struct sensor
{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int temper;
};
//-----------------
struct st
{
    int *arrmin;
    int *arrmax;
    float *arrmidl;
    int *arrdate;
};

//------------------
// const char Month[12][12] = {
//     "January",
//     "February",
//     "March",
//     "April",
//     "May",
//     "June",
//     "July",
//     "August",
//     "September",
//     "October",
//     "November",
//     "December"};
//---------------------

int reference();
//_______________________________
char **read_File_in_Err1(char **err, FILE *file, int *p);// Read txt & csv file
int print_Reading(FILE *file, char *filename);
int reint_arr_Error(FILE *file,char *FileName);  //print error arr & sring hev error
int *Read_Csv_Error_Buff(struct sensor *info, FILE *file, int *p);   //arrey number lain error
void print_Error(char **err, int *arr, int n_err, int n_arr);

//-------------| Key -f |-------------------
//_______________| SORT_DATE |__________________________
void cgangeIJ(struct sensor *info, int i, int j);
int CompareDate(struct sensor *a, struct sensor *b);
void SortByDate_Compe(struct sensor *info, int n);

//_______________| READ_PRINT |_______________________
int Read_Csv_Error_Outstruct(struct sensor *info, FILE *file);
void print(struct sensor *info, int n);

//______________STATIST_YEAR________________
int *staticM_Year_min2(struct sensor *in, int numb, int n, int *mont);
int *staticM_Year_max2(struct sensor *in, int numb, int n);
float *staticM_Year_midl(struct sensor *in, int numb, int n);

//______________ASC___________________
int Asc();

//_____________GENERAL STATISTIC_____________
void max_Tem(struct sensor *sens, int number);
void min_Tem(struct sensor *sens, int number);
int midl_Tem(struct sensor *sens, int number);
// --------------------| FOR KEY -f  |-------
int print_Statistic_Year(FILE *file, char *fileName);

// ------------| FOR KEY -m |--------
int rpint_Month(FILE *file, char *fileName, int numbr);
void max_Tem_mons(struct sensor *sens, int number, int year, int month);
void midl_Tem_mons(struct sensor *sens, int number, int year, int month);
void min_Tem_mons(struct sensor *sens, int number, int year, int month);

int *staticM_month_date3(struct sensor *in, int numb, int index, int *n);
float *staticM_month_midl(struct sensor *in, int numb, int index, int *n);
int *staticM_month_max2(struct sensor *in, int numb, int index, int *n, int *f);
int *staticM_month_min2(struct sensor *in, int numb, int index, int *n);
//_______________| ERRORS_MASSEG |________________
int Read_Csv_Error_Maseg(struct sensor *info, FILE *file);
int  mesag_Errors(FILE *file,char *filename);

int prpint_Month(FILE *file, char *fileName, int numbr);

//_________________| for key -d |______________
int del_Error_p(FILE *file, char *fileName,int index);
void Del_Error(char **err, int len, int num);