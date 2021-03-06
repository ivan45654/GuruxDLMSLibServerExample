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

#include "GXNet.h"
#include "GuruxCommon/GXMediaListener.h"
#include "GuruxDLMS/GXDLMSServerBase.h"

class CGXDLMSBase : public CGXDLMSServerBase, 
					IGXMediaListener, IGXNetListener
{
	CGXNet m_Media;
	std::string serialNo;
public:		
	/////////////////////////////////////////////////////////////////////////
	//Constructor.
	/////////////////////////////////////////////////////////////////////////
	CGXDLMSBase(bool UseLogicalNameReferencing = true,
		GXDLMS_INTERFACETYPE IntefaceType = GXDLMS_INTERFACETYPE_GENERAL, 
		unsigned short MaxReceivePDUSize = 0xFFFF) :
				CGXDLMSServerBase(UseLogicalNameReferencing, 
				IntefaceType, 0xFFFF)
	{
	}


	/////////////////////////////////////////////////////////////////////////
	//Destructor.
	/////////////////////////////////////////////////////////////////////////
	~CGXDLMSBase(void)
	{
		m_Media.Close();
	}

	int Init(int port);
	int OnRead(CGXDLMSObject* pItem, int index, CGXDLMSVariant& value, DLMS_DATA_TYPE& type);
	int OnWrite(CGXDLMSObject* pItem, int index, int selector, CGXDLMSVariant& value);
	int OnAction(CGXDLMSObject* pItem, int index, CGXDLMSVariant& data);
	int OnInvalidConnection();

	void OnClientConnected(IGXMedia* pSender, CConnectionEventArgs& e)
	{
		printf("Client Connected : %s\r\n", e.GetInfo().c_str());
	}

    /** 
     Called when the client has been disconnected from the GXNet server.

     @param sender The source of the event.    
     @param e Event arguments.
    */
    void OnClientDisconnected(IGXMedia* pSender, CConnectionEventArgs& e)
	{
    	printf("Client Disonnected : %s\r\n", e.GetInfo().c_str());
	}

	void OnError(IGXMedia* pSender, basic_string<char>& ex)
	{
		printf("Error has occurred : %s\r\n", ex.c_str());
	}

    /** 
     Media component sends received data through this method.

     @param sender The source of the event.
     @param e Event arguments.
    */
    void OnReceived(IGXMedia* pSender, CReceiveEventArgs& e)
	{
		unsigned char* pReply = NULL;
		int size = 0;
		printf("<- %s\r\n", GXHelpers::bytesToHex(&e.getData()[0], e.getData().size()).c_str());

		HandleRequest(e.getData(), pReply, size);
        //Reply is null if we do not want to send any data to the client.
        //This is done if client try to make connection with wrong server or client address.
        if (size != 0)
        {		
			printf("-> %s\r\n", GXHelpers::bytesToHex(pReply, size).c_str());
            m_Media.Send(pReply, size, e.getSenderInfo());
        }
	}

    /** 
     Media component sends notification, when its state changes.

     @param sender The source of the event.    
     @param e Event arguments.
    */
    void OnMediaStateChange(IGXMedia* pSender, CMediaStateEventArgs& e)
	{
	}

    /** 
     Called when the Media is sending or receiving data.

     @param sender
     @param e
     @see IGXMedia.Trace Traceseealso>
    */
    void OnTrace(IGXMedia* pSender, CTraceEventArgs& e)
	{
    	printf("%s\r\n", e.ToString().c_str());
	}
    
    // Summary:
    //     Represents the method that will handle the System.ComponentModel.INotifyPropertyChanged.PropertyChanged
    //     event raised when a property is changed on a component.
    //
    // Parameters:
    //   sender:
    //     The source of the event.
    //
    //   e:
    //     A System.ComponentModel.PropertyChangedEventArgs that contains the event
    //     data.
    void OnPropertyChanged(IGXMedia* pSender, CPropertyChangedEventArgs& e)
	{

	}
};
