#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

FILE *historyfile;
//function declarations for internal commands

int for_cd(char **args);
//int for_alias(char **args);
//int for_unalias(char **args);
int for_history(char **args);
int for_exit(char **args);
//int for_logout(char **args);
int for_pwd(char **args);
int for_help(char **args);
int for_echo(char **args);

//list of internal commands

char *internals[6] = {"cd", "history", "exit", "pwd", "help", "echo"};

//int (*for_internals[6])(char**)={&for_cd,&for_history,&for_exit,&for_pwd,&for_help,&for_echo};

int numofinternals = 6;

//functions for internals implementation

int for_cd(char **args) //checked..
{
    if (args[1] == NULL)
    {
        char *user = getenv("USER");
        char usera[] = "/home/";
        strcat(usera, user);
        return (chdir(usera));
    }
    else
    {
        printf("insidecd\n");
        if (chdir(args[1]) != 0)
        {
            perror("mysh");
            return -1;
        }
    }
    //want to update PWD?
    return 0;
}

int for_help(char **args)
{
    //write better explanation in help
    int i;
    printf("built in commands are:");
    for (i = 0; i < numofinternals; i++)
    {
        printf("%s\n", internals[i]);
    }
    return 1;
}

int for_pwd(char **args)
{
    char pwd[1000];
    getcwd(pwd, 1000);
    printf("\ndir: %s", pwd);
    return 1;
}

int for_echo(char **args)
{
    int i = 1;
    while (1)
    {
        if (args[i] == NULL)
        {
            break;
        }
        printf("%s ", args[i]);
        i++;
    }
    //update it to include $variable printing
    printf("\n");
    return 1;
}

int for_exit(char **args)
{
    fclose(historyfile);
    char *line[2];
    line[0] = "cd";
    line[1] = NULL;
    int ret = for_cd(line);
    remove("myshellhistory.txt");
    printf("exiting");
    exit(0);
}

/*int for_logout(char **args)
{
    //do research and improve it
    return 0;
}*/

int for_history(char **args) //checked..
{
    int num = 1;
    int c;
    fseek(historyfile, 0, SEEK_SET);
    if (strcmp(args[1], ">") == 0)
    {
        FILE *outhis = fopen(args[2], "w");
        c = fgetc(historyfile);
        if (c != EOF)
        {
            fprintf(outhis, "%d  ", num);
        }
        while (c != EOF)
        {
            fprintf(outhis, "%c", c);
            if (c == '\n')
            {
                fprintf(outhis, "%d  ", ++num);
            }
            c = fgetc(historyfile);
        }
        fclose(outhis);
        return 0;
    }
    else if (strcmp(args[1], ">>") == 0)
    {
        FILE *outhis = fopen(args[2], "a");
        c = fgetc(historyfile);
        if (c != EOF)
        {
            fprintf(outhis, "%d  ", num);
        }
        while (c != EOF)
        {
            fprintf(outhis, "%c", c);
            if (c == '\n')
            {
                fprintf(outhis, "%d  ", ++num);
            }
            c = fgetc(historyfile);
        }
        fclose(outhis);
        return 0;
    }
    else
    {
        c = fgetc(historyfile);
        if (c != EOF)
        {
            printf("%d  ", num);
        }
        while (c != EOF)
        {
            printf("%c", c);
            if (c == '\n')
            {
                printf("%d  ", ++num);
            }
            c = fgetc(historyfile);
        }
    }

    //can history be redirected to file?
    return 0;
}
/*

            space


*/
int iamdoing(int i, char **args)
{
    if (i == 1)
    {
        return (for_cd(args));
    }
    if (i == 2)
    {
        return (for_history(args));
    }
    if (i == 3)
    {
        return (for_exit(args));
    }
    if (i == 4)
    {
        return (for_pwd(args));
    }
    if (i == 5)
    {
        return (for_help(args));
    }
    if (i == 6)
    {
        return (for_echo(args));
    }
}
int executewhere(char **args, int j);

#define LINESIZE 500
//int Linesize=0;

char *reading() //checked..
{
    int size = LINESIZE;
    int num = 0;
    char *tmp = (char *)malloc(sizeof(char) * size);
    int c;
    //read a line of command
    while (1)
    {
        c = getchar();
        if (c == '\\')
        {
            c = getchar();
            if (c == '\n')
            {
            }
            else if (c == EOF)
            {
                tmp[num] = '\0';
                return tmp;
            }
            else
            {
                tmp[num] = '\\';
                tmp[num + 1] = c;
                num = num + 2;
            }
        }
        else if (c == '\n' || c == EOF || c == '\r')
        {
            tmp[num] = '\0';
            return tmp;
        }
        else
        {
            tmp[num] = c;
            num++;
        }
        //reallocate if tmpsize is less
        if (num >= size)
        {
            size += LINESIZE;
            tmp = realloc(tmp, size);
        }
    }
    printf("%s", tmp);
}

