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

#ifndef _PF_MAPPER_BASE_CC_
#define _PF_MAPPER_BASE_CC_

PfMapperBase::PfMapperBase(const string& sSrcFile, const string& sXmlFile, const string& sOutFile)
{
	_M_tagNum = 0;
	setPrintTag(true);
	setMapper("Base Mapper");
	setSrcFile(sSrcFile);
	setOutFile(sOutFile);
	setXmlFile(sXmlFile);
}

void 
PfMapperBase::setSrcFile(const string& value)
{
	/*
	 * Open the ipv4 source file for reading
	 */
	try 
	{
		_M_inFile.open(value.c_str(), std::ios::in);
		if (!_M_inFile)
		{
			throw (PF_ERROR);
		}
	}
	catch (int errorNum)
	{
		std::cerr << "\n" << _M_mapper <<" encounter an error: cannot load source file:" << value << "\n"; 
		_M_inFile.close();
		exit (errorNum);
	}
};

void 
PfMapperBase::setXmlFile(const string& value)
{
	/*
	 * Load the XML metadata file
	 */
	TiXmlDocument doc(value); 

	doc.SetCondenseWhiteSpace(false); // DO NOT CONDENSE WHITESPACE !!! See TinyXml for more information

	bool loadOkay = doc.LoadFile();
	if (!loadOkay)
	{
		std::cerr << "\n" << _M_mapper <<" encounter an error: cannot load xml file:" << value << "\n"; 
		exit (PF_ERROR);
	};

	TiXmlHandle docHandle(&doc);
	TiXmlElement* rulesAttr = docHandle.FirstChild("ipv4_metadata").Child(0).Element();
	
	for(rulesAttr; rulesAttr; rulesAttr=rulesAttr->NextSiblingElement())
	{
		TiXmlElement* ruleAttr = rulesAttr->FirstChildElement();
		gXmlTagData _gXmlTagData;
		bool IsReady = false; // If True all the elements of a node were read

		for(ruleAttr; ruleAttr; ruleAttr=ruleAttr->NextSiblingElement())
		{
			if (ruleAttr->ValueStr() == "line")
			{
				_gXmlTagData.line = atoi(ruleAttr->GetText());
				continue;
			} 
			if (ruleAttr->ValueStr() == "typeid")
			{
				_gXmlTagData.typeId = atoi(ruleAttr->GetText());
				continue;
			}

			if (ruleAttr->ValueStr() == "type")
			{
				_gXmlTagData.type = ruleAttr->GetText();
				continue;
			}
			if (ruleAttr->ValueStr() == "name")
			{
				_gXmlTagData.name = ruleAttr->GetText();
				continue;
			}

			if (ruleAttr->ValueStr() == "comment")
			{
				_gXmlTagData.comment = ruleAttr->GetText();
				IsReady = true;
				continue;
			}
		}
		
		if (IsReady)
		{
			_M_xmlList.push_back(_gXmlTagData);
		}
	}
};

void 
PfMapperBase::setOutFile(const string& value)
{
	/*classifyHeader
	 * Open file for write
	 */
	try 
	{
		_M_outFile.open(value.c_str() , std::ios::out);	
		if (!_M_outFile)
		{
			throw (PF_ERROR);
		}
	}
	catch (int errorNum)
	{
		std::cerr << "\n" << _M_mapper << " encounter an error: cannot create file:" << value << "\n"; 
		_M_outFile.close();
		exit (errorNum);
	}
};

void 
PfMapperBase::incTagNumber(void)
{
	this->_M_tagNum++;
};

void 
PfMapperBase::decTagNumber(void)
{
	if ( !(this->_M_tagNum <= 0) )
	{
		this->_M_tagNum--;
	}
};

PfMapperBase::~PfMapperBase()
{
	_M_inFile.close();
	_M_outFile.close();
}

void 
PfMapperBase::setMapper(const string& value)
{
	_M_mapper = value;
}

const string& 
PfMapperBase::getMapper(void)
{
	return this->_M_mapper;
}

