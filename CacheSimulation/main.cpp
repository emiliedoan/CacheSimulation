#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <queue>
using namespace std;
//My name is Emilie Doan


//each address will be split into fields depending on the type of cache
//to do this translate the hex into binary, and split up


//take in how many bytes in a cache, bytes in a block/line, and lines in a set (1 for direct mapped)
//with this calculate the number of lines in a cache (cachesize/linesize)

//for each address
//get the tag and line or set
//map the address to where it could be in the data structure
    //direct mapped
        // offset = log_2(line size)
        // # lines = cache size / block size
        //line field = log_2(#lines)
        //tage field = bits in address - line field - offset
    //set associative
    //fully assoc

//translate tag to decimal for storage and comparison

//look in the data structure to see if a block with that tag is already in a place where the new one could be inserted
//if so, hit ; if not, miss and place block in cache
//if when placing block in cache, if all relevant lines are full, use a replacement policy
        // fifo or LRU
        //if there are empty lines, just put it there
        //if its direct mapped theres only one choice, so the line just needs ot be replaced

//conversion funcitions based off geeks to geeks pages
string hexToBinary(string hexString){
    long int i = 0;
    string binaryAddress;

    while (hexString[i]) {

        switch (hexString[i]) {
            case '0':
                binaryAddress += "0000";
                break;
            case '1':
                binaryAddress += "0001";
                break;
            case '2':
                binaryAddress += "0010";
                break;
            case '3':
                binaryAddress += "0011";
                break;
            case '4':
                binaryAddress += "0100";
                break;
            case '5':
                binaryAddress += "0101";
                break;
            case '6':
                binaryAddress += "0110";
                break;
            case '7':
                binaryAddress += "0111";
                break;
            case '8':
                binaryAddress += "1000";
                break;
            case '9':
                binaryAddress += "1001";
                break;
            case 'A':
            case 'a':
                binaryAddress += "1010";
                break;
            case 'B':
            case 'b':
                binaryAddress += "1011";
                break;
            case 'C':
            case 'c':
                binaryAddress += "1100";
                break;
            case 'D':
            case 'd':
                binaryAddress += "1101";
                break;
            case 'E':
            case 'e':
                binaryAddress += "1110";
                break;
            case 'F':
            case 'f':
                binaryAddress += "1111";
                break;
            default:
                cout << "\nInvalid hexadecimal digit "
                     << hexString[i];
        }
        i++;
    }
    return binaryAddress;
}

int binaryToDec (string binaryString){
    int decVal = 0;
    int power = 0 ;
    int n = binaryString.length() ;

    for(int i = n-1 ; i>=0 ; i--){
        if(binaryString[i] == '1'){
            decVal += (1<<power) ;
        }
        power++ ;
    }
    return decVal;
}

//from https://www.quora.com/How-do-I-check-an-element-in-a-queue-when-I-have-used-the-STL-queue-because-the-function-contains-is-not-working-its-showing-no-member-in-queue-int

bool isContains(queue<int> q, int x){
    while(!q.empty()){
        if(q.front() == x)
            return true;
        q.pop();
    }
    return false;
}
//from geeks for geeks
bool sortbysec(const pair<int,int> &a, const pair<int,int> &b){
    return (a.second < b.second);
}

