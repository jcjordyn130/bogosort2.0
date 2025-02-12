# bogosort2.0
Bogo Sort but Improved

# But why?
Because I felt like writing BogoSort but felt like I could improve on the algorithm slightly
so it wasn't completely random.

# How well does it work?
On my machine, it can sort a randomly generated list of 4096 elements in around ~80 million iterations.

Changing the code to pass the big vector by reference instead of by value caused an exponential increase in iteration speed.

The two critical functions are is_sorted and is_in_vector, is_sorted is called every sort iteration and is_in_vector is called for every element
generated for the random vector.

# How... does it work?
Instead of running a *true* bogosort where it shuffles the list then checks every iteration, this implementation does it a little bit differently.

This implementation takes two random list indexes, swaps them to they are smallest to largest (ie. to make sure it's comparing left to right), then swaps the list elements if they are out of order.

After this, it checks to see if the list is sorted, and if it isn't, it runs the loop again until it is.

# Optimizing
Compiling with -O2/-O3 makes it run a lot faster per iteration than if it was compiled with -g.

Both of these runs are with 4096 length lists.

```
$ g++ -O3 main.cpp
$ time ./a.out >/dev/null

real	0m7.492s
user	0m7.463s
sys	0m0.004s

$ g++ -g main.cpp
$ time ./a.out >/dev/null

real	0m55.309s
user	0m55.108s
sys	0m0.010s
```

# Example Run
```
$ ./a.out 
Random: 557628183
Generating random list of size 4096
Iter: 4000
Running shuffle_list loop 65536 times!
List<4096>: 1029175657, 963886788, 1661807123, 1890972807, 1782916117, ... [rest omitted for brevity]
Iter: 88056482
List Sorted...
List<4096>: 1, 119918, 202365, 293885, 886184, ... [rest omitted for brevity]
```