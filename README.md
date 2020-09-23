
# WI Shell
By Ariel Flaster and Jon Takagi
## Program Specifications

### Basic Shell: `wish`

`wish` operates in either interactive or batch mode. In interactive mode, it takes input from `stdin`, printing the line ` wish>` when it is ready for the next command. In batch mode, it reads commands from the file passed to it, ex `wish batch.sh` and executes them silently.

## Structure

### Basic Shell
In interactive mode, the shell continues to run until the command `exit` is input.

### Paths

The initial path is `/bin`. Using the command `path`, one can change the path: `path /usr/bin` would set the current path to `/usr/bin`.

### Built-in Commands

The builtin commands supported by `wish` are:

* `exit`: Takes no arguments. Exits the shell.

* `cd`: Takes 1 argument. Changes the current working directory to the one specified by the argument.

* `path`: Takes any number of arguments. Sets the path to the concatenation of the arguments. See above.

### Redirection

Output redirection is supported using `>`

### Parallel Commands

Programs can be run in parallel using the `&` operator. All processes will be started simultaneously, and execution of the script / interactive input will resume after all commands finish.
