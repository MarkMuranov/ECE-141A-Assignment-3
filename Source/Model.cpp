//
//  Model.cpp
//  Assignment4
//
//  Created by rick gessner on 2/15/20.
//

#include "Model.h"

namespace ECE141 {

	ModelQuery::ModelQuery(Model &aModel) : model(aModel) {
	}

	ModelQuery &ModelQuery::all(const std::string &aTarget) {
		return *this;
	}

	ModelQuery &ModelQuery::first(const std::string &aTarget) {
		return *this;
	}

	ModelQuery &ModelQuery::last(const std::string &aTarget) {
		return *this;
	}

	ModelQuery &ModelQuery::nth(const std::string &aTarget, size_t anIndex) {
		return *this;
	}

	ModelQuery &ModelQuery::before(const std::string &aTarget) {
		return *this;
	}

	ModelQuery &ModelQuery::after(const std::string &aTarget) {
		return *this;
	}

	ModelQuery &ModelQuery::within(const std::string &aTarget) {
		return *this;
	}

	ModelCollection *ModelQuery::get() {
		return nullptr;
	}

	std::string ModelQuery::get(const std::string &aKey) {
		return std::string(""); //retrieve the key from a value if query matches, otherwise return ""
	}

	size_t ModelQuery::count() {
		return 0;
	}

	double avg(const std::string &aField) {
		return 0.0;
	}

	double ModelQuery::sum(const std::string &aField) {
		return 0.0;
	}

	//---------------------- implement the model class... --------------------

	Model::Model() {
	}

	Model::Model(const Model &aCommand) {
	}

	Model &Model::operator=(const Model &aCommand) {
		return *this;
	}

	ModelQuery Model::query() {
		ModelQuery theQuery(*this);
		return theQuery;
	}

	bool Model::addKeyValuePair(const std::string &aKey, const std::string &aValue, Element aType) {
		// Print statement for debugging, remove after implementation
		std::cout << "\t'" << aKey << "' : '" << aValue << "' \taddKeyValuePair()\n";
		return true;
	}

	bool Model::addItem(const std::string &aValue, Element aType) {
		// Print statement for debugging, remove after implementation
		std::cout << "\t'" << aValue << "' \taddItem()\n";
		return true;
	}

	bool Model::openContainer(const std::string &aContainerName, ECE141::Element aType) {
		// Print statement for debugging, remove after implementation
		//open a new unnamed container in our model...
		std::cout << aContainerName << " { \topenContainer()\n";
		return true;
	}

	bool Model::closeContainer(const std::string &aContainerName, ECE141::Element aType) {
		// Print statement for debugging, remove after implementation
		std::cout << " } \tcloseContainer()\n";
		return true;
	}

} // namespace ECE141