/***************************************************************************
 *   Copyright (C) 2005-2017 by Antonios Gouglidis						   *
 *   e-mail: agouglidis@gmail.com   					 				   *
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

#ifndef _PF_MAPPER_WINSOCK_CC_
#define _PF_MAPPER_WINSOCK_CC_

PfMapperWinsock::~PfMapperWinsock(){};

const string& 
PfMapperWinsock::classifyStructure(gXmlTagData* pXmlTagData, const string& buffer)
{
	if (findString(pXmlTagData->name, "SOCKADDR_IN"))
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
			_M_buffer = replaceString(buffer, "SOCKADDR_IN", "SOCKADDR_IN6");
			break;
		case 1:
			_M_buffer = replaceString(buffer, "SOCKADDR_IN", "SOCKADDR_STORAGE");
			break;
		default:
			_M_buffer = replaceString(buffer, "SOCKADDR_IN", "SOCKADDR_IN6");
		}
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "IP_ADAPTER_INFO"))
	{
		char _choise[PF_CHAR_BUFFER];
		short int _selection;

		std::cout << "\nIdentified at line: " << (pXmlTagData->line);
		std::cout << "\nChange " << (pXmlTagData->name) << " with:";
		std::cout << "\n(0) IP_ADAPTER_ADDRESS (Default)";
		std::cout << "\n(1) IP_ADAPTER_ADDRESSES";
		std::cout << "\nSelect:";
		std::cin.getline(_choise, PF_CHAR_BUFFER);
		
		_selection = atoi(_choise);

		switch (_selection)
		{
		case 0:
			_M_buffer = replaceString(buffer, "IP_ADAPTER_INFO", "IP_ADAPTER_ADDRESS");
			break;
		case 1:
			_M_buffer = replaceString(buffer, "IP_ADAPTER_INFO", "IP_ADAPTER_ADDRESSES");
			break;
		default:
			_M_buffer = replaceString(buffer, "IP_ADAPTER_INFO", "IP_ADAPTER_ADDRESS");
		}
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "LPSOCKADDR_IN"))
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
			_M_buffer = replaceString(buffer, "LPSOCKADDR_IN", "LPSOCKADDR_IN6");
			break;
		case 1:
			_M_buffer = replaceString(buffer, "LPSOCKADDR_IN", "LPSOCKADDR_STORAGE");
			break;
		default:
			_M_buffer = replaceString(buffer, "LPSOCKADDR_IN", "LPSOCKADDR_IN6");
		}
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "PSOCKADDR_IN"))
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
			_M_buffer = replaceString(buffer, "PSOCKADDR_IN", "PSOCKADDR_IN6");
			break;
		case 1:
			_M_buffer = replaceString(buffer, "PSOCKADDR_IN", "PSOCKADDR_STORAGE");
			break;
		default:
			_M_buffer = replaceString(buffer, "PSOCKADDR_IN", "PSOCKADDR_IN6");
		}
		return _M_buffer;
	};

	if (findString( pXmlTagData->name, "LPIN_ADDR"))
	{
		_M_buffer = replaceString(buffer, "LPIN_ADDR", "LPIN6_ADDR");
		return _M_buffer;
	};

	if (findString( pXmlTagData->name, "PIN_ADDR"))
	{
		_M_buffer = replaceString(buffer, "PIN_ADDR", "PIN6_ADDR");
		return _M_buffer;
	};

	if (findString(pXmlTagData->name, "LPHOSTENT"))
	{
		_M_buffer = replaceString(buffer, "LPHOSTENT", "LPADDRINFO");
		return _M_buffer;
	};

	return (PfMapperCommonCCPP::classifyStructure(pXmlTagData, buffer));
};

const string& 
PfMapperWinsock::classifyFunction(gXmlTagData* pXmlTagData, const string& buffer)
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

	if (findString(pXmlTagData->name, "GetAdaptersInfo"))
	{
		_M_buffer = port_GetAdaptersInfo(pXmlTagData, buffer);
		return _M_buffer;
	};

	return (PfMapperCommonCCPP::classifyFunction(pXmlTagData, buffer));
};

const string& 
PfMapperWinsock::classifyHeader(gXmlTagData* pXmlTagData, const string& buffer)
{
	if (findString( pXmlTagData->name, "winsock.h"))
	{
		_M_buffer = replaceString(buffer, "winsock.h", "winsock2.h");
		return _M_buffer;
	};

	return (PfMapperCommonCCPP::classifyHeader(pXmlTagData, buffer));
};

const string& 
PfMapperWinsock::port_inet_ntoa(gXmlTagData* pXmlTagData, const string& buffer)
{
	using namespace std;

	char _lpsaAddress[PF_PARAMS_BUFFER];
	char _dwAddressLength[PF_PARAMS_BUFFER];
	char _lpProtocolInfo[PF_PARAMS_BUFFER];
	char _lpszAddressString[PF_PARAMS_BUFFER];
	char _lpdwAddressStringLength[PF_PARAMS_BUFFER];

	cout << "\nIdentified at line: " << (pXmlTagData->line);
	cout << "\nIPv4 code: " << buffer;
	cout << "\nDeclare new parameter names: ";
	cout << "\n\tLPSOCKADDR lpsaAddress: ";
	cin.getline(_lpsaAddress, PF_PARAMS_BUFFER);
	cout << "\tDWORD dwAddressLength: ";
	cin.getline(_dwAddressLength, PF_PARAMS_BUFFER);
	cout << "\tLPWSAPROTOCOL_INFO lpProtocolInfo: ";
	cin.getline(_lpProtocolInfo, PF_PARAMS_BUFFER);
	cout << "\tLPTSTR lpszAddressString: ";
	cin.getline(_lpszAddressString, PF_PARAMS_BUFFER);
	cout << "\tLPDWORD lpdwAddressStringLength: ";
	cin.getline(_lpdwAddressStringLength, PF_PARAMS_BUFFER);

	/* Prepare inet_ntop */
	string codeFunction = "WSAAddressToString( ";
	codeFunction += _lpsaAddress;
	codeFunction += ", ";
	codeFunction += _dwAddressLength;
	codeFunction += ", ";
	codeFunction += _lpProtocolInfo;
	codeFunction += ", ";
	codeFunction += _lpszAddressString;
	codeFunction += ", ";
	codeFunction += _lpdwAddressStringLength;
	codeFunction += " );";

	/* Prepare variables */
	string codeVars = "\n\t/* Automatic generated variables */\n\tLPSOCKADDR ";
	codeVars += _lpsaAddress;
	codeVars += ";";
	codeVars += "\n\tDWORD ";
	codeVars += _dwAddressLength;
	codeVars += ";\n\tLPWSAPROTOCOL_INFO ";
	codeVars += _lpProtocolInfo;
	codeVars += ";\n\tLPTSTR ";
	codeVars += _lpszAddressString;
	codeVars += ";";
	codeVars += ";\n\tLPDWORD ";
	codeVars += _lpdwAddressStringLength;
	codeVars += ";";
	codeVars += "\n\tINT retValue;";

	/* Prepare IPv6 code */
	string codeIpv6 = "";
	codeIpv6 += codeVars;
	codeIpv6 += "\n\n\tretValue = ";
	codeIpv6 += codeFunction;

	_M_buffer = replaceString(buffer, buffer, codeIpv6); 
	return _M_buffer;
};

