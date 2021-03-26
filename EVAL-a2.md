
# CSC 360, Spring 2021
## Assignment #2 evaluation

* Name: `Zhang, Paul`
* VNum: `V00929523`
* Netlink: `zhangpaul1023`

---

The evaluation below refers in places to specific test numbers.
Details of these tests can be found in `TESTS.md` located on
`linux.csc.uvic.ca` in `/home/zastre/csc360/assign2/eval-info/`. Also
in that directory are some very rough visualizations of the behavior
sought in the tests (although we needed to interpret output rather
than comparing your submission with a very specific output script).


---
### Preliminaries

* `rw.c`, `rw.h`, `meetup.c`, `meetup.h` submitted: **File correctly submitted**
* `myserver` build without errors: **Able to make submission**
* `README.md` (or equivalent) provided: **README provided but not as a file using Markdown format.**

---
### Readers/writers
* Write with no competing read: **Expected value of "314" is read**
* Write, three overlapping reads: **Expected value of "314" is read, and reading tasks are free from convoying**
* Reader forces writer to wait: **Active reader correctly causes a writer to wait**
* Three writers are correctly convoyed, last read correct: **Three writing tasks in sequence are properly convoyed, with subsequent read successful (i.e., last written value)**

---
### Meetup
* Write with no competing read: **Both tasks meet up with "A" correctly shared.**
* Write, three overlapping reads: **First six tasks meet up in a suitable way, with "A" and "E" the codewords.**
* Reader forces writer to wait: **First six tasks meet up in a suitable way, with "A" and "E" the codewords.**
* Three writers are correctly convoyed, last read correct: **First six tasks meet up in a suitable way, with "Z" and "Y" the codewords.**

---
### Validate required strategy
* Only semaphores used for readers/writers: **Semaphores are used (and only semaphores) for task 1**
* Only CVs/mutexes used for meetup: **Condition variables and mutexes (and only these) are used for task 2**

---
### Further comments
Well done! Keep up the good work!

Would recommend making use of informative code comments to make the code easier to understand/maintain.

Please ensure that you provide a README file and  highlight a bit more of the implementation details / strategies used.

---
### Grade for submitted work (either letter or out of 100)
* **B+**

