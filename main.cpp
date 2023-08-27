  #include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <exception>
#include <algorithm>
#include <iomanip>
#include "functions.h"
using namespace std;


int main(int argc, char **argv)
{
    //Initialising variables
    vector <bodyClass> bodies;
    vector<double> row;  // each row from parameters.txt
    double G;
    double T;      //Values from first line of parameters.txt
    double dt;




    //READING FILE
    try {
        readFile(bodies, G, T, dt);
    }
    catch(const logic_error& e) {
        std::cout << "An error occured: " << e.what() << std::endl;
        return 1;
    }
    



    //More initialising
    int n = ceil(T/dt);  // Total number of timesteps
    vector <double> timestep={0};  //Calculation of time steps       
    for (int i=0; i<n; i++) {      
        timestep.push_back(timestep[i]+dt);
    }
    //Each row in y  = timestep.
    //Each column in y  =  body object which has paramters: x, x_dot, y, y_dot, m
    //K vectors have datatype of bodyClass with corresponding x, x_dot, y, y_dot, m
    vector <bodyClass> k1(bodies.size());
    vector <bodyClass> k2(bodies.size());
    vector <bodyClass> k3(bodies.size());
    vector <bodyClass> k4(bodies.size());
    vector<vector<bodyClass>> y;
    y = {bodies};  // y-values at t=0
     
    //vectors for final summation of Runge Kutta Method: y[i+1]=y[i]+ k1/6+ (K2+k3)/3 + K4/4
    vector<bodyClass> k1_sum(bodies.size());    // k1/6
    vector<bodyClass> k2_k3_sum(bodies.size()); //(K2+k3)/3
    vector<bodyClass> k4_sum(bodies.size());    // K4/4
    vector<bodyClass> yRow;




    //RUNGE KUTTA LOOP
    for (int t=0; t<n; t++) {    
        k1 = f(y[t], G);  //k=vector of bodies
        transform(k1.begin(), k1.end(), k1.begin(), [&dt](bodyClass body) {return body = body.multiplyBody(dt);}); //multiplying each body's paramters by dt (except mass)

        k2 = f(addBodyVector(y[t],k1, 2), G);
        transform(k2.begin(), k2.end(), k2.begin(), [&dt](bodyClass body) {return body = body.multiplyBody(dt);});

        k3 = f(addBodyVector(y[t],k2, 2), G);
        transform(k3.begin(), k3.end(), k3.begin(), [&dt](bodyClass body) {return body = body.multiplyBody(dt);});

        k4 = f(addBodyVector(y[t],k3, 1), G);
        transform(k4.begin(), k4.end(), k4.begin(), [&dt](bodyClass body) {return body = body.multiplyBody(dt);});
        

        transform(k1.begin(), k1.end(), k1_sum.begin(), [] (bodyClass& body) {return body.divideBody(6);});
        transform(k2.begin(), k2.end(), k3.begin(), k2_k3_sum.begin(), [] (bodyClass& body1, bodyClass& body2) {return (body1.addBody(body2)).divideBody(3);});
        transform(k4.begin(), k4.end(), k4_sum.begin(), [] (bodyClass& body) {return body.divideBody(6);});


        for (int j=0; j<bodies.size(); j++) {
            yRow.push_back(y[t][j].finalSum(k1_sum[j], k2_k3_sum[j], k4_sum[j]));  //final summation of RK4
        }
        y.push_back(yRow);
        yRow={};
 
    }




    //OUTPUTTING FILE
    ofstream outputFile("output.txt", ios::out | ios::trunc); 
    outputFile.precision(5);
    int width=15;
    
    //Headers
    outputFile << setw(width) <<"Timestep" << setw(width) << "body-index" << setw(width) << "x" << setw(width) << "y"<< setw(width) << "x_dot"<<setw(width)<< "y_dot"<<setw(width)<<"Mass"<<setw(width)<<endl;   

    for (int bodyNum=0; bodyNum<bodies.size(); bodyNum++) {
        for (int i=0; i<n; i++) {  //i represents timestep
            bodyClass tempBody = y[i][bodyNum];
            outputFile<< setw(width) <<timestep[i] << setw(width) <<bodyNum+1<< setw(width)<< tempBody.getX()<< setw(width)<< tempBody.getY()<< setw(width)<< tempBody.getX_dot()<< setw(width) << tempBody.getY_dot()<< setw(width) << tempBody.getM()<<endl;
        }
    }   
    

	return 0;
}