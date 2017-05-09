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

#ifndef _PF_COMMON_CC_
#define _PF_COMMON_CC_

#include "common.h"

void setGlobalActiveApi(int apiNumber)
{
	for (unsigned int i=0; i<gVectorApis.size(); i++)
	{
		gVectorApis[i].inUse = false;
	}

	gVectorApis[apiNumber].inUse = true;
	gActiveApi = apiNumber;	
}

int getGlobalActiveApi(void)
{
	unsigned int i;
	int _globalApi = 0;
	
	for (i=0; i<gVectorApis.size(); i++)
	{
		if (gVectorApis[i].inUse == true)
		{
			_globalApi = i;
			break;
		}
	}

	/* Make sure this is the only active API */
	if (gActiveApi != _globalApi)
	{ 
		setGlobalActiveApi(_globalApi);
	}
	return gActiveApi;
}

const string removeString(const string& str, const string& subStr)
{
	string sText = str;
	size_t* ip = new size_t(sText.find(subStr));

	if (*ip != string::npos) 
	{
		sText.erase(*ip, subStr.length());
	}
	
	delete ip;	
	return sText;
}

const string replaceString(const string& str, const string& removeStr, const string& replaceStr)
{
	string sText = str;
	size_t* ip = new size_t(sText.find(removeStr));

	if (*ip != string::npos) 
	{
		sText.replace(*ip, removeStr.length(), replaceStr);
	}
	
	delete ip;
	return sText;
}

bool findString(const string& str, const string& subStr)
{
	bool result = false;

	size_t* ip = new size_t(str.find(subStr));
	
	if (*ip != string::npos)
	{
		result = true;
	}
	else 
	{
		result = false;
	}

	delete ip;
	return result;
};

#endif
