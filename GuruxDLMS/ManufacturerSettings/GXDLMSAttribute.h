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
#include "../Enums.h"

class CGXDLMSAttribute
{
	ACCESSMODE			m_Access;
	int					m_Index;
	DLMS_DATA_TYPE		m_Type;
	DLMS_DATA_TYPE		m_UIType;
	int					m_MinimumVersion;
	METHOD_ACCESSMODE	m_MethodAccess;
	bool				m_Static;
	int					m_Order;

	void Initialize(int index, DLMS_DATA_TYPE Type, DLMS_DATA_TYPE UiType, ACCESSMODE Access, int MinimumVersion)
	{
		m_Access = Access;
		m_Static = false;
		m_Order = 0;
		m_Index = index;
		m_Type = Type;
		m_UIType = UiType;
		m_MethodAccess = METHOD_ACCESSMODE_NONE;
		m_MinimumVersion = MinimumVersion;
	}

public:
	//Constructor.
	CGXDLMSAttribute(int index, DLMS_DATA_TYPE Type = DLMS_DATA_TYPE_NONE, DLMS_DATA_TYPE UiType = DLMS_DATA_TYPE_NONE, ACCESSMODE Access = ACCESSMODE_READ, int MinimumVersion = 1) :
					m_Access(Access), m_Index(index), m_Type(Type), m_UIType(UiType), m_MinimumVersion(MinimumVersion)
	{
		Initialize(index, Type, UiType, Access, MinimumVersion);
	}

	/// <summary>
    /// Attribute Index.
    /// </summary>
    int GetIndex()
    {
        return m_Index;
    }

    /// <summary>
    /// Attribute data type.
    /// </summary>
    DLMS_DATA_TYPE GetType()
    {
        return m_Type;
    }

    /// <summary>
    /// Data type that user want's to see.
    /// </summary>
    DLMS_DATA_TYPE GetUIDataType()
    {
        return m_UIType;            
    }

	void SetUIDataType(DLMS_DATA_TYPE type)
    {
        m_UIType = type;
    }
    
    ACCESSMODE GetAccess()
    {
        return m_Access;
    }
    void SetAccess(ACCESSMODE value)
    {
        m_Access = value;
    }

    METHOD_ACCESSMODE GetMethodAccess()
    {
        return m_MethodAccess;
    }

    void SetMethodAccess(METHOD_ACCESSMODE value)
    {
        m_MethodAccess = value;
    }

    bool GetStatic()
    {
        return m_Static;            
    }

	void SetStatic(bool value)
    {
        m_Static = value;            
    }

	/*
    /// <summary>
    /// Attribute values.
    /// </summary>
    [Browsable(false)]
    [XmlIgnore]
    public GXObisValueItemCollection Values
    {
        get;
        set;
    }
	*/

    /// <summary>
    /// Read order.
    /// </summary>        
    int GetOrder()
    {
        return m_Order;            
    }

    /// <summary>
    /// Minimum version vhere this attribute is implemented.
    /// </summary>
    int GetMinimumVersion()
    {
        return m_MinimumVersion;
    }		
};
