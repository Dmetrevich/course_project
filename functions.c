#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//---------------| For Key -r -------------
char **read_File_in_Err1(char **err, FILE *f, int *p) // Read txt & csv file
{
    err = (char **)malloc(sizeof(char *) * N);
    int c = 1;
    char buff[10000];
    while (fgets(buff, sizeof(buff), f))
    {
        err[c] = (char *)malloc(sizeof(char) * 100);
        strcpy(err[c], buff);
        c++;
    }
    *(p) = c;
    return err;
    free(err);
}
//---------------| for -e|------
int *Read_Csv_Error_Buff(struct sensor *info, FILE *file, int *p) // arrey number lain error
{
    int read = 0, rec = 0, r = 1, i = 0, shot = 0;
    int *arr = malloc(100 * sizeof(int));
    do
    {
        read = fscanf(file, "\n%d;%d;%d;%d;%d;%d\n",
                      &info[rec].year, &info[rec].month, &info[rec].day, &info[rec].hour, &info[rec].min, &info[rec].temper);

        if (read == 6)
            rec++;
        if (read != 6 && !feof(file))
        {
            char buf[50];
            fgets(buf, sizeof(buf), file);
            read = 6;
            arr[i] = r;
            i++;
            shot++;
        }
        if (ferror(file))
        {
            perror("Error opening file");
            exit(1);
        }
        r++;
    } while (!feof(file));
    (*p) = shot;
    return arr;
}

//-------------| Key -f |-------------------
//_______________| SORT_DATE |__________________________
void cgangeIJ(struct sensor *info, int i, int j)
{
    struct sensor temp;
    temp = info[i];
    info[i] = info[j];
    info[j] = temp;
}

int CompareDate(struct sensor *a, struct sensor *b)
{
    if ((a->year - b->year) != 0)
        return a->year - b->year;
    else if ((a->month - b->month) != 0)
        return a->month - b->month;
    else if ((a->day - b->day) != 0)
        return a->day - b->day;
    else if ((a->hour - b->hour) != 0)
        return a->hour - b->hour;
    else if ((a->min - b->min) != 0)
        return a->min - b->min;
    return 0;
}

void SortByDate_Compe(struct sensor *info, int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            if (CompareDate(info + i, info + j) > 0)
                cgangeIJ(info, i, j);
}

//_______________| READ_PRINT |_______________________
int Read_Csv_Error_Outstruct(struct sensor *info, FILE *file) // Read whisaot error
{
    int read = 0;
    int rec = 0;
    int r = 1;
    do
    {
        r++;

        read = fscanf(file, "\n%d;%d;%d;%d;%d;%d\n",
                      &info[rec].year, &info[rec].month, &info[rec].day, &info[rec].hour, &info[rec].min, &info[rec].temper);

        if (read == 6)
            rec++;
        if (read != 6 && !feof(file))
        {
            char buf[50];
            fgets(buf, sizeof(buf), file);
            read = 6;
        }
        if (ferror(file))
        {
            perror("Error opening file");
            exit(1);
        }

    } while (!feof(file));

    return rec;
}

void print(struct sensor *info, int n) // print data file
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d,%d,%d,%d,(%d),%d\n", i, info[i].year, info[i].month, info[i].day, info[i].hour, info[i].min, info[i].temper);
    }
    printf("===================\n");
}

