#pragma once

#include "D3D11/IRender.h"
//--------------------------------------------------------------------

class ConstantBuffer : public IRender
{
public:

	/*
		Constructor.
	*/
	ConstantBuffer();

	/*
		Destructor.
	*/
	~ConstantBuffer();

	/*
		This function is called to initialize the constant buffer from a given object.
	*/
	template<class T>
	bool init(const T &data);

	/*
		This function is called to initialize the constant buffer.
	*/
	bool init(const void * data, int size, const char * const name = nullptr);

	/*
		This function is called to update the resource data from a given object.
	*/
	template<class T>
	void updateData(const T &data) const;

	/*
		This function is called to update the resource data from memory.
	*/
	void updateData(const void * data) const;

	/*
		This function is called to apply the buffer to vertex shader.
	*/
	void applyVS(UINT startSlot) const;
	
	/*
		This function is called to apply the buffer to geometry shader.
	*/
	void applyGS(UINT startSlot) const;
	
	/*
		This function is called to apply the buffer to pixel shader.
	*/
	void applyPS(UINT startSlot) const;
	
protected:
	
	//	Pointer to the constant buffer.
	ID3D11Buffer * m_constantBuffer;
};
//--------------------------------------------------------------------

#include <typeinfo>
template<class T>
inline bool ConstantBuffer::init(const T &data)
{
    return init(&data, sizeof(data), typeid(data).name());
}
//--------------------------------------------------------------------

template<class T>
inline void ConstantBuffer::updateData(const T &data) const
{
    if (m_constantBuffer) m_deviceContext->UpdateSubresource(m_constantBuffer, 0, NULL, &data, 0, 0);
}
//--------------------------------------------------------------------

inline void ConstantBuffer::updateData(const void * data) const
{
    if (m_constantBuffer) m_deviceContext->UpdateSubresource(m_constantBuffer, 0, NULL, data, 0, 0);
}
//--------------------------------------------------------------------

inline void ConstantBuffer::applyVS(UINT startSlot) const
{
    if (m_constantBuffer) m_deviceContext->VSSetConstantBuffers(startSlot, 1, &m_constantBuffer);
}
//--------------------------------------------------------------------

inline void ConstantBuffer::applyGS(UINT startSlot) const
{
    if (m_constantBuffer) m_deviceContext->GSSetConstantBuffers(startSlot, 1, &m_constantBuffer);
}
//--------------------------------------------------------------------

inline void ConstantBuffer::applyPS(UINT startSlot) const
{
    if (m_constantBuffer) m_deviceContext->PSSetConstantBuffers(startSlot, 1, &m_constantBuffer);
}
//--------------------------------------------------------------------