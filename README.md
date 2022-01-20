# monte-carlo
A program that outputs the results of multiple monte carlo calculations. Proudly O(1) (kind of*)!

Tested on Carbonate, one of Indiana University's supercomputer clusters. Not sure if the following statement is required in this context but I'll put it here anyway:
This research was supported in part by Lilly Endowment, Inc., through its support for the Indiana University Pervasive Technology Institute.

The .ipynb file contains the code I wrote for my Scientific Computing class and adapted into this project.

*results may vary, for best results increment to your desired value by a resonably small value, like from 1,000 to 500,000 in increments of 1,000. On top of that, further testing shows it might actually be either O(nlog(n)) where it becomes like O(1) after 1,000, or O(n^2) but at a very steep increase. Either way, in my testing I saw a slight increase in time, from 18-19 seconds per calculation when starting at 1,000 to 19-20 seconds per calculation when reaching 1,000,000.


# Usage
Modify/run mc.sh. No need to compile, mc.sh compiles it for you.
If you want to run the program by itself, the first arg is the depth (number of points to calculate, greater value = greater accuracy per calculation) and the second is the number of times to run (greater value = greater average value). Outputs three values, first is the minimum value, second value is maximum, third is the average.