//______________STATIST_YEAR________________
int *staticM_Year_min2(struct sensor *in, int numb, int n, int *mont)
{

    int *arr = malloc(n * sizeof(int));
    int temp, flag = 0, month = -2;
    int t_temp = in[0].temper;

    for (size_t i = 1, k = -1, j = 1; i < (numb + 2); ++i, ++j)
    {
        if (j == numb) // the lact step for write data
        {
            flag = 1;
        }
        if (t_temp > in[i].temper)
        {
            t_temp = in[i].temper;
        }
        if (in[i].month != in[i + 1].month || flag == 1)
        {
            month++;
            k++; // counter arr
            arr[k] = t_temp;
            t_temp = in[i + 1].temper; // new mans temperature
        }
    }
    *(mont) = month;
    return arr;
    free(arr);
}
int *staticM_Year_max2(struct sensor *in, int numb, int n)
{

    int *arr = malloc(n * sizeof(int));
    int temp, flag = 0;
    int t_temp = in[0].temper;

    for (size_t i = 1, k = -1, j = 1; i < (numb + 1); ++i, ++j)
    {
        if (j == numb) // the lact step for write data
        {
            flag = 1;
        }
        if (t_temp < in[i].temper)
        {
            t_temp = in[i].temper;
        }

        if (in[i].month != in[i + 1].month || flag == 1)
        {
            k++; // counter arr
            arr[k] = t_temp;
            t_temp = in[i + 1].temper; // new mans temperature
        }
    }
    return arr;
    free(arr);
}
float *staticM_Year_midl(struct sensor *in, int numb, int n)
{

    float *arr = malloc(n * sizeof(int));
    unsigned int temp, flag = 0, count = 0;
    double sum = 0;
    int t_temp = in[0].temper;
    temp = in[0].month;
    for (size_t i = 1, k = -1, j = 1; i < (numb + 2); ++i, ++j)
    {
        if (j == numb) // the lact step for write data
        {
            flag = 1;
        }
        if (temp == in[i].month)
        {
            sum += in[i].temper;
            count++;
        }

        if (in[i].month != in[i + 1].month || flag == 1)
        {
            k++; // counter arr
            arr[k] = sum / (double)count;
            count = 0; // new mans temperature
            temp = in[i + 1].month;
            sum = 0;
        }
    }
    return arr;
    free(arr);
}

//______________ASC___________________
int Asc()
{
    printf("\n____________________________________________\n");
    char y = 'y', x;
    printf("If sorting is needed enter [Y] if the file has already been sorted press eny key end press enter\n");
    scanf("\n %c", &x);
    if (y == x)
        return 1;
    else
        return 0;
}
//_____________GENERAL STATISTIC_____________
void max_Tem(struct sensor *sens, int number)
{
    int temp = sens[0].temper;
    for (size_t i = 0; i < number; i++)
    {
        if (temp < sens[i].temper)
            temp = sens[i].temper;
    }
    printf("\tMaximum temperature for year: %d \n", temp);
}
void min_Tem(struct sensor *sens, int number)
{
    int temp = sens[0].temper;
    for (size_t i = 0; i < number; i++)
    {
        if (temp > sens[i].temper)
            temp = sens[i].temper;
    }
    printf("\tMinimum temperature for year: %d\n", temp);
}
int midl_Tem(struct sensor *sens, int number)
{
    double sum = 0;
    int count = 0;
    for (size_t i = 0; i < number; i++)
    {
        sum += sens[i].temper;
        count++;
    }
    return printf("\tAvarge temperature for year:  %.2f \n", sum / (double)count);
}
//______________|MONTH KEY -m |__________________

void min_Tem_mons(struct sensor *sens, int number, int year, int month)
{
    int temp1 = 0;
    _Bool flag = 0;

    for (size_t i = 0; i < number; i++)
    {
        if (sens[i].year == year && sens[i].month == month && flag == 0)
        {
            temp1 = sens[i].temper;
            flag = 1;
        }
        if (sens[i].year == year && sens[i].month == month)
        {
            if (temp1 > sens[i].temper)
                temp1 = sens[i].temper;
        }
    }
    printf("\tMinimum temperature for month: %4d \n", temp1);
}
void max_Tem_mons(struct sensor *sens, int number, int year, int month)
{
    int temp1 = 0;
    _Bool flag = 0;

    for (size_t i = 0; i < number; i++)
    {
        if (sens[i].year == year && sens[i].month == month && flag == 0)
        {
            temp1 = sens[i].temper;
            flag = 1;
        }
        if (sens[i].year == year && sens[i].month == month)
        {
            if (temp1 < sens[i].temper)
                temp1 = sens[i].temper;
        }
    }
    printf("\tMaximum temperature for month: %4d \n", temp1);
}
void midl_Tem_mons(struct sensor *sens, int number, int year, int month)
{
    double tempS = 0;
    int count = 0;
    _Bool flag = 0;

    for (size_t i = 0; i < number; i++)
    {
        if (sens[i].year == year && sens[i].month == month && flag == 0)
        {

            flag = 1;
        }
        if (sens[i].year == year && sens[i].month == month)
        {
            tempS += sens[i].temper;
            count++;
        }
    }
    printf("\tAvarge temperature for month:   %4.2f \n", tempS / (double)count);
}
// +++++++++++++++++++++++++++++++++++
int *staticM_month_min2(struct sensor *in, int numb, int index, int *n)
{
    int *arr = malloc(monN * sizeof(int));
    if (arr == NULL)
    {
        puts("Not memore");
    }
    int temp_d = 0, t_temp = 0, count = 0, flag = 0, flag1 = 0;

    for (size_t i = 0, k = -1, j = 1; i < (numb); ++i, ++j)
    {

        if (index == in[i].month && flag1 == 0)
        {
            flag1 = 1;
            t_temp = in[i].temper;
            temp_d = in[i].day;

            flag = 1;
        }

        if (temp_d != in[i].day && index == in[i].month)
        {
            k++; // counter arr
            arr[k] = t_temp;
            t_temp = in[i].temper; // new mans temperature
            temp_d = in[i].day;
            count++;
        }
        if (t_temp > in[i].temper && index == in[i].month)
        {
            t_temp = in[i].temper;
        }
        if (index != in[i + 1].month && flag == 1)
        {
            k++; // counter arr
            arr[k] = t_temp;
            t_temp = in[i].temper; // new mans temperature
            temp_d = in[i].day;
            count++;
            flag = 0;
        }
    }
    printf("ARR_MIN\n");
    *(n) = count;
    return arr;
}

