# WI-24 Assignment 3 - JSON Processor
## Due TODO!

Build your own JSON parser, API, and CLI! 
This will involve
- Parsing the JSON
- Building an in-memory model of the JSON
- Creating and using a simple command language for querying the in-memory model

## 0. What is JSON?

JSON (or **J**ava**S**cript **O**bject **N**otation) was created for use in web development.
The goal was to create a simple text-format to transmit and store complex data. 

For instance, imagine you want to store data for a school classroom. What would you want to store?
- Classroom description (class name, teacher, location, class times, etc.)
- A list of students
  - Store each student's name, age, grade, etc.

Here is how you can represent that data in the JSON format:

```json
{
  "className": "Math 101",
  "teacher": "Mr. Farber",
  "startTime": "10:00am",
  "endTime": "11:00am",
  "hasFinalExam": true,
  "location": {
    "roomNumber": 247,
    "floor": 2
  },
  "students": [
    {
      "name": "Micheal",
      "age": 17,
      "grade": 94
    },
    {
      "name": "Sarah",
      "age": 18,
      "grade": 96.5
    },
    {
      "name": "Brian",
      "age": 16,
      "grade": 73
    },
    {
      "name": "Lisa",
      "age": 19,
      "grade": null
    }
  ]
}
```

Important things to notice:
- To store anything you need a **key** and a **value**.
  - For instance, `"className"` is the key and `"Math 101"` is the value.
- A value can be 6 different types: `null`, `boolean`, `number`, `string`, `list`, or `object`
  - An `object` is a value that can store additional key-value pairs with itself.
  - Notice the `number` type. In Javascript, `number` can represent both `long` and `double` types. 
    - In C++, we can separate this `number` type into distinct `long` and `float` types to correctly store the value.
