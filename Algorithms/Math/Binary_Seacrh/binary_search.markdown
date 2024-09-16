# Binary Search

Binary search also known as _**half-interval search**_, _**logarithmic search**_ or _**binary chop**_
- is a search algorithm that finds the position of a target value within a sorted array.
Binary search algorithm checks if the index "start" is greater than the index "end". Based on the value present at the variable "mid", the function is called again to search for element.

In other words binary search: 
- comparing an element in the middle of the array with the target value. 
  - if the target value matches the element, its position in the array is returned. 
  - If the target value is less than the element, the search continues in the lower half of the array. 
  - If the target value is greater than the element, the search continues in the upper half of the array. 
- By doing this, the algorithm eliminates the half in which the target value cannot lie in each iteration.

Ginen: 
    Array $X_{0}^{n-1 (elements)}$ sorted such as $X_{0} \le X_{1} \le X_{2} \le \dots \le X_{n - 1}$ and terget value $T$ let's find value $T$ in $X^{n-1 (elements)}_{0}$.
-  set $S$ as start_index, $0$ and $E$ as end_index, $n - 1$
   - if $E \ge S$. $set:$ _**mid_index**_, $m$ as $S + \frac{(E - S)}{2}$ 
   - if $X_{m} = T$. $then:$  return _**mid_index**_, $m$
   - if $X_{m} > T$. $set$ _**end_index**_, $E$ to $m - 1$
   - if $X_{m} \le T$. $set$ _**star_index**_, $S$ to $m + 1$ 
      
![Binary_Search_Depiction.svg.png](images/Binary_Search_Depiction.svg.png)
- Note:
   - While it is possible to perform binary search using _**for-loop**_ and compare each number, the sequential search (binary search) is efficient, especially if the list is long.
 
![Binary Search Code](images/binary_search_code.png)
