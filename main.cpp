#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int find_pivot(vector<int>& list, int first, int middle, int last){// returns the median of the three numbers 

  int mid[3] = { list[first], list[middle], list[last] };
  int larger = mid[0];
  int temp;

  for(int i = 0; i < 2; i++){
    if(larger < mid[i]){
      larger = mid[i];
    }
  }

  if(larger == mid[0]){
    temp = mid[2];
    mid[2] = larger;
    mid[0] = temp;
    if(mid[0]< mid[1]){
      return middle;
    }else{
      return last;
    }
  }

  if(larger == mid[1]){
    temp = mid[2];
    mid[2] = larger;
    mid[1] = temp;
    if(mid[0]< mid[1]){
      return last;
    }else{
      return first;
    }
  }

  if(larger == mid[2]){

    if(mid[0]<mid[1]){
      return middle;
    }else{
      return first;
    }
  }

  return 0;

}

void swap(vector<int> &list, int first, int second){// swap function
  int temp;
  temp = list[first];
  list[first] = list[second];
  list[second] = temp;
}

int partition(vector<int>& list, int first, int last) {
  // The pivot should be the median of the
  // first, middle, and last elements.
  int pivot, smallindex, index;
  int middle = (list.size() / 2);//  we find the middle of the list
 
  pivot = find_pivot(list, first, middle, last);//  we set pivot to the find_pivot functions return value

  swap(list , first, pivot);//  we swap pivot to the begining of the list

  pivot = list[first]; //  we set the pivot to first beacuse we changed it's position to the begining of the array
  smallindex = first; //  we start keeping track of smaller numbers with this index

  for(index = first + 1; index <= last; index++){//  loop to arrage all numbers smaller than the pivot to the beggining of the list

    if(list[index] < pivot){
      smallindex++;
      swap(list, smallindex, index);
    }
  }

  swap(list, first, smallindex);//  now we replace pivot back where it should go at the middle of the list, thus all elements before it are now smaller

  return smallindex; // return the number of smaller elements, which is also the index of the pivot
}

void quicksort(vector<int>& list, int first, int last) {

  int pivot_quicksort;//  we initialize the pivot below by calling partition and setting it's return and assigning it to pivot

  if(first < last){//  making sure our list isn't negative
    pivot_quicksort = partition(list, first, last);//  the list has been spllit and partitioned, all elements before pivot are smaller
    quicksort(list, first, pivot_quicksort - 1); // now we sort the two halfs, first half
    quicksort(list, pivot_quicksort +1, last); // second right half
  }

}

typedef struct list_entry_t{// we save the values original index in this struc

  int value;
  int origin;

} list_entry;


bool comparison(const list_entry &a, const list_entry &b){//  this is used to satisfy the heap functions parameter format

  return (a.value > b.value);
}

void multiway_merge(vector<vector<int> >& input_lists, vector<int>&  output_list) {

  vector<list_entry> min_heap;// dummy variable to hold values of our n sorted lists for sorting

  list_entry temp;// dummy variable to transfer between input_lists and output_list
  int list_to_draw_from = 0;// to hold origin indexes 

  for(int i = 0; i < input_lists.size(); i++){//  load the first lowest value of each row into temp and save the index it came from
    temp.value = input_lists[i][0];
    temp.origin = i;

    input_lists[i].erase(input_lists[i].begin());// we remove that most recent entry

    min_heap.push_back(temp);// we push it onto the the heap
  }

  while(1)
  {

    std::make_heap(min_heap.begin(), min_heap.end(), comparison);// all new entries get sorted with make_heap()

    output_list.push_back( min_heap[0].value);//  we take the smallest each time and put it on our final combined sorted list
    list_to_draw_from = min_heap[0].origin;// tells us which list to draw from next time

    min_heap.erase(min_heap.begin());// we erase the first element

    if(!input_lists[list_to_draw_from].empty())// we check to see if theres any elements left to add to list
    {
      temp.value = input_lists[list_to_draw_from][0];// we push the next elements needed to be sorted into the heap
      temp.origin = list_to_draw_from;

      input_lists[list_to_draw_from].erase(input_lists[list_to_draw_from].begin());

      min_heap.push_back(temp);

    }

    if(min_heap.empty())// finished, if this is empty after the previous if statement is called, then we're done
    {
      break;
    }

  }

} 

int main(int argc, char** argv) {
  int n, m;
  cin >> n >> m;

  vector<vector<int> > input_lists(n, vector<int>(m));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> input_lists[i][j];
    }
  }

  // Quicksort k sublists
  for (int i = 0; i < input_lists.size(); ++i)
    quicksort(input_lists[i], 0, m-1);

  // Merge n input sublists into one sorted list
  vector<int> output_list;
  multiway_merge(input_lists, output_list);

  for (int i = 0; i < output_list.size(); ++i)
    cout << output_list[i] << " ";
    cout << endl;
}
