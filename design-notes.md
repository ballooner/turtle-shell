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
	* Store commands in an array and order them by execution order
	* Single command parsing:
		- First string literal is always the command name
		- Lexer seperated command flags so that is easy to put into the command struct
		- Any other string literal is an argument

-------------------------------------------------------------------------------------------------------------------------------------

- Output/input redirection

Control operator functionality:
'command1 | command2'  = pass output of command1 as input to command2
'command1 || command2' = run command2 if command1 exited unsuccesfully
'command1 & command2'  = run command1 in the background and command2 in the foreground
'command1 && command2' = run command2 if command1 exited succesfully
'command1; command2'   = run command1 and then command2

Redirection operator functionality:
'command1 > out.txt'   = put the output of command1 into out.txt
'command1 >> out.txt'  = if out.txt exists, append command1 output to it
'command1 < file.txt'  = use the contents of file.txt as input for command1


