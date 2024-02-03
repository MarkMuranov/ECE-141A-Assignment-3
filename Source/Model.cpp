//
//  Model.cpp
//  Assignment4
//
//  Created by rick gessner on 2/15/20.
//

#include "Model.h"

namespace ECE141 {

	// ---Model---

	Model::Model() {
		TODO; // Remove once you have implemented this method
	}

	Model::Model(const Model &aCommand) {
		TODO;
	}

	Model &Model::operator=(const Model &aCommand) {
		TODO;
		return *this;
	}

	ModelQuery Model::createQuery() {
		return ModelQuery(*this);
	}

	bool Model::addKeyValuePair(const std::string &aKey, const std::string &aValue, Element aType) {
		TODO;
		// Print statement for debugging, remove after implementation
		//std::cout << "\t'" << aKey << "' : '" << aValue << "'\n";
		return true;
	}

	bool Model::addItem(const std::string &aValue, Element aType) {
		TODO;
		// Print statement for debugging, remove after implementation
		//std::cout << "\t'" << aValue << "'\n";
		return true;
	}

	bool Model::openContainer(const std::string &aContainerName, ECE141::Element aType) {
		TODO;
		// Print statement for debugging, remove after implementation
		//std::cout << (aContainerName.empty() ? "EMPTY" : aContainerName) << " " << (aType == Element::object ? "{" : "[") << "\n";
		return true;
	}

	bool Model::closeContainer(const std::string &aContainerName, ECE141::Element aType) {
		TODO;
		// Print statement for debugging, remove after implementation
		//std::cout << " " << (aType == Element::object ? "}" : "]") << "\n";
		return true;
	}


	// ---ModelQuery---

	ModelQuery::ModelQuery(Model &aModel) : model(aModel) {}

	ModelQuery& ModelQuery::select(const std::string& aQuery) {
		DBG("select(" << aQuery << ")");
		TODO;

		return *this;
	}

	ModelQuery& ModelQuery::filter(const std::string& aQuery) {
		DBG("filter(" << aQuery << ")");
		TODO;

		return *this;
	}

	size_t ModelQuery::count() {
		DBG("count()");
		TODO;

		return 0;
	}

	double ModelQuery::sum() {
		DBG("sum()");
		TODO;

		return 0.0;
	}

	std::optional<std::string> ModelQuery::get(const std::string& aKeyOrIndex) {
		DBG("get(" << aKeyOrIndex << ")");
		TODO;

		return std::nullopt;
	}

} // namespace ECE141