#define NUMWORDS 500
char **parseline(char *line) //checked..
{
    int numwords = NUMWORDS;
    int i = 0;
    char **parsedline = (char **)malloc(numwords * sizeof(char *));
    for (i = 0; i < numwords; i++)
    {
        parsedline[i] = (char *)malloc(20 * sizeof(char));
    }
    //int i=0;
    int num = 0;
    while (1)
    {
        parsedline[i] = strsep(&line, " ");
        i++;
        if (parsedline[i] == NULL)
        {
            //printf("hi");
            return parsedline;
        }
        //if(strlen(parsedline[i])==0){i--;}
        /*if(i>=numwords)
        {
            numwords+=NUMWORDS;
            parsedline=realloc(parsedline,numwords*sizeof(char *));
        }*/
        num++;
    }
}
//finding pipes
//can work only for single piping
char **pipes(char *line)
{
    int i;
    char **parts = (char **)malloc(2 * sizeof(char *));
    for (i = 0; i < 2; i++)
    {
        //printf("hoi");
        parts[i] = (char *)malloc(50 * sizeof(char));
        parts[i] = strsep(&line, "|");
        if (parts[i] == NULL)
        {
            break;
        }
    }
    return parts;
}

//to clear
void clearsc()
{ //checked...
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}
void start_shell() //checked..
{
    clearsc();
    printf("\n******************\t\t******************\t\t******************");
    printf("\n\n********************myshell by nandini sharma****************************");
    printf("\n******************\t\t******************\t\t******************");
    char *user = getenv("USER");
    printf("\n\nuser: @%s\n", user);
    sleep(2);
    clearsc();
}
//printing directory
void dirprint() //checked..
{
    char arr[1000];
    getcwd(arr, 1000);
    printf("\nDir: %s", arr);
}
//to execute system commands