void directMapped(double bytesPC, double lineSize){
    map <string, int> directMap;
    string hexAddress;
    string binaryAddress;
    string textLine;
    double offset; //change to double?
    double numLines;
    double lineField;
    double tagField;
    double linesPSet = 1;
    string lineValue;
    double tagValue;
    string tagValueStr;
    double hits = 0;
    double actions = 0;

    //calculations
    offset = log2(lineSize);
    numLines = bytesPC/lineSize;
    lineField = log2(numLines);
    tagField = 32.00 - lineField - offset;

    //for every line, read it and then do the operations

    ifstream file("gcc.trace"); // change for different files
    while (getline(file, textLine)){
        //cout << textLine << endl;
        //get rid of unnecesary digits
        hexAddress = textLine.substr(4, 8);
        //cout << hexAddress << endl;
        //convert into binary
        binaryAddress = hexToBinary(hexAddress);
        //cout << binaryAddress << endl;
        //separate line field (in binary) this will be the index
        lineValue = binaryAddress.substr(tagField-1, lineField);
        //cout << lineValue << endl;

        //separate and save the tag field (this will be the value, turn it into a decimal)
        tagValueStr = binaryAddress.substr(0, tagField);
        tagValue = binaryToDec(tagValueStr);
        //cout << tagValue << endl;

        //insert into map

        if (directMap.find(lineValue) == directMap.end()) {
            //key is not found, make it
            if (directMap.size() == numLines){//not enough lines


            }
            // insert and increment action counter but not hit counter
            directMap[lineValue] = tagValue;
            //cout << "inserted" << endl;
            actions++;

        } else {
            //key is found
            //check if tag is same, if so increment both counters
            if (tagValue == directMap.at(lineValue)) {
                //cout << "increase hits" << endl;
                actions++;
                hits++;
            } else {
                //if not, insert value
                //cout << "inserted" << endl;
                directMap[lineValue] = tagValue;
                actions++;
            }
    }


    }
    file.close();
    //cout << hits << endl;
    double hitRate = hits / actions;
    cout << hitRate << endl;

}

