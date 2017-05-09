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

#ifndef _PF_MAPPER_BSD_CC_
#define _PF_MAPPER_BSD_CC_

PfMapperBsd::~PfMapperBsd(){};

const string& 
PfMapperBsd::classifyFunction(gXmlTagData* pXmlTagData, const string& buffer)
{
	if (findString(pXmlTagData->name, "inet_ntoa"))
	{
		_M_buffer = port_inet_ntoa(pXmlTagData, buffer);
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "inet_addr"))
	{
		_M_buffer = port_inet_addr(pXmlTagData, buffer);
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "inet_aton"))
	{
		_M_buffer = port_inet_aton(pXmlTagData, buffer);
		return _M_buffer;
	};

	return (PfMapperCommonCCPP::classifyFunction(pXmlTagData, buffer));
};

const string& 
PfMapperBsd::port_inet_ntoa(gXmlTagData* pXmlTagData, const string& buffer)
{
	using namespace std;

	char _af[PF_PARAMS_BUFFER];
	char _src[PF_PARAMS_BUFFER];
	char _dst[PF_PARAMS_BUFFER];
	char _size[PF_PARAMS_BUFFER];

	cout << "\nIdentified at line: " << (pXmlTagData->line);
	cout << "\nIPv4 code: " << buffer;
	cout << "\nDeclare new parameter names: ";
	cout << "\n\tint af: ";
	cin.getline(_af, PF_PARAMS_BUFFER);
	cout << "\tconst void* src: ";
	cin.getline(_src, PF_PARAMS_BUFFER);
	cout << "\tchar* dst: ";
	cin.getline(_dst, PF_PARAMS_BUFFER);
	cout << "\tsize_t size: ";
	cin.getline(_size, PF_PARAMS_BUFFER);

	/* Prepare inet_ntop */
	string codeFunction = "inet_ntop( ";
	codeFunction += _af;
	codeFunction += ", ";
	codeFunction += _src;
	codeFunction += ", ";
	codeFunction += _dst;
	codeFunction += ", ";
	codeFunction += _size;
	codeFunction += " );";

	/* Prepare variables */
	string codeVars = "\n\t/* Automatic generated variables */\n\tint ";
	codeVars += _af;
	codeVars += ";";
	codeVars += "\n\tconst void* ";
	codeVars += _src;
	codeVars += ";\n\tchar* ";
	codeVars += _dst;
	codeVars += ";\n\tsize_t ";
	codeVars += _size;
	codeVars += ";";
	codeVars += "\n\tconst char* retValue;";

	/* Prepare IPv6 code */
	string codeIpv6 = "";
	codeIpv6 += codeVars;
	codeIpv6 += "\n\n\tretValue = ";
	codeIpv6 += codeFunction;

	_M_buffer = replaceString(buffer, buffer, codeIpv6); 
	return _M_buffer;
};

const string& 
PfMapperBsd::port_inet_addr(gXmlTagData* pXmlTagData, const string& buffer)
{
	using namespace std;

	char _af[PF_PARAMS_BUFFER];
	char _src[PF_PARAMS_BUFFER];
	char _dst[PF_PARAMS_BUFFER];

	cout << "\nIdentified at line: " << (pXmlTagData->line);
	cout << "\nIPv4 code: " << buffer;
	cout << "\nDeclare new parameter names: ";
	cout << "\n\tint af: ";
	cin.getline(_af, PF_PARAMS_BUFFER);
	cout << "\tconst char* src: ";
	cin.getline(_src, PF_PARAMS_BUFFER);
	cout << "\tvoid* dst: ";
	cin.getline(_dst, PF_PARAMS_BUFFER);

	/* Prepare inet_pton */
	string codeFunction = "inet_pton( ";
	codeFunction += _af;
	codeFunction += ", ";
	codeFunction += _src;
	codeFunction += ", ";
	codeFunction += _dst;
	codeFunction += " );";

	/* Prepare variables */
	string codeVars = "\n\t/* Automatic generated variables */\n\tint ";
	codeVars += _af;
	codeVars += ";";
	codeVars += "\n\tconst char* ";
	codeVars += _src;
	codeVars += ";\n\tvoid* ";
	codeVars += _dst;
	codeVars += ";";
	codeVars += "\n\tint retValue;";

	/* Prepare IPv6 code */
	string codeIpv6 = "";
	codeIpv6 += codeVars;
	codeIpv6 += "\n\n\tretValue = ";
	codeIpv6 += codeFunction;

	_M_buffer = replaceString(buffer, buffer, codeIpv6); 
	return _M_buffer;
};

const string& 
PfMapperBsd::port_inet_aton(gXmlTagData* pXmlTagData, const string& buffer)
{
	return (this->port_inet_addr(pXmlTagData, buffer));
}

#endif
