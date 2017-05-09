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

#ifndef _PF_MAPPER_COMMON_CCPP_CC_
#define _PF_MAPPER_COMMON_CCPP_CC_

PfMapperCommonCCPP::~PfMapperCommonCCPP(){};

const string& 
PfMapperCommonCCPP::classifyStructure(gXmlTagData* pXmlTagData, const string& buffer)
{
	if (findString(pXmlTagData->name, "sockaddr_in"))
	{
		char _choise[PF_CHAR_BUFFER];
		short int _selection;

		std::cout << "\nIdentified at line: " << (pXmlTagData->line);
		std::cout << "\nChange " << (pXmlTagData->name) << " with:";
		std::cout << "\n(0) an IPv6 only stucture (Default)";
		std::cout << "\n(1) a protocol independent structure";
		std::cout << "\nSelect:";
		std::cin.getline(_choise, PF_CHAR_BUFFER);	
		
		_selection = atoi(_choise);
		
		switch (_selection)
		{
		case 0:
			_M_buffer = replaceString(buffer, "sockaddr_in", "sockaddr_in6");
			break;
		case 1:
			_M_buffer = replaceString(buffer, "sockaddr_in", "sockaddr_storage");
			break;
		default:
			_M_buffer = replaceString(buffer, "sockaddr_in", "sockaddr_in6");
		}
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "sockaddr"))
	{
		char _choise[PF_CHAR_BUFFER];
		short int _selection;

		std::cout << "\nIdentified at line: " << (pXmlTagData->line);
		std::cout << "\nChange " << (pXmlTagData->name) << " with:";
		std::cout << "\n(0) an IPv6 only stucture";
		std::cout << "\n(1) a protocol independent structure";
		std::cout << "\n(2) leave generic socket as is (Default)";
		std::cout << "\nSelect:";
		std::cin.getline(_choise, PF_CHAR_BUFFER);
		
		_selection = atoi(_choise);

		switch (_selection)
		{
		case 0:
			_M_buffer = replaceString(buffer, "sockaddr", "sockaddr_in6");
			break;
		case 1:
			_M_buffer = replaceString(buffer, "sockaddr", "sockaddr_storage");
			break;
		case 2:
			_M_buffer = buffer;
			break;
		default:
			_M_buffer = buffer;
		}
		return _M_buffer;
	};

	if (findString( pXmlTagData->name, "in_addr"))
	{
		_M_buffer = replaceString(buffer, "in_addr", "in6_addr");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "ip_mreq"))
	{
		_M_buffer = replaceString(buffer, "ip_mreq", "ipv6_mreq");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "hostent"))
	{
		_M_buffer = replaceString(buffer, "hostent", "addrinfo");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "PHOSTENT"))
	{
		_M_buffer = replaceString(buffer, "PHOSTENT", "LPADDRINFO");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "HOSTENT"))
	{
		_M_buffer = replaceString(buffer, "HOSTENT", "ADDRINFO");
		return _M_buffer;
	};

	_M_buffer = "\n" + getMapper() + ": ClassifyStructure: No match\n";
	return _M_buffer;
};

