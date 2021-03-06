/*
 For more information, please see: http://software.sci.utah.edu

 The MIT License

 Copyright (c) 2009 Scientific Computing and Imaging Institute,
 University of Utah.


 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 */

#ifndef CORE_PYTHON_PYTHONINTERPRETER_H
#define CORE_PYTHON_PYTHONINTERPRETER_H

// Boost includes
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2/signal.hpp>

// Core includes
#include <Core/Utils/Singleton.h>
#include <Core/Utils/StringContainer.h>
#include <Core/EventHandler/EventHandler.h>
#include <Core/Python/PythonActionContext.h>

class PythonStdIO;

namespace Core
{

// CLASS PYTHONINTERPRETER
/// A wrapper class of the python interpreter.
/// It calls the python interpreter on a separate thread.

// Forward declaration
class PythonInterpreter;
class PythonInterpreterPrivate;
typedef boost::shared_ptr< PythonInterpreterPrivate > PythonInterpreterPrivateHandle;

// Class definition
class PythonInterpreter : private Core::EventHandler
{
	CORE_SINGLETON( PythonInterpreter );
	
public:
	typedef std::pair< std::string, PyObject* ( * )( void ) > module_entry_type;
	typedef std::list< module_entry_type > module_list_type;

	// -- constructor/destructor --
private:
	PythonInterpreter();
	virtual ~PythonInterpreter();

	// -- overloaded event handler --
private:
	// INITIALIZE_EVENTHANDLER:
	/// This function initializes the event handler associated with the singleton
	/// class. It initializes the python interpreter.
	virtual void initialize_eventhandler();

public:
	// INITIALIZE:
	/// Initialize the python interpreter with extra modules.
	void initialize( wchar_t* program_name, const module_list_type& init_list );

	// GET_ACTION_CONTEXT:
	/// Get the action context for running actions from python.
	PythonActionContextHandle get_action_context();

	// PRINT_BANNER:
	/// Print the basic information about the python interpreter to output_signal_.
	void print_banner();

	// RUN_STRING:
	/// Execute a single python command.
	/// NOTE: The command is run in the main namespace.
	void run_string( std::string command );

	// RUN_SCRIPT:
	/// Execute a python script.
	/// NOTE: The script is run in its own local namespace.
	void run_script( std::string script );

	// RUN_SCRIPT:
	/// Execute a python script.
	/// NOTE: The script is run in its own local namespace.
	void run_script( StringVectorConstHandle script );

	// RUN_FILE:
	/// Execute a python script from file.
	/// NOTE: The script is run in its own local namespace.
	void run_file( std::string file_name );

	// INTERRUPT:
	/// Interrupt the current execution.
	void interrupt();

	// START_TERMINAL:
	/// To be implemented.
	void start_terminal();

	// -- signals --
public:
	typedef boost::signals2::signal< void ( std::string ) > console_output_signal_type;
	console_output_signal_type prompt_signal_;
	console_output_signal_type error_signal_;
	console_output_signal_type output_signal_;

private:
	friend class ::PythonStdIO;
	PythonInterpreterPrivateHandle private_;

public:
	// GETACTIONCONTEXT:
	/// Returns the action context for the python interpreter.
	static PythonActionContextHandle GetActionContext();

	// ESCAPEQUOTES:
	/// Escape the quotes(') and backslashes(\) in a string so it can be used as a python string enclosed
	/// by a pair of single quotes.
	static std::string EscapeSingleQuotedString( const std::string& input_str );
};

} // end namespace Core

#endif