const string& 
PfMapperWinsock::port_inet_addr(gXmlTagData* pXmlTagData, const string& buffer)
{
	using namespace std;

	char _AddressString[PF_PARAMS_BUFFER];
	char _AddressFamily[PF_PARAMS_BUFFER];
	char _lpProtocolInfo[PF_PARAMS_BUFFER];
	char _lpAddress[PF_PARAMS_BUFFER];
	char _lpAddressLength[PF_PARAMS_BUFFER];

	cout << "\nIdentified at line: " << (pXmlTagData->line);
	cout << "\nIPv4 code: " << buffer;
	cout << "\nDeclare new parameter names: ";
	cout << "\n\tLPTSTR AddressString: ";
	cin.getline(_AddressString, PF_PARAMS_BUFFER);
	cout << "\tINT AddressFamily: ";
	cin.getline(_AddressFamily, PF_PARAMS_BUFFER);
	cout << "\tLPWSAPROTOCOL_INFO lpProtocolInfo: ";
	cin.getline(_lpProtocolInfo, PF_PARAMS_BUFFER);
	cout << "\tLPSOCKADDR lpAddress: ";
	cin.getline(_lpAddress, PF_PARAMS_BUFFER);
	cout << "\tLPINT lpAddressLength: ";
	cin.getline(_lpAddressLength, PF_PARAMS_BUFFER);

	/* Prepare inet_ntop */
	string codeFunction = "WSAStringToAddress( ";
	codeFunction += _AddressString;
	codeFunction += ", ";
	codeFunction += _AddressFamily;
	codeFunction += ", ";
	codeFunction += _lpProtocolInfo;
	codeFunction += ", ";
	codeFunction += _lpAddress;
	codeFunction += ", ";
	codeFunction += _lpAddressLength;
	codeFunction += " );";

	/* Prepare variables */
	string codeVars = "\n\t/* Automatic generated variables */\n\tLPTSTR ";
	codeVars += _AddressString;
	codeVars += ";";
	codeVars += "\n\tINT ";
	codeVars += _AddressFamily;
	codeVars += ";\n\tLPWSAPROTOCOL_INFO ";
	codeVars += _lpProtocolInfo;
	codeVars += ";\n\tLPSOCKADDR ";
	codeVars += _lpAddress;
	codeVars += ";";
	codeVars += ";\n\tLPINT ";
	codeVars += _lpAddressLength;
	codeVars += ";";
	codeVars += "\n\tINT retValue;";

	/* Prepare IPv6 code */
	string codeIpv6 = "";
	codeIpv6 += codeVars;
	codeIpv6 += "\n\n\tretValue = ";
	codeIpv6 += codeFunction;

	_M_buffer = replaceString(buffer, buffer, codeIpv6); 
	return _M_buffer;
};


