#include<iostream>
#include<vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include "bodyClass.h"
using namespace std;



void readFile(vector<bodyClass>& bodies, double& G, double& T, double& dt) {
    ifstream vMyFile("parameters.txt");
    string tempLine;  //temporary string to store each line
    string tempElement;  //temporary string to store each element
    vector<double> row;  
  
    if (vMyFile.good()) { // Check file opened ok
    
        int rowNum=0; 
        while (true) { 
            // Converts each line into a temporary row, then each number into a temporary element, to be stored in a row vector
            getline(vMyFile, tempLine); 
            stringstream lineStream(tempLine); 
            while (getline(lineStream, tempElement, ' ')) {  // White-space delimited
                row.push_back(stod(tempElement));  
            }
            
            
            if (rowNum==0) {
                G = row[0];
                T = row[1];
                dt=row[2];

                if (dt<=0 || T<=0 || G<=0) {  // Sanitising input
                    throw logic_error("Either G, T, or dt must be > 0");
                    
                }
                else if (dt>T) {
                    throw logic_error("dt needs to be smaller than T");
                    
                }
                else if (row.size()!=3) {
                    throw logic_error("Ensure G, T and dt are defined");
                }
            }

            else {
                if (row.size()!= 5) {
                    throw logic_error("Ensure all paramters are defined");
                }
                bodies.push_back(bodyClass(row[0], row[1], row[2], row[3], row[4]));
            }

            row={};
            rowNum++;

            if (vMyFile.eof()) {
                break; 
            } 
        }
        vMyFile.close();
    }
    else {
        cout << "Failed to open file" << endl;
    }
} 




//This function takes in V for each body and outputs V_dot for each body where V=[x,y,x_dot, y_dot]
//Takes in a vector of bodies, outputs a vector of the same bodies with parameters corresponding to V_dot
vector<bodyClass> f(vector<bodyClass> bodies, const double G) {  
    double dij;
    double v3dot_sum=0;  // The summations for v3_dot and v4_dot (x and y accelerations) 
    double v4dot_sum=0;
    vector <bodyClass> f;


    for (int i=0; i<bodies.size(); i++) {  
        v3dot_sum=0;
        v4dot_sum=0;

        for (int j=0; j<bodies.size(); j++) {
            if (i!=j ) {  
                dij = pow((pow((bodies[j].getX()-bodies[i].getX()),2) + pow((bodies[j].getY()-bodies[i].getY()),2)),1.5);
                v3dot_sum += bodies[j].getM()*(bodies[j].getX()-bodies[i].getX())/dij;
                v4dot_sum += bodies[j].getM()*(bodies[j].getY()-bodies[i].getY())/dij;
            }
        }

        f.push_back({bodyClass(bodies[i].getX_dot(), bodies[i].getY_dot(), G*v3dot_sum, G* v4dot_sum, bodies[i].getM())});
    }
    return f;
}




// This function adds 2 vectors together which can be done with transform, but for code readability during RK4, was made as a seperate function
// *is used on lines 63 in main.cpp for calculation of K2, K3 and K4
vector<bodyClass> addBodyVector(vector<bodyClass> yVec, vector<bodyClass> kVec,const double divisor) {
    vector<bodyClass> sumVector;
    
    for (int i=0; i<yVec.size(); i++) {
        kVec[i] = kVec[i].divideBody(divisor);
        sumVector.push_back(yVec[i].addBody(kVec[i]));
    }
    return sumVector;
}