int *staticM_month_max2(struct sensor *in, int numb, int index, int *n, int *f)
{

    int *arr = malloc(monN * sizeof(int));
    if (arr == NULL)
    {
        puts("Not memore");
    }
    int temp_d = 0, t_temp = 0, count = 0, flag = 0, flag1 = 0;

    for (size_t i = 0, k = -1, j = 1; i < (numb); ++i, ++j)
    {

        if (index == in[i].month && flag1 == 0)
        {
            flag1 = 1;
            t_temp = in[i].temper;
            temp_d = in[i].day;

            flag = 1;
        }

        if (temp_d != in[i].day && index == in[i].month)
        {
            k++; // counter arr
            arr[k] = t_temp;
            t_temp = in[i].temper; // new mans temperature
            temp_d = in[i].day;
            count++;
        }
        if (t_temp < in[i].temper && index == in[i].month)
        {
            t_temp = in[i].temper;
        }
        if (index != in[i + 1].month && flag == 1)
        {
            k++; // counter arr
            arr[k] = t_temp;
            t_temp = in[i].temper; // new mans temperature
            temp_d = in[i].day;
            count++;
            flag = 0;
        }
    }
    printf("ARR_MAX\n");
    *(f) = flag1;
    *(n) = count;
    return arr;
}
float *staticM_month_midl(struct sensor *in, int numb, int index,int *n)
{
    puts("HELLU");
    float *arr = malloc(monN * sizeof(int));
    if (arr == NULL)
    {
        puts("Not memore");
    }
    unsigned int temp_d, flag = 0, flag1 = 0, count = 0, count1 = 0;
    double sum = 0;
    int t_temp;

    for (size_t i = 0, k = -1, j = 1; i < (numb + 2); ++i, ++j)
    {
        if (index == in[i].month && flag1 == 0)
        {
            flag1 = 1;
            t_temp = in[i].temper;
            temp_d = in[i].day;
            flag = 1;
        }
        if (temp_d != in[i].day && index == in[i].month)
        {
            k++; // counter arr
            arr[k] = sum / (double)count;

            t_temp = in[i].temper;
            temp_d = in[i].day;
            count = 0;
            count1++;
            sum = 0;
        }
        if (temp_d == in[i].day && index == in[i].month)
        {
            sum += in[i].temper;
            count++;
        }
        if (index != in[i + 1].month && flag == 1)
        {
            k++; // counter arr
            arr[k] = sum / (double)count;

            t_temp = in[i].temper;
            temp_d = in[i].day;
            count = 0;
            count1++;
            sum = 0;
            flag = 0;
        }
    }
    printf("ARR_MIDL\n");
    *(n) = count1;
    return arr;
}
int *staticM_month_date3(struct sensor *in, int numb, int index, int *n)
{
    int *arr = malloc(monN * sizeof(int));
    if (arr == NULL)
    {
        puts("Not memore");
    }

    int temp_d = 0, t_temp = 0, count = 0, flag = 0, flag1 = 0;
    int t;
    for (size_t i = 0, k = -1, j = 1; i < (numb); ++i, ++j)
    {

        if (index == in[i].month && flag1 == 0)
        {
            flag1 = 1;
            t_temp = in[i].temper;
            temp_d = in[i].day;

            flag = 1;
        }

        if (temp_d != in[i].day && index == in[i].month)
        {
            k++; // counter arr
            arr[k] = temp_d;
            t_temp = in[i].temper; // new mans temperature
            temp_d = in[i].day;
            count++;
        }
        if (t_temp > in[i].temper && index == in[i].month)
        {
            t_temp = in[i].temper;
        }
        if (index != in[i + 1].month && flag == 1)
        {
            k++; // counter arr
            arr[k] = temp_d;
            t_temp = in[i].temper; // new mans temperature
            temp_d = in[i].day;
            count++;
            flag = 0;
        }
    }
    printf("ARR_DATE\n");
    *(n) = count;
    return arr;
}
//_______________| ERRORS_MASSEG |________________
int Read_Csv_Error_Maseg(struct sensor *info, FILE *file)
{
    int read = 0, rec = 0, r = 1;
    do
    {
        r++;
        read = fscanf(file, "\n%d;%d;%d;%d;%d;%d\n",
                      &info[rec].year, &info[rec].month, &info[rec].day, &info[rec].hour, &info[rec].min, &info[rec].temper);
        if (read == 6)
            rec++;
        if (read != 6 && !feof(file))
        {
            return 1;
        }
        if (ferror(file))
        {
            perror("Error opening file");
            exit(1);
        }
    } while (!feof(file));

    return rec;
}

