#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <cstddef>

enum class Boolean {
	TRUTHY = GL_TRUE,
	FALSY  = GL_FALSE,
};

enum class ValueType {
	FLOAT = GL_FLOAT,
};

GLuint CalculateValueSize(const ValueType value);

class VertexAttribute {
public:
	class Layout {
	public:
		Layout(const GLuint totalCount, const GLuint count, const ValueType type, const Boolean normilized, const GLuint offset);
		Layout(const Layout&) = default;
		Layout(Layout&&) = default;
		Layout& operator=(const Layout&) = default;
		Layout& operator=(Layout&&) = default;
		~Layout();

		GLuint GetTotalCount() const;
		GLuint GetCount() const;
		ValueType GetType() const;
		Boolean GetNormilized() const;
		GLuint GetOffset() const;

	private:
		GLuint m_totalCount{ 0 };
		GLuint m_count{ 0 };
		ValueType m_type{};
		Boolean m_normilized{};
		GLuint m_offset{};
	};

	VertexAttribute(const GLint id, const GLuint attributeCount, const Layout& layout);
	VertexAttribute(const VertexAttribute&) = default;
	VertexAttribute(VertexAttribute&&) = default;
	VertexAttribute& operator=(const VertexAttribute&) = default;
	VertexAttribute& operator=(VertexAttribute&&) = default;
	~VertexAttribute();

	GLint GetId() const;
	Layout GetLayout() const;
	void SetLayout(const Layout& layout);

private:
	GLint m_id;
	Layout m_layout;
};

/*
*/
class VertexArray {
public:
	VertexArray();
	VertexArray(const VertexArray&) = delete;
	VertexArray(VertexArray&&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;
	VertexArray& operator=(VertexArray&&) = delete;
	~VertexArray();

	void Bind() const;

	void AddAttribute(const ValueType type, const GLuint count);
	void EnableAttribute(const GLint id = -1);

	GLuint GetBufferSizeInBytes() const;

private:
	GLuint generate() const;
	void enableAttributeInternal(const VertexAttribute& attribute) const;

private:
	const GLuint m_vao{ 0 };
	std::vector<VertexAttribute> m_vertexAttributes;
};