void 
PfMapperBase::iterateFiles(void)
{
	unsigned int i = 1;
	bool IsMulti = false; // Used if multiple patterns are detected in a single line of code
	bool IsChanged = false; // If true then we must print out the manipulated line of code
	string retLine = "";
	
	_M_xmlIterator = _M_xmlList.begin();

	while (!_M_inFile.eof())
	{
		if ( !IsMulti )
		{
			_M_inFile.getline( _M_lineBuffer, PF_MAX_BUFFER );
			// TODO: Here I can keep the original line of code
		}

		// Found a line of code that needs to change
		if ((*_M_xmlIterator).line == i)
		{
			if (!IsMulti)
			{
				retLine = classifier(&(*_M_xmlIterator), _M_lineBuffer);
			}
			else
			{
				retLine = classifier(&(*_M_xmlIterator), retLine); 
			}

			// Check if next pattern was detected in the same line of code
			if ((++_M_xmlIterator != _M_xmlList.end()) && ((*_M_xmlIterator).line == i))
			{
				IsMulti = true;
			}
			else 
			{
				IsMulti = false;
				IsChanged = true;
			}
		};
		
		if (!IsMulti)
		{	
			if (!IsChanged)
			{
				_M_outFile << _M_lineBuffer << "\n";
			}
			else
			{
				incTagNumber();
				
				if (_M_doPrint) 
				{
					_M_outFile << printTag(i, _M_lineBuffer);
				}
				
				_M_outFile << retLine; 
				
				if (_M_doPrint)
				{
					_M_outFile << "\n/* END OF TAG ID: " << toString<long>(_M_tagNum, std::dec) << " */\n";
				}
	
				IsChanged = false;
			}
			++i;
		};
	};
};


const string& 
PfMapperBase::classifier(gXmlTagData* pXmlTagData, const string& buffer)
{
	switch (pXmlTagData->typeId)
	{
		case PF_STRUCTURE:
			_M_buffer = portStructure(pXmlTagData, buffer);
			return _M_buffer;
//			break;
		case PF_FUNCTION:
			_M_buffer = portFunction(pXmlTagData, buffer);
			return _M_buffer;
//			break;
		case PF_IPV4ADDR:
			_M_buffer = portIpv4Addr(pXmlTagData, buffer);
			return (_M_buffer);
//			break;
		case PF_URL:
			_M_buffer = portUrl(pXmlTagData, buffer);
			return _M_buffer;
//			break;
		case PF_HEADER_FILE:
			_M_buffer = portHeaderFile(pXmlTagData, buffer);
			return _M_buffer;
//			break;
		case PF_MACRO:
			_M_buffer = portMacro(pXmlTagData, buffer);
			return _M_buffer;
//			break;
		case PF_IPV4_CENTRIC:
			_M_buffer = portIpv4Centric(pXmlTagData, buffer);
			return _M_buffer;
//			break;
		default:
			;
	};
	
	_M_buffer = "\n" + getMapper() + ": Classifier: No match\n";
	return _M_buffer;
};

const string& 
PfMapperBase::genericPort(gXmlTagData* pXmlTagData, const string& buffer, const string& custom)
{
	std::cout << "\nIdentified at line: " << (pXmlTagData->line);
	std::cout << "\nIPv4 " << custom << ": " << (pXmlTagData->name); 
	std::cout << "\nReplace with: ";

	char buf[PF_MAX_BUFFER];
	std::cin.getline(buf, PF_MAX_BUFFER);

	_M_buffer = replaceString(buffer, (pXmlTagData->name), buf); 
	return _M_buffer;
};

const string& 
PfMapperBase::printTag(int lineNum, const string& lineCode)
{
	string TagText = "";

	TagText += "\n/* TAG ID: ";
	TagText += toString<long>( _M_tagNum, std::dec );
	TagText += "\n * Original line number: ";
	TagText += toString<long>( lineNum, std::dec );
	TagText += "\n * Original code: ";
	TagText += lineCode;
	TagText += "\n */\n";

	_M_buffer = TagText;
	return _M_buffer;
};

void 
PfMapperBase::setPrintTag(bool value)
{
	_M_doPrint = value;
};

