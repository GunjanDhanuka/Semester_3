
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <bits/stdc++.h>
#include <fcntl.h>
using std::cout;
using std::endl;
using std::ofstream;
using std::string;
#define BUFFER_LEN 1024

//prompt function which displays the present working directory
void prompt()
{
    char cwd[256]; //ahar array for storing address of the present directory
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("getcwd() error");
    else
        printf("%s$ ", cwd);
}
//help function for displaying the commands present in the mini-shell
void help()
{
    cout << "Shell implementation by Pranjal Singh(200101084)" << endl;
    cout << "type the command and the argument and press enter to run" << endl;
    cout << "-----" << endl;
    cout << "Following functions are available in my mini shell" << endl;
    cout << "In-built commands:-" << endl;
    cout << "  1) cd" << endl;
    cout << "  2) echo" << endl;
    cout << "  3) setenv" << endl;
    cout << "  4) unsetenv" << endl;
    cout << "  5) history" << endl;
    cout << "  6) exit" << endl;
    cout << "  7) help" << endl;
    cout << "-----" << endl;
    cout << "System commands" << endl;
    cout << "  for running system commands like ls, pwd, mkdir, rmdir etc enter command with arguments and press enter" << endl;
    cout << "-----" << endl;
    cout << "Single level piped commands" << endl;
    cout << "  for running single level piped commands like ls -l | more enter command with arguments and press enter\n  WARNING!!!: take care of proper spacing between each argument" << endl;
    cout << "-----" << endl;
    cout << "Commands with redirection operation" << endl;
    cout << "  for running commands with redirection operation like ls > ouput.txt enter command with arguments and press enter\n  WARNING!!!: take care of proper spacing between each argument" << endl;
    cout << "-----" << endl;
    cout << "Thanks :)" << endl;
    cout << "Shell implementation by Pranjal Singh(200101084)" << endl;
}
//function for parsing the commands given by the user
void parse_command(char **arguments, int counter, char *input)
{
    char *token;
    //setting the delimiter as empty space and dividing the user input into tokens based on the empty spaces
    token = strtok(input, " ");
    counter = 0;

    while (token != NULL)
    { //setting the argument with the index counter equal to the current token
        arguments[counter] = token;
        //setting the token as empty
        token = strtok(NULL, " ");
        //increasing the counter
        counter++;
    }
    //setting the final argument as NULL
    arguments[counter] = NULL;
}
//function to run inbuilt commands as well as simple system commands
void run_command(char **argv, char file_path[50])
{ //set path at bin
    char path[] = "/bin/";

    //implementing cd using chdir function
    if (strcmp(argv[0], "cd") == 0)
    {
        chdir(argv[1]);
    }

    //implementing exit
    else if (strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "quit") == 0 || strcmp(argv[0], "x") == 0)
    {
        std::cout << "thankyou \nshell implementation using c++ by Pranjal\n";
        //
        remove("/tmp/history.txt");
        //bool remove( const std::filesystem::path& filename );
        exit(0);
    }

    //giving out user information
    else if (strcmp(argv[0], "USER") == 0 || strcmp(argv[0], "HOME") == 0 || strcmp(argv[0], "SHELL") == 0 || strcmp(argv[0], "TERM") == 0)
    { //using getenv function to display the required environment variable
        std::cout << getenv(argv[0]) << std::endl;
    }

    

    //Implementing echo function
    else if (strcmp(argv[0], "echo") == 0)
    {
        //if no specific environment variable is called print an empty line
        if (argv[1] == NULL)
        {
            cout << endl;
        }
        else
        { //char array pointer to store the value of the required variable separate from the $ sign
            char *fileinput3[2];
            char *fileinputstring3 = argv[1];
            for (int i = 0; i < 2; i++)
            {
                //separating the variable in argv[1] from $ symbol using strsep
                fileinput3[i] = strsep(&fileinputstring3, "$");
                //break when arguments are over
                if (fileinput3[i] == NULL)
                    break;
            }
            //if no $ sign is found print the command excluding echo
            if (fileinput3[1] == NULL)
            {
                int m = 1;
                // print all arguments except the first one
                while (argv[m] != NULL)
                {
                    cout << argv[m] << " ";
                    m++;
                }
                //change line
                cout << endl;
            }
            //else find if the given variable exists and proceed accordingly
            else
            {   //if the required env variable is not NULL print its value
                if (getenv((const char *)fileinput3[1]) != NULL)
                {
                    std::cout << getenv((const char *)fileinput3[1]) << std::endl;
                }
                //else print an empty line
                else
                {
                    cout << endl;
                }
            }
        }
    }
    //implementing setenv function
    else if (strcmp(argv[0], "setenv") == 0)
    {
        //if no variable or value is passed after setenv declare the command as invalid
        if (argv[1] == NULL || argv[2] == NULL)
        {
            cout << "invalid command " << endl;
        }
        //otherwise set the value of the environment variable as the given value
        else
        {
            setenv(argv[1], argv[3], 1);
        }
    }
    //implementing unsetenv function 
    else if (strcmp(argv[0], "unsetenv") == 0)
    {
        //clear the value of the given variable
        setenv(argv[1], "", 1);
    }

    //implementing help function
    else if (strcmp(argv[0], "HELP") == 0 || strcmp(argv[0], "Help") == 0 || strcmp(argv[0], "help") == 0)
    {   //calling hte help function
        help();
    }

    //inplementing history command
    else if (strcmp(argv[0], "HISTORY") == 0 || strcmp(argv[0], "History") == 0 || strcmp(argv[0], "history") == 0)
    {   //setting the input stream to history file
        std::ifstream input("/tmp/history.txt");
        //getting the inputs stored in the history file line by line and printing them on the screen
        for (std::string line; getline(input, line);)
        {
            cout << line << endl;
        }
    }
    //a simple function showing information about the creator
    else if(strcmp(argv[0], "info") == 0 )
    {
        cout<<endl;
        cout << "This is a shell in cpp made by Pranjal Singh "<<endl;
        cout << "I am sophomore at IIT Guwahati pursuing my B.tech in Computer Science and Engineering"<<endl;
        cout<< "I love computers and hope you have a good day"<<endl;
        cout <<":)"<<endl;
        cout <<endl;
    }
    //implementing system commands if no inbuilt command is used
    else
    {   //Assign path to file_path
        strcpy(file_path, path);
        //conctanate command and file path    
        strcat(file_path, argv[0]); 

        if (access(file_path, F_OK) == 0)
        { 
            //check the command is available in /bin
            int fd[2], i = 0;
            pipe(fd);
            pid_t pid, wpid;
            int status;
            char readbuf[1024];
            //finding process ID using fork()
            pid = fork();
            //if pid==0 run child process
            if (pid == 0)
            {

                if (execvp(file_path, argv) == -1)
                {
                    perror("Child proccess end");
                }
                exit(EXIT_FAILURE);
            }
            //if pid>0 run parent process
            else if (pid > 0)
            { 

                wpid = waitpid(pid, &status, WUNTRACED);
                while (!WIFEXITED(status) && !WIFSIGNALED(status))
                {
                    wpid = waitpid(pid, &status, WUNTRACED);
                }
            }
            else
            {
                //process id can not be null
                perror("Fork Failed"); 
            }
        }
        else
        {   
            //Command is not available in the bin
            printf("Command is not available in the bin\n"); 
        }
    }
}
//function for running the 2nd command in the piped input
void rundest(int pfd1[], char **args)
{   //declare a new process id
    int pid2;
    //find pid2 using fork()
    pid2 = fork();
    //if pid2=0 run child process
    if(pid2==0)
    {
        dup2(pfd1[0], 0);
        close(pfd1[1]);
        execvp(args[0], args);
        perror(args[0]);
    }
    //if pid2 =-1 return error
    else if(pid2==-1)
    {
        perror("fork error");
        exit(1);
    }  
}
//function to run the first command in the piped command
void runsource(int pfd2[], char **args)
{   //declare a new process id
    int pid3;
    //find pid3 using fork()
    pid3 = fork();
    //if pid2=0 run child process
    if(pid3==0)
    {
        dup2(pfd2[1], 1);
        close(pfd2[0]);
        execvp(args[0], args);
        perror(args[0]);
    }
    //if pid3 =-1 return error
    else if(pid3==-1)
    {
        perror("fork");
        exit(1);
    }
    
}
//function to take input
int take_input(char user_input[BUFFER_LEN])
{
    //break if the command length exceed the defined BUFFER_LEN
    if (!fgets(user_input, BUFFER_LEN, stdin))
    {
        return 0; 
    }

    //set the variable lenght equal to length of the user input
    size_t length = strlen(user_input);
    
    //if empty input is passed return 0
    if (length == 0 || length == 1)
    {
        return 0;
    }
    
    if (user_input[length - 1] == '\n')
    {
         // replace last char by '\0' if it is new line char
        user_input[length - 1] = '\0';
    }
    //return 1 if input is taken successfully
    return 1;
}
//function to check if the input has pipes
int check_piping(char *user_string, char *user_string_piped[2])
{
    for (int i = 0; i < 2; i++)
    {   //separate and store the input based on the | present in the input
        user_string_piped[i] = strsep(&user_string, "|");
        //break when input is over
        if (user_string_piped[i] == NULL)
            break;
    }
    // returns zero if no pipe is found
    if (user_string_piped[1] == NULL)
        return 0; 
    // returns one if pipe is found
    else
    {
        return 1;
    }
}
void run_redirection(char **args, int argc, string redirection_type)
{
    
    int status;
    int size = 0;
    //find the size of the input
    while (args[size] != NULL)
    {
        size++;
    }
    //find forkvalue using fork()
    int forkvalue=fork();
    //if forkvalue = 0 run child process
    if(forkvalue==0)
    {
        char *args_clean[size];
        int cleanidx = 0;
        int in, out;
        
        for (int j = 0; j < size; j++)
        {
            if (!strcmp(args[j], "<"))
            { 
                // looking for input character
                ++j;
                if ((in = open(args[j], O_RDONLY)) < 0)
                { 
                    // open file for reading
                    perror("Error in opening file!");
                }
                // duplicate stdin to input file
                dup2(in, STDIN_FILENO); 
                // close after use
                close(in);              
                continue;
                // end input chech
            } 

            if (!strcmp(args[j], ">"))
            { 
                // looking for output character
                ++j;
                // create new output file
                out = creat(args[j], 0644); 
                // redirect stdout to file
                dup2(out, STDOUT_FILENO); 
                // close after usere
                close(out);               
                continue;
                // end output check
            } 

            if (!strcmp(args[j], ">>"))
            { 
                // looking for append
                ++j;
                int append = open(args[j], O_CREAT | O_RDWR | O_APPEND, 0644);
                
                dup2(append, STDOUT_FILENO);
                close(append);
                continue;
            }

            args_clean[cleanidx++] = args[j];
         // end loop   
        } 

        args_clean[cleanidx] = NULL;
        // execute in parent
        execvp(args_clean[0], args_clean);  
        // error
        perror("Error in child process execution");
        exit(EXIT_SUCCESS);
        //return 1;
    }
    //if forkvalue = -1 show error
    else if(forkvalue==-1)
    {
        perror("Error in forking!");
    
    }
    //otherwise wait for the process to finish
    else{
        wait(&status);
    }
   
    
}

