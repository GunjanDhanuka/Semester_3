#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    char* var = argv[1];
    //setenv("GUNJAN", "gd", 1);
    if(getenv(var) == NULL){
        printf("Warning: %s environment variable does not exist already!\n", var);
        printf("Enter 0 if you wish to exit.\n");
        printf("Enter 1 if you wish to add this variable\n");
        printf("Enter choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("Exiting...\n");
            return 0;
            break;
        
        case 1:
            printf("Enter value for variable: ");
            char value[100];
            scanf("%s", value);
            setenv(var, value, 1);
            printf("%s environment variable added successfully!\n", var);
            printf("%s is now set to %s.\n", var, getenv(var));;
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
        return 0;
    }
    else{
        printf("%s is set to %s.\n", var, getenv(var));
        printf("Enter 0 if you wish to retain this value.\n");
        printf("Enter 1 if you wish to change this value\n");
        printf("Enter choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("No changes made to existing variable!\n");
            printf("%s is set to %s.\n", var, getenv(var));
            return 0;
            break;
        
        case 1:
            printf("Enter new value for %s: ", var);
            char new_val[100];
            scanf("%s", new_val);
            setenv(var, new_val, 1);
            printf("%s environment variable updated successfully!\n", var);
            printf("%s is now set to %s.\n", var, getenv(var));
            break;
        default:
            printf("Invalid choice!\n");
            return 0;
            break;
        }
    }
}