const string& 
PfMapperBase::convertIpv4ToIpv6(const string& ipv4Addr, short int addrType, short int prefixType)
{
	string hexPrefix = "0000";
	string _ipv4Addr = ipv4Addr;


	switch (prefixType)
	{
		case PF_RP_GLOBAL_UNICAST:
			hexPrefix = "2000";
			break;
		case PF_RP_LINK_LOCAL_UNICAST:
			hexPrefix = "fe80";
			break;
		case PF_RP_SITE_LOCAL_UNICAST:
			hexPrefix = "fec0";
			break;
		case PF_RP_LOCAL_IPV6_ADDRESS:
			hexPrefix = "fc00";
			break;
		case PF_RP_PRIVATE_ADMINISTRATION:
			hexPrefix = "fd00";
			break;
		case PF_RP_MULTICAST:
			hexPrefix = "ff00";
			break;
		case PF_RP_TEREDO:
			hexPrefix = "2001";
			break;
		case PF_RP_6TO4:
			hexPrefix = "2002";
			break;
		case PF_RP_6BONE:
			hexPrefix = "3ffe";
			break;
		default:
			hexPrefix = "0000";
	}

	if ((addrType < 0) || (addrType > 3)) 
	{
		_M_buffer = _ipv4Addr;
		return _M_buffer;
	}

	if (addrType == 2) // IPv6 and dot notation full address
	{
		_M_buffer = hexPrefix + ":0000:0000:0000:0000:0000:" + _ipv4Addr;
		return _M_buffer;
	}

	if (addrType == 3) // IPv6 and dot notation shorthand address
	{
		if (hexPrefix == "0000")
		{
			_M_buffer = "::" + _ipv4Addr;
			return _M_buffer;
		}
		else
		{
			_M_buffer = hexPrefix + "::" + _ipv4Addr;
			return _M_buffer;
		}
	}
	
	unsigned long long dotPos = 0;
	string addrPart_1 = "0"; 
	string addrPart_2 = "0"; 
	string addrPart_3 = "0"; 
	string addrPart_4 = "0"; 
	string hex_addrPart_1 = "00";
	string hex_addrPart_2 = "00";
	string hex_addrPart_3 = "00";
	string hex_addrPart_4 = "00";

	dotPos = _ipv4Addr.find(".", 0);
	if (dotPos != string::npos)
	{
		addrPart_1 = _ipv4Addr.substr(0, dotPos);
		hex_addrPart_1 = toString<long>(atoi(addrPart_1.c_str()), std::hex);
		if ((hex_addrPart_1.length() % 2) != 0)
		{
			hex_addrPart_1 = "0" + hex_addrPart_1;
		}
		_ipv4Addr.erase(0, dotPos+1);
		dotPos = _ipv4Addr.find(".", 0);
		if (dotPos != string::npos)
		{
			addrPart_2 = _ipv4Addr.substr( 0, dotPos );
			hex_addrPart_2 = toString<long>( atoi(addrPart_2.c_str()), std::hex );
			if ((hex_addrPart_2.length() % 2) != 0)
			{
				hex_addrPart_2 = "0" + hex_addrPart_2;
			}
			_ipv4Addr.erase(0, dotPos+1);
			dotPos = _ipv4Addr.find(".", 0);
			if (dotPos != string::npos)
			{
				addrPart_3 = _ipv4Addr.substr( 0, dotPos );
				hex_addrPart_3 = toString<long>( atoi(addrPart_3.c_str()), std::hex );
				if ((hex_addrPart_3.length() % 2) != 0)
				{
					hex_addrPart_3 = "0" + hex_addrPart_3;
				}
				_ipv4Addr.erase(0, dotPos+1);
					
				// Last part
				addrPart_4 = _ipv4Addr.substr( 0, _ipv4Addr.length() );
				hex_addrPart_4 = toString<long>( atoi(addrPart_4.c_str()), std::hex );
				if ((hex_addrPart_4.length() % 2) != 0)
				{
					hex_addrPart_4 = "0" + hex_addrPart_4;
				}
			}
		}
	}

	string hexIpv6Addr = hex_addrPart_1 + hex_addrPart_2 + ":" + hex_addrPart_3 + hex_addrPart_4;

	if (addrType == 0) // IPv6 full address
	{
		_M_buffer = hexPrefix + ":0000:0000:0000:0000:0000:" + hexIpv6Addr; 
		return _M_buffer;
	}

	if (addrType == 1) // IPv6 Shorthand address
	{
		if ( hexPrefix == "0000" )
		{
			_M_buffer = "::" + hexIpv6Addr;
			return _M_buffer;
		}
		else
		{
			_M_buffer = hexPrefix + "::" + hexIpv6Addr;
			return _M_buffer;
		}
	}
	
	// Should never reach this return. Removes warning during compilation.
	_M_buffer = _ipv4Addr;
	return _M_buffer;
};

#endif
