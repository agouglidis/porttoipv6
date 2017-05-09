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

/*! 
    MOS - Meta Object Scanner 
 */

%{

#ifdef __CYGWIN__
using namespace std;
#endif /* __CYGWIN__ */

// Include files
#include <iostream>
#include <string>
#include <fstream>
using std::fstream;

#include "../include/common.h"
#include "../tinyxml/tinyxml.h"

/*! \fn void helpScreen(void)
	\brief Prints help screen
	\return void
 */
void helpScreen(void);

/*! \fn int initScanner(int argc, char** argv)
	\brief Initialise Scanner variables based on given commands
	\param argc 
	\param argv
	\return int
 */
int initScanner(int argc, char** argv);

/*! \fn void printTag(void)
	\brief Prints an information tag
	\return void
 */
void printTag(void);

// Variables
const string& PF_SCANNER_VERSION = "0.0.5"; /*!< Contains scanner version*/
const string& PF_SCANNER_NAME = "mos"; /*!< Contains scanner name */

%}

%option c++
%option noyywrap

/* WhiteSpace */
DELIMITER [ \t]
QUOTE ["\""]
VALIDCHARSET [[:alnum:]+.?:?\\?/?]+

%%

"#include_xml"{DELIMITER}+{QUOTE}{VALIDCHARSET}{QUOTE}	{

	string sIncludeFilename = removeString(YYText(), "#include_xml");
	// Get rid of quotes	
	sIncludeFilename = removeString(sIncludeFilename, "\""); 
	sIncludeFilename = removeString(sIncludeFilename, "\""); 

	// Remove all kind of delimiters (spaces and tabs)
	string sNoDelimiters = removeString(sIncludeFilename, " "); 
	while ((sIncludeFilename = removeString(sNoDelimiters, " ")) != (sNoDelimiters = removeString(sIncludeFilename, " "))); 

	while ((sIncludeFilename = removeString(sNoDelimiters, "\t")) != (sNoDelimiters = removeString(sIncludeFilename, "\t"))); 

	TiXmlDocument doc(sIncludeFilename); 
	bool loadOkay = doc.LoadFile();
	if (!loadOkay)
	{
		std::cerr << "\n" << PF_SCANNER_NAME << " encounter an error: cannot load xml file:" << sIncludeFilename << "\n"; 
		exit (PF_ERROR);
	}

	TiXmlHandle docHandle(&doc);
	TiXmlElement* rulesAttr = docHandle.FirstChild("rules").Child(0).Element();
	
	for(rulesAttr; rulesAttr; rulesAttr = rulesAttr->NextSiblingElement())
	{
		std::cout << "\n";

		TiXmlElement* ruleAttr = rulesAttr->FirstChildElement();
		for(ruleAttr; ruleAttr; ruleAttr = ruleAttr->NextSiblingElement())
		{
			if (ruleAttr->GetText() != PF_NULL)
			{
				if (ruleAttr->ValueStr() == "CONDITION")
				{
					std::cout << "<" << ruleAttr->GetText() << ">";
				} 
				else if (ruleAttr->ValueStr() == "PATTERN")
				{
					std::cout << ruleAttr->GetText() << "\t{\n";
					std::cout << "\n\tgXmlTagData xmlTagData;"
	                          	  	<< "\n\tstring sYYText = static_cast<string>(YYText());\n"
				  	  	<< "\n\txmlTagData.line = lineno();"
				  	  	<< "\n\txmlTagData.name = sYYText;";
				} 
				else if (ruleAttr->ValueStr() == "TYPE")
				{
					std::cout << "\n\txmlTagData.typeId = " << ruleAttr->GetText() << ";";
				} 
				else if (ruleAttr->ValueStr() == "COMMENT")
				{
					std::cout << "\n\txmlTagData.comment = \"" << ruleAttr->GetText() << 	"\";"
					  	<< "\n\n\tcopyToFile(&xmlTagData);\n}\n";
				}
			}
		}
	}
}

