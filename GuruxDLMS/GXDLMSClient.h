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

#include "Enums.h"
#include "GXDLMS.h"
#include "GXDLMSVariant.h"
#include "GXDLMSLimits.h"
#include "GXStandardObisCodeCollection.h"

class CGXDLMSClient
{
	CGXDLMS m_base;
public:
	static void UpdateOBISCodes(CGXObjectCollection& objects);
public:
	/////////////////////////////////////////////////////////////////////////////
	//Constructor
	/////////////////////////////////////////////////////////////////////////////
	CGXDLMSClient(bool UseLogicalNameReferencing, 
				CGXDLMSVariant ClientID = (unsigned char) 0x21,
				CGXDLMSVariant ServerID = (unsigned char) 0x3,
				//Authentication type.
				GXDLMS_AUTHENTICATION Authentication = GXDLMS_AUTHENTICATION_NONE, 
				//Password if authentication is used.
				const char* pPassword = NULL,
				GXDLMS_INTERFACETYPE IntefaceType = GXDLMS_INTERFACETYPE_GENERAL);

	bool UseLogicalNameReferencing()
	{
		return m_base.m_UseLogicalNameReferencing;
	}

	GXDLMSLimits& GetLimits()
	{
		return m_base.m_Limits;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Returns SNRMRequest query as byte array.
	/////////////////////////////////////////////////////////////////////////////
	// Packets: Packets to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int SNRMRequest(std::vector< std::vector<unsigned char> >& Packets);
	
	/////////////////////////////////////////////////////////////////////////////
	// Parses UAResponse byte array.
	/////////////////////////////////////////////////////////////////////////////
	// buff: buffer containing the data from the meter.
	// buffSize: size of the buffer.
	// dataSize: size of data to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int ParseUAResponse(unsigned char* buff, int buffSize);

	/////////////////////////////////////////////////////////////////////////////
	// Parses UAResponse byte vector.
	/////////////////////////////////////////////////////////////////////////////
	// buff: vector containing the data from the meter.
	// Returns: 0 if succeed. Otherwise error number.
	int ParseUAResponse(vector<unsigned char>& data);

	/////////////////////////////////////////////////////////////////////////////
	// Returns AARQRequest query as byte array.
	/////////////////////////////////////////////////////////////////////////////
	// buff: allocated buffer.
	// buffSize: size of buffer.
	// dataSize: size of data to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int AARQRequest(vector< std::vector<unsigned char> >& Packets);

	/////////////////////////////////////////////////////////////////////////////
	// Returns KeepAlive request as byte array.
	/////////////////////////////////////////////////////////////////////////////
	// buff: allocated buffer.
	// buffSize: size of buffer.
	// dataSize: size of data to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int GetKeepAlive(vector< vector<unsigned char> >& Packets);
	
	/////////////////////////////////////////////////////////////////////////////
	// Parses AAREResponse byte array.
	/////////////////////////////////////////////////////////////////////////////
	// buff: buffer containing the data from the meter.
	// buffSize: size of the buffer.
	// dataSize: size of data to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int ParseAAREResponse(unsigned char* buff, int buffSize);

	/////////////////////////////////////////////////////////////////////////////
	// Parses AAREResponse byte array.
	/////////////////////////////////////////////////////////////////////////////
	// buff: buffer containing the data from the meter.
	// buffSize: size of the buffer.
	// dataSize: size of data to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////	
	int ParseAAREResponse(vector<unsigned char>& data);

	/////////////////////////////////////////////////////////////////////////////
	// Returns DisconnectedMode query as byte array.
	/////////////////////////////////////////////////////////////////////////////
	// buff: allocated buffer.
	// buffSize: size of buffer.
	// dataSize: size of data to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int DisconnectedModeRequest(vector< vector<unsigned char> >& Packets);

	/////////////////////////////////////////////////////////////////////////////
	// Returns Disconnect request as byte array.
	/////////////////////////////////////////////////////////////////////////////
	// buff: allocated buffer.
	// buffSize: size of buffer.
	// dataSize: size of data to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int DisconnectRequest(vector< vector<unsigned char> >& Packets);

	/////////////////////////////////////////////////////////////////////////////
	// Returns GetObjects query as byte array.
	/////////////////////////////////////////////////////////////////////////////
	// Packets: Packets to send.
	/////////////////////////////////////////////////////////////////////////////
	int GetObjectsRequest(vector< vector<unsigned char> >& Packets);

	/////////////////////////////////////////////////////////////////////////////
	// Returns Read query as byte array.
	/////////////////////////////////////////////////////////////////////////////
	// name: Short name of Logical name of the requested object.
	// InterfaceClass: Type of the DLMS object.
	// AttributeOrdinal: The ordinal number of the requested attribute.
	// Packets: packets to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int Read(CGXDLMSVariant& name, OBJECT_TYPE InterfaceClass, int AttributeOrdinal, vector< vector<unsigned char> >& Packets);

	/////////////////////////////////////////////////////////////////////////////
	// Returns Write query as byte array.
	/////////////////////////////////////////////////////////////////////////////
	// SN: Short name of the requested object.
	// InterfaceClass: Type of the DLMS object.
	// AttributeOrdinal: The ordinal number of the requested attribute.
	// pData: Written data.
	// DataLength: Length of the data written to.
	// buff: allocated buffer.
	// buffSize: size of buffer.
	// dataSize: size of data to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int Write(CGXDLMSVariant& name, OBJECT_TYPE InterfaceClass, int AttributeOrdinal, CGXDLMSVariant Data, vector< vector<unsigned char> >& Packets);
	
	/////////////////////////////////////////////////////////////////////////////
	// Changes byte array received from the meter to given type.
	/////////////////////////////////////////////////////////////////////////////
	// value Byte array received from the meter.
	// type Wanted type.
	// returns Value changed by type.
	static int ChangeType(vector<unsigned char> value, DLMS_DATA_TYPE type, CGXDLMSVariant& newValue);

	/////////////////////////////////////////////////////////////////////////////
	// Parses a byte array containing DLMS objects.
	/////////////////////////////////////////////////////////////////////////////
	// buff: buffer containing the data from the meter.
	// buffSize: size of the buffer.
	// dataSize: size of data to send.
	// objects: list of the parsed objects
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int ParseObjects(vector<unsigned char>& data, CGXObjectCollection& objects);
	
	/////////////////////////////////////////////////////////////////////////////
	// Parses a byte array containing Profile Generic DLMS objects.
	/////////////////////////////////////////////////////////////////////////////
	// buff: buffer containing the data from the meter.
	// data: size of the buffer.
	// pg: the profile generic DLMS object.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int ParseColumns(vector<unsigned char>& data, CGXObjectCollection* pg);

	/////////////////////////////////////////////////////////////////////////////
	// Parses a byte array containing Profile Generic sort object.
	/////////////////////////////////////////////////////////////////////////////
	int ParseSortObject(vector<unsigned char>& data, CGXObject*& pObj);

	/////////////////////////////////////////////////////////////////////////////
	// Returns Read query as byte array.
	/////////////////////////////////////////////////////////////////////////////
	// SN: short name of the profile generic DLMS object.
	// class_id: the data type of the sorted column. Usually 8 (Clock).
	// LN: logical name of the sorted column.
	// AttributeIndex: attribute index of the sorted column.
	// Version: version of the sorted column.
	// start: start time of requested time span.
	// end: end time of requested time span.
	// Packets: Packets to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////	
	int ReadRowsByRange(CGXDLMSVariant& Name, CGXObject* pSortObject, struct tm* start, struct tm* end, vector< vector<unsigned char> >& Packets);

	/////////////////////////////////////////////////////////////////////////////
	// Returns Read query as byte array.
	/////////////////////////////////////////////////////////////////////////////
	// SN: Short name of the profile generic DLMS object.
	// Index: Zero based starting index.
	// Count: The number of requested rows.
	// pBuff: allocated buffer.
	// buffSize: size of buffer.
	// dataSize: size of data to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int ReadRowsByEntry(CGXDLMSVariant& Name, unsigned int Index, unsigned int Count, vector< vector<unsigned char> >& Packets);

	/////////////////////////////////////////////////////////////////////////////
	// Returns ReceiverReady query as byte array.
	/////////////////////////////////////////////////////////////////////////////
	// Type: type of the next requested packet.
	// Data: Data to send.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int ReceiverReady(GXDLMS_DATA_REQUEST_TYPES Type, vector< vector<unsigned char> >& Data);

	/////////////////////////////////////////////////////////////////////////////
	// Returns true if received data is a full packet.
	/////////////////////////////////////////////////////////////////////////////
	// Data: buffer containing the data from the meter.
	// buffSize: size of the buffer.
	// Returns: true if the packet is complete.
	/////////////////////////////////////////////////////////////////////////////
	bool IsDLMSPacketComplete(unsigned char* Data, int buffSize);

	/////////////////////////////////////////////////////////////////////////////
	// Return error numbers if there is any present.
	/////////////////////////////////////////////////////////////////////////////
	// SendData: buffer containing the sent data
	// SendbuffSize: size of the sent data buffer.
	// ReceivedData: buffer containing the data from the meter.
	// ReceivedbuffSize: size of the reply buffer.
	// Returns: error numbers if there is any present.
	/////////////////////////////////////////////////////////////////////////////
	int CheckReplyErrors(unsigned char* SendData, int SendbuffSize, unsigned char* ReceivedData, int ReceivedbuffSize);

	/////////////////////////////////////////////////////////////////////////////
	// Returns zero if the packet is correct and an error number if not.
	/////////////////////////////////////////////////////////////////////////////
	// SendData: buffer containing the sent data
	// SendbuffSize: size of the sent data buffer.
	// ReceivedData: buffer containing the data from the meter.
	// ReceivedbuffSize: size of the reply buffer.
	// Returns: 0 if packet is reply. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int IsReplyPacket(unsigned char* SendData, int SendbuffSize, unsigned char* ReceivedData, int ReceivedbuffSize);
	
	/////////////////////////////////////////////////////////////////////////////
	// Returns the data (payload) from of the packet.
	/////////////////////////////////////////////////////////////////////////////
	// Packet: buffer containing the data from the meter.
	// PacketSize: size of the buffer.
	// Data: allocated buffer.
	// DataSize: size of the allocated buffer.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int GetDataFromPacket(unsigned char* Packet, int PacketSize, unsigned char*& Data, int& DataSize, GXDLMS_DATA_REQUEST_TYPES& moreData);

	/////////////////////////////////////////////////////////////////////////////
	// Returns the data (payload) from of the packet.
	/////////////////////////////////////////////////////////////////////////////
	// Packet: buffer containing the data from the meter.
	// PacketSize: size of the buffer.
	// reply: received data.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int GetDataFromPacket(unsigned char* Packet, int PacketSize, std::vector<unsigned char>& reply, GXDLMS_DATA_REQUEST_TYPES& moreData);

	/////////////////////////////////////////////////////////////////////////////
	// Returns the value of a DLMS object
	/////////////////////////////////////////////////////////////////////////////
	// pBuff: buffer received from the meter.
	// Size: size of the buffer.
	// Value: Received value.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int GetValue(unsigned char* pBuff, int Size, CGXDLMSVariant& value);

	/////////////////////////////////////////////////////////////////////////////
	// Returns the value of a DLMS object
	/////////////////////////////////////////////////////////////////////////////
	// data: Data received from the meter.
	// Value: Received value.
	// Returns: 0 if succeed. Otherwise error number.
	/////////////////////////////////////////////////////////////////////////////
	int GetValue(vector<unsigned char>& data, CGXDLMSVariant& value);
};
