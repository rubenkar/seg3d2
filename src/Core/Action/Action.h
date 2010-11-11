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

#ifndef CORE_ACTION_ACTION_H
#define CORE_ACTION_ACTION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif 

// STL includes
#include <vector>
#include <string>
#include <map>

// Boost includes
#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

// Core includes
#include <Core/Utils/EnumClass.h>
#include <Core/Utils/Log.h>
#include <Core/Utils/IntrusiveBase.h>

// Action includes
#include <Core/Action/ActionInfo.h>
#include <Core/Action/ActionContext.h>
#include <Core/Action/ActionParameter.h>
#include <Core/Action/ActionResult.h>

namespace Core
{

class Action;
typedef boost::shared_ptr< Action > ActionHandle;
typedef boost::weak_ptr< Action > ActionWeakHandle;
typedef std::vector< ActionHandle > ActionHandleList;

// CLASS ACTION:
// Main class that defines an action in the program
// An action is not copyable as that would invalidate 
// the ActionParameter pointers used internally.

class Action : public boost::enable_shared_from_this< Action >
{
	// -- Constructor/Destructor --
public:
	// Construct an action of a certain type and with certain properties
	Action();

	// Virtual destructor for memory management of derived classes
	virtual ~Action(); // << NEEDS TO BE REIMPLEMENTED

	// -- query information (from the action info) --
public:
	// GET_ACTION_INFO:
	// Get the action information class that contains all the information about the
	// action.
	// NOTE: this function is generated using the macro for each function. Hence it does not need
	// to be implemented
	virtual ActionInfoHandle get_action_info() const = 0;

	// -- direct functions for querying information --
	// NOTE: The following functions are implemented through get_action_info() and query the static
	// information provided in the action.
	
	// NOTE: The reason for implementing ActionInfo in a separate class, is that it avoids 
	// duplicating this information for each action and all the actions of the same type share all
	// the information stored in memory. Hence although the interface allows querying the 
	// information through member functions, this information is shared with the static functions
	// provided for each sub class of this class. Hence that also explains why the get_action_info
	// function is virtual. It accesses the record from the derived class.
	
	// GET_DEFINTION:
	// Get the definition of the action (in XML format)
	std::string get_definition() const;
	
	// GET_TYPE:
	// Get the type of the action
	std::string get_type() const;
	
	// GET_USAGE:
	// Get a usage description
	std::string get_usage() const;
	
	// GET_KEY:
	// Get the name of the key with a certain index
	std::string get_key( size_t index ) const;

	// GET_KEY_DEFAULT_VALUE:
	// Get the name of the key with a certain index
	std::string get_default_key_value( size_t index ) const;
	
	// GET_KEY_INDEX:
	// Get the index of a certain key
	int get_key_index( const std::string& name ) const;
	
	// IS_UNDOABLE:
	// Chekc whether the action is undoable
	bool is_undoable() const;
	
	// -- query overloadable data ( from the action info if not overloaded ) --
public:
	// CHANGES_PROJECT_DATA:
	// Query whether the action changes the data
	virtual bool changes_project_data();
	
	// NOTE: This function is overloadable from the default subclass definition. As certain 
	// functions like Set, Add, etc, have this property depend on the actual object they operate
	// on. For example setting a layer state variable should change this, whereas a interface
	// variable should not. For these functions the default implementation that picks up this
	// property from the macro can thence be overwritten.
	
	// -- Run/Validate interface --
public:

	// VALIDATE:
	// Each action needs to be validated just before it is posted. This way we
	// enforce that every action that hits the main post_action signal will be
	// a valid action to execute.
	// NOTE: This function is *not* const and may alter the values of the parameters
	//       and correct faulty input. Run on the other hand is not allowed to
	//       change anything in the action, as it is posted to any observers
	//       after the action is validated.

	virtual bool validate( ActionContextHandle& context ) = 0;

	// RUN:
	// Each action needs to have this piece implemented. It spells out how the
	// action is run. It returns whether the action was successful or not.
	// NOTE: In case of an asynchronous action, the return value is ignored and the
	// program relies on report_done() from the context to be triggered when
	// the asynchronous part has finished. In any other case the ActionDispatcher
	// will issue the report_done() when run returns.

	virtual bool run( ActionContextHandle& context, ActionResultHandle& result ) = 0;
	// -- Action parameters --

public:

