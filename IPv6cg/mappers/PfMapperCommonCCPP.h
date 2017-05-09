/***************************************************************************
 *   Copyright (C) 2005-2017 by Antonios Gouglidis						   *
 *   e-mail: agouglidis@gmail.com   									   *
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

#ifndef _PF_MAPPER_COMMON_CCPP_H_
#define _PF_MAPPER_COMMON_CCPP_H_

#include <iostream>
#include <string>
#include <fstream>
using std::fstream;

#include "../../include/common.h"
#include "../../tinyxml/tinyxml.h"

#include "PfMapperBase.h"

//! The C/C++ mapper class
/*!
	The PfMapperCommonCCPP class implements common C/C++ IPv6 mappings
 */
class PfMapperCommonCCPP : public PfMapperBase
{
public:
	PfMapperCommonCCPP(const string sSrcFile, const string sXmlFile, const string sOutFile)
	: PfMapperBase(sSrcFile, sXmlFile, sOutFile)
	{ setMapper("C/C++ Common Mapper"); }

	~PfMapperCommonCCPP();

	virtual const string& 
	classifyStructure(gXmlTagData* pXmlTagData, const string& buffer);

	virtual const string& 
	classifyMacro(gXmlTagData* pXmlTagData, const string& buffer);

	virtual const string& 
	classifyIpv4Centric(gXmlTagData* pXmlTagData, const string& buffer);

	virtual const string& 
	classifyFunction(gXmlTagData* pXmlTagData, const string& buffer);

	virtual const string& 
	classifyHeader(gXmlTagData* pXmlTagData, const string& buffer);

	virtual const string& 
	classifyIpv4Addr(gXmlTagData* pXmlTagData, const string& buffer);

	virtual const string& 
	classifyUrl(gXmlTagData* pXmlTagData, const string& buffer);

	const string& 
	port_gethostbyname(gXmlTagData* pXmlTagData, const string& buffer);
	
	const string& 
	port_gethostbyaddr(gXmlTagData* pXmlTagData, const string& buffer);	
	
};

#include "PfMapperCommonCCPP.cc"

#endif
