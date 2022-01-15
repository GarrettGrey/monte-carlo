/*
    Calculates pi using the Monte Carlo Method.
    Adapted and modified from python code.
    Made to be ran multiple times from a bash script.
    Garrett Grey

    12/21/21 - 1/14/22
*/
#include <iostream>
#include <cmath>
#include <time.h>
#include <array>
#include <fstream>
#include <vector>

using namespace std;

ofstream out,preo,info;
ifstream prei,in,infi;
vector<array<double,2>> points;
double numc,minnumc;
int pre,dpnt = 0; //counts the times a duplicate point was come across.
	
bool checkpt(array<double,2> pnt){ //checks if a point has already been used
  	for(int i=0; i < points.size(); i++){
      	if(points[i][0] == pnt[0] && points[i][1] == pnt[1])return true;
    }
    return false;
}

double dist(double x1, double y1, double x2, double y2){ // calculates the distance between two points
    return sqrt((pow((x1-x2),2)) + pow((y1-y2),2));
}

double monteCarlo(int nump, int pr){ //nump is the number of points that will be created
        array<double,2> pt; //current point being processed. Index 0 is X and 1 is Y.
		numc = minnumc; // Number of points in the circle.
  		//cout << "Calculating "<< nump << endl;
        for(int i = 0; i < nump; i++){
            pt[0] = (double)rand() / RAND_MAX;
            pt[1] = (double)rand() / RAND_MAX;

            if(checkpt(pt)){
                i--;
                dpnt++;
            }else{
                if (dist(.5,.5,pt[0],pt[1]) <= .5)numc++; //The distance between a circle's center and a point within the circle cannot be greater than the cirlce's radius
				out << pt[0] << " " << pt[1] << endl;
            }
            if(dpnt >= 10){
                cout << "Too many duplicate points, stopping calculations" << endl; //assume that we've done so many calculations that we've ran out of unique doubles to use. This is an extreme case, but this is just to save face.
                return 123;
            }
        }
  		//cout << numc << " / (" << nump << " + " << pre << endl;
        double ret = numc/(nump+pre);
        return ret*4;
}

int main(int args, char** argv){

    if(args != 3){
        cout << "Usage: ./a.out [Depth of each calculation] [Number of calculations]" << endl;
        return 0;
    }
    srand(time(NULL));
	out.open("ptsout.txt");
	in.open("pts.txt");
  	preo.open("valsout.txt");
    prei.open("vals.txt");
  	info.open("infout.txt");
  	infi.open("inf.txt");
  	

    double min = 100;
    double max = 0;
    int dep,vals = 0;
    double avg = 0;
  	
  	if (infi.is_open()){
      	infi >> minnumc;
      	infi >> dpnt;
      	infi >> pre;
    }
  	
  	if(prei.is_open()){
      //cout << "prei is open\n";
      vector<double> v;
      while(!prei.eof()){
        	double t;
        	prei >> t;
        	v.push_back(t);
        	if(abs(t-3.14159) < abs((minnumc/pre * 4)-3.14159))minnumc = t/4 * pre; //use the closest value to pi found thus far to influence the next round of calculations
      }
      //cout << minnumc << endl;
      for(int i = 0; i < v.size()-1; i++){
        	vals++;
            avg += v[i];
      }
      if(in.is_open()){
		int t = 0;
      	string dum;
      	while(getline(in,dum))t++;
        dep = atoi(argv[1]) - pre;
      }
    }else dep = atoi(argv[1]);
  
  	
      if(in.is_open()){
        double x,y;
        while(!in.eof()){
            in >> x;
            in >> y;
            points.push_back({x,y});
        }
      }
      	
  
  	if(dep < 0){
      	cout << "Requested depth is smaller than previous depth, please delete pts.txt before continuing.\n";
      	return 0;
    }
  
  	prei.close();
  	in.close();
  	infi.close();

    for(int i = 0; i < atoi(argv[2]); i++){
        //cout << i+1 << endl << "\x1b[1A"; //"\x1b[1A" Goes up one line, allowing the counter to increment rather than print the last number after calculations are complete. Only works in *nux and in the terminal.
        double val = monteCarlo(dep,pre);
      	if(dpnt >= 10)return 0;
        preo << val << " ";
        if(val < min)min = val;
        else if(val > max)max = val;
        vals++;
        avg += val;
    }
    avg /= vals;

    //cout << "Min: " << min << "\nMax: " << max << "\nAvg: " << avg << endl;
    cout << min << "," << max << "," << avg << endl;
  	info << minnumc << " " << dpnt << " " << atoi(argv[1]);
  	for(int i=0; i < points.size(); i++){
      	out << points[i][0] << " " << points[i][1] << endl;
    }
  	preo.close();
	out.close();
  	info.close();
    return 0;
}
