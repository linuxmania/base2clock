base2clock
==========

base two clock, arduino code

This code will run a clock of 8 led's which will run through an eight hour cycle, so three cycles per day.
The cycle start times I use are morning (4am), midday (noon), evening (8pm). But can start whenever deemed appropriate.
The eight led's represent:
  4hrs, 2hrs, 1hr, 1/2hr, 1/4hr, 8min, 4min, 2min
and run in 2 minute increments, except at quarter past, half past, quarter of, and the hour when it is a 1 minute increment.  

The time set inputs are for coarse and fine setting. When the coarse is pushed there will be a tenth of a second delay before incrementing. For the fine there is a one second delay.
