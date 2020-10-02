
#pragma once
#include <string>
using namespace std;
#include "common.hpp"
// Model is responsible for data get and set
// Speacs with server
class Model {
    public:
        Model(const string &data);
        Model(); // default constructor
        string getData();
        void setData(const string &data);
        void RegisterDataChangeHandler(DataChangeHandler handler);  //  register the event when data changes.
    private:
        string data = "";
        DataChangeHandler event = nullptr;
};