	// ADD_ARGUMENT:
	// A argument to the action needs to be registered with the base
	// class so we can import and export the arguments to a string.
	// This function links the arguments of the action to an internal
	// record of all the arguments
	template< class ARGUMENT >
	void add_argument( ARGUMENT& argument )
	{
		this->add_argument_ptr( &argument );
	}

	// ADD_KEY:
	// A key needs to be registered with the base class
	// so we can import and export the keys to a string.
	// This function links the keys of the action to an internal
	// key value pair system to records all the keys
	template< class KEY >
	void add_key( KEY& param )
	{
		this->add_key_ptr( &param );
	}

	// EXPORT_TO_STRING:
	// Export the action command into a string, so it can stored
	// The action factory can recreate the action from this string
	std::string export_to_string() const;

	// IMPORT_ACTION_FROM_STRING:
	// Import an action command from astring. This function is used by the
	// ActionFactory.
	bool import_from_string( const std::string& action, std::string& error );

	// IMPORT_ACTION_FROM_STRING:
	// Same as function above, but without the error report
	bool import_from_string( const std::string& action );

	// CLEAR_CACHE:
	// Clear any objects that were given as a short cut to improve performance.
	// NOTE: An action should not contain any persistent handles, as actions may be kept
	// for a provenance record.
	virtual void clear_cache();

	// CLEAR_REDO_CACHE:
	// Clear all the information that was recorded for redoing the action
	// NOTE: This function is only implemented for actions that can be redone. Its main purpose is
	// to ensure that when redoing actions it will generate the same unique identifiers.
	// NOTE: The context is suppied to check whether the function is run from the undo buffer.
	virtual void clear_redo_cache( ActionContextHandle& context );

private:

	// IMPLEMENTATION OF ADD_PARAMETER, ADD_ARGUMENT AND ADD_CACHEDHANDLE:
	// These take pointers to the base class, the ones defined above work
	// with references of the parameters for more convenience.
	void add_argument_ptr( ActionParameterBase* param );
	void add_key_ptr( ActionParameterBase* param );

	// Typedefs
	typedef std::vector< ActionParameterBase* > parameter_list_type;

	// Vector that stores the required arguments of the action.
	parameter_list_type arguments_;

	// Vector that stores the option key value pairs of the action.
	parameter_list_type keys_;
};

// CORE_ACTION:
// Action type should be defined at the top of each action. It renders code that
// allows both the class as well as the Action object to determine what its 
// properties are. By defining class specific static functions the class 
// properties can be queried without instantiating the action. On the other
// hand you want to query these properties from the object as well, even when
// we only have a pointer to the base object. Hence we need virtual functions
// as well. 

} // end namespace Core

#define CORE_ACTION_TYPE( name, description ) \
"<action name=\"" name "\">" description "</action>"

#define CORE_ACTION_ARGUMENT( name, description ) \
"<argument name=\"" name "\">" description "</argument>"

#define CORE_ACTION_KEY( name, default_value, description ) \
"<key name=\"" name "\" default=\"" default_value "\"> " description "</key>"

#define CORE_ACTION_CHANGES_PROJECT_DATA() \
"<changes_project_data/>"

#define CORE_ACTION_IS_UNDOABLE() \
"<undoable/>"

#define CORE_ACTION(definition_string) \
public: \
	static std::string Definition() { return GetActionInfo()->get_definition(); }\
	static std::string Type() { return GetActionInfo()->get_type(); } \
	static std::string Usage() { return GetActionInfo()->get_usage(); } \
	static Core::ActionInfoHandle GetActionInfo() \
	{\
		static bool initialized_; \
		static Core::ActionInfoHandle info_; \
		if ( !initialized_ ) \
		{\
			{\
				Core::ActionInfo::lock_type lock( Core::ActionInfo::GetMutex() );\
				std::string definition = std::string( "<?xml version=\"1.0\"?>\n" definition_string "\n" ); \
				if ( !info_ ) info_ = Core::ActionInfoHandle( new Core::ActionInfo( definition ) ); \
			}\
			{\
				Core::ActionInfo::lock_type lock( Core::ActionInfo::GetMutex() );\
				initialized_ = true;\
			}\
		}\
		return info_;\
	} \
	\
	virtual Core::ActionInfoHandle get_action_info() const { return GetActionInfo(); }

#endif

