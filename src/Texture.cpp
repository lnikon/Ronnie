#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include "Texture.h"

Texture::Texture(std::string path)
	: m_path{std::move(path)},
	  m_description{loadTextureInternal(GetPath())},
	  m_id{generate(GetDescription())}
{
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

std::string Texture::GetPath() const
{
	return m_path;
}

Texture::Description Texture::GetDescription() const
{
	return m_description;
}

GLuint Texture::GetId() const
{
	return m_id;
}

Texture::Description Texture::loadTextureInternal(const std::string_view path)
{
	Description parameters;
	parameters.pData = stbi_load(path.data(),
	                             &parameters.width,
	                             &parameters.height,
	                             &parameters.numberOfChannels,
	                             0);
	return parameters;
}

GLuint Texture::generate(const Description& description)
{
	GLuint id{0};
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		description.width,
		description.height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		description.pData);
	glGenerateMipmap(GL_TEXTURE_2D);

	// TODO: Find better place for this
	stbi_image_free(description.pData);

	return id;
}
