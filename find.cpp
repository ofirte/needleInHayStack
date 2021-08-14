#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <cstring>
#include <mutex>          
using namespace std;
using namespace std::chrono;
int niddleFoundAt = -1;
mutex mtx; 

static bool search(const string &txt, const string &pattern, int &lineCounter, int ignoreChars) {
    auto txtPoint = txt.c_str();
    auto endPoint = txtPoint + txt.length();
    std::vector<size_t> newLinesLocs; 
    while(txtPoint = (char *)memchr(txtPoint, '\n', endPoint - txtPoint)) { //Mark the newLines indices.
        newLinesLocs.push_back(txtPoint - txt.c_str());
        txtPoint++;
    }  
    auto patternPointer = txt.find(pattern);
    if (patternPointer != std::string::npos) { //pat is in txt,update the line counter and return true
        for (auto breakLineIndex : newLinesLocs) {
            if (patternPointer > breakLineIndex) {
                lineCounter++;
            }
        }
        return true;
    }
    else   //otherwise, just update line counter
        for (auto breakLineIndex : newLinesLocs) 
            lineCounter++;
    return false;
}

auto fileSearcher = [](const string &line, const string &pattern, int &counter, int paritionIndex, int ignoreCharCounter) {
    auto needleIsFound = search(line, pattern, counter, ignoreCharCounter);
    if (needleIsFound){   //Update which thread found the niddle
        mtx.lock();
        if(niddleFoundAt == -1 || paritionIndex < niddleFoundAt )
            niddleFoundAt = paritionIndex;
        mtx.unlock();
    }
};
 
string createBuffer(int bufferSize,ifstream & fileStream, int back){
    string line;
    line.resize(bufferSize);
    fileStream.read(&line[0],bufferSize);
    fileStream.seekg(-back,ios_base::cur);
    return line;
}

int printResult(int rowsCounter,int firstThreadCounter,int secondThreadCounter){
    if (niddleFoundAt == 0) {
        std::cout << "Pattern found at line " << rowsCounter + firstThreadCounter << endl;
        return 1;
    } else if (niddleFoundAt == 1) {
        std::cout << "Pattern found at line " << rowsCounter + firstThreadCounter + secondThreadCounter << endl;
        return 1;
    }
    return 0;
}

void find(ifstream & fileStream,string pattern){
    size_t rowsCounter = 1;
    int overlap = 0;
    while (fileStream) {
        size_t bufferSize = 1024 * 1024 + overlap;
        string line1 = createBuffer(bufferSize,fileStream,overlap);
        string line2= createBuffer(bufferSize + pattern.length(),fileStream, pattern.length());
        int firstThreadCounter = 0,secondThreadCounter = 0;
        std::thread first(fileSearcher, line1, pattern, std::ref(firstThreadCounter), 0, overlap);
        std::thread second(fileSearcher, line2, pattern, std::ref(secondThreadCounter), 1, pattern.length());
        first.join();
        second.join();
        overlap = pattern.size();
        if(printResult(rowsCounter,firstThreadCounter,secondThreadCounter))
            return;
        rowsCounter += firstThreadCounter + secondThreadCounter;
    }
    cout << "pattern wasn't found at this text file!";
}

int main(int argc, char *argv[])
{
    if (argc < 3){
        cout << "missing arguments!";
        exit(0);
    }
    auto t1 = high_resolution_clock::now(); //Performance measurement
    ifstream fileStream(argv[2]);
    string pattern = argv[1];
    find(fileStream,pattern); 
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    cout <<"Runtime is " << ms_int.count() << " miliseconds\n";
    return 0;
}
