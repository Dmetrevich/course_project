//  ./Test_Txt_Csv/temperature_small.csv
//  ./Test_Txt_Csv/temperature_big.csv
#include "header.h"

int main(int argc, char **argv)
{
    FILE *file;
    char fileHelp[] = {"./Test_Txt_Csv/text.txt"};
    printf("%s\n", argv[0]);
    int size = 0;
    char *filename;
    if ((argc < 2) || (strlen(argv[1]) > 2) ||
        ((argv[1][1] != 'h') && (argv[1][1] != 'f') && (argv[1][1] != 'm') && (argv[1][1] != 'e') && (argv[1][1] != 'r') && (argv[1][1] != 'd')))
    {
        reference();
    }
    for (int i = 0; i < argc; i++)
    {
        char *str = argv[i];
        char *mon = argv[4];
        if (str[0] == '-')
            switch (str[1])
            {
            case 'h':
                printf("=== 0-lain ==\n");
                print_Reading(file, fileHelp);
                break;
            case 'f':
                filename = argv[i + 1];
                size = atoi(argv[i + 2]);
                if (argc < 5 && size > 0)
                    reference();
                if ((strcmp(mon, "-m") == 0) && (size > 0))
                {

                    printf("===============================================\n");
                    printf("This name file  %s\n", filename);
                    //____________________________________________________________________________________
                    prpint_Month(file, filename, size);
                    // rpint_Month(file, filename, size); // dont work
                    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                    mesag_Errors(file, filename);
                }
                if ((strcmp(mon, "-m") != 0))
                {
                    printf("This name file  %s\n", filename);
                    print_Statistic_Year(file, filename);
                    mesag_Errors(file, filename);
                }
                break;
            case 'm':
                filename = argv[i + 1];
                size = atoi(argv[i + 2]);
                printf("====================================================\n");
                printf("This name file  %s\n", filename);
                printf("Number mons = %d\n", size);
                prpint_Month(file, filename, size);
                mesag_Errors(file, filename);
                break;
            case 'e':
                filename = argv[i + 1];
                if (argc < 3 || argc > 3)
                    reference();
                else
                {
                    printf("=========================================\n");
                    printf("This name file  %s\n", filename);
                    reint_arr_Error(file, filename);
                }
                break;
            case 'd':
                filename = argv[i + 1];
                size = atoi(argv[i + 2]);
                if (argc < 4 || argc > 4)
                    reference();
                else
                {

                    printf("This name file  %s\n", filename);
                    printf("The deletion line - %d\n", size);
                    del_Error_p(file, filename, size);
                    printf("===| The deletion is complete |===\n");
                }
                break;
            case 'r':
                filename = argv[i + 1];
                if (argc < 3 || argc > 3)
                    reference();
                else
                {
                    printf("=== 6[R]-lain ==\n");
                    printf("This name file  %s\n", filename);
                    print_Reading(file, filename);
                }
                break;
            default:
                break;
            }
    }
    return 0;
}
