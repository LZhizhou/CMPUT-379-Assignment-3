
- We use the single linked list to implement FIFO and LRU. 

The element in the first node is always the first one to be moved away and the last node in the list will have the minimum priority to be moved. 

If a new element is added, it will be placed at the end of the list, as the last node.

To improve space efficiency, each node in the linked list will be allocated memory only when the node exists in the lists. The  memory will be free after the node is moved.

The storage occupied is matched with the size of the entries.

For time efficiency, the linked list will be traversed one time for each opeartion. 

For miss, the first node will be moved away and a new node will be added to the end of the list. 

For hit, it will return the result after it traversed the list and found. Thus, the time used for each opeartion is less or equal to the time used to traverse the list.

We build a script using Python to collect the result data save in to a scv file for each situation(162 in total for three different instance size). 

After that, we using Excel to plot the bar chart for different situations and compare them to explain the TLB behaviour.
