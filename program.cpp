//Student Name:     Medina Zaganjori
//Student Number:   150160908
//Due Date:         29.10.2019

#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
//#include <ctime>        //Clock Operation
#include <fstream>      //Read and Write the file
#include <limits>       //Number Range
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <stdlib.h>

using namespace std;

void bubble(int *,int&);
void merge_sort(int*,int,int);
void merge(int *,int,int,int);

/*All parameters are explained below*/

int main(int argc,char* argv[]) {

    ifstream filename1(argv[3]);
    ofstream filename2("output.txt");//the file where we will printing the sorted numbers

    int counter_run; //How many numbers we will be passing to the function
    counter_run = atoi(argv[2]);//since the program reads it as string ==> convert to integer
    char algo_id;
    algo_id = argv[1][0];
    //filename1 = argv[3];

    if (!filename1.is_open())	// File opening control
    {
        cout << "Read README.txt file for further explanation" << endl;
        return 0;
    }

    if (argc != 4) {
        cout << "Your program requires 4 parameters" << endl;
        cout << "Read README.txt file for further explanation" << endl;
        return 0; //program finishes
    }

    int *my_num; //array to save the numbers extracted from the file
    my_num = new int[counter_run];

    int i = 0;
    while (i < counter_run) {
        filename1 >> my_num[i];
        i++;
    }

    //close the file
    filename1.close();

    switch(algo_id){
        case 'b': //time for bubble Sort function to be called
            //type defined as an alias of fundamental arithmetic type
            clock_t t1;
            t1=clock();
            cout<<"Calculating.."<<endl;
            bubble(my_num,counter_run); //call the function
            t1 = clock()-t1; //this value will hold the running time
            cout<<"For Bubble Sort Algorithm it took me "<<t1<<" clicks and "<<((float)t1)/CLOCKS_PER_SEC<<"seconds and my counter run is "<<counter_run;
            cout<<endl;
            break;
        case 'm':   //time for Merge_Sort function to be called
            clock_t t2;
            t2=clock();
            cout<<"Calculating.."<<endl;
            merge_sort(my_num, 0, counter_run-1);
            t2 = clock()-t2;
            cout<<"For Merge Sort Algorithm it took me "<<t2<<" clicks and "<<((float)t2)/CLOCKS_PER_SEC<<"seconds and my counter run is "<<counter_run;
            cout<<endl;
            break;
    }
    for (int i = 0; i < counter_run; i++) // Print sorted array to output file
    {
        filename2<< my_num[i] << endl;
        //cout << i+1 << ". " << my_num[i] << endl;
    }
    filename2.close();
    delete my_num;


    return 0;
}

void bubble(int *my_num,int &counter_run){
    //Based on the algorithm given in pdf homework
    for (int i = 0; i < counter_run; i++)
    {
        for (int j = counter_run - 1; j >= i + 1; j--)
        {
            if (my_num[j] < my_num[j - 1])
            {
                int momentary = my_num[j];
                my_num[j] = my_num[j - 1];
                my_num[j - 1] = momentary;
            }
        }
    }
}
void merge(int*my_num,int min,int median, int max){

    int i;
    int j;

    int size1,size2; //sizes of the momentary subarrays
    size1=(median-min)+1;
    size2=(max-median);

    int *mom_max;
    int *mom_min;

    //save dynamically place for the stored values
    mom_max=new int[size2+1];
    mom_min=new int[size1+1];

    for(i=0;i<size1;i++){
        mom_min[i] = my_num[min+i];
    }
    for(j=0;j<size2;j++){
        mom_max[j] = my_num[median+j+1];
    }
    
    mom_min[size1]=numeric_limits<int>::max(); 
    mom_max[size2]=numeric_limits<int>::max();
    
    //Corresponding respectively to indexes of 1st,2nd,merged array
    int k=0;
    int l=0;
    int m=min;
	
    while(k<size1 && l<size2){
        if(mom_min[k]<=mom_max[l]){
            my_num[m]=mom_min[k];
            k++;
        }
        else{
            my_num[m]=mom_max[l];
            l++;
        }
        m++;
    }
    while(k<size1){
        my_num[m]=mom_min[k];
        k++;
        m++;
    }
    while(l<size2){
        my_num[m]=mom_min[l];
        l++;
        m++;
    }
    //free the pointers
    delete mom_max;
    delete mom_min;
}

void merge_sort(int * my_num,int min,int max){
    if(min<max){
        int median = min+(max+min)/2;
        //recursive function, calls itself
        merge_sort(my_num,min,median);      //first half of array
        merge_sort(my_num,median+1,max);    //second half of array
        //now we call the merge function
        merge(my_num,min,median,max);       //merging sorted halves
    }
}
