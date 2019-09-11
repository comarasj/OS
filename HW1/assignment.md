Operating Systems & Systems Programming EECE4029
Homework 1

(1) Write a Unix program that does the following

      You run the program in command line using the following syntax:

                       you_program_name N

       Where N is a number

      When the program starts, it does the following

      1) If N is not specified in the command line, or the parameter is not a number, or if there are too many parameters, display the correct usage and then exit.

      2) It  forks three (3) child processes

          2a)  The main process then enters N loops that repeatedly displays
                 one line of information like "This is the main process, my PID is ...."
                 then pauses for about 2 seconds, then displays the above information again
          2b)  Each of the three child processes repeatedly displays one line of information
                 like "This is a child process, my PID is ..., my parent PID is ...",
                 then pauses for about 2 seconds, then displays the above information again, for a total of N times.

(2) Write a Unix program that does the following

      You run the program in command line using the following syntax:

                       you_program_name file_name

       Where file_name is the name of a text file under the current directory

      When the program starts, it does the following

      If filename is not specified in the command line, or if there are too many parameters, display the correct usage and then exit. Otherwise,

      It forks three (3) child processes


      The parent process then displays its own PID information only once, then waits for all its child processes die (hint: use wait() for this.. The wait() system call suspends the calling process until one of its child processes dies.)


      Let one child-process run the "ls -l" command (using the "execl" system call);
      Let another child-process run the "ps -ef" command;
      Let the third child-process display the content of the file (specified by file_name). You can use the program "more" or "cat" to display it.
      After all child processes terminate, the main process displays "main process terminates" then exits.  This should be the last piece of information displayed by your program.



