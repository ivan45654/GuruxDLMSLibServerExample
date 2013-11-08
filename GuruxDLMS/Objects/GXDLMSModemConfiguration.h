//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL:  $
//
// Version:         $Revision:  $,
//                  $Date:  $
//                  $Author: $
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
#pragma once

#include "IGXDLMSBase.h"
#include "GXObject.h"
#include "../GXHelpers.h"
#include "GXDLMSModemInitialisation.h"

class CGXDLMSModemConfiguration : public CGXObject
{
    vector<CGXDLMSModemInitialisation> m_InitialisationStrings;
    vector< basic_string<char> > m_ModemProfile;
    BAUDRATE m_CommunicationSpeed;

    void Init()
    {
        m_CommunicationSpeed = BAUDRATE_9600;
		m_ModemProfile.push_back("OK");
		m_ModemProfile.push_back("CONNECT");
		m_ModemProfile.push_back("RING");
		m_ModemProfile.push_back("NO CARRIER");
		m_ModemProfile.push_back("ERROR");
		m_ModemProfile.push_back("CONNECT 1200");
		m_ModemProfile.push_back("NO DIAL TONE");
		m_ModemProfile.push_back("BUSY");
		m_ModemProfile.push_back("NO ANSWER");
		m_ModemProfile.push_back("CONNECT 600");
		m_ModemProfile.push_back("CONNECT 2400");
		m_ModemProfile.push_back("CONNECT 4800");
		m_ModemProfile.push_back("CONNECT 9600");
		m_ModemProfile.push_back("CONNECT 14 400");
		m_ModemProfile.push_back("CONNECT 28 800");
		m_ModemProfile.push_back("CONNECT 33 600");
		m_ModemProfile.push_back("CONNECT 56 000");
    }

public:

    /**  
     Constructor.
    */
    CGXDLMSModemConfiguration() : CGXObject(OBJECT_TYPE_MODEM_CONFIGURATION, "0.0.2.0.0.255")
    {
        Init();
    }

    /**  
     Constructor.
     @param ln Logican Name of the object.
    */
    CGXDLMSModemConfiguration(basic_string<char> ln) : CGXObject(OBJECT_TYPE_MODEM_CONFIGURATION, ln)
    {   
        Init();
    }

    /**  
     Constructor.
     @param ln Logican Name of the object.
     @param sn Short Name of the object.
    */
    CGXDLMSModemConfiguration(int sn) : CGXObject(OBJECT_TYPE_MODEM_CONFIGURATION, sn)
    {        
        Init();
    }   

    BAUDRATE GetCommunicationSpeed()
    {
        return m_CommunicationSpeed;
    }
    void SetCommunicationSpeed(BAUDRATE value)
    {
        m_CommunicationSpeed = value;
    }

    vector<CGXDLMSModemInitialisation>& GetInitialisationStrings()
    {
        return m_InitialisationStrings;
    }
    void SetInitialisationStrings(vector<CGXDLMSModemInitialisation>& value)
    {
        m_InitialisationStrings = value;
    }

    vector< basic_string<char> > GetModemProfile()
    {
        return m_ModemProfile;
    }

    void SetModemProfile(vector< basic_string<char> >& value)
    {
        m_ModemProfile = value;
    }              
    
    // Returns amount of attributes.
    int GetAttributeCount()
    {
        return 4;
    }
    
    // Returns amount of methods.
    int GetMethodCount()
    {
        return 0;
    }    
    
    // Returns value of given attribute.
    int GetValue(int index, unsigned char* parameters, int length, CGXDLMSVariant& value, DLMS_DATA_TYPE& type)
    {
        if (index == 1)
        {
            GXHelpers::AddRange(value.byteArr, m_LN, 6);
            type = value.vt = DLMS_DATA_TYPE_OCTET_STRING;
            return ERROR_CODES_OK;
        }
        if (index == 2)
        {
            type = DLMS_DATA_TYPE_ENUM;
            value = m_CommunicationSpeed;
			return ERROR_CODES_OK;
        }
        if (index == 3)
        {
            type = DLMS_DATA_TYPE_ARRAY;
            vector<unsigned char> data;
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            //Add count
            int cnt = m_InitialisationStrings.size();
            CGXOBISTemplate::SetObjectCount(cnt, data);
            for (vector<CGXDLMSModemInitialisation>::iterator it = m_InitialisationStrings.begin(); 
                it != m_InitialisationStrings.end(); ++it)
            {
                data.push_back(DLMS_DATA_TYPE_STRUCTURE);
                data.push_back(3); //Count                        
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, it->GetRequest());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, it->GetResponse());
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_UINT16, it->GetDelay());
            }
            value = data;
			return ERROR_CODES_OK;
        }
        if (index == 4)
        {
            type = DLMS_DATA_TYPE_ARRAY;
            vector<unsigned char> data;
            data.push_back(DLMS_DATA_TYPE_ARRAY);
            //Add count
            int cnt = m_ModemProfile.size();
            CGXOBISTemplate::SetObjectCount(cnt, data);
            //for(String it : m_ModemProfile)
			for (vector< basic_string<char> >::iterator it = m_ModemProfile.begin(); 
                it != m_ModemProfile.end(); ++it)
            {
                CGXOBISTemplate::SetData(data, DLMS_DATA_TYPE_OCTET_STRING, *it);
            }
            value = data;
			return ERROR_CODES_OK;
        }
        return ERROR_CODES_INVALID_PARAMETER;
    }
    
    // Set value of given attribute.
    int SetValue(int index, CGXDLMSVariant& value)
    {
        if (index == 1)
        {
            if (value.vt != DLMS_DATA_TYPE_OCTET_STRING || value.GetSize() != 6)
            {
                return ERROR_CODES_INVALID_PARAMETER;
            }
            memcpy(m_LN, &value.byteArr[0], 6);
            return ERROR_CODES_OK;
        }
        else if (index == 2)
        {
			m_CommunicationSpeed = (BAUDRATE) value.bVal;
			return ERROR_CODES_OK;
        }
        else if (index == 3)
        {
            m_InitialisationStrings.clear();  
			int ret;
			for (vector<CGXDLMSVariant>::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)
			{
                CGXDLMSModemInitialisation item;                                        
				CGXDLMSVariant tmp;
				if((ret = CGXDLMSClient::ChangeType(it->Arr[0].byteArr, DLMS_DATA_TYPE_STRING, tmp)) != ERROR_CODES_OK)
				{
					return ret;
				}
				item.SetRequest(tmp.ToString());
				if((ret = CGXDLMSClient::ChangeType(it->Arr[1].byteArr, DLMS_DATA_TYPE_STRING, tmp)) != ERROR_CODES_OK)
				{
					return ret;
				}
				item.SetResponse(tmp.ToString());
                if (it->Arr.size() > 2)
                {
                    item.SetDelay(it->Arr[2].uiVal);
                }
                m_InitialisationStrings.push_back(item);
            }
			return ERROR_CODES_OK;
        }
        else if (index == 4)
        {
            m_ModemProfile.clear();
			int ret;
            for (vector<CGXDLMSVariant>::iterator it = value.Arr.begin(); it != value.Arr.end(); ++it)			
            {
				CGXDLMSVariant tmp;
				if((ret = CGXDLMSClient::ChangeType(it->byteArr, DLMS_DATA_TYPE_STRING, tmp)) != ERROR_CODES_OK)
				{
					return ret;
				}
                m_ModemProfile.push_back(tmp.ToString());
            }
			return ERROR_CODES_OK;
        }
        return ERROR_CODES_INVALID_PARAMETER;
    }
};
