#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

void print_array(std::vector<int> lst, int size) {
	cout << "List<" << size << ">: ";

	for (int i = 0; i < size; i++) {
		cout << lst[i];

		if (i < size - 1) {
			cout << ", ";
		}
	}

	cout << endl;
}

bool is_sorted(std::vector<int> &lst, int size) {
	for (int i = 0; i < size - 1; i++) {
		if (lst[i] > lst[i + 1]) {
			return false;
		}
	}

	return true;
}

void print_bar(long long int iter, bool final) {
	if ((iter % 100 != 0) && ! final) {
		return;
	}

	cout << "\rIter: " << iter;
	if (final) {
		cout << endl;
	}
}

bool is_in_vector(std::vector<int> &lst, int num) {
	// Special case for if we are ran in a while loop and called with an empty vector
	// Because vector[0] causes a segfault if it is empty
	if (lst.size() == 0) {
		return false;
	}

	for (int i = 0; i <= lst.size(); i++) {
		if (lst[i] == num) {
			return true;
		}
	}

	return false;
}

void fill_random_list(std::vector<int> &lst, int size, int upperlimit = 0) {
	int num;

	// Only output limit if we were given one.
	std::cout << "Generating random list of size " << size;
	if (upperlimit > 0) {
		std::cout << " with an upper limit of " << upperlimit;
	}
	std::cout << std::endl;

	// Size list to number of elements, this makes sense for large lists so
	// we aren't spending a TON of time resizing constantly.
	lst.reserve(size);

	// Finally put in some random nums
	for (int i = 0; i <= size; i++) {
		while(is_in_vector(lst, num)) {
			if (upperlimit > 0) {
				num = rand() % upperlimit;
			} else {
				num = rand();
			}
		}

		lst.push_back(num);

		print_bar(i, false);
	}

	std::cout << std::endl;
}

void shuffle_list(std::vector<int> &lst, int times) {
	std::cout << "Running shuffle_list loop " << times << " times!" << std::endl;

	for (int i = 0; i <= times; i++) {
		int j = 0;
		int k = 0;
		int temp = 0;
		while(j == k) {
			j = rand() % lst.size();
			k = rand() % lst.size();
		}

		// Swap
		temp = lst[j];
		lst[j] = lst[k];
		lst[k] = temp;
	}
}

int main(int argc, char *argv[]) {
	// init rand
	srand(time(NULL) + getpid() + gettid() + sizeof(int));
	cout << "Random: " << rand() << endl;

	// Generate list
	int lst_size = 4096;
	std::vector<int> lst;
	fill_random_list(lst, lst_size);

	// Shuffle list
	shuffle_list(lst, 4096 * 16);

	// Dump array
	print_array(lst, lst_size);

	long long int iter = 1;

	while(true) {
		iter+=1;

		// Shuffle
		// Pick two random indexes
		// Keep looping until i and j aren't the same
		int i = 0;
		int j = 0;
		int temp = 0;
		while(i == j) {
			i = rand() % lst_size;
			j = rand() % lst_size;
		}

		// Ensure we're comparing left to right
		if (i > j) {
			temp = i;
			i = j;
			j = temp;
		}

		// Only swap if out of order
		if (lst[i] > lst[j]) {
			temp = lst[i];
			//lst[i], lst[j] = lst[j], lst[i];
			lst[i] = lst[j];
			lst[j] = temp;
		}

		// Check for sort
		if ( is_sorted(lst, lst_size)) {
			print_bar(iter, true);
			cout << "List Sorted..." << endl;
			print_array(lst, lst_size);
			return 0;
		}

		print_bar(iter, false);
	}
}
