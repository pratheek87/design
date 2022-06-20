// Stockapp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include "kafka/KafkaProducer.h"
#include <iostream>
#include <thread>
#include <memory>
#include <chrono>
#include <cstdlib>
#include <restbed>
#include <future>

using namespace std;
using namespace restbed;

void add_message(kafka::Topic& topic);
void make_requests_finance() {

	vector<future<void>> futures;
	int i = 0, j = 0;
	for (auto i = 0; i < 25 ; ++i) {
		kafka::Topic topic("get_nifty");
		futures.push_back(std::async(std::launch::async, std::bind(add_message,topic)));
		if (j == 0)
			j = 1;
		else
			j = 0;
	}


	for (auto i = 0; i < futures.size(); ++i) {
		futures[i].get();
	}
	return;
}

void make_requests_tech() {

	vector<future<void>> futures;
	int i = 0, j = 0;
	for (auto i = 0; i < 25; ++i) {
		futures.push_back(std::async(std::launch::async, std::bind(add_message, kafka::Topic("get_tech"))));
		if (j == 0)
			j = 1;
		else
			j = 0;
	}


	for (auto i = 0; i < futures.size(); ++i) {
		futures[i].get();
	}
	return;
}

void make_requests_stock() {

	vector<future<void>> futures;
	int i = 0, j = 0;
	for (auto i = 0; i < 25; ++i) {

		string s = "Nifty";
		futures.push_back(std::async(std::launch::async, std::bind (add_message, kafka::Topic("get_stock"))));
		if (j == 0)
			j = 1;
		else
			j = 0;
	}


	for (auto i = 0; i < futures.size(); ++i) {
		futures[i].get();
	}
	return;
}
void get_method_handler(const shared_ptr< Session > session)
{

	cout << "Inside gethandler" << endl;
	auto f1 = async(make_requests_finance);
	auto f2 = async(make_requests_stock);
	f1.get(); f2.get();
	//session->close(OK, "Put in queue", { {"Content-Type", "application/json;charset=utf-8"},  { "Connection", "close" } });
}

void service_ready_handler(Service&)
{
	fprintf(stderr, "Hey! The service is up and running.");
}

void callback(const kafka::clients::producer::RecordMetadata& metadata, const kafka::Error& error) {
	cout << metadata.toString() << endl;
}

void add_message(kafka::Topic& topic)
{
	std::string brokers = "localhost:9092";
	//kafka::Topic topic = "get_stock";

	kafka::Properties props({
		  {"bootstrap.servers", brokers},
		  {"enable.idempotence", "true"},
	});

	// Create a producer instance.
	kafka::clients::KafkaProducer producer(props);
	string t = "placing order for stock:  ";
	kafka::ConstBuffer buff("Key", 4);
	auto record = kafka::clients::producer::ProducerRecord(topic,
		buff,
		kafka::Value(t.c_str(), t.size()));

	const kafka::clients::producer::Callback cb = callback;

	try {
		int x = 20;
		while (x > 0) {
			producer.send(record, cb);
			--x;
		}
		//std::cout << "% Message delivered: " << std::endl;
	}
	catch (const kafka::KafkaException& e) {
		std::cerr << "% Message delivery failed: " << e.error().message() << std::endl;
	}
	cout << "Complete" << endl;

}



int main(const int, const char**)
{

	auto resource = make_shared< Resource >();
	resource->set_path("/makerequests");
	resource->set_method_handler("GET", get_method_handler);

	auto settings = make_shared< Settings >();
	settings->set_port(8084);
	settings->set_default_header("Access-Control-Allow-Origin", "*"); 
	auto service = make_shared< Service >();
	service->publish(resource);
	service->set_ready_handler(service_ready_handler);
	service->start(settings);

	return EXIT_SUCCESS;
}
