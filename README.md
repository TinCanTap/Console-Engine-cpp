# Console-Engine-cpp
Console engine (with windows functions) in C++

refresh() function should be included in your main cpp file
3 vectors must be sent when calling the function: characters, ints and another int vector
characters are put on screen via the coords in the second vector (so the second vector is twice the size of the char vector)
example:
vector<char> characters = {'a','b','c'};
vector<int> coords = {1,1,2,1,3,1};
vector<int> colors = {4,8,12};

however, colors are not required if you choose to disable color via the bool value parameter, although you still have to send an empty int vector to make it happy
it is ok for coords to be outside the box boundaries, but it is not ok for there to be more coords than chars or vice versa
char border is what borders the screen, can be disabled by using space as a char