const string& 
PfMapperWinsock::port_GetAdaptersInfo(gXmlTagData* pXmlTagData, const string& buffer)
{
	using namespace std;

	char _Family[PF_PARAMS_BUFFER];
	char _Flags[PF_PARAMS_BUFFER];
	char _Reserved[PF_PARAMS_BUFFER];
	char _AdapterAddresses[PF_PARAMS_BUFFER];
	char _SizePointer[PF_PARAMS_BUFFER];

	cout << "\nIdentified at line: " << (pXmlTagData->line);
	cout << "\nIPv4 code: " << buffer;
	cout << "\nDeclare new parameter names: ";
	cout << "\n\tULONG Family: ";
	cin.getline(_Family, PF_PARAMS_BUFFER);
	cout << "\tULONG Flags: ";
	cin.getline(_Flags, PF_PARAMS_BUFFER);
	cout << "\tPVOID Reserved: ";
	cin.getline(_Reserved, PF_PARAMS_BUFFER);
	cout << "\tPIP_ADAPTER_ADDRESSES AdapterAddresses: ";
	cin.getline(_AdapterAddresses, PF_PARAMS_BUFFER);
	cout << "\tPULONG SizePointer: ";
	cin.getline(_SizePointer, PF_PARAMS_BUFFER);

	/* Prepare inet_ntop */
	string codeFunction = "GetAdaptersAddresses( ";
	codeFunction += _Family;
	codeFunction += ", ";
	codeFunction += _Flags;
	codeFunction += ", ";
	codeFunction += _Reserved;
	codeFunction += ", ";
	codeFunction += _AdapterAddresses;
	codeFunction += ", ";
	codeFunction += _SizePointer;
	codeFunction += " );";

	/* Prepare variables */
	string codeVars = "\n\t/* Automatic generated variables */\n\tULONG ";
	codeVars += _Family;
	codeVars += ";";
	codeVars += "\n\tULONG ";
	codeVars += _Flags;
	codeVars += ";\n\tPVOID ";
	codeVars += _Reserved;
	codeVars += ";\n\tPIP_ADAPTER_ADDRESSES ";
	codeVars += _AdapterAddresses;
	codeVars += ";";
	codeVars += ";\n\tPULONG ";
	codeVars += _SizePointer;
	codeVars += ";";
	codeVars += "\n\tULONG retValue;";

	/* Prepare IPv6 code */
	string codeIpv6 = "";
	codeIpv6 += codeVars;
	codeIpv6 += "\n\n\tretValue = ";
	codeIpv6 += codeFunction;

	_M_buffer = replaceString(buffer, buffer, codeIpv6); 
	return _M_buffer;
};

#endif

