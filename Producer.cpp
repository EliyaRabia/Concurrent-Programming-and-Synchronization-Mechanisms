#include "Producer.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <map>

using std::vector;
using std::string;
using std::map;
using std::to_string;

void producerFunction(int producerId, int numberOfProducts, BoundedBuffer& buffer) {
    vector<string> types = {"SPORTS", "NEWS", "WEATHER"};
    map<string, int> counts = {{"SPORTS", 0}, {"NEWS", 0}, {"WEATHER", 0}};
    
    for (int i = 0; i < numberOfProducts; ++i) {
        string type = types[rand() % types.size()]; // Randomly select a type
        string item = "Producer " + to_string(producerId) + " " + type + " " + to_string(counts[type]);
        counts[type]++; // Increment the count for the selected type
        buffer.insert(item);
    }
    buffer.insert("DONE");
}
