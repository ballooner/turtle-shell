Good shell operations write-up: https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators

-------------------------------------------------------------------------------------------------------------------------------------

- Input Loop
- Parsing
	- Lexical Analysis/Tokenization
* enum that contains token names
* struct to hold each found token that contains: enum of token name and value of token
* loop over string of text (in our case, a command), separate the tokens:values and put them in an array
	** command [command modifiers] [command inputs]
		ex. grep -i "hello" input.txt > output.txt

Tokens: 
STRING_LITERAL = grep,
COMMAND_FLAG = -i,
STRING_LITERAL = "hello",
STRING_LITERAL = input.txt,
OPERATOR = >,
STRING_LITERAL = output.txt

(We classify commands and parameters as string literals because their meaning is based on their location, not their grammar.
	For example a command will always come before a parameter and it may take parameters, so whether the token is located before/after something matters.)

-------------------------------------------------------------------------------------------------------------------------------------

- Executing standard terminal commands like ls, cd, touch, etc...
	* Create a command struct that can hold all command-specific information
	* Store commands in an array and order them by execution order (we only deal with single commands right now)
	* Single command parsing:
		- First string literal is always the command name
		- Lexer seperated command flags so that is easy to put into the command struct
		- Any other string literal is an argument
    * To execute a single command we just need to call loop through the command array, fork the process and then call execvp
        with the command name and argv.

-------------------------------------------------------------------------------------------------------------------------------------
typedef struct Command
{
	char* name;
	char ctrl_op;
	char redir_op;
	FILE* input;
	FILE* output;
	int return_code;
	size_t argc;
	char* argv[256];
} command_t;

- Redirection Operator Implementation
    * For commands with operators we will need to change either stdouts output location (can be done with freopen()) or 
        change stdin to point to the specified file, dup2() can be used here.
    * When parsing command, if we encounter '>' we need to create a new file, as '>' replaces file contents instead of appending, and
        put the file into the output member of the command struct. fopen with mode of "w" works here.
    * Same rule applies above if we encounter ">>" but we need to append to a file instead. fopen with mode of "a" works here.
    * When encountering '<', before we execute the command, we need to change stdin to the file specified.


Redirection operator functionality:
'command1 > out.txt'   = put the output of command1 into out.txt
'command1 >> out.txt'  = if out.txt exists, append command1 output to it
'command1 < file.txt'  = use the contents of file.txt as input for command1




Control operator functionality:
'command1 | command2'  = pass output of command1 as input to command2
'command1 || command2' = run command2 if command1 exited unsuccesfully
'command1 & command2'  = run command1 in the background and command2 in the foreground
'command1 && command2' = run command2 if command1 exited succesfully
'command1; command2'   = run command1 and then command2

