#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstddef>
#include <vector>

enum class BufferType {
  ARRAY_BUFFER = GL_ARRAY_BUFFER,
  ELEMENT_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
};

/*
 * Class representing an OpenGL buffer of type GL_ARRAY_BUFFER.
 * On construction, will automatically generate a buffer, bind it, and fill with
 * data.
 */
template <typename ValueType> class Buffer {
public:
  Buffer(const BufferType bufferType, const std::vector<ValueType> &data,
         const int drawHint = GL_STATIC_DRAW);
  Buffer(const Buffer &) = delete;
  Buffer(Buffer &&) = delete;
  Buffer &operator=(const Buffer &) = delete;
  Buffer &operator=(Buffer &&) = delete;
  ~Buffer();

private:
  GLuint generate(std::vector<ValueType> data,
                  const int drawHint = GL_STATIC_DRAW) const;

private:
  const BufferType m_bufferType;
  const std::vector<ValueType> m_data;
  const int m_drawHint;
  const GLuint m_vbo{0};
};

template <typename ValueType>
Buffer<ValueType>::Buffer(const BufferType bufferType,
                          const std::vector<ValueType> &data,
                          const int drawHint)
    : m_bufferType{bufferType},
      m_data(data), m_drawHint{drawHint}, m_vbo{generate(m_data, m_drawHint)} {}

template <typename ValueType> inline Buffer<ValueType>::~Buffer() {
  glDeleteBuffers(1, &m_vbo);
}

template <typename ValueType>
inline GLuint Buffer<ValueType>::generate(std::vector<ValueType> data,
                                          const int drawHint) const {
  GLuint vbo{0};
  const int count{1};

  glGenBuffers(count, &vbo);
  glBindBuffer(static_cast<GLenum>(m_bufferType), vbo);
  glBufferData(static_cast<GLenum>(m_bufferType),
               data.size() * sizeof(ValueType), data.data(), drawHint);

  return vbo;
}
