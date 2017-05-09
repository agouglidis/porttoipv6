/***************************************************************************
 *   Copyright (C) 2005-2017 by Antonios Gouglidis			   			   *
 *   e-mail: agouglidis@gmail.com   					   				   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _PF_MAPPER_BASE_H_
#define _PF_MAPPER_BASE_H_

#include <iostream>
#include <string>
#include <list>
using std::list;
#include <fstream>
using std::fstream;

#include "../../include/common.h"
#include "../../tinyxml/tinyxml.h"

const string& MapperVersion = "0.0.5"; /*!< Contains mapper version*/

//! The Base Class
/*!
	This base class encapsulates all the basic functionalities of a mapper
 */
class PfMapperBase
{
public:
	//! A constructor.
	/*!
		Initialize a mapper 
	*/
	PfMapperBase(const string& sSrcFile, const string& sXmlFile, const string& sOutFile);

	//! A destructor.
	/*!
		Virtual destructor
	*/
	virtual 
	~PfMapperBase();

	//! A classifier identifies the type of data that we will proccess
	/*!
		\param pXmlDataNode structure
		\param buffer contains one line of code
		\return manipulated string
	*/
	const string& 
	classifier(gXmlTagData* pXmlDataNode, const string& buffer);
	
	//! Prints an information tag containing original line number and code
	/*!
     		\param lineNum original line number
     		\param lineCode original code
    		\return manipulated string
	*/
	virtual const string& 
	printTag( int lineNum, const string& lineCode );

	//! Loads an IPv4 source file
   	/*!
     		\param value IPv4 source file
     		\return void
	*/
	void 
	setSrcFile(const string& value);

	//! Loads an XML metadata file
	/*!
		\param value XML metadata file
		\return void
	*/
	void 
	setXmlFile(const string& value);

	//! Defines the name of the output IPv6 filename
	/*!
		\param value output IPv6 filename
		\return void
	*/
	void 
	setOutFile(const string& value);
	
	//! Iterate given files to produce IPv6 code
	/*!
		\return void
	*/
	void 
	iterateFiles(void);

	//! A generic function that supports simple porting
	/*!
		\param pXmlDataNode A gXmlTagData* structure
		\param buffer contains one line of code
		\param custom contains a label string, used for the interactive mode 
		\return manipulated string
	*/
	const string& 
	genericPort(gXmlTagData* pXmlDataNode, const string& buffer, const string& custom);

	//! Sets the name of the mapper
	/*!
		\param value the name of the mapper
		\return void
	*/
	void 
	setMapper(const string& value);

	//! Get the name of the mapper
	/*!
		\return the name of the mapper
	*/
	const string& 
	getMapper(void);

	//! Enable/Disable print of tag (output IPv6 file)
	/*!
		\param value true to enable, false to disable
		\return void
	*/
	void 
	setPrintTag(bool value);

	//! Internal increment of tag number
	/*!
		\return void
	*/
	void 
	incTagNumber(void);

	//! Internal decrement of tag number
	/*!
		\return void
	*/
	void 
	decTagNumber(void);

	//! Construct an IPv6 address out of an IPv4 one
	/*!
		\param ipv4Addr original ipv4 address
		\param addrType type of returned IPv6 address. 
				Select: 0 for IPv6 full address
					1 for IPv6 Shorthand address
					2 for IPv6 and dot notation full address
					3 for IPv6 and dot notation shorthand address
		\param prefixType routing prefix hex as defined in common.h
		\return string with an IPv6 address
	*/
	const string&
	convertIpv4ToIpv6(const string& ipv4Addr, short int addrType, short int prefixType);

	virtual const string& 
	portStructure(gXmlTagData* pXmlTagData, const string& buffer)
	{
		_M_buffer = classifyStructure(pXmlTagData, buffer);
		return _M_buffer;
	};

	virtual const string& 
	portFunction(gXmlTagData* pXmlTagData, const string& buffer)
	{
		_M_buffer = classifyFunction(pXmlTagData, buffer);
		return _M_buffer;
	};

	virtual const string& 
	portUrl(gXmlTagData* pXmlTagData, const string& buffer)
	{
		_M_buffer = classifyUrl(pXmlTagData, buffer);
		return _M_buffer;
	};

	virtual const string& 
	portHeaderFile(gXmlTagData* pXmlTagData, const string& buffer) 
	{ 
		_M_buffer = classifyHeader(pXmlTagData, buffer);
		return _M_buffer;
	};

	virtual const string& 
	portMacro(gXmlTagData* pXmlTagData, const string& buffer)
	{
		_M_buffer = classifyMacro(pXmlTagData, buffer);
		return _M_buffer;
	};

	virtual const string& 
	portIpv4Centric(gXmlTagData* pXmlTagData, const string& buffer) 
	{
		_M_buffer = classifyIpv4Centric(pXmlTagData, buffer);
		return _M_buffer;
	};

	virtual const string& 
	portIpv4Addr(gXmlTagData* pXmlTagData, const string& buffer) 
	{
		_M_buffer = classifyIpv4Addr(pXmlTagData, buffer);
		return _M_buffer;
	};

	//! Pure Virtual member
	virtual const string& 
	classifyFunction(gXmlTagData* pXmlDataNode, const string& buffer) = 0;

	//! Pure Virtual member
	virtual const string& 
	classifyIpv4Centric(gXmlTagData* pXmlDataNode, const string& buffer) = 0;

	//! Pure Virtual member
	virtual const string& 
	classifyMacro(gXmlTagData* pXmlDataNode, const string& buffer) = 0;

	//! Pure Virtual member
	virtual const string& 
	classifyStructure(gXmlTagData* pXmlDataNode, const string& buffer) = 0;

	//! Pure Virtual member
	virtual const string& 
	classifyHeader(gXmlTagData* pXmlDataNode, const string& buffer) = 0;

	//! Pure Virtual member
	virtual const string& 
	classifyIpv4Addr(gXmlTagData* pXmlDataNode, const string& buffer) = 0;

	//! Pure Virtual member
	virtual const string& 
	classifyUrl(gXmlTagData* pXmlDataNode, const string& buffer) = 0;

protected:
	string _M_buffer; /*!< A general purpose buffer. */

private:
	unsigned int _M_tagNum; /*!< Contains current tag number*/
	string _M_tagText; /*!< Contains current tag text*/
	string _M_mapper;  /*!< Contains the name of the mapper*/
	fstream _M_inFile; /*!< Source IPv4 file*/
	fstream _M_outFile; /*!< Destination IPv6 file*/
	char _M_lineBuffer[PF_MAX_BUFFER]; /*!< A line buffer*/
	bool _M_doPrint; /*!< Used for printing or not the tag*/
	list<gXmlTagData> _M_xmlList; /*!< Contains all XML data*/
	list<gXmlTagData>::iterator _M_xmlIterator; /*!< An iterator */
};

#include "PfMapperBase.cc"

#endif
