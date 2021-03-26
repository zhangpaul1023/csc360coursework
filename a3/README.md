For the task 1 of this assignment:
The marker should use "make" first in order to generate the usable file for C program. Secondly, if marker want to test the sample output which shows in the assignment discreption. They should type ./rrsim --quantum 3 --dispatch 2, type in the:
1 5 3.5
2 7 4.9
3 14 1.1
which is the tasks in the sample test.
and press ctrl-d
the output will be show as below:
[00000] IDLE
[00001] IDLE
[00002] IDLE
[00003] IDLE
[00004] IDLE
[00005] DISPATCHING
[00006] DISPATCHING
[00007] id=00001 req=3.50 used=0.00
[00008] id=00001 req=3.50 used=1.00
[00009] id=00001 req=3.50 used=2.00
[00010] DISPATCHING
[00011] DISPATCHING
[00012] id=00002 req=4.90 used=0.00
[00013] id=00002 req=4.90 used=1.00
[00014] id=00002 req=4.90 used=2.00
[00015] DISPATCHING
[00016] DISPATCHING
[00017] id=00001 req=3.50 used=3.00
[00018] id=00001 EXIT w=9.50 ta=13.00
[00018] DISPATCHING
[00019] DISPATCHING
[00020] id=00003 req=1.10 used=0.00
[00021] id=00003 req=1.10 used=1.00
[00022] id=00003 EXIT w=6.90 ta=8.00
[00022] DISPATCHING
[00023] DISPATCHING
[00024] id=00002 req=4.90 used=3.00
[00025] id=00002 req=4.90 used=4.00
[00026] id=00002 EXIT w=14.10 ta=19.00

if marker want to test the output by using simgen
they should type:
./simgen (total task) (seed number) | ./rrsim --quantum (quantum length) --dispatch (dispatch length)

For task 2 of this assignment:
I remove the original output of rrsim. Instead, it will print out the dispatch_size, quantum_size, average_wait, and average_ta.
In order to do this, i commend all the original output, and i wrote:
printf("%d, %d, %.2f, %.2f\n", dispatch_size, quantum_size, (float)wait_total/event_count, (float)ta_total/event_count);
at the end of main.
After the change of rrsim, i wrote a script to generate the output of different quantum length and dispatch length, and those output will be put into a txt file.
Finally, I input the txt into a excel file, and generate the PNG file as show in the submision.