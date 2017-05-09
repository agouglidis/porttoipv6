/***************************************************************************
 *   Copyright (C) 2005-2017 by Antonios Gouglidis                         *
 *   e-mail: agouglidis@gmail.com                                          *
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

#ifndef _PF_COMMON_H_
#define _PF_COMMON_H_

// Definitions
/*! \def PF_ERROR 
	\brief Currently describe any error that occur
*/
#define PF_ERROR     	-1 

/*! \def PF_SUCCESS 
	\brief Describe success
*/
#define PF_SUCCESS     	0 

/*! \def PF_STRUCTURE 
	\brief The string being parsed is an IPv4 Structure 
*/
#define PF_STRUCTURE	10 

/*! \def PF_FUNCTION 
	\brief The string being parsed is an IPv4 Function 
*/
#define PF_FUNCTION	11 

/*! \def PF_IPV4ADDR 
	\brief The string being parsed is an IPv4 Address 
*/
#define PF_IPV4ADDR	12 

/*! \def PF_URL 
	\brief The string being parsed is an IPv4 URL 
*/
#define PF_URL		13 

/*! \def PF_HEADER_FILE 
	\brief The string being parsed is an IPv4 specific header file 
*/
#define PF_HEADER_FILE	14

/*! \def PF_MACRO 
	\brief The string being parsed is an IPv4 Macro 
*/
#define PF_MACRO	15

/*! \def PF_IPV4_CENTRIC 
	\brief The string being parsed doesn't belong to anyone of the above categoties.
    Use this definition to describe all other categories.
 */
#define PF_IPV4_CENTRIC	20

/*! \def PF_MAX_BUFFER 
	\brief Define PF_MAX_BUFFER 
*/
#define PF_MAX_BUFFER 1024

/*! \def PF_CHAR_BUFFER  
	\brief Define PF_CHAR_BUFFER 
*/
#define PF_CHAR_BUFFER 3

/*! \def PF_PARAMS_BUFFER 
	\brief Define PF_PARAMS_BUFFER
*/
#define PF_PARAMS_BUFFER 256

/*! \def PF_NULL
	\brief Define PF_NULL
*/
#define PF_NULL 0



/*
 *  Routing Prefixes
 */

/*! \def PF_RP_GLOBAL_UNICAST
	\brief Prefix hex: 2000::/3
*/
#define PF_RP_GLOBAL_UNICAST		0

/*! \def PF_RP_LINK_LOCAL_UNICAST
	\brief Prefix hex: FE80::/10
*/
#define PF_RP_LINK_LOCAL_UNICAST	1

/*! \def PF_RP_SITE_LOCAL_UNICAST
	\brief Prefix hex: FEC0::/10
*/
#define PF_RP_SITE_LOCAL_UNICAST	2

/*! \def PF_RP_LOCAL_IPV6_ADDRESS
	\brief Prefix hex: FC00::/7
*/
#define PF_RP_LOCAL_IPV6_ADDRESS	3

/*! \def PF_RP_PRIVATE_ADMINISTRATION
	\brief Prefix hex: FD00::/8
*/
#define PF_RP_PRIVATE_ADMINISTRATION	4

/*! \def PF_RP_MULTICAST
	\brief Prefix hex: FF00::/8
*/
#define PF_RP_MULTICAST			5

/*! \def PF_RP_TEREDO
	\brief Prefix hex: 2001:0000::/32, RFC-4380
*/
#define PF_RP_TEREDO			6

/*! \def PF_RP_6TO4
	\brief Prefix hex: 2002::/16, RFC-3056
*/
#define PF_RP_6TO4			7

/*! \def PF_RP_6BONE
	\brief Prefix hex: 3FFE::/16, RFC-2471
*/
#define PF_RP_6BONE			8

// Include files
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
using std::string;

const string& PF_NAME= "PortToIPv6"; /*!< Contains the name of the framework */
const string& PF_VERSION = "0.0.5"; /*!< Contains the version of the framework */
const string& PF_RELEASE = "Alpha"; /*!< Contains the release of the framework */

const string& PF_COMMON_VERSION = "0.0.5"; /*!< Contains the version of common{h.cpp} */
const string& PF_COPYRIGHT = "Copyright (C) 2005-2017 by Antonios Gouglidis, e-mail: agouglidis@gmail.com"; /*!< Contains the copyright text */


/*! \struct gXmlTagData
	\brief Holds all the required information of the matched pattern
*/
struct gXmlTagData	
{
	unsigned int line; /*!< The line number in which pattern was identified */
	unsigned int typeId; /*!< The id of the data type */
	string type; /*!< The string value of the data type. Resolve is made automatic by createXmlTag function */
	string name; /*!< Holds the matched pattern */
	string comment; /*!< A comment automatically generated by the scanner */
};

/*! \struct gApi
	\brief Holds all the required information for an API
*/
struct gApi
{
	bool inUse; /*!< inUse Defines if current API is in use or not */
	string name; /*!< Defines the API name */
};

std::vector<gApi> gVectorApis(PF_NULL); /*! A vector of all the available APIs */
int gActiveApi; /*! Keeps the API in use globally */

/*! \fn void setGlobalActiveApi(int apiNumber)
	\brief A function to set a global active API 
	\param apiNumber Number of API to set globally active
	\return void
*/
void setGlobalActiveApi(int apiNumber);

/*! \fn int getGlobalActiveApi(void)
	\brief A function to get the global active API 	
	\return int Number of the global active API
*/
int getGlobalActiveApi(void);

/*! \fn template <class T> string toString(T t, std::ios_base & (*f)(std::ios_base&))
	\brief Convert a dec, oct or hex number into a string
	\param t Variable holding the number
	\param f Should be one of std::hex, std::dec or std::oct
	\return The given number in string format
*/
template <class T> 
	string 
	toString(T t, std::ios_base & (*f)(std::ios_base&))
{
	std::ostringstream oss;
	oss << f << t;
	return oss.str();
};

/*! \fn const string removeString(const string& str, const string& subStr)
	\brief A function to remove a substring from a string
	\param str whole string
	\param subStr substring to remove
	\return The manipulated string
*/
const string removeString(const string& str, const string& subStr);

/*! \fn const string replaceString(const string& str, const string& removeStr, const string& replaceStr)
	\brief A function to replace a substring that exists in a string with a given substring
	\param str string
	\param removeStr Substring to remove
	\param replaceStr Substring to replace with
	\return The manipulated string
*/
const string replaceString(const string& str, const string& removeStr, const string& replaceStr);

/*! \fn bool findString(const string& str, const string& subStr)
	\brief A function to check if a given substring exists in a string
	\param str whole string
	\param subStr substing
	\return True if subStr is a substring of str. False if subStr is absent.
*/
bool findString(const string& str, const string& subStr);

#endif

#include "common.cc"