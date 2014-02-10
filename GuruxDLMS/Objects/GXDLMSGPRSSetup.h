//
// --------------------------------------------------------------------------
//  Gurux Ltd
// 
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License 
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2. 
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#pragma once

#include "GXDLMSObject.h"
#include "GXDLMSQualityOfService.h"

class CGXDLMSGPRSSetup : public CGXDLMSObject
{
private: 
	string m_APN;
    long m_PINCode;
    CGXDLMSQualityOfService m_DefaultQualityOfService;
    CGXDLMSQualityOfService m_RequestedQualityOfService;   

public:	
	//Constructor.
	CGXDLMSGPRSSetup();

	//SN Constructor.
	CGXDLMSGPRSSetup(unsigned short sn);

	//LN Constructor.
	CGXDLMSGPRSSetup(basic_string<char> ln);

	string GetAPN();
    void SetAPN(string value);

	long GetPINCode();
    void SetPINCode(long value);
    
    CGXDLMSQualityOfService& GetDefaultQualityOfService();

	CGXDLMSQualityOfService& GetRequestedQualityOfService();

    // Returns amount of attributes.
	int GetAttributeCount();

    // Returns amount of methods.
	int GetMethodCount();

	void GetAttributeIndexToRead(vector<int>& attributes);	

	int GetDataType(int index, DLMS_DATA_TYPE& type);

	// Returns value of given attribute.
	int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value);

	// Set value of given attribute.
	int SetValue(int index, CGXDLMSVariant& value);
};
