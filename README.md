# EmbASP++
A C++ porting of the framework for integration of Logic Programming EmbASP  (see [DeMaCS-UNICAL/EmbASP](https://github.com/DeMaCS-UNICAL/EmbASP "DeMaCS-UNICAL/EmbASP"))

- The library uses some C++17 features and the **Boost.Filesystem** and **Boost.Process** libraries; 
- The library also uses the C++11 thread library;

Use the following flags to compile without "undefined reference" problems:

`-std=c++17 -lboost_system -lboost_filesystem -pthread`
    
---
### Usage
Use the framework in the same way you use the official EmbASP Java framework.

If you need a predicate with arity = 0 just extend the class **Fact**.

Define all of your predicate (with arity >= 0) classes extending the base class **Predicate**.
You have to override all of the pure virtual methods defined in Predicate.
They are:
- void initPredicate(): Add the predicate arguments here with the addArgument method;
- void initPredicate(const std::vector&lt;std::string&gt; &predicateArguments):  parse the values of the predicate from a vector of strings and call the initPredicate method;
- std::vector&lt;std::string&gt;listArguments(): put the arguments of te predicate in form of string into a vector and return it;

To add arguments use the `void addArgument<T>(int pos, T *argument)` template method.

Remeber to register your new class if you want to retrieve some possible atoms from the answer set of the same type. To do so use the template method of the singleton class ASPMapper ```void registerPredicateType<T>()```

    
---
### Sample code
#### Fact
```cpp
class Example : public embasp::Fact {
public:
	Example(): Predicate("fact_name") {  }
};

/*
* Just use your class as a normal class
*/
```

#### Predicate
```cpp
class ExitCode : public embasp::Predicate {
public:
	ExitCode(int code = 0): Predicate("exit_code"), code(code) { }

	void initPredicate(const vector<string> &args) override final {
		code = stoi(args[0]);

		initPredicate();
	}

	vector<string> listArguments() override {
		return vector<string> {
			to_string(code)
		};
	}

	string toString() {
		return "ExitCode{" + to_string(code) + "}";
	}

protected:
	void initPredicate() override final {
		addArgument<int>(0, &code);
	}

private:
	int code;

};
```
