/*
    Calculates pi using the Monte Carlo Method.
    Rewritten version of mc.cpp that does multiple monte carlo calculations without the use of a shell script, at the expense of not being able to check if it used a point multiple times.
    Because of this, I technically can't call this version O(1).
    Garrett Grey

    3/22/22 - 4/15/22
    
    Current state: Considerably slower than mc.sh
    At min = 1000, inc = 1000, max = 100000, calc = 25:
    	mc.sh: 23.179 sec
    	mc_RW.cpp:
        	initial: Unknown, est 8h
        	Change first for to while loop: No change, conclusion: for/while loops affect calculation speed equally
          	Change first for to if and add goto: No change, conclusion: goto is the same as a loop
            Move code in checkpt from a dedicated function to the nested loops: No change, conclusion: putting a function with a loop in it within a loop still counts as a nested loop
            Remove duplicate point checking: .432 sec, conclusion: what

    TODO: Revise the disgusting triple nested for loop.
*/
#include <iostream>
#include <cmath>
#include <time.h>
#include <array>
#include <fstream>
#include <vector>

using namespace std;

vector<array<double,2>> points;

double dist(double x1, double y1, double x2, double y2){ // calculates the distance between two points
    return sqrt((pow((x1-x2),2)) + pow((y1-y2),2));
}

/*bool checkpt(array<double,2> pnt){ //checks if a point has already been used
  	for(int i=0; i < points.size(); i++){
      	if(points[i][0] == pnt[0] && points[i][1] == pnt[1])return true;
    }
    return false;
}*/


int main(int args, char** argv){
    if(args != 5){
        cout << "Usage: ./a.out [Min value] [Incrementor] [Max value] [Number of calculations per value]\n";
        return 0;
    }
    srand(time(NULL));
  	ofstream out;
  	out.open("out.csv");
    
  	
    int dpnt = 0;
    double numc,minnumc; //the minumum value for the starting number of points in the circle. Should be an int but has to be a double because calculating a double from ints results in an int.
    double min = 100;
    double max = 0;
    double avg = 0;
    array<double,2> pt; //current point being processed. Index 0 is X and 1 is Y.
    double closest = 0;
  	int vals = 0;
  

    for(int i = atoi(argv[1]); i < atoi(argv[3]); i += atoi(argv[2])){
      	cout << i << endl << "\x1b[1A";
      	int previ = i;
    	for(int j = 0; j < atoi(argv[4]); j++){
        	numc = minnumc;
        	for(int k = i; k < previ + atoi(argv[2]); k++){
                pt[0] = (double)rand() / RAND_MAX;
                pt[1] = (double)rand() / RAND_MAX;
                /*if(checkpt(pt)){
                    k--;
                    dpnt++;
                    if(dpnt >= 10){
                        throw invalid_argument("Too many duplicate points, stopping calculations."); //assume that we've done so many calculations that we've ran out of unique doubles to use. This is an extreme case, but this is just to save face.
                    }
                }else{*/
                    points.push_back({pt[0],pt[1]});
                    if (dist(.5,.5,pt[0],pt[1]) <= .5)numc++;
                //}
        	}
            double val = numc/(i)*4;
          	//cout << numc << "/(" << i << ")*4 = " << val << endl;
            if(min > val)min = val;
          	if(max < val)max = val;
          	avg += val;
          	vals++;
          	if(abs(val-3.14159265359) <= abs(closest-3.14159265359)){
              	closest = val;
            }
          	i = previ;
        }
      	out << min << "," << max << "," << avg/vals << endl;
      	minnumc = closest/4*i;
      	min = 100;
    	max = 0;
    }
    
    
    out.close();
    return 0;
}