int executing(char **cmline)
{
    // Forking a child
    pid_t pid = fork();

    if (pid == -1)
    {
        printf("\nFailed forking child..");
        return -1;
    }
    else if (pid == 0)
    {
        //child
        //printf("inside child\n");
        /*char *cmp;
        cmp=getenv("PATH");
		strcat(cmp, " ");
        strcat(cmp,cmline[0]);
		printf("%s\n\n",cmp);*/
        printf("THIS IS PRINTING%s %s\n", *(cmline + 0), *(cmline + 1));
        if (execvp(cmline[0], cmline) == -1)
        {
            printf("%s\n", cmline[0]);
            perror("mysh");
        }
        exit(EXIT_FAILURE);
    }
    else
    {
        /*do{
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));*/
        wait(NULL);
        //exit(0);
    }
    //printf("hogya\n");
    return 1;
}
// Function where the piped system commands is executed
int executingpipes(char **arg1, char **arg2)
{
    // 0 is read end, 1 is write end

    pid_t p1, p2;
    int pipenum[2];

    if (pipe(pipenum) == -1)
    {
        printf("\nPiping unsuccessfull");
        return -1;
    }
    p1 = fork();
    if (p1 == -1)
    {
        printf("\nforking unsuccessfull");
        return -2;
    }

    if (p1 == 0)
    {
        // Child 1 executing..
        // It only needs to write at the write end
        close(pipenum[0]);
        dup2(pipenum[1], STDOUT_FILENO);
        close(pipenum[1]);
        //write a good func to run internal and external commands
        if (executewhere(arg1, 1) < 0)
        {
            printf("\nCould not execute command 1..");
            return -3;
        }
    }
    else
    {
        // Parent executing
        p2 = fork();

        if (p2 < 0)
        {
            printf("\nforking unsuccessfull");
            return -3;
        }

        // Child 2 executing..
        // It only needs to read at the read end
        if (p2 == 0)
        {
            close(pipenum[1]);
            dup2(pipenum[0], STDIN_FILENO);
            close(pipenum[0]);
            //write a good func to run internal and external commands
            if (executewhere(arg2, 1) < 0)
            {
                printf("\nCould not execute command 2..");
                return -4;
            }
        }
        else
        {
            // parent executing, waiting for two children
            wait(NULL);
            wait(NULL);
            return 0;
        }
    }
}
int compare(char **line, char *symb);
//where to run
int executewhere(char **args, int j)
{
    int i;
    int ret;
    if (args[0] == NULL)
    {
        // An empty command was entered.
        return 1;
    }
    if (j == 0)
    {
        int std_in, std_out, std_err;
        std_in = dup(0);
        std_out = dup(1);
        std_err = dup(2);

        if (compare(args, "<") >= 0)
        {
            int pos = compare(args, "<");
            int inp = open(args[i + 1], O_RDONLY);
            if (inp < 0)
            {
                perror("mysh");
                return -1;
            }
            if (dup2(inp, 0) < 0)
            {
                perror("mysh");
                return -1;
            }
            close(inp);
            args[pos] = NULL;
            args[pos + 1] = NULL;
        }
        if (compare(args, ">") >= 0)
        {
            int pos = compare(args, ">");
            int outp = open(args[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0755);
            if (outp < 0)
            {
                perror("mysh");
                return -1;
            }
            if (dup2(outp, 1) < 0)
            {
                perror("mysh");
                return -1;
            }
            close(outp);
            args[pos] = NULL;
            args[pos + 1] = NULL;
        }
        if (compare(args, ">>") >= 0)
        {
            int pos = compare(args, ">>");
            int outt = open(args[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0755);
            if (outt < 0)
            {
                perror("mysh");
                return -1;
            }
            if (dup2(outt, 1) < 0)
            {
                perror("mysh");
                return -1;
            }
            close(outt);
            args[pos] = NULL;
            args[pos + 1] = NULL;
        }
        if (compare(args, "2>") >= 0)
        {
            int pos = compare(args, "2>");
            int oute = open(args[i + 1], O_WRONLY | O_CREAT, 0755);
            if (oute < 0)
            {
                perror("mysh");
                return -1;
            }
            if (dup2(oute, 2) < 0)
            {
                perror("mysh");
                return -1;
            }
            close(oute);
            args[pos] = NULL;
            args[pos + 1] = NULL;
        }
        if (compare(args, "2>>") >= 0)
        {
            int pos = compare(args, "2>>");
            int oute = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0755);
            if (oute < 0)
            {
                perror("mysh");
                return -1;
            }
            if (dup2(oute, 2) < 0)
            {
                perror("mysh");
                return -1;
            }
            close(oute);
            args[pos] = NULL;
            args[pos + 1] = NULL;
        }

        //built in commands
        //int i;
        for (i = 0; i < 6; i++)
        {
            if (strcmp(args[0], internals[i]) == 0)
            {
                ret = iamdoing(i + 1, args);
                dup2(std_in, 0);
                dup2(std_out, 1);
                dup2(std_err, 2);

                return ret;
            }
        }

        ret = executing(args);
        dup2(std_in, 0);
        dup2(std_out, 1);
        dup2(std_err, 2);
    }
    if (j == 1)
    {
        for (i = 0; i < 6; i++)
        {
            if (strcmp(args[0], internals[i]) == 0)
            {
                ret = iamdoing(i + 1, args);

                return ret;
            }
        }

        printf("HERE %s\n", args[0]);
        ret = executing(args);
    }

    printf("executing\n");
    return ret;
}

int compare(char **line, char *symb)
{
    int i = 0;
    while (line[i] != NULL)
    {
        if (strcmp(line[i], symb) == 0)
        {
            return i;
        }
        i++;
    }
    return -1;
}
int processing(char *line, char **lineparsed, char **piped)
{
    piped = pipes(line);
    if (piped[1] != NULL)
    {
        char **arg1 = parseline(piped[0]);
        char **arg2 = parseline(piped[1]);
        executingpipes(arg1, arg2);
        free(piped[0]);
        free(piped[1]);
        free(arg1);
        free(arg2);
        return 1;
    }
    else
    {
        lineparsed = parseline(line);
        executewhere(lineparsed, 0);
        //free(lineparsed);
        return 1;
    }
}
int main()
{
    historyfile = fopen("myshellhistory.txt", "w+");
    char *line;
    char **piped;
    char **lineparsed;
    int status = 1;
    start_shell();
    while (status < 12)
    {
        dirprint();
        printf("\n>>>");
        line = reading();
        //check for environment variables and execute
        fprintf(historyfile, "%s\n", line);
        processing(line, lineparsed, piped);
        free(line);
        status++;
    }
    //fclose(historyfile);
    return 0;
}
