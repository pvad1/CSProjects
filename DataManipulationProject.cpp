#include "program2.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int CountingSortCount[MAX_VALUE+1] = {0};
int CountingSortCountSize=0;
int RadixSortCount[MAX_VALUE+1] = {0};
int RadixSortCountSize=0;
int BucketSortCount[MAX_VALUE+1] = {0};
int BucketSortCountSize=0;

bool arrayValidity(int arr[]) {
    int size = arr[0];
    for (int i = 1; i <= size; i++) {
        if (arr[i] <= 0 || arr[i] > MAX_VALUE) {
            return false;
        }
    }
    return true;
}


void countingSort(int inputArray[], int sortedArray[], int n,int exp,int base) {
  
    if (base == 0) {
        //this is regular counting sort
        int max = *max_element(inputArray, inputArray+n);
        int min = *min_element(inputArray, inputArray+n);
        
        int range = max - min + 1;
        
        int count[range], output[range];
        
        
        for (int i=0;i<range;i++) {
            count[i] = 0;
            output[i] =0;
        }
        
        for (int i = 0; i < n; i++)
            count[inputArray[i] - min]++;
        
        for (int i=0;i<range;i++){
            CountingSortCount[i]=count[i];
            CountingSortCountSize=range;
        }
        
        
        
        
        for (int i = 1; i < range; i++)
            count[i] += count[i - 1];
        
        
        for (int i = n - 1; i >= 0; i--) {
            output[count[inputArray[i] - min] - 1] = inputArray[i];
            count[inputArray[i] - min]--;
        }
        
        for (int i = 0; i < n; i++)
            sortedArray[i+1] = output[i];
        
    }else {
        
        int radixoutput[n]; // output array
        int radixcount[base];
        
        for(int i=0; i<n;i++) {
            radixoutput[i]=0;
        }
        for(int i=0; i<base;i++) {
            radixcount[i]=0;
        }
         
            // Store count of occurrences in count[]
            for (int i = 0; i < n; i++)
                radixcount[(inputArray[i] / exp) % base]++;
         
            // Change count[i] so that count[i] now contains actual
            //  position of this digit in output[]
            for (int i = 1; i < base; i++)
                radixcount[i] += radixcount[i - 1];
         
            // Build the output array
            for (int i = n - 1; i >= 0; i--) {
                radixoutput[radixcount[(inputArray[i] / exp) % base] - 1] = inputArray[i];
                radixcount[(inputArray[i] / exp) % base]--;
            }
         
            // Copy the output array to arr[], so that arr[] now
            // contains sorted numbers according to current digit
        for (int i = 0; i < n; i++) {
            inputArray[i] =radixoutput[i];
            sortedArray[i+1] = radixoutput[i];
        }
        
        
        
         }
    
}

void radixSort(int arr[], int sorted[], int n, int base) {
    
    int max_val = *max_element(arr, arr + n);
    //cout<<"max val" << max_val <<"\n";
    
    for (int exp = 1; max_val / exp > 0; exp *= base)
        countingSort(arr,sorted, n, exp,base);
}

void bucketSort(int arr[], int size) {
    
    vector<int> bucket[size];

    int max_val = *max_element(arr, arr + size);
    int min_val = *min_element(arr, arr + size);
    if (max_val == min_val) {
        //all values are same
        return;
    }
    
    
    int range = (max_val - min_val) /size;
    int bucketIndex=0;
    for(int i = 0; i<size; i++) { //adding elements into different buckets
        if (range != 0) {
            //different formula for index
            bucketIndex = (arr[i] - min_val) / range;
        }else {
            if (arr[i] != max_val)
                bucketIndex = 0;
            else
                bucketIndex = size - 1;
        }
            
        if (bucketIndex >= size )
            bucketIndex = size -1 ;
        //cout<<"bucketIndex is " << bucketIndex<<endl;
          bucket[bucketIndex].push_back(arr[i]);
    }
    
    for(int i=0;i<size;i++) {
        
    }
    
    for(int i = 0,j=0; i<size; i++) {
        
        //bucket is empty
        //bucket has multiple entries
        //bucket has only one entry
        
        //cout<<"size of each bucket "<<endl;
        //cout<<"bucket["<<i<<"] = "<<bucket[i].size()<<endl;
        
        if (bucket[i].size() > 1) {
            //cal bucketsort
            bucketSort(&bucket[i][0],(int)bucket[i].size());
        }
        if (bucket[i].size() == 1){
            while(!bucket[i].empty()) {
                arr[j++] = *(bucket[i].begin());
                bucket[i].erase(bucket[i].begin());
            }
        }
    }
    //cout<<"end of all of each bucket "<<endl;
   
}

int* GetSortedOrder(int a[], int sortType, int base) {
    int size = a[0];
    if (!arrayValidity(a)) {
        return NULL;
    }
    int* sorted = new int[size + 1];
    sorted[0] = size;
    switch (sortType) {
    case 1:
        countingSort(a + 1, sorted, size,0,0);
        break;
    case 2:
        radixSort(a + 1, sorted, size, base);
        break;
    case 3:
        bucketSort(a + 1, size);
        //for (int i = 0; i < size; i++) {
        //    sorted[i + 1] = a[i + 1];
        //}
        break;
    default:
        return nullptr; // invalid sort type
}
return sorted;
}
               
// Returns the statistic the last time the sort was done using the specified sort type.
int GetStatistic(int sortType, int bucketNumber) {
    
    if ((sortType == 1) && (CountingSortCountSize !=0) ){
        return CountingSortCount[bucketNumber];
    }
    if ((sortType == 2) && (RadixSortCountSize !=0)){
        return RadixSortCount[bucketNumber];
    }
    if ((sortType ==3) && (BucketSortCountSize !=0)) {
        return BucketSortCount[bucketNumber];
    }
    return NO_SORT;
    
    return 0;
}



