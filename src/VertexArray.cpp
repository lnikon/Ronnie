#include <iostream>
#include <cassert>

#include "VertexArray.h"

GLuint CalculateValueSize(const ValueType value) {
	switch (value)
	{
	case ValueType::FLOAT:
		return sizeof(float);
	default:
		assert(false);
		break;
	}
}

/*
* VertexArray
*/
VertexArray::VertexArray()
	: m_vao{generate()}
{
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vao);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_vao);
}

GLuint VertexArray::generate() const
{
	GLuint vao{ 0 };
	glGenVertexArrays(1, &vao);
	return vao;
}

void VertexArray::enableAttributeInternal(const VertexAttribute& attribute) const
{
	glEnableVertexAttribArray(attribute.GetId());
}

void VertexArray::AddAttribute(const ValueType type, const GLuint count)
{
	GLuint totalAttribDataCount{ count * CalculateValueSize(type) };
	for (const auto& attrib : m_vertexAttributes) {
		totalAttribDataCount += attrib.GetLayout().GetCount() * CalculateValueSize(attrib.GetLayout().GetType());
	}

	for (auto& attrib : m_vertexAttributes) {
		attrib.SetLayout(VertexAttribute::Layout{
			totalAttribDataCount,
			attrib.GetLayout().GetCount(),
			attrib.GetLayout().GetType(),
			attrib.GetLayout().GetNormilized(),
			attrib.GetLayout().GetOffset()
		});
	}

	GLint nextId{ 0 };
	GLuint offset{ 0 };
	if (!m_vertexAttributes.empty()) {
		const auto& lastAttribute{ m_vertexAttributes.back() };
		nextId = lastAttribute.GetId() + 1;
		offset = lastAttribute.GetLayout().GetOffset() + CalculateValueSize(lastAttribute.GetLayout().GetType()) * lastAttribute.GetLayout().GetCount();
	}
	
	m_vertexAttributes.emplace_back(VertexAttribute{
		nextId,
		totalAttribDataCount,
		VertexAttribute::Layout{
			totalAttribDataCount,
			count,
			type,
			Boolean::FALSY,
			offset,
		}
	});
}

void VertexArray::EnableAttribute(const GLint id)
{
	if (id == -1) {
		for (const auto& attribute : m_vertexAttributes) {
			enableAttributeInternal(attribute);
		}
	}
	else {
		assert(id >= 0 && id < m_vertexAttributes.size());
		enableAttributeInternal(m_vertexAttributes[id]);
	}
}

/*
* VertexAttribute::Layout
*/
VertexAttribute::Layout::Layout(const GLuint totalCount, const GLuint count, const ValueType type, const Boolean normilized, const GLuint offset)
	: m_totalCount{ totalCount }, m_count { count }, m_type{ type }, m_normilized{ normilized }, m_offset{ offset }
{
}

VertexAttribute::Layout::~Layout()
{
}

GLuint VertexAttribute::Layout::GetTotalCount() const
{
	return m_totalCount;
}

GLuint VertexAttribute::Layout::GetCount() const
{
	return m_count;
}

ValueType VertexAttribute::Layout::GetType() const
{
	return m_type;
}

Boolean VertexAttribute::Layout::GetNormilized() const
{
	return m_normilized;
}

GLuint VertexAttribute::Layout::GetOffset() const
{
	return m_offset;
}

VertexAttribute::Layout VertexAttribute::GetLayout() const
{
	return m_layout;
}

void VertexAttribute::SetLayout(const Layout& layout)
{
	m_layout = layout;
	glVertexAttribPointer(m_id, layout.GetCount(), static_cast<GLint>(layout.GetType()),
		static_cast<GLint>(layout.GetNormilized()), m_layout.GetTotalCount(), (void*)(layout.GetOffset()));
}

/*
* VertexAttribute
*/
VertexAttribute::VertexAttribute(const GLint id, const GLuint bufferSizeInBytes, const Layout& layout)
	: m_id{ id }, m_layout{ layout }
{
	SetLayout(layout);
}

VertexAttribute::~VertexAttribute()
{
}

GLint VertexAttribute::GetId() const
{
	return m_id;
}