- For a more detailed and formal description, check out [json.org](https://www.json.org/json-en.html).

We have addition JSON examples in this repository, feel free to look through them to better familiarize yourself with the syntax.

## 1. The Parser

Before we can implement any fancy functionality, 
we first need to be able to **read/write** JSON files and **parse** the JSON syntax.

Luckily for you, we provide a fully-functional JSON parser!
We highly recommend that you take the time to familiarize yourself with the parser code.

Even though this parser is built to parse JSON, the same design can be used to parse nearly any language!

### Using the parser

To connect your code to the parser, your `Model` must inherit from `JSONListener` and implement the pure virtual methods.
These listener methods will be called by the parser each time a new JSON element is parsed and must be added to the
in-memory model.

It is your responsibility to implement these methods correctly. We will go into more detail about the model in the
next section.


## 2. The In-Memory Model

Now that we can parse JSON, we need a way to represent the extracted information in memory.

### Why do we need a in-memory model?

We actually don't *need* one. We could instead perform all the queries on the raw text.
However, parsing text is slow. 

It would be much faster if we can build our own representation of the JSON
which the rest of our code could easily interact with!

Hence, the in-memory model.

### How do we build our in-memory model?

This is up to you. However, there is no point in reinventing the wheel, 
so here are some structures/patterns people use to create such models.

For something as dynamic and flexible as JSON, we need to build some sort of "graph".
This graph will need to store key-value pairs, 
where the values can be any of the 6 (or 7, if we split `number` into `long` and `double`) types described earlier.

Each of these key-value pairs can be considered a "node" in our graph. 
To paint a clearer picture of what I mean, let's take a look at the following example JSON:

```json
{
  "stringNode": "Hello!",
  "numberNode": 42,
  "objectNode": {
    "innerStringNode": "Hello again!",
    "innerBoolNode": true,
    "innerListNode": [
      "item1", "item2", "item3"
    ]
  }
}
```

Let's start at the very beginning. The first character we see is the open-curly-brace `{`.
This character is associated with the start of an `object` type. 

What can the `object` type do? It can store key-value pairs, 
and this is exactly what we see inside the curly-braces.

Since the root element of JSON is *always* an `object`, we know our model/graph will start with an `object`.

So we can add an object to the root of our model/graph:
```
node(object) -> ...
```

Let's look inside the object at the key-value pairs. 
The first one is `"stringNode": "Hello!"`, 
where the key is `"stringNode"` and the value is the string `"Hello!"`.

This means that inside our `object` node, we need to store this and all other key-value pairs,
where each key is a string and each value is another node in our graph.

> Think about which STL container can be used to store key-value pairs...

```
node(object) -> {
    key: "stringNode", value -> node(string)
    key: "numberNode", value -> node(int)
    key: "objectNode", value -> ???
}
```

Now that we have gotten to the `"objectNode"`, how should we update our graph?
Well, the value is a node like the other key-value pairs, just this time the node is of type `object`:

```
node(object) -> {
    key: "stringNode", value -> node(string)
    key: "numberNode", value -> node(int)
    key: "objectNode", value -> node(object) -> {
        ...
    }
}
```

And guess what? Our node of type `object` can store additional key-value pairs, 
which is exactly what see in our JSON:

```
node(object) -> {
    key: "stringNode", value -> node(string)
    key: "numberNode", value -> node(int)
    key: "objectNode", value -> node(object) -> {
        key: "innerStringNode", value -> node(string)
        key: "innerBoolNode", value -> node(bool)
        key: "innerListNode", value -> node(list) -> {
            ...
        }
    }
}
```

What about the `"innerListNode`? Well lists store an array of values (NOT key-value pairs),
and remember that values are just nodes for us, so let's update our graph with an array of nodes:

> Think about which STL container can store dynamic arrays...

```
node(object) -> {
    key: "stringNode", value -> node(string)
    key: "numberNode", value -> node(int)
    key: "objectNode", value -> node(object) -> {
        key: "innerStringNode", value -> node(string)
        key: "innerBoolNode", value -> node(bool)
        key: "innerListNode", value -> node(list) -> {
            node(string), node(string), node(string)
        }
    }
}
```

Aaaand there we have it! We have successfully created a model/graph representation of the JSON file!

### Using `JSONListener`

We have already touched on the `JSONListener` and its methods, but let's delve deeper now that we better
understand the in-memory model.

```cpp
// Add basic key-value data types (null, bool, number, or string)
bool addKeyValuePair(const std::string& aKey, const std::string& aValue, Element aType);
```

Like the comment says, this method will be called by the `JSONParser` each time it encounters a key-value pair
where the value is a basic type (either `null`, `boolean`, `number`, or `string`).

Imagine the case where the value is `"42"`. This is clearly a string, but the parser has already removed
the quotation `"` marks for you, so this may at first appear like a `number`. How do you differentiate between
strings and other types? 

This is what the `Element aType` parameter is for. If the value is a `string`, 
`aType` will be `Element::quoted`. Otherwise, it will be `Element::constant`.

For storing key-value pairs where the value is an object, the `openContainer()` method will be called instead.

```cpp
// Add values to a list
bool addItem(const std::string& aValue, Element aType);
```

If we are within a list rather than an object, 
then we should **not** be storing key-value pairs, just values.
This is what the `addItem()` method is for.

```cpp
// Start of an object or list container ('{' or '[')
bool openContainer(const std::string& aKey, Element aType);
```

When the parser encounters the start of an object or list, `openContainer()` will be called.
Use the `Element aType` argument to differentiate between the two.

If we are within an object, then this container will have a key associate with it, hence the
`const std::string& aKey` argument. However, if we are within a list, then this argument will be empty.
Remember, you can check if an `std::string` is empty using the `std::string::empty()` method.

```cpp
// End of an object or list container ('}' or ']')
bool closeContainer(const std::string& aKey, Element aType);
```

Lastly, the `closeContainer()` method. As you may expect, this method is called at the end of an
object or list. 

Same rules apply for the arguments as for the `openContainer()` method.

## 3. Query Language

Now that we can build JSON in-memory models, we need a way to interact with the model.

### Traversal

Used to navigate between nodes in the JSON structure.

```cpp
ModelQuery& select(const std::string& query);
```
Traverse the JSON tree.

- The `query` is a string that contains a series of keys (for key-value pairs within objects) or indices (for elements in a list).
  - The indices start counting from `0`, just like indexing an array in C++.
  - You can assume that an index will only be used if querying a list.
  - All keys will be surrounded by single quotes `'`.
  - All indices will **not** be surrounded by single quotes.
- Think of this command as moving some sort of pointer that points to a JSON element/node.
- Ex: `select("'firstNode'.'secondNode'.5")`. This will navigate to the element with `'firstNode'` as the key, then the child that has the key of `'secondNode'` and lastly, the child that has the index of `5`, as `'secondNode'` contains a list.

### Filtering

Used to 'skip' or 'ignore' certain JSON elements.

```cpp
ModelQuery& filter(const std::string& aQuery);
```
Filter certain elements in the current scope.

- The `query` is a string which contains some sort of comparison. This comparison can be applied to the element's key or index.

Filtering by key: `filter("key {action} '{value}'")`.
- Actions: `contains`
- Ex: `filter("key contains 'hello'")`: Will only include JSON elements where the key contains the substring `"hello"`.

Filtering by index: `filter("index {comparison} {value}")`
- Comparisons: All 6 (`<`, `>`, `<=`, `>=`, `==`, `!=`) comparisons.
- Ex: `filter("index > 2")`: Will only include JSON elements where the index is greater than 2. This only applies to elements within lists.

### Consuming

After navigating and filtering the JSON, 
these commands will be used at the end of the command chain to actually return some data/values.

- Notice how these methods return actual values instead of `ModelQuery&`.

```cpp
size_t count();
```
- Counts number of child elements of the currently selected node. Don't forget to apply the filter(s)!

```cpp
double sum();
```
- Sum values in a list. This will only be used in lists of numbers.

```cpp
std::optional<std::string> get(const std::string& aKeyOrIndex);
```
- Get values of a certain key-value pair or value at index of a list. 
If the value is a list/object, be sure to return all the elements (view examples below).
- Passing `"*"` as the argument will return all child nodes of the currently selected node (see examples below). Don't forget to apply filters!

### Example:

```json
{
  "sammy": {
    "username": "SammyShark",
    "online": true,
    "followers": {
      "count": 100,
      "avg-age": 25
    }
  },
  "items": [
    {"key1": "100"}
  ],
  "list": [
    100, 250, 3000
  ]
}
```

- `select("'sammy'").get("'username'")`: Should result in `"SammyShark"`.

- `select("'list'").sum()`: Should result in `3350`.

- `select("'list'").filter("index >= 1").sum()`: Should skip the value at index `0` and result in `3250`.

- `select("'sammy'").count()`: There are three nodes within the `"sammy"` object (`"username"`, `"online"`, `"followers"`), this should return `3`.

- `select("'sammy'.'followers'").get("*")`: Should return `{"count":100,"avg-age":25}`.

- `select("'sammy'.'followers'").get("'count'")`: Should return `100`.

- `select("'items'").get("0")`: Should return `{"key1":"100"}`.

- `select("'list'").filter("index < 2").get("*")`: Should return `[100, 250]`.


## 4. Tests

Just like the previous two assignments, it is very important to write some tests.

## What to Submit



## Grading