void setAssocFIFO(double bytesPC, double blockSize, double linesPSet){
    map <string, queue<int>> setAssocFIFOMap;
    string hexAddress;
    string binaryAddress;
    string textLine;
    double offset; //change to double?
    double numSets;
    double setField;
    double tagField;
    string setValue;
    double tagValue;
    string tagValueStr;
    double hits = 0;
    double actions = 0;

//    cout << bytesPC << endl;
//    cout << blockSize << endl;
//    cout << linesPSet << endl;

    //calculations
    offset = log2(blockSize);
    numSets = bytesPC / (blockSize * linesPSet);
    setField = log2(numSets);
    tagField = 32.00 - setField - offset;

    ifstream file("gcc.trace"); // change for different files
    while (getline(file, textLine)) {
        //get rid of unnecesary digits
        hexAddress = textLine.substr(4, 8);
        //cout << hexAddress << endl;
        //convert into binary
        binaryAddress = hexToBinary(hexAddress);
        //cout << binaryAddress << endl;
        //cout << tagField << endl;
        //cout << setField << endl;
        //separate line field (in binary) this will be the index
        setValue = binaryAddress.substr(tagField -1, setField);
        //cout << setValue << endl;

        //separate and save the tag field (this will be the value, turn it into a decimal)
        tagValueStr = binaryAddress.substr(0, tagField);
        tagValue = binaryToDec(tagValueStr);
        //cout << tagValue << endl;

        //queue size cannot exceed n, if there are n values in the queue and another needs to be inserted use FIFO
        //insert into map

        //insert into set (key)
        //find key, if it does not exist make it. and insert a tag into it
        //traverse queue to check if the tag already exists, if so, hit and do not insert
        //if the tag does not already exist and the queue size = n, FIFO
        //if tag does not exist and the queue size is less than n, insert it to the queue
        if (setAssocFIFOMap.find(setValue) == setAssocFIFOMap.end()) { //if key is not found
            //insert
            setAssocFIFOMap[setValue].push(tagValue);
            actions++;
        } else { //if key is found
            //traverse queue
            //if found in queue, increase hit counter
            //if not found in queue, check queue size. if size = n, use replacement
            if (isContains(setAssocFIFOMap.at(setValue), tagValue)) { //contains it
                hits++;
                actions++;
            } else { //does not contain

                if ((setAssocFIFOMap.at(setValue)).size() == linesPSet) {
                    //use FIFO
                    setAssocFIFOMap[setValue].pop();
                    setAssocFIFOMap[setValue].push(tagValue);
                    actions++;
                } else {
                    //insert
                    setAssocFIFOMap[setValue].push(tagValue);
                    actions++;
                }
            }


        }
    }
    file.close();
   double hitRate  = hits / actions;
    cout << hitRate << endl;

}
void setAssocLRU(double bytesPC, double blockSize, double linesPSet){
    map <string, vector< pair <double, double>> >setAssocLRUMap;
    //double LRUCounter;
    string hexAddress;
    string binaryAddress;
    string textLine;
    double offset; //change to double?
    double numSets;
    double setField;
    double tagField;
    string setValue;
    double tagValue;
    string tagValueStr;
    double hits = 0;
    double actions = 1;
    //double numLines;

    //calculations
    offset = log2(blockSize);
    numSets = (bytesPC) / (blockSize * linesPSet);
    //numLines = numSets * linesPSet;
    setField = log2(numSets);
    tagField = 32 - setField - offset;

    ifstream file("gcc.trace"); // change for different files
    while (getline(file, textLine)) {
        //get rid of unnecesary digits
        hexAddress = textLine.substr(4, 8);
        //cout << hexAddress << endl;
        //convert into binary
        binaryAddress = hexToBinary(hexAddress);
        //cout << binaryAddress << endl;
        //separate line field (in binary) this will be the index
        setValue = binaryAddress.substr(tagField-1, setField);
        //cout << setValue << endl;

        //separate and save the tag field (this will be the value, turn it into a decimal)
        tagValueStr = binaryAddress.substr(0, tagField);
        tagValue = binaryToDec(tagValueStr);
        //cout << tagValue << endl;


        //insert
        if (setAssocLRUMap.find(setValue) == setAssocLRUMap.end()) { //if key is not found create a new key and a new pair
            //insert
//            if (setAssocLRUMap.size() == numSets){ //then delete LRU set and insert
//                double smallestSum = 0.00;
//                string smallestKey = "";
//                //sum the values of each pair in a vector and compare each map key to eachother. the one with the least sum must be deleted
//                for (auto it = setAssocLRUMap.begin(); it!= setAssocLRUMap.end(); it++){ //for every key1
//                    double tempSum = 0.00;
//                    //sum its pairs
//                    for (auto j = it->second.begin(); j != it->second.end(); j++){
//                        tempSum = tempSum + j->second;
//                    }
//                   if (tempSum < smallestSum) { // if this sum is less than the previous,
//                       smallestSum = tempSum;
//                       smallestKey = it->first;
//                   }
//                }
//                setAssocLRUMap.erase(smallestKey);
                setAssocLRUMap[setValue].push_back(make_pair(tagValue, actions));
                actions++;
            //}
            //else{ //just insert
                setAssocLRUMap[setValue].push_back(make_pair(tagValue, actions));
                actions++;
           // }

        }
        else { //if key is found
            //check to see if tag is in vector, if so increase hit counter and action counter
            bool contains = false;
            for (auto it = setAssocLRUMap.at(setValue).begin(); it != setAssocLRUMap.at(setValue).end(); it++) {
                if (it->first == tagValue){
                    hits ++;
                    actions ++;
                    it->second = actions;
                    contains = true;
                }
            }
            //if not, check if n = size, if n=zise then LRU, if not then insert
            if (!contains){
                //check if n = size
                if (setAssocLRUMap.at(setValue).size() == linesPSet){ //no space, LRU
                    //delete the pair with the lowest second value
                    //sorts the vector by the second value of the pair in ascending order
                    sort(setAssocLRUMap.at(setValue).begin(), setAssocLRUMap.at(setValue).end(), sortbysec);
                    setAssocLRUMap.at(setValue).erase(setAssocLRUMap.at(setValue).begin());
                    //insert eh new pair
                    actions++;
                    setAssocLRUMap[setValue].push_back(make_pair(tagValue, actions));
                }
                else{//space
                    actions++;
                    setAssocLRUMap[setValue].push_back(make_pair(tagValue, actions));
                }
            }


            }


        }
    file.close();
    double hitRate = hits / actions;
    cout << hitRate << endl;

    }