const string& 
PfMapperCommonCCPP::classifyMacro(gXmlTagData* pXmlTagData, const string& buffer)
{
	if (findString(pXmlTagData->name, "AF_INET"))
	{
		_M_buffer = replaceString(buffer, "AF_INET", "AF_INET6");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "PF_INET"))
	{
		_M_buffer = replaceString(buffer, "PF_INET", "PF_INET6");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "INADDR_ANY"))
	{
		_M_buffer = replaceString(buffer, "INADDR_ANY", "in6addr_any");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "INADDR_LOOPBACK"))
	{
		_M_buffer = replaceString(buffer, "INADDR_LOOPBACK", "in6addr_loopback");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "IP_MULTICAST_IF"))
	{
		_M_buffer = replaceString(buffer, "IP_MULTICAST_IF", "IPV6_MULTICAST_IF");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "IP_MULTICAST_LOOP"))
	{
		_M_buffer = replaceString(buffer, "IP_MULTICAST_LOOP", "IPV6_MULTICAST_LOOP");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "IP_ADD_MEMBERSHIP"))
	{
		_M_buffer = replaceString(buffer, "IP_ADD_MEMBERSHIP", "IPV6_ADD_MEMBERSHIP");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "IP_DROP_MEMBERSHIP"))
	{
		_M_buffer = replaceString(buffer, "IP_DROP_MEMBERSHIP", "IPV6_DROP_MEMBERSHIP");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "IP_MULTICAST_TTL"))
	{
		_M_buffer = replaceString(buffer, "IP_MULTICAST_TTL", "IPV6_MULTICAST_HOPS");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "IN_CLASSD"))
	{
		_M_buffer = replaceString(buffer, "IN_CLASSD", "IN6_IS_ADDR_MULTICAST");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "IN_MULTICAST"))
	{
		_M_buffer = replaceString(buffer, "IN_MULTICAST", "IN6_IS_ADDR_MULTICAST");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "IP_TTL"))
	{
		_M_buffer = replaceString(buffer, "IP_TTL", "IPV6_UNICAST_HOPS");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "IPPROTO_IP"))
	{
		_M_buffer = replaceString(buffer, "IPPROTO_IP", "IPPROTO_IPV6");
		return _M_buffer;
	};

	_M_buffer = "\n" + getMapper() + ": ClassifyMacro: No match\n";
	return _M_buffer;
};

const string& 
PfMapperCommonCCPP::classifyIpv4Centric(gXmlTagData* pXmlTagData, const string& buffer)
{
	if (findString(pXmlTagData->name, "sin_" ))
	{
		_M_buffer = replaceString(buffer, "sin_", "sin6_");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "h_addrtype" ))
	{
		_M_buffer = replaceString(buffer, "h_addrtype", "ai_family");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "h_name" ))
	{
		_M_buffer = replaceString(buffer, "h_name", "ai_canonname");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "IPAddr" ))
	{
		_M_buffer = replaceString(buffer, "IPAddr", "SOCKADDR_STORAGE");
		return _M_buffer;
	};

	_M_buffer = "\n" + getMapper() + ": ClassifyIpv4Centric: No match\n";
	return _M_buffer;
};

const string&
PfMapperCommonCCPP::classifyUrl(gXmlTagData* pXmlTagData, const string& buffer)
{
	return (genericPort(pXmlTagData, buffer, "url"));
};

const string& 
PfMapperCommonCCPP::classifyFunction(gXmlTagData* pXmlTagData, const string& buffer)
{
	if (findString( pXmlTagData->name, "gethostbyname"))
	{
		_M_buffer = port_gethostbyname(pXmlTagData, buffer);
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "gethostbyaddr"))
	{
		_M_buffer = port_gethostbyaddr(pXmlTagData, buffer);
		return _M_buffer;
	};

	_M_buffer = "\n" + getMapper() + ": ClassifyFunction: No match\n";
	return _M_buffer;
};

const string& 
PfMapperCommonCCPP::classifyHeader(gXmlTagData* pXmlTagData, const string& buffer)
{
	_M_buffer = "\n" + getMapper() + ": ClassifyHeader: No match\n";
	return _M_buffer;
};

