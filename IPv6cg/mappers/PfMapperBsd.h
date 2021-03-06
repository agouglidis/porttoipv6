/***************************************************************************
 *   Copyright (C) 2005-2017 by Antonios Gouglidis			   			   *
 *   e-mail: agouglidis@gmail.com   					      			   *
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

#ifndef _PF_MAPPER_BSD_H_
#define _PF_MAPPER_BSD_H_

#include <iostream>
#include <string>
#include <fstream>
using std::fstream;

#include "../../include/common.h"
#include "../../tinyxml/tinyxml.h"

#include "PfMapperCommonCCPP.h"

//! The BSD mapper class
/*!
	The PfMapperBsd class implements IPv6 mappings for BSD sockets
 */
class PfMapperBsd : public PfMapperCommonCCPP
{
public:
	PfMapperBsd(const string sSrcFile, const string sXmlFile, const string sOutFile)
	: PfMapperCommonCCPP(sSrcFile, sXmlFile, sOutFile)
	{ setMapper("BSD Mapper"); }

	~PfMapperBsd();

	virtual const string& 
	classifyFunction(gXmlTagData* pXmlTagData, const string& buffer);

	const string& 
	port_inet_ntoa(gXmlTagData* pXmlTagData, const string& buffer);
	
	const string& 
	port_inet_addr(gXmlTagData* pXmlTagData, const string& buffer);

	const string& 
	port_inet_aton(gXmlTagData* pXmlTagData, const string& buffer);
};

#include "PfMapperBsd.cc"

#endif
