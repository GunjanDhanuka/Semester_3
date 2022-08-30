#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//main function which takes input from command line a arguments
void main(int argc, char *argv[])
{
    //if the environment variable entered by the user doesn't exist, show warning and ask if the user wants to set a new environment variable
    if (getenv(argv[1]) == NULL)
    {
        printf("The given environment variable doesn't exist. Do you want to create a new one?\nEnter YES or NO\n");

        char str[5];
        scanf("%s", str);
        //if the user enters YES then ask for the new value of the environment variable
        if (strcmp(str, "YES") == 0 || strcmp(str, "yes") == 0 || strcmp(str, "Yes") == 0)
        {

            char new[100];
            printf("Enter new value for this environment variable\n");
            //read the new value for the environment variable from the user input
            scanf("%s", new);
            //using setenv function to change the value of the environment variable
            setenv(argv[1], new, 1);
            //print the new value of the environment variable and exit
            printf("New value of this environment variable is: %s\n", getenv(argv[1]));
        }else{
            printf("New environment variable hasn't beeen set\n");
        }
    }
    //else proceed
    else
    {
        //print the current value of the environment variable and ask the user if they want to chnage it
        printf("Value of this env var is : %s\nDo you want to change the value of the variable?\nEnter YES or NO\n", getenv(argv[1]));
        char str[5];
        scanf("%s", str);
        //if the user enters YES then ask for the new value of the environment variable
        if (strcmp(str, "YES") == 0 || strcmp(str, "yes") == 0 || strcmp(str, "Yes") == 0)
        {

            char new[100];
            printf("Enter new value for this environment variable\n");
            //read the new value for the environment variable from the user input
            scanf("%s", new);
            //using setenv function to change the value of the environment variable
            setenv(argv[1], new, 1);
            //print the new value of the environment variable and exit
            printf("New value of this environment variable is: %s\n", getenv(argv[1]));
        }
        //else if the user enters NO, print the current value of the environment variable and exit
        else
        {
            printf("Value of environment variable is still: %s\n", getenv(argv[1]));
        }
    }
}