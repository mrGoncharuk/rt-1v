#include "Model.hpp"

Model::Model() { } // default constructor
Model::Model(const string &data)
{
	this->setData(data);
}

string Model::getData()
{
	return this->data;
}

void Model::setData(const string &data)
{
	this->data = data;
	if (this->event != nullptr)
	{ // data change callback event
		this->event(data);
	}   
}
//  register the event when data changes.
void Model::RegisterDataChangeHandler(DataChangeHandler handler)
{
	this->event = handler;
}