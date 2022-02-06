#include "Python.h"
#include <string>
#include <iostream>

#include "common.h"

class BigDataStore
{
  private:
	static BigDataStore* mInstance;
    PyObject* mGobblerObj;
    BigDataStore() {
		// open the python script and create the Gobbler Object
		PyObject *module_name, *module, *dict, *python_class;

		// Initializes the Python interpreter
		Py_Initialize();
		// Get the script name encoded in python unicode inside a pyobject
		module_name = PyUnicode_FromString("gobble");
        // import the script as a module
		module = PyImport_Import(module_name);
		if (module == nullptr) {
			PyErr_Print();
			std::cerr << "Fails to import the module.\n";
			return;
		}
		Py_DECREF(module_name);

		// class is interanlly a dictionary in python - so get the handle to
        // the dict
		dict = PyModule_GetDict(module);
		if (dict == nullptr) {
			PyErr_Print();
			std::cerr << "Fails to get the dictionary.\n";
			return;
		}
		Py_DECREF(module);

		// Builds the name of a callable class
		python_class = PyDict_GetItemString(dict, "Gobbler");
		if (python_class == nullptr) {
			PyErr_Print();
			std::cerr << "Fails to get the Python class.\n";
			return;
		}
		Py_DECREF(dict);

		// Creates an instance of the class
		if (PyCallable_Check(python_class)) {
            // create an object of the class
			mGobblerObj = PyObject_CallObject(python_class, nullptr);
			Py_DECREF(python_class);
		} else {
			std::cout << "Cannot instantiate the Python class" << std::endl;
			Py_DECREF(python_class);
			return;
		}
    }
  public:
	static BigDataStore* instance() {
		if (mInstance == nullptr) {
			mInstance = new BigDataStore();
		}
        return mInstance;
    }
    std::string get(int idx) {
      // call the get_data method of the python Gobbler class
      // "(i)" is the format string for the arguments
      PyObject *value = PyObject_CallMethod(mGobblerObj, "get_data", "(i)", idx); 
      if (value) {
          // extract the string from the returned pyobject
          PyObject* str = PyUnicode_AsEncodedString(value, "utf-8", "~E~");
          const char *bytes = PyBytes_AS_STRING(str);
          return bytes;
      } else {
          PyErr_Print();
      }
      return "";
    }
};

BigDataStore* BigDataStore::mInstance = nullptr;

extern "C" std::string getBigData(int idx) {
  return BigDataStore::instance()->get(idx);
}

/* // tester
int main()
{
	std::cout << getBigData(0) << std::endl;
	std::cout << getBigData(1) << std::endl;
	std::cout << getBigData(2) << std::endl;
	return 0;
} */
