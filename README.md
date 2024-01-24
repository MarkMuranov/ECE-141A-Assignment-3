# WI-24 Assignment 3 - JSON CLI
## Due TODO!

Build your own JSON parser, API, and CLI! 
This will involve
- Reading JSON files
- Parsing the JSON to a model which will be stored in memory
- Have an API that can query the data in the model
- Create a simple CLI (**C**ommand **L**ine **I**nterface) to query the JSON file

## 0. What is JSON?

JSON (or **J**ava**S**cript **O**bject **N**otation) was created for use in web development.
The goal was to create a simple text-format to transmit and store complex data. 

For instance, imagine you want to store data for a school classroom. What would you want to store?
- Classroom description (class name, teacher, location, class times, etc.)
- A list of students
  - You will need to store each student's name, age, grade, etc.

Here is how you can represent that data in the JSON format:

```json
{
  "className": "Math 101",
  "teacher": "Mr. Farber",
  "startTime": "10:00am",
  "endTime": "11:00am",
  "roomNumber": 247,
  "hasFinalExam": true,
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
- A value can be 7 different types: `null`, `boolean`, `int`, `float`, `string`, `list`, or `object`
  - An `object` is a value that can store additional key-value pairs with itself.
  - Think back to your `Variant` assignment to come up with ways to store these dynamic types.
- For a more detailed and former description, check out [json.org](https://www.json.org/json-en.html).
  - Notice that this description has a `number` type. In Javascript, `number` can represent both `int` and `float` types. 
  - In C++, we can separate this `number` type into distinct `int` and `float` types to correctly store the value.

We have addition JSON examples in this repository, feel free to look through them to better familiarize yourself with the syntax.

## 1. The Parser

Before we can implement any fancy functionality, 
we first need to be able to **read/write** JSON files and **parse** the JSON syntax.

### Reading/Writing

Thanks to the standard library, this part should be simple. We can use `std::fstream`.

**TODO**: Finish this part


### Parsing

Parsing any language/syntax can become complex very quickly, as you try to consider every edge-case; 
parsing code that consists of webs of `if` statements is common to see. 
However, we are here to tell you there is a better way!

Using **iterators**, careful state management and separating your code based on distinct responsibilities will prove to be valuable.

Attached below is a video that will walk you through building your own parser.
This parser will not be 100% comprehensive, so it is your responsibility to complete the parser.

**TODO**: Film and add a link to the video.

Even though we are specifically building a JSON parser, 
these same structures and patterns can be used to build a parser for **any** language/syntax.

In fact, later in this assignment, you will be building another parser, 
this one for a simple command-line interface which users can use to query JSON files.

## 2. The Memory Model

Now that we can parse JSON, we need a way to represent the extracted information in memory.

### Why do we *need* a memory model?

We actually don't *need* one. We could instead perform all the queries on the raw parsed representation.
However, parsing text is slow. And having to parse the text each time a query is performed is wasteful, 
especially if the JSON has not changed.

Creating a memory model will allow us to perform multiple complex queries on large JSON files much more quickly.
It will also further help us separate our code into distinct responsibilities, allowing our code to be more modular,
more flexible, easier to maintain and easier to use for future projects.

### How do we build our memory model?

This is up to you. However, there is no point in reinventing the wheel, 
so here are some structures/patterns people use to create such models.

For something as dynamic and flexible as JSON, we need to build some sort of "graph".
This graph will need to store key-value pairs, where the values can be any of the 7 types described earlier.

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

So we know that our model/graph starts with an `object` at the root. 
This is *always* the case in JSON.

So we can add an object to the root of our model/graph:
```
node(object) -> ...
```

Let's look inside the object at the key-value pairs. 
The first one is `"stringNode": "Hello!"`, 
where the key is `"stringNode"` and the value is the string `"Hello!"`.

This means that inside our `object` node, we need to store this and all other key-value pairs,
where each value is another node in our graph.

> Think about which STL container can be used to store key-value pairs...

```
node(object) -> {
    key: "stringNode", value -> node(string)
    key: "numberNode", value -> node(int)
    key: "objectNode", value -> ???
}
```

Now that we have gotten to the `"objectNode"`, how should we update our graph?
Well, since our node can represent object types, we can just have this value store
a node of type `object`:

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

What about the list node? Well lists store an array of values (NOT key-value pairs),
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

### Error handling

Believe it or not, not every JSON file you parse will be correctly written. 
If there is a mistake in the syntax of the JSON text, 
our code should be able to catch these errors and relay them back to the user.

**TODO**: add a section on error handling. Should this be in the parsing section?

## 3. Model API

Now that we can build JSON memory models, we need a way to interact with the model.

Here we can use fancy operator overloading and clever designs to create an easy-to-use API.

