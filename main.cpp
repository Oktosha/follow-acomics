#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>

#include <http_client.h>
#include <filestream.h>

#include <regex>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

struct Comics {
    Comics(std::string name, int readed_pages, int published_pages)
        : name(name), 
          readed_pages(readed_pages), 
          published_pages(published_pages) {}

    Comics(): name(""), readed_pages(0), published_pages(0) {}
    
    std::string name;
    int readed_pages;
    int published_pages;
};

int parsePublishedPagesFromResponce(std::string catalogPage, std::string comics_name) {
    std::regex e("~" + comics_name + "/([0-9]*)");
    std::smatch m;
    std::regex_search(catalogPage, m, e);
    return std::stoi(m[1]);
}

int getPublishedPages(std::string comics_name) {
    
    http_client client(U("http://acomics.ru/"));

    uri_builder builder(U("/search"));
    builder.append_query(U("keyword"), U(comics_name));

    int result;
    auto resp = client.request(methods::GET, builder.to_string()).then([=, &result](http_response response){
        concurrency::streams::container_buffer<std::string> bufferStream;
        auto bytesRead = response.body().read_to_end(bufferStream).get();
        result = parsePublishedPagesFromResponce(bufferStream.collection(), comics_name);
    });
    resp.wait();
    return result;
}

int main() {
    using namespace std;
    vector<Comics> comics;
    ifstream fin("follow-configure.txt");
    while(!fin.eof()) {
        string name;
        fin >> name;
        int readed_pages;
        fin >> readed_pages;
        comics.emplace_back(name, readed_pages, -1);
    }
    while(true){
        for (int i = 0; i < 100; ++i) {
            cout << endl;
        }
        for (int i = 0; i < comics.size(); ++i) {
            comics[i].published_pages = getPublishedPages(comics[i].name);
            cout.width(20);
            cout << comics[i].name << ": ";
            cout.width(4);
            cout << comics[i].readed_pages << " / ";
            cout.width(4);
            cout << comics[i].published_pages << endl;
        }
        std::this_thread::sleep_for(chrono::seconds(2));
    }
    return 0;
}