int main()
{   
    //welcome statement
    cout << "Welcome to shell implementation by Pranjal using c++ \npress HELP for help" << endl;
    string base = "";
    int s = 0;
    char home[256];

    //getting the home directory
    if (getcwd(home, sizeof(home)) == NULL)
        s++;
    else
        s++;

    int r = 0;
    //converting the home directory address to a string
    while (home[r] != '\0')
    {
        base = base + home[r];
        r++;
    }
    base = base + "/tmp/history.txt";
    //opening a file to store inputs given by the user
    std::ofstream ofs;
    ofs.open("/tmp/history.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    string filename("/tmp/history.txt");
    ofstream file_out;

    char *filename1 = const_cast<char *>(base.c_str());
    int command_counter = 1;
    int t = 0;

    char user_input[BUFFER_LEN]; //get command line
    char *piped_argv[120];       //if command has pipe
    char *argv[120];
    int piped_argc;        //user command
    int argc;              //argument count
    char path[] = "/bin/"; //set path at bin
    char file_path[50];    //full file path
    //a loop which runs till user exits the shell
    while (1)
    {
        //showing prompt to the user
        prompt();
        //take input function
        if (take_input(user_input) == 0)
        {
            continue;
        }

        //checking if input has pipes
        int piped = 0;
        char *user_string_piped[2];
        char *user_string = user_input;
        piped = check_piping(user_string, user_string_piped);

        if (piped == 1)
        {   
            //parsing first part of the command
            parse_command(argv, argc, user_string_piped[0]);
            //storing the user input to the inputs.txt file which contains the history

            file_out.open(filename, std::ios_base::app);
            int q = 0;

            while (argv[q] != NULL)
            {
                file_out << " " << argv[q] << " |";
                q++;
            }
            file_out.close();
            
            //parsing second part of the command
            parse_command(piped_argv, piped_argc, user_string_piped[1]);
            //storing the user input to the inputs.txt file which contains the history

            file_out.open(filename, std::ios_base::app);
            q = 0;

            while (argv[q] != NULL)
            {
                file_out << " " << piped_argv[q] << " ";
                q++;
            }
            file_out << endl;
            file_out.close();
            command_counter++;
            
            //creating a new pipe
            int pipefd[2];
            int pid1, status1;
            pipe(pipefd);
            
            //runsource function for running first part of the piped command
            runsource(pipefd, argv);
            //rundest function for running second part of the piped command
            rundest(pipefd, piped_argv);
            //close pipes after use
            close(pipefd[0]);
            close(pipefd[1]);

            while ((pid1 = wait(&status1)) != -1)
            {
                //pick up dead children
                //cerr << "process " << pid << " exits with " << WEXITSTATUS(status) << endl;
            }
        }
        else
        {   

            //finding if input has redirection
            int redirection = 0;
            string redirection_type;
            //new array to store the parts of the input
            char *fileinput[2];
            //creating a copy of the user input
            char input_copy[1024];
            int lp = 0;
            while (user_input[lp] != '\0')
            {
                input_copy[lp] = user_input[lp];
                lp++;
            }
            char *fileinputstring = input_copy;
            
            //separating input on the basis of the redirection symbol >
            for (int i = 0; i < 2; i++)
            {
                fileinput[i] = strsep(&fileinputstring, ">");
                if (fileinput[i] == NULL)
                    break;
            }

            if (fileinput[1] != NULL)
            {
                //redirection = 1 if command has output operation
                redirection = 1;
                redirection_type = "output";
            }
            
            //new array to store the parts of the input
            char *fileinput1[2];
            //creating a copy of the user input
            char input_copy1[1024];
            lp = 0;
            while (user_input[lp] != '\0')
            {
                input_copy1[lp] = user_input[lp];
                lp++;
            }
            char *fileinputstring1 = input_copy1;

            //separating input on the basis of the redirection symbol <
            for (int i = 0; i < 2; i++)
            {
                fileinput1[i] = strsep(&fileinputstring1, "<");
                if (fileinput1[i] == NULL)
                    break;
            }

            if (fileinput1[1] != NULL)
            {
                 //redirection = 2 if command has input operation
                redirection = 2;
                redirection_type = "input";
            }

            //new array to store the parts of the input
            char *fileinput2[2];
            //creating a copy of the user input
            char input_copy2[1024];
            lp = 0;
            while (user_input[lp] != '\0')
            {
                input_copy2[lp] = user_input[lp];
                lp++;
            }
            char *fileinputstring2 = input_copy2;
            
            //separating input on the basis of the redirection symbol >>
            for (int i = 0; i < 2; i++)
            {
                fileinput2[i] = strsep(&fileinputstring2, ">>");
                if (fileinput2[i] == NULL)
                    break;
            }
            if (fileinput2[1] != NULL)
            {
                //redirection = 3 if command has append operation
                redirection = 3;
                redirection_type = "append";
            }
            
            //if there is no redirection proceed for runnif=ngthe simple command
            if (redirection == 0)
            {
                //function to parse the user command
                parse_command(argv, argc, user_input);

                //adding the parsed command to history
                file_out.open(filename, std::ios_base::app);
                int q = 0;

                while (argv[q] != NULL)
                {
                    file_out << " " << argv[q] << " ";
                    q++;
                }
                file_out << endl;
                file_out.close();
                command_counter++;

                //run the command using run_command function
                run_command(argv, file_path);
            }
            //otherwise if the system contains redirection proceed accordingly
            else
            {
                //parse the user input
                parse_command(argv, argc, user_input);

                //add the command to history
                file_out.open(filename, std::ios_base::app);
                int qk = 0;

                while (argv[qk] != NULL)
                {
                    file_out << " " << argv[qk] << " ";
                    qk++;
                }
                file_out << endl;
                file_out.close();
                command_counter++;
                
                //run the command using run_redirection function
                run_redirection(argv, argc, redirection_type);
            }
        }
    }

    return 0;
}

// the end
//shell implementation in cpp by Pranjal Singh