"#include_verbatim"{DELIMITER}+{QUOTE}{VALIDCHARSET}{QUOTE}	{
	
	string sIncludeFilename = removeString(YYText(), "#include_verbatim");
	// Get rid of quotes	
	sIncludeFilename = removeString(sIncludeFilename, "\""); 
	sIncludeFilename = removeString(sIncludeFilename, "\""); 
	
	// Remove all kind of delimiters (spaces and tabs)
	string sNoDelimiters = removeString(sIncludeFilename, " "); 
	while ((sIncludeFilename = removeString(sNoDelimiters, " ")) != (sNoDelimiters = removeString(sIncludeFilename, " "))); 

	while ((sIncludeFilename = removeString(sNoDelimiters, "\t")) != (sNoDelimiters = removeString(sIncludeFilename, "\t"))); 
			
	fstream inFile;
	string  sFilename;

	try
	{
		inFile.open(sIncludeFilename.c_str(), std::ios::in);
	
		if (!inFile)
		{
			std::cerr << "\n" << PF_SCANNER_NAME <<" encounter an error: line(" << lineno() << "): file " << sIncludeFilename << " does not exist\n"; 
			throw (PF_ERROR);
		}
	
		char ch;
		while (inFile.get(ch)) std::cout << ch;
	
		if (!inFile.eof())
		{
			std::cerr << "\n" << PF_SCANNER_NAME <<" encounter an error: unknown !?!?!?\n";
			throw (PF_ERROR);
		}
	}
	catch (int errorNum)
	{
		inFile.close();
		exit (errorNum);
	}
	
	inFile.close();
}

<<EOF>> { 	
	// Will be executed ONCE at the end of the file being parsed.		
	yyterminate(); 
}

%%
/*  C++ code */

/*! \fn int main(int argc, char** argv)
	\brief The main programme
	\param argc Number of parameters
	\param argv Contains the string of the parameters
	\return Error codes, and 0 for success
*/
int main(int argc, char** argv)
{
	initScanner(argc, argv);

	// Instansiate a FlexLexer Object
	FlexLexer* lexer = new yyFlexLexer;

	printTag();	

	// Start parsing file
	lexer->yylex();
	
	delete lexer;
	return PF_SUCCESS;
}

void printTag(void)
{
	std::cout << "/********************************************************************************" 
	<< "\n * This file was generated using " << PF_SCANNER_NAME << " version " << PF_SCANNER_VERSION << "\t\t\t\t*"
	<< "\n * MOS Meta Object Scanner - An integral part of PortToIPv6 framework" << "\t\t*"
	<< "\n * " << PF_COPYRIGHT << "\t*"
	<< "\n ********************************************************************************/\n\n\n";
}

void helpScreen(void)
{
	using std::cout;

	cout << PF_SCANNER_NAME << " - An integral part of PortToIPv6 framework\n";
	cout << PF_COPYRIGHT << "\n\n";

	cout << PF_SCANNER_NAME <<" < mosFile > outputFile\n";
	cout << "\t-h\t\tproduce this help message\n";
	cout << "\t--help\t\tproduce this help message\n";
	cout << "\t--version\treport " << PF_SCANNER_NAME << " version\n";
	cout << "\t-?\t\tproduce this help message\n";
}

int initScanner(int argc, char** argv)
{
	const char* arg;

	for (--argc, ++argv; argc; --argc, ++argv )
	{
		arg = argv[0];

		if (arg[0] != '-' || arg[1] == '\0')
		{
			break;
		}

		if (arg[1] == '-')
		{
			if (!strcmp(arg, "--help"))
				arg = "-h";
			else if (!strcmp(arg,"--version"))
				arg = "-v";
			else if (!strcmp(arg, "--" ))
			{
				--argc;
				++argv;
				break;
			}
		}
			
		for (int i=1; arg[i] != '\0'; ++i)
			switch (arg[i])
			{
				case '?':
				case 'h':
					helpScreen();
					exit (PF_SUCCESS);
				case 'v':
					std::cout << PF_NAME << " version " << PF_VERSION << " Release " << PF_RELEASE << "\n";
					std::cout << PF_SCANNER_NAME << " version " << PF_SCANNER_VERSION << "\n";
					exit (PF_SUCCESS);

				default:
					std::cerr << PF_SCANNER_NAME << ": unknown flag " << arg[i] << ".  For usage, try\n\t"<< PF_SCANNER_NAME << " --help\n";
					exit (PF_ERROR);
			}
				
	}
	return PF_SUCCESS;
}
