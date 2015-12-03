#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>

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

int getPublishedPages(std::string comics_name) {
    return 0;
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