const string& 
PfMapperCommonCCPP::classifyIpv4Addr(gXmlTagData* pXmlTagData, const string& buffer)
{
	using namespace std;

	char _choise[PF_CHAR_BUFFER];
	char _ipv6Addr[PF_MAX_BUFFER];
	short int _prefix = 0;
	short int _addrtype = 0;

	cout << "\nIdentified at line: " << (pXmlTagData->line);
	cout << "\nIPv4 address: " << (pXmlTagData->name); 

	cout << "\n\t(0) Global unicast address [2000::/3] (Default)";
	cout << "\n\t(1) Link-local unicast address [fe80::/10]";
	cout << "\n\t(2) Site-local unicast address [fec0::/10]";
	cout << "\n\t(3) Local IPv6 address [fc00::/7]";
	cout << "\n\t(4) Private administration [fd00::/8]";
	cout << "\n\t(5) Multicast address [ff00::/8]";
	cout << "\n\t(6) Teredo [2001:0000::/32]";
	cout << "\n\t(7) 6to4 [2002::/16]";
	cout << "\n\t(8) 6Bone [3ffe::/16]";
	cout << "\n\t(9) None of the above";
	cout << "\nSelect prefix type:";
	cin.getline(_choise, PF_CHAR_BUFFER);
	
	_prefix = atoi(_choise);

	cout << "\n\t(0) for IPv6 full address: " << convertIpv4ToIpv6(pXmlTagData->name, 0 , _prefix) << " (Default)";
	cout << "\n\t(1) for IPv6 shorthand address: " << convertIpv4ToIpv6(pXmlTagData->name, 1 , _prefix);
	cout << "\n\t(2) for IPv6 dot notation full address: " << convertIpv4ToIpv6(pXmlTagData->name, 2, _prefix);
	cout << "\n\t(3) for IPv6 dot notation shorthand address: " << convertIpv4ToIpv6(pXmlTagData->name, 3, _prefix);
	cout << "\n\t(4) enter a user defined ipv6 address";
	cout << "\nSelect:";
	cin.getline(_choise, PF_CHAR_BUFFER);

	_addrtype = atoi(_choise);

	if  ((_addrtype >= 0) && (_addrtype <=3))
	{
		_M_buffer = convertIpv4ToIpv6(pXmlTagData->name, _addrtype, _prefix);
	}	
	else if (_addrtype == 4)
	{
		cout << "\nEnter IPv6 address:";
		cin.getline(_ipv6Addr, PF_MAX_BUFFER);
		_M_buffer = _ipv6Addr;
	}
	else
	{ 
		_M_buffer = pXmlTagData->name;
	}
	return _M_buffer;
};

const string& 
PfMapperCommonCCPP::port_gethostbyname(gXmlTagData* pXmlTagData, const string& buffer)
{
	using namespace std;

	char _nodename[PF_PARAMS_BUFFER];
	char _servname[PF_PARAMS_BUFFER];
	char _hints[PF_PARAMS_BUFFER];
	char _res[PF_PARAMS_BUFFER];

	cout << "\nIdentified at line: " << (pXmlTagData->line);
	cout << "\nIPv4 code: " << buffer;
	cout << "\nDeclare new parameter names: ";
	cout << "\n\tconst char* nodename: ";
	cin.getline(_nodename, PF_PARAMS_BUFFER);
	cout << "\tconst char* servname: ";
	cin.getline(_servname, PF_PARAMS_BUFFER);
	cout << "\tconst struct addrinfo* hints: ";
	cin.getline(_hints, PF_PARAMS_BUFFER);
	cout << "\tstruct addrinfo** res: ";
	cin.getline(_res, PF_PARAMS_BUFFER);

	/* Prepare getaddrinfo */
	string codeFunction = "";
	codeFunction += "getaddrinfo( ";
	codeFunction += _nodename;
	codeFunction += ", ";
	codeFunction += _servname;
	codeFunction += ", &";
	codeFunction += _hints;
	codeFunction += ", &";
	codeFunction += _res;
	codeFunction += " );";

	/* Prepare variables */
	string codeVars= "\n\t/* Automatic generated variables */\n\tstruct addrinfo ";
	
	codeVars += _hints;
	codeVars += ", *";
	codeVars += _res; 
	codeVars += ", *AI; /* Use AI to iterate onto struct addrinfo */\n\tint retValue; /* Use this variable to get getaddrinfo result */\n\n";

	codeVars += "\tmemset(&";
	codeVars += _hints;
	codeVars += ", 0, sizeof(";
	codeVars += _hints;
	codeVars += "));\n\n\t/* Support of both IPv4 and IPv6 addresses. */\n\t";

	codeVars += _hints;
	codeVars += ".ai_family = PF_UNSPEC;\n\t/* Uncomment the following line to support STREAM SOCKETS */\n\t//";
	codeVars += _hints;
	codeVars += ".ai_socktype = SOCK_STREAM;\n\t";
	codeVars += _hints;
	codeVars += ".ai_protocol = IPPROTO_TCP;\n\t/* Uncomment the following line to support name resolving */\n\t//";
	codeVars += _hints;
	codeVars += ".ai_flags = AI_CANONNAME | AI_NUMERICHOST ;";
	codeVars += "\n\tconst char *";
	codeVars += _nodename;
	codeVars += ", ";
	codeVars += _servname;
	codeVars += ";";

	/* Prepare IPv6 code */
	string codeIpv6 = "";
	codeIpv6 += codeVars;
	codeIpv6 += "\n\n\tretValue = ";
	codeIpv6 += codeFunction;

	codeIpv6 += "\n\n\tfreeaddrinfo (";
	codeIpv6 += _res;
	codeIpv6 += ");";

	_M_buffer = replaceString(buffer, buffer, codeIpv6); 
	return _M_buffer;
};

