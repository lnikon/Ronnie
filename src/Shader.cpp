#include <fstream>
#include <sstream>

#include "Shader.h"

Shader::Shader(const std::string &path, const ShaderType type)
    : m_path{path}, m_type{type}, m_code{readShaderFile(m_path)}, m_id{generate(
                                                                      m_code)} {

}

Shader::~Shader() {}

GLuint Shader::GetId() const { return m_id; }

GLuint Shader::generate(std::string_view code) const {
  const char *pShaderCode = code.data();

  GLuint id = glCreateShader(static_cast<GLuint>(m_type));
  glShaderSource(id, 1, &pShaderCode, nullptr);
  glCompileShader(id);
  checkCompileErrors(id, m_type, ShaderStatus::COMPILE);

  return id;
}

std::string Shader::readShaderFile(std::string_view path) const {
  std::ifstream shaderFile;
  shaderFile.open(path.data());
  if (!shaderFile.is_open()) {
    std::cerr << "(Shader::Shader(const std::string&)): unable to open shader "
                 "file by path="
              << path << std::endl;
    return "";
  }

  return std::string{(std::istreambuf_iterator<char>(shaderFile)),
                     std::istreambuf_iterator<char>()};
}

std::string ShaderTypeToString(const ShaderType type) {
  switch (type) {
  case ShaderType::UNKOWN:
    return "UNKOWN";
  case ShaderType::VERTEX:
    return "VERTEX";
  case ShaderType::FRAGMENT:
    return "FRAGMENT";
  default:
    return "";
    break;
  }
}

bool checkCompileErrors(unsigned int shader, const ShaderType type,
                        const ShaderStatus status) {
  int success;
  char infoLog[1024];

  if (status == ShaderStatus::COMPILE) {
    glGetShaderiv(shader, static_cast<GLenum>(status), &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: "
                << ShaderTypeToString(type) << "\n"
                << infoLog << std::endl;
      return false;
    }
  } else if (status == ShaderStatus::LINK) {
    glGetProgramiv(shader, static_cast<GLenum>(status), &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cerr
          << "ERROR::PROGRAM_LINKING_ERROR of type: "
          << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
      return false;
    }
  } else {
    std::cerr << "(Shader::checkCompileErrors): Unkown ShaderCompileStatus as "
                 "argument";
    return false;
  }

  return true;
}

ShaderProgramm::ShaderProgramm() : m_id{glCreateProgram()} {}

Shader &ShaderProgramm::AddShader(Shader shader) {
  Shader &last{m_shaders.emplace_back(std::move(shader))};
  glAttachShader(GetId(), last.GetId());
  return last;
}

bool ShaderProgramm::Create() {
  glLinkProgram(GetId());
  if (checkCompileErrors(GetId(), ShaderType::UNKOWN, ShaderStatus::LINK)) {
    // TODO: Find better place/way to do this deletion
    /*for (const auto& shader : m_shaders) {
        glDeleteShader(shader.GetId());
    }*/
  }

  return false;
}

GLuint ShaderProgramm::GetId() const { return m_id; }

void ShaderProgramm::SetInt(std::string_view name, int value) const {
  glUniform1i(glGetUniformLocation(GetId(), name.data()), value);
}

void ShaderProgramm::SetFloat(std::string_view name, float value) const {
  glUniform1f(glGetUniformLocation(GetId(), name.data()), value);
}

void ShaderProgramm::SetBool(std::string_view name, bool value) const {
  glUniform1i(glGetUniformLocation(GetId(), name.data()), value);
}

void ShaderProgramm::SetMat4f(std::string_view name, glm::mat4 value) {
  glUniformMatrix4fv(glGetUniformLocation(GetId(), name.data()), 1, GL_FALSE,
                     glm::value_ptr(value));
}

void ShaderProgramm::Use() { glUseProgram(GetId()); }
