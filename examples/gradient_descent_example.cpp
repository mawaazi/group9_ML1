#include<iostream>
#include<vector>
#include<iomanip>
#include "../include/machine_learning_1/gradient_descent.hpp"


int main(){
    /*
    Example: learn the relationship y=2 + 3x1 +4x2

    Training data:
    x1=1, x2=1, y=9
    x1=2, x2=1, y=12
    x1=1, x2=2, y=13
    x1=2, x2=2, y=16
    x1=3, x2=2, y=15

    The model is:
    y_predicted = bias + (weight1*x1) + (weight2*x2)

    Parameters to learn:
    weights[0] = bias
    weights[1] = weight for x1
    weights[2] = weight for x2
    */
   std::vector<vector<double>> x = {
    {1.0, 1.0},
    {2.0, 1.0},
    {1.0, 2.0},
    {2.0, 2.0},
    {3.0, 1.0}
   };

   std::vector<double> y ={9.0, 12.0,13.0, 16.0,15.0};

   //First guess is that all parameters are zero
   std::vector<double> weights = {0.0,0.0,0.0};
   double learningRate = 0.01;
   int iterations = 5000;

   std::cout<<std::fixed<<std::setprecision(6);
   std::cout<<"\nStarting parameters: \n";
   std::cout<<"Bias= "<<weights[0]<<'\n';
   std::cout<<"Weight1= "<<weights[1]<<'\n';
   std::cout<<"Weight2= "<<weights[2]<<'\n';

   //Perform gradient descent
   std::vector<double> finalWeights = LinearRegression:: computeGradientDescent(
    x, y, weights, learningRate, iterations
   );

   std::cout<< "After"<<iterations<< "iterations: \n";
   std::cout<< "Learned bias ="<<finalWeights[0]<< '\n';
   std::cout<< "Learned weight 1= "<< finalWeights[1]<< '\n';
   std::cout<< "Learned weight 2= "<< finalWeights[2]<< '\n';

   std::cout<< "Predictions using the learned model:\n";
   for(size_t i=0; i < x.size(); ++i){
    double predictedy = finalWeights[0]+ finalWeights[1] *x[i][0] + finalWeights[2]*x[i][1];

    std::cout<< "x1= "<< x[i][0]<< ",x2= "<< x[i][1]<< ",actual y ="<<y[i]
    <<",predicted y= "<<predictedy<<'\n';
   }

   std::cout <<"\nExpected result: bias close to 2,"
   <<" weight 1 close to 3, and weight 2close to 4.\n ";
    
   return 0;
}