const string& 
PfMapperCommonCCPP::port_gethostbyaddr(gXmlTagData* pXmlTagData, const string& buffer)
{
	using namespace std;

	char _sa[PF_PARAMS_BUFFER];
	char _salen[PF_PARAMS_BUFFER];
	char _host[PF_PARAMS_BUFFER];
	char _hostlen[PF_PARAMS_BUFFER];
	char _serv[PF_PARAMS_BUFFER];
	char _servlen[PF_PARAMS_BUFFER];
	char _flags[PF_PARAMS_BUFFER];

	cout << "\nIdentified at line: " << (pXmlTagData->line);
	cout << "\nIPv4 code: " << buffer;
	cout << "\nDeclare new parameter names: ";
	cout << "\n\tconst struct sockaddr* sa: ";
	cin.getline(_sa, PF_PARAMS_BUFFER);
	cout << "\tsize_t salen: ";
	cin.getline(_salen, PF_PARAMS_BUFFER);
	cout << "\tchar* host: ";
	cin.getline(_host, PF_PARAMS_BUFFER);
	cout << "\tsize_t hostlen: ";
	cin.getline(_hostlen, PF_PARAMS_BUFFER);
	cout << "\tchar* serv: ";
	cin.getline(_serv, PF_PARAMS_BUFFER);
	cout << "\tsize_t servlen: ";
	cin.getline(_servlen, PF_PARAMS_BUFFER);
	cout << "\tint flags: ";
	cin.getline(_flags, PF_PARAMS_BUFFER);

	/* Prepare getnameinfo */
	string codeFunction = "getnameinfo( ";
	codeFunction += _sa;
	codeFunction += ", ";
	codeFunction += _salen;
	codeFunction += ", ";
	codeFunction += _host;
	codeFunction += ", ";
	codeFunction += _hostlen;
	codeFunction += ", ";
	codeFunction += _serv;
	codeFunction += ", ";
	codeFunction += _servlen;
	codeFunction += ", ";
	codeFunction += _flags;
	codeFunction += " );";

	/* Prepare variables */
	string codeVars = "\n\t/* Automatic generated variables */\n\tconst struct sockaddr *";
	codeVars += _sa;
	codeVars += ";";
	codeVars += "\n\tsize_t ";
	codeVars += _salen;
	codeVars += ", ";
	codeVars += _hostlen;
	codeVars += ", ";
	codeVars += _servlen;
	codeVars += ";";
	codeVars += "\n\tchar ";
	codeVars += _host;
	codeVars += ", ";
	codeVars += _serv;
	codeVars += ";";
	codeVars += "\n\tint retValue, ";
	codeVars += _flags;
	codeVars += ";";

	/* Prepare IPv6 code */
	string codeIpv6 = "";
	codeIpv6 += codeVars;
	codeIpv6 += "\n\n\tretValue = ";
	codeIpv6 += codeFunction;

	_M_buffer = replaceString(buffer, buffer, codeIpv6); 
	return _M_buffer;
};

#endif
