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
#include "GXDLMSPushObject.h"
#include "GXSendDestinationAndMethod.h"

class CGXDLMSPushSetup : public CGXDLMSObject
{
	vector<CGXDLMSPushObject> m_PushObjectList;
	CGXSendDestinationAndMethod m_SendDestinationAndMethod;
	vector<pair<CGXDateTime, CGXDateTime> > m_CommunicationWindow;
	int m_RandomisationStartInterval, m_NumberOfRetries, m_RepetitionDelay;

public:	
	//Constructor.
	CGXDLMSPushSetup();

	//SN Constructor.
	CGXDLMSPushSetup(unsigned short sn);

	//LN Constructor.
	CGXDLMSPushSetup(basic_string<char> ln);

/** 
    Defines the list of attributes or objects to be pushed. 
    Upon a call of the push (data) method the selected attributes are sent to the desti-nation 
    defined in send_destination_and_method.
*/
    vector<CGXDLMSPushObject>& GetPushObjectList()
    {
        return m_PushObjectList;
    }

    CGXSendDestinationAndMethod& GetSendDestinationAndMethod()
    {
        return m_SendDestinationAndMethod;
    }

    /** 
     Contains the start and end date/time 
     stamp when the communication window(s) for the push become active 
     (for the start instant), or inac-tive (for the end instant).
    */
    vector<pair<CGXDateTime, CGXDateTime> >& GetCommunicationWindow()
    {
        return m_CommunicationWindow;
    }

    /** 
     To avoid simultaneous network connections of a lot of devices at ex-actly 
     the same point in time, a randomisation interval in seconds can be defined.
     This means that the push operation is not started imme-diately at the
     beginning of the first communication window but started randomly delayed.
    */
    int GetRandomisationStartInterval()
    {
        return m_RandomisationStartInterval;
    }
    void SetRandomisationStartInterval(int value)
    {
        m_RandomisationStartInterval = value;
    }
    /** 
     The maximum number of retrials in case of unsuccessful push at-tempts. After a successful push no further push attempts are made until the push setup is triggered again. 
     A value of 0 means no repetitions, i.e. only the initial connection at-tempt is made.
    */

    int GetNumberOfRetries()
    {
        return m_NumberOfRetries;
    }
    void SetNumberOfRetries(int value)
    {
        m_NumberOfRetries = value;
    }

    int GetRepetitionDelay()
    {
        return m_RepetitionDelay;
    }

    void SetRepetitionDelay(int value)
    {
        m_RepetitionDelay = value;
    }
    // Returns amount of attributes.
	int GetAttributeCount();

	// Returns amount of methods.
	int GetMethodCount();

	//Get attribute values of object.
	void GetValues(vector<string>& values);

	void GetAttributeIndexToRead(vector<int>& attributes);	

	int GetDataType(int index, DLMS_DATA_TYPE& type);

	// Returns value of given attribute.
	int GetValue(int index, int selector, CGXDLMSVariant& parameters, CGXDLMSVariant& value);

	// Set value of given attribute.
	int SetValue(int index, CGXDLMSVariant& value);
};
