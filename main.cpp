#include <iostream>
#include <string>
#include <list>
#include <fstream>
using namespace std;


long getNumEmptyBetween(list<int> &empty, long a, long b) {
    long num = 0;

    for (list<int>::iterator curr = empty.begin(); curr != empty.end(); curr++) {
        if (a < b) {
            if (a < (*curr) && (*curr) < b) {
                num++;
            }
        }
        else {
            if (b < (*curr) && (*curr) < a) {
                num++;
            }
        }
    }
    return num;
}


class Galaxy {
private:
    long x;
    long y;
public:
    Galaxy(long newX, long newY) {
        x = newX;
        y = newY;
    }
    long getX() {
        return x;
    }
    long getY() {
        return y;
    }

    long distance_to(Galaxy &galaxy1, list<int> &emptyColumns, list<int> &emptyRows) {
        long x2 = galaxy1.getX();
        long y2 = galaxy1.getY();
        long distance = abs(x2 - x) + abs(y2 - y);
        // Part 1: multiplier = 1
        // Part 2: multiplier = 999999
        long multiplier = 999999;
        distance += multiplier * getNumEmptyBetween(emptyColumns, x, x2);
        distance += multiplier * getNumEmptyBetween(emptyRows, y, y2);
        return distance;
    }
};


bool is_all_empty_row(string line) {
    bool isAllEmpty = true;
    for (int i = 0; i < line.length() && isAllEmpty; i++) {
        isAllEmpty = (isAllEmpty && line[i] == '.');
    }
    return isAllEmpty;
}

bool is_all_empty_column(list<string> &input, int column) {
    bool isAllEmpty = true;

    list<string>::iterator row = input.begin();
    while (isAllEmpty && row != input.end()) {
        isAllEmpty = isAllEmpty && (*row)[column] == '.';
        row++;
    }
    return isAllEmpty;
}


void add_empty_in_column(list<string> &input, int column) {
    list<string>::iterator it = input.begin();
    while (it != input.end()) {
        it->insert(column, ".");
        it++;
    }
}

long sum_of_paths(list<Galaxy> &galaxies, list<Galaxy>::iterator &current, list<int> &emptyColumns, list<int> &emptyRows) {
    long sum = 0;
    if (current == galaxies.end()) {
        return sum;
    }
    else {
        list<Galaxy>::iterator next = current;
        next++;
        sum = sum_of_paths(galaxies, next, emptyColumns, emptyRows);
        while (next != galaxies.end()) {
            sum += current->distance_to(*next, emptyColumns, emptyRows);
            next++;
        }
        return sum;
    }
}


int main(int argc, char **argv) {
    ifstream input_file;

    input_file.open("input.txt");

    string line;
    list<string> input_data;

    while (getline(input_file, line)) {
        input_data.push_back(line);
    }

    list<int> emptyRows;
    list<int> emptyColumns;

    list<string>::iterator row = input_data.begin();

    int rowNum = 0;
    for (row = input_data.begin(); row != input_data.end(); row++, rowNum++) {
        if (is_all_empty_row(*row)) {
            emptyRows.push_back(rowNum);
        }
    }

    row = input_data.begin();

    for (int column = 0; column < row->length(); column++) {
        if (is_all_empty_column(input_data, column)) {
            emptyColumns.push_back(column);
        }
    }

    row = input_data.begin();

    list<Galaxy> galaxies;

    rowNum = 0;
    for (row = input_data.begin(); row != input_data.end(); row++, rowNum++) {
        for (int column = 0; column < row->length(); column++) {
            if ((*row)[column] == '#') {
                galaxies.push_back(Galaxy(column, rowNum));
            }
        }
    }

    list<Galaxy>::iterator topGalaxy = galaxies.begin();

    long sum = sum_of_paths(galaxies, topGalaxy, emptyColumns, emptyRows);

    cout << "Sum of the shortest paths is " << sum << endl;

    return 0;
}