void fullAssocLRU(double bytesPC, double blockSize){
vector<pair<double, double>> fullAssocVec;
    string hexAddress;
    string binaryAddress;
    string textLine;
    double offset; //change to double?
    //double numSets;
    double tagField;
    double tagValue;
    string tagValueStr;
    double hits = 0;
    double actions = 1;
    double numLines;

    offset = log2(blockSize);
    numLines = bytesPC / blockSize;
    tagField = 32.00 - offset;

    ifstream file("gcc.trace"); // change for different files
    while (getline(file, textLine)) {
        //get rid of unnecesary digits
        hexAddress = textLine.substr(4, 8);
        //cout << hexAddress << endl;
        //convert into binary
        binaryAddress = hexToBinary(hexAddress);

        tagValueStr = binaryAddress.substr(0, tagField);
        tagValue = binaryToDec(tagValueStr);

        //insert

        //the vector size must not exceed numLines
        //traverse through vector, if the tag is found pair->second = action count, hits++ actions++
        bool contains = false;
        for (auto it = fullAssocVec.begin(); it != fullAssocVec.end(); it++) {
            if (it->first == tagValue){
                hits ++;
                actions ++;
                it->second = actions;
                contains = true;
            }
        }
        //if does not have it, and size != numLines
        if (!contains){
            if(fullAssocVec.size() == numLines){
                //delete lru and then insert
                sort(fullAssocVec.begin(), fullAssocVec.end(), sortbysec);
                fullAssocVec.erase(fullAssocVec.begin());

                actions++;
                fullAssocVec.push_back(make_pair(tagValue, actions));
            }
            else{//there is space insert
                actions ++;
                fullAssocVec.push_back(make_pair(tagValue, actions));

            }
        }

    }
    file.close();
    double hitRate = hits / actions;
    cout << hitRate << endl;

}

void fullAssocFIFO(double bytesPC, double blockSize){
 queue<int> fullAssocQ;
    string hexAddress;
    string binaryAddress;
    string textLine;
    double offset; //change to double?
    //double numSets;
    double tagField;
    double tagValue;
    string tagValueStr;
    double hits = 0;
    double actions = 1;
    double numLines;

    offset = log2(blockSize);
    numLines = bytesPC / blockSize;
    tagField = 32.00 - offset;

    ifstream file("gcc.trace"); // change for different files
    while (getline(file, textLine)) {
        //get rid of unnecesary digits
        hexAddress = textLine.substr(4, 8);
        //cout << hexAddress << endl;
        //convert into binary
        binaryAddress = hexToBinary(hexAddress);

        tagValueStr = binaryAddress.substr(0, tagField);
        tagValue = binaryToDec(tagValueStr);

        //insert

        //the queue must not exceed size numlines
        //go through queue, if the tag does not exist already insert it action ++. if it does already exist hit++
        //if needs to insert but the size = numLines then pop.
        if (isContains(fullAssocQ, tagValue)) { //contains it
            hits++;
            actions++;
        }
        else{ //does not contain it
            if (fullAssocQ.size() == numLines){ // not enough space to insert
                fullAssocQ.pop();
                fullAssocQ.push(tagValue);
                actions++;
            }
            else{ //enough space
                fullAssocQ.push(tagValue);
                actions++;
            }

        }
    }
    file.close();
    double hitRate = hits / actions;
    cout << hitRate << endl;
}

int main(){

int cacheType;
double blockSize;
double cacheSize;
double linesPset;
int replaceStrat;
//int n;

//prompt for type
cout << "enter 0 for direct mapped, 1 for set associative, 2 for fully associative: " << endl;
cin >> cacheType;
if(cacheType ==1 ){
    cout << "specify what type set associative (enter a n value): " << endl;
    cin >> linesPset;
}
    if (cacheType != 0){
        //cout << "enter the number of lines per set: " << endl;
        //cin >> linesPset;
        cout << "enter 1 for FIFO, 2 for LRU: " << endl;
        cin >> replaceStrat;
    }
cout << "enter the block size:" << endl;
cin >> blockSize;
cout << "enter the cache size: " << endl;
cin >> cacheSize;


if(cacheType == 0){//direct mapped
    cout << "direct mapped" << endl;
    directMapped(cacheSize, blockSize);
}

if((cacheType == 1) && (replaceStrat == 1)){ //set assoc FIFO
    cout << "set associative FIFO" << endl;
    setAssocFIFO(cacheSize, blockSize, linesPset);
}
if((cacheType == 1) && (replaceStrat == 2)){ //set assoc LRU
 cout << "set associative LRU" << endl;
    setAssocLRU(cacheSize, blockSize, linesPset);
}

if((cacheType == 2) && (replaceStrat == 1)){ //fully assoc FIFO
    cout << "fully associative FIFO" << endl;
    fullAssocFIFO(cacheSize, blockSize);

}
if((cacheType == 2) && (replaceStrat == 2)){ //fully assoc LRU
    cout << "fully associative LRU" << endl;
    fullAssocLRU(cacheSize, blockSize);

}

}
