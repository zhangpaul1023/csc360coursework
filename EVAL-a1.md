
# CSC 360, Spring 2021
## Assignment #1 evaluation

* Name: `Zhang, Paul`
* VNum: `V00929523`
* Netlink: `zhangpaul1023`

---

The evaluation below refers in places to specific test numbers.
Details of these tests can be found in `TESTS.md` located on
`linux.csc.uvic.ca` in `/home/zastre/csc360/assign1/eval-info/`. Also
in that directory are the test `.sh360rc` files used for the tests
(i.e., files that were renamed to `.sh360rc` before running
`./sh360`).

Evaluation attempted to avoid "double-docking" as much as possible
(e.g., when testing for a command with one pipe, sub-commands without
arguments were used just in case arguments are not yet supported by
the shell implementation).


---
### Preliminaries

* `sh360.c` submitted: **Submitted**
* `sh360.c` compiles without errors: **Successfully compiled solution**
* `README.md` (or equivalent) provided: **Good info in README**
* Prompt as indicated by `.sh360rc` is shown (test 1): **Prompt appears as expected from .sh360rc file.**

---
### Command arguments
* Commands with zero arguments work (test 2): **Single command with no arguments is correctly executed, and once the
command is completed, the shell prompt returns.**
* Commands with one argument work (test 3): **Single command with one argument is correctly executed, and once the
command is completed, the shell prompt returns.**
* Commands with three arguments work (test 4): **Single command with three arguments is *not* correctly executed (i.e., the
command is not found from the path, or the arguments are not passed in, or both).**
* Commands with six arguments work (test 5): **Single command with six arguments is *not* correctly executed (i.e., the
command is not found from the path, or the arguments are not passed
in, or both.)**

---
### Path, exit
* Shell when no paths are provided in `.sh360rc` (test 6): **When single command is entered when the path is empty, the shell
correctly indicates that the command cannot be found.**
* Shell when two paths are provided in `.sh360rc` (test 7): **When two commands located in two different paths are entered, the
shell correctly executes one of the commands but not the other.**
* Shell when three paths are provided in `.sh360rc` (test 8): **When three commands located in three different paths are entered, the
shell correctly executes the commands.**
* `exit` command behaves as expected (test 9): **Exit works as expected.**


---
### Output re-direction, pipes
* Output redirection implemented (test 10): **Output redirection is correctly implemented.**
* Command with one pipe works (test 11): **Creates an infinite loop.**
* Command with two pipes works (test 11): **Creates an infinite loop.**

---
### Further comments


---
### Grade for submitted work (either letter or out of 100)
* **B-**

