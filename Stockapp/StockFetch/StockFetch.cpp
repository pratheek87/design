// StockFetch.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <cpr.h>

#include <sstream>
using namespace restbed;
using namespace std;


void fnPrintArray(uint8_t key[], int length) {

	stringstream list;

	for (int i = 0; i < length; ++i)
	{
		list << (int)key[i];
	}
	string key_string = list.str();
	cout << key_string << endl;
}

string stock_data;

//api_key = 02UHFL93GS04438I

void service_ready_handler(Service&)
{
	fprintf(stderr, "Stock market receiver service running !! ");
}

size_t writefunc(void* ptr, size_t size, size_t nmemb, std::string* s)
{
	s->append(static_cast<char*>(ptr), size * nmemb);
	stock_data = s->c_str();
	//cout << stock_data;
	return size * nmemb;
}

string fetch_data()
{
	CURL* hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(hnd, CURLOPT_URL, "https://nse-data1.p.rapidapi.com/nifty_fifty_indices_data");
	curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writefunc);

	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, "X-RapidAPI-Host: nse-data1.p.rapidapi.com");
	headers = curl_slist_append(headers, "X-RapidAPI-Key: e1219ee7dfmshfa5eadbc533e1dap1ec629jsn12232e268fc8");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	CURLcode ret = curl_easy_perform(hnd);

	return stock_data;
}


string make_stock_req()
{
	CURL* hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(hnd, CURLOPT_URL, "http://localhost:8084/makerequests");
	curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writefunc);

	struct curl_slist* headers = NULL;
	//headers = curl_slist_append(headers, "X-RapidAPI-Host: nse-data1.p.rapidapi.com");
	//headers = curl_slist_append(headers, "X-RapidAPI-Key: e1219ee7dfmshfa5eadbc533e1dap1ec629jsn12232e268fc8");
	//curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	CURLcode ret = curl_easy_perform(hnd);

	return stock_data;
}

void get_method_handler(const shared_ptr< Session > session)
{
	cout << "received request" << endl;
	string data = move(fetch_data());
	session->close(OK, data, { {"Content-Type", "application/json;charset=utf-8"},  { "Connection", "close" },
		{"Access-Control-Allow-Methods",  "DELETE, POST, GET, OPTIONS" },
		{"Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With"} });
	cout << "request complete" << endl;
}

void buy_stock_handler(const shared_ptr< Session > session)
{
	
	const auto request = session->get_request();

	int content_length = request->get_header("Content-Length", 0);

	session->fetch(content_length, [](const shared_ptr< Session > session, const Bytes& body)
		{
			
			cout << ("%52s\n", 48, body.data()) << endl;
			session->close(OK, "Hello, World!", { {"Content-Type", "application/json;charset=utf-8"},  { "Connection", "close" },	
				{"Access-Control-Allow-Methods",  "DELETE, POST, GET, OPTIONS" },
		{"Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With"} }); });

	make_stock_req();
}


int main()
{
	auto resource = make_shared<Resource>();
	resource->set_path("/getnifty");
	resource->set_method_handler("GET", get_method_handler);

	auto resource1 = make_shared<Resource>();
	resource1->set_path("/buystock");
	resource1->set_method_handler("POST", buy_stock_handler);

	auto settings = make_shared< Settings >();
	settings->set_port(8083);
	settings->set_default_header("Access-Control-Allow-Origin", "*");
	//shared_ptr< thread > worker = nullptr;
	auto service = make_shared< Service >();
	service->publish(resource);
	service->publish(resource1);
	service->set_ready_handler(service_ready_handler);
	service->start(settings);
	//worker->join();
	return EXIT_SUCCESS;
}
