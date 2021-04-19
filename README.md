# Simple Shell

### Description
The shell is an interactive user interface with an operating system. In this case, it´s a Command-Line Interface (CLI). It takes commands from the user and executes them. 

### Environmet
Developed and tested on Ubuntu 14.04 LTS

### Installation
Clone this repository and compile all the ".c" files as it's suggested, then run the executable

`$ git clone https://github.com/Blacksterhack/simple_shell.git`

### Compilation
For compile the program, enter the following command

`$ gcc -Wall -Werror -Wextra -pedantic *.c -o hsh`

### Syntax
The syntax for executing commands on this simple shell it's the same as other therminals as sh

`$ <command> <options> <argument 1> <argument 2> `

#### Examples

    $ ls -l
    total 84
    -rw-rw-r-- 1 vagrant vagrant   211 Apr 16 08:49 AUTHORS
    -rw-rw-r-- 1 vagrant vagrant  3746 Apr 16 08:49 changedir.c
    -rw-rw-r-- 1 vagrant vagrant  3100 Apr 16 08:49 envhandler.c

### Authors
- [Blacksterhack](https://github.com/Blacksterhack)
- [Elizabeth Cuentas](https://github.com/ElizabethCuentas)
