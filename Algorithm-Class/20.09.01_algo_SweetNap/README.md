

# SweetNap

#### Write a program to help her longest nap with the task.

- Students lead very busy lives with full schedules of work and 
  appointments.
- Student J likes to lap during the day, but her schedule is so busy 
  that she doesn’t have many chances to do so. 
- She really wants to take one nap every day, however.
- Naturally, she wants to the longest nap possible given her schedule. 
- Write a program to help her with the task. 
- Test Using 3 Different Data Sets.



#### Sample Input

```
4
10:00 12:00 Lectures
12:00 13:00 Lunch, like always.
13:00 15:00 Boring lectures…
16:45 17:45 Reading ( to be or not to be?)
```

#### Sample Output

```
Day #1: the longest nap starts at 15:00 and will last for 1 hours and 45 minutes
```

- Input

  - All times will be greater than or equal of 10:00 and less than or equal to 18:00. Thus your response must be in this interval as well.
  - The appointment can be any sequence of characters, but will always be on the same line. 
  - You can assume that no line is be longer than 255 characters, that 10<hh<18 and that 0<mm<60
  - You cannot assume, however, that the input will be in any specific order, and must read the input until you reach the end of file

- Output

  - For each test case, you must print the following line:
  - Day #d: the longest nap starts at hh:mm and will last for [H hours and] M minutes. 
  - where d stands for the number of the test case (staring from 1) and hh:mm is the time when the nap can start. To display the length of the nap, follow these rules:

  1. If the total time X is less than 60 minutes, just print “X minutes.”

  2. If the total duration X is at least 60 minutes, print “H hours and M minutes,” 
    where H = X / 60 (integer division, of course) and M = X mod 60

    You don’t have to worry about correct pluralization; i.e. , you must print “1 minutes” or “ 1 hours” if that is the case.
  - the duration of the nap is calculated by the difference between the ending time and the beginning time.
  - If there is more than one longest nap with the same duration, print the earliest one