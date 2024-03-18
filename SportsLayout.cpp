#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
// #include <thread>

using namespace std;

#include "SportsLayout.h"

    SportsLayout::SportsLayout(string inputfilename)
    {
          
        readInInputFile(inputfilename);
        mapping= new int[z];

    }

    bool SportsLayout::check_output_format()
    {

        vector<bool> visited(l,false);
        for(int i=0;i<z;i++)
        {
            if((mapping[i]>=1 && mapping[i]<=l))
            {
                if(!visited[mapping[i]-1])
                visited[mapping[i]-1]=true;
                else
                {
                    cout<<"Repeated locations, check format\n";
                    return false;
                }
            }
            else
            {
                cout<<"Invalid location, check format\n";
                return false;
            }
        }

        return true;

    }

    // void SportsLayout::readOutputFile(string output_filename)
    // {
    //         fstream ipfile;
	//         ipfile.open(output_filename, ios::in);
    //         if (!ipfile) {
    //             cout << "No such file\n";
    //             exit( 0 );
    //         }
    //         else {
                
    //             vector<int> ip;

    //             while (1) {
    //                 int t;
    //                 ipfile >> t;
    //                 ip.push_back(t);
    //                 if (ipfile.eof())
    //                     break;
                    
    //             }
            
    //         if(ip.size()!=z)
    //         {
    //             cout<<"number of values not equal to number of zones, check output format\n";
    //             exit(0);
    //         }
    //         for(int i=0;i<z;i++)
    //         mapping[i]=ip[i];
    //     ipfile.close();

    //     if(!check_output_format())
    //         exit(0);
    //     cout<<"Read output file, format OK"<<endl;

    //         }
        
    // }


    long long SportsLayout::cost_fn(){


        long long cost=0;

        for(int i=0;i<z;i++)
        {
           for(int j=0;j<z;j++) 
           {
                cost+=(long long)N[i][j]*(long long)T[mapping[i]-1][mapping[j]-1];
           }
        }

        return cost;
    }

    void SportsLayout::readInInputFile(string inputfilename)
    {
            fstream ipfile;
	        ipfile.open(inputfilename, ios::in);
            if (!ipfile) {
                cout << "No such file\n";
                exit( 0 );
            }
            else {
                

                ipfile>> time;
                ipfile >> z;
                ipfile >> l;

                if(z>l)
                {
                    cout<<"Number of zones more than locations, check format of input file\n";
                    exit(0);
                }


            

            int **tempT;
            int **tempN;

          tempT = new int*[l];
         for (int i = 0; i < l; ++i)
            tempT[i] = new int[l];
        
        tempN = new int*[z];
        for (int i = 0; i < z; ++i)
            tempN[i] = new int[z];

        for(int i=0;i<z;i++)
        {
            for(int j=0;j<z;j++)
            ipfile>>tempN[i][j];
        }

        for(int i=0;i<l;i++)
        {
            for(int j=0;j<l;j++)
            ipfile>>tempT[i][j];
        }

        ipfile.close();

        T= tempT;
        N= tempN;
            }

    }

    void SportsLayout::write_to_file(string outputfilename){

         // Open the file for writing
    ofstream outputFile(outputfilename);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file for writing." << endl;
        exit(0);
    }

    for(int i=0;i<z;i++)
    outputFile<<mapping[i]<<" ";

    // Close the file
    outputFile.close();

    cout << "Allocation written to the file successfully." << endl;

    }
    vector<int> SportsLayout::generateDistinctRandomNumbers(int k, int n) {
            if (k > n) {
                cerr << "Error: k should be less than or equal to n." << endl;
                exit(1);
            }

            vector<int> result;
            for (int i = 1; i <= n; ++i) {
                result.push_back(i);
            }

            random_device rd;
            mt19937 gen(rd());

            for (int i = 0; i < k; ++i) {
                uniform_int_distribution<int> dis(i, n - 1);
                int j = dis(gen);
                swap(result[i], result[j]);
            }

            // return vector<int>(result.begin(), result.begin() + k);
            return  result;       
        }


    void SportsLayout::compute_allocation()
    {
        //you can write your code here 
        //comment out following dummy code
        
       


        vector<int> rand  = generateDistinctRandomNumbers(z, l);
        for (int i=0 ; i<z ; ++i){
            mapping[i]=rand[i];
        } 

        long long min_cost = cost_fn();
        
        int desired_duration = int (time * 60.0);
        auto start_time = chrono::steady_clock::now();
        while(true){

        for  (int i=0;i<z;++i){
            for (int j=i+1; j<z;++j){
                swap(mapping[i], mapping[j]);
                long long p = cost_fn();
                if (p>=min_cost){
                swap(mapping[i], mapping[j]);

                }
                else{
                    min_cost = p;
                    swap(rand[i],rand[j]);
                }
            }

        }
       
        for (int i=0;i<z;++i){
            for (int j=z;j<l;++j){
                mapping[i]=rand[j];
                long long p= cost_fn();
                if (p<min_cost){
                    swap(rand[i],rand[j]);
                    min_cost= p;

                }
                else{
                    mapping[i]=rand[i];


                }

            }
        }
        auto current_time = chrono::steady_clock::now();
        auto elapsed_time = chrono::duration_cast<chrono::seconds>(current_time - start_time).count();
        if (elapsed_time >=desired_duration){
            break;
        }
        
    } 
    for (int i =0 ; i<z;i++){
        cout<< mapping[i]<<" ";
    }
    cout<< endl;
        
  
    }



