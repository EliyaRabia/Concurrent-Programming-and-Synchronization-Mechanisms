#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

struct ProducerConfig {
    int id;
    int numberOfProducts;
    int queueSize;
};

struct Config {
    std::vector<ProducerConfig> producers;
    int coEditorQueueSize;
};

Config parseConfig(const std::string& filename);

#endif
