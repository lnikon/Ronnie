#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

enum class ShaderType {
	VERTEX = GL_VERTEX_SHADER,
	FRAGMENT = GL_FRAGMENT_SHADER,

	UNKOWN = -1,
};

enum class ShaderStatus {
	COMPILE = GL_COMPILE_STATUS,
	LINK = GL_LINK_STATUS,
};

std::string ShaderTypeToString(const ShaderType type);
bool checkCompileErrors(unsigned int shader, const ShaderType type, const ShaderStatus status);

class Shader {
public:
	Shader(const std::string& path, const ShaderType type);
	Shader(const Shader&) = default;
	Shader(Shader&&) = default;
	Shader& operator=(const Shader&) = default;
	Shader& operator=(Shader&&) = default;
	~Shader();

	GLuint GetId() const;

private:
	GLuint generate(std::string_view) const;
	std::string readShaderFile(std::string_view) const;

private:
	// TODO: switch to fs::path
	const std::string m_path;
	const ShaderType m_type;
	const std::string m_code;
	GLuint m_id;
};

class ShaderProgramm {
public:
	ShaderProgramm();
	ShaderProgramm(const ShaderProgramm&) = default;
	ShaderProgramm(ShaderProgramm&&) = default;
	ShaderProgramm& operator=(const ShaderProgramm&) = default;
	ShaderProgramm& operator=(ShaderProgramm&&) = default;
	~ShaderProgramm() = default;

	// TODO: Add some logic to check if shader is allowed
	Shader& AddShader(Shader shader);
	bool Create();
	void Use();

	GLuint GetId() const;

	void SetInt(std::string_view name, int value) const;
	void SetFloat(std::string_view name, float value) const;
	void SetBool(std::string_view name, bool value) const;
	void SetMat4f(std::string_view name, glm::mat4 value);

private:
	const GLuint m_id;
	std::vector<Shader> m_shaders;
};
