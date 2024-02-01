//
//  Model.h
//  Assignment4
//
//  Created by rick gessner on 2/15/20.
//

#pragma once

#include <string>
#include "JSONParser.h"

namespace ECE141 {

	class ModelQuery; // Forward declare

	// STUDENT: Your Model is built from a bunch of these...
	class ModelNode {
		// Sometimes a node holds a basic value (null, bool, number, string)
		// Sometimes a node holds a list of other nodes (list)
		// Sometimes a node holds a collection key-value pairs, where the value is a node (an object)

	};

	class Model : public JSONListener {
	public:
		Model();
		~Model() override = default;
		Model(const Model &aCommand);
		Model &operator=(const Model &aCommand);

		ModelQuery query();

	protected:
		// JSONListener methods
		bool addKeyValuePair(const std::string &aKey, const std::string &aValue, Element aType) override;
		bool addItem(const std::string &aValue, Element aType) override;
		bool openContainer(const std::string &aKey, Element aType) override;
		bool closeContainer(const std::string &aKey, Element aType) override;

		// STUDENT: Your model will contain a collection of ModelNode*'s
		//          Choose your container(s) wisely

	};

	// This is what gets returned when you query a model for a list of elements
	class ModelCollection {
	public:
		//STUDENT: choose an STL container to hold ModelNode* elements from your Model after a query...
	};

	class ModelQuery {
	public:
		ModelQuery &all(const std::string& aTarget);

		ModelQuery &first(const std::string& aTarget);

		ModelQuery &last(const std::string& aTarget);

		ModelQuery &nth(const std::string& aTarget, size_t anIndex);

		ModelQuery &before(const std::string& aTarget);

		ModelQuery &after(const std::string& aTarget);

		ModelQuery &within(const std::string& aTarget);

		size_t count();

		double sum(const std::string& aField);

		double avg(const std::string& aField);

		ModelCollection* get();

		std::string get(const std::string& aKey); // return value or empty string

		ModelQuery(Model& aModel);

		friend class Model;

		Model &model;
	};


} // namespace ECE141