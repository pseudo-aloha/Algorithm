// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int key = 0;
    int j = 0;
    for(int i = 1; i < data.size(); i++){
	    key = data[i];
	    j = i - 1;
	    while (i > 0 && data[j] > key){
		    data[j+1] = data[j];
		    j = j - 1;
	    }
	    data[j+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    int middle = 0;
    if (low < high){
        middle = Partition(data, low, high);
        QuickSortSubVector(data, low, middle - 1);
        QuickSortSubVector(data, middle + 1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int x = data[high];
    int i = low - 1;
    int temp = 0;
    for (int j = low; j < high; j++){
        if (data[j] <= x){
            i++;
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    temp = data[i + 1];
    data[i + 1] = data[high];
    data[high] = temp;
    return (i + 1);
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    int middle = 0;
    if (low < high){
        int middle = int(low + (high - low) / 2);
        MergeSortSubVector(data,low,middle);
        MergeSortSubVector(data,middle+1,high);
        Merge(data,low,middle,high,high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1 = middle1 - low + 1;
    int n2 = high - middle1;
    int L[n1];
    int R[n2];
    for (int i = 0; i < n1; i++){
        L[i] = data[low + i];
    }
    for (int i = 0; i < n2; i++){
        R[i] = data[middle1 + i + 1];
    }
    int i = 0;
    int j = 0;
    //L[n1] = 2147483647;
    //R[n2] = 2147483647;
    for(int k = low; k <= high; k++){
        if ((L[i] <= R[j] && i < n1) | j >= n2){
            data[k] = L[i];
            i++;
        }
        else{
            data[k] = R[j];
            j++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = 2 * root + 1;
    int r = 2 * root + 2;
    int temp = 0;
    int largest = 0;
    if (l < heapSize && data[l] > data[root]){
        largest = l;
    }
    else{
        largest = root;
    }
    if (r < heapSize && data[r] > data[largest]){
        largest = r;
    }
    if (largest != root){
        temp = data[root];
        data[root] = data[largest];
        data[largest] = temp;
        MaxHeapify(data,largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = int(heapSize / 2)  ; i >= 0; i--){
        MaxHeapify(data,i);
    }
}