//_________________| for key -d |______________
void Del_Error(char **err, int len, int num)
{
    for (size_t i = num; i < len - 1; i++)
    {
        err[i] = err[i + 1];
    }
   
}
//####################################################################

int rpint_Month(FILE *file, char *fileName, int numbr)
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
    int c = 0, ind = 0, f = 0;
    struct st mnarr;
    mnarr.arrmax = (int *)malloc(monN * sizeof(int));
    if (mnarr.arrmax == 0)
    {
        puts("Not memore");
        return 1;
    }
    mnarr.arrmin = (int *)malloc(monN * sizeof(int));
    if (mnarr.arrmax == 0)
    {
        puts("Not memore");
        return 1;
    }
    mnarr.arrmidl = (float *)malloc(monN * sizeof(int));
    if (mnarr.arrmax == 0)
    {
        puts("Not memore");
        return 1;
    }
    mnarr.arrdate = (int *)malloc(monN * sizeof(int));
    if (mnarr.arrmax == 0)
    {
        puts("Not memore");
        return 1;
    }
    if (Asc() == 1)
    {
        printf("Start_Sort\n");
        SortByDate_Compe(in, numb);
        printf("Finish_Sort\n");
         printf("\n__________________________________________________________________________________________________\n");
    }
    // 
    mnarr.arrmin = staticM_month_min2(in, numb, numbr, &c);
    mnarr.arrmax = staticM_month_max2(in, numb, numbr, &c, &f);
    mnarr.arrmidl = staticM_month_midl(in, numb, numbr, &c);
    mnarr.arrdate = staticM_month_date3(in, numb, numbr, &c);
    if (f == 1)
    {
        printf("\n\t\t=======| STATISTIC for MONTH |============\n");

        printf("\n #      YEAR             DAY             Max_Tem         Min_Tem        Midl\n");
        printf("%-8s ", Month[numbr - 1]);
        printf("____________________________________________________________________________\n");
        for (size_t i = 0; i < c; i++)
        {

            printf(" %d\t%4d \t\t%3d  \t\t%3d  \t\t%3d  \t\t%.2f \n", i + 1, in[i].year, mnarr.arrdate[i],
             mnarr.arrmax[i], mnarr.arrmin[i], mnarr.arrmidl[i]);
            
        }
        printf("\n===================| General statistics for the month |=========================\n");
        min_Tem_mons(in, numb, 2021, numbr);
        max_Tem_mons(in, numb, 2021, numbr);
        midl_Tem_mons(in, numb, 2021, numbr);
    }
    else
    {
        printf("\nNo information available for print for the month \n\n");

       
    }

    fclose(file);
    free(in);
}
//##################################################################