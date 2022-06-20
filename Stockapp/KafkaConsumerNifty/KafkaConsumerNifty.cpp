// KafkaConsumer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "kafka/KafkaConsumer.h"

#include <iostream>
#include <sstream>
#include <future>
using namespace std;


void callback_method(kafka::Topic topic)
{
    std::string brokers = "localhost:9092";

    kafka::Properties props({
          {"bootstrap.servers", brokers}
        });

    // Create a producer instance.
    kafka::clients::KafkaConsumer consumer(props);
    consumer.subscribe({ topic });

    std::cout << "% Reading messages from topic: " << topic << std::endl;
    while (true) {
        auto records = consumer.poll(std::chrono::milliseconds(100));
        for (const auto& record : records) {
            // In this example, quit on empty message
            cout << "record value size:" << record.value().size() << endl;
            if (record.value().size() == 0) {}

            if (!record.error()) {
                std::cout << "% Got a new message..." << std::endl;
                std::cout << "    Topic    : " << record.topic() << std::endl;
                std::cout << "    Partition: " << record.partition() << std::endl;
                std::cout << "    Offset   : " << record.offset() << std::endl;
                std::cout << "    Timestamp: " << record.timestamp().toString() << std::endl;
                std::cout << "    Headers  : " << kafka::toString(record.headers()) << std::endl;
                std::cout << "    Key   [" << record.key().toString() << "]" << std::endl;
                std::cout << "    Value [" << record.value().toString() << "]" << std::endl;
            }
            else {
                // Errors are typically informational, thus no special handling is required
                std::cerr << record.toString() << std::endl;
            }
        }
    }
}

int main() {


    callback_method(kafka::Topic("get_nifty"));

    return 1;
}