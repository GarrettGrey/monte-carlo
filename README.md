# monte-carlo
A program that outputs the results of multiple monte carlo calculations. Proudly O(1) (kind of*)!

# Usage
Modify/run mc.sh. No need to compile, mc.sh compiles it for you.
If you want to run the program by itself, the first arg is the depth (number of points to calculate, greater value = greater accuracy per calculation) and the second is the number of times to run (greater value = greater average value). Outputs three values, first is the minimum value, second value is maximum, third is the average.

Tested on Carbonate, one of Indiana University's supercomputer clusters. Not sure if the following statement is required in this context but I'll put it here anyway.
This research was supported in part by Lilly Endowment, Inc., through its support for the Indiana University Pervasive Technology Institute.




*results may vary, for best results increment to your desired value by a resonably small value, like from 1,000 to 500,000 in increments of 1,000.
