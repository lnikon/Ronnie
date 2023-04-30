#pragma once

#include <string>
#include <string_view>

class Texture final {
public:
	struct Description final
	{
		unsigned char* pData{nullptr};
		int width{ 0 };
		int height{ 0 };
		int numberOfChannels{ 0 };
	};

	Texture(std::string path);
	Texture(const Texture& other) = delete;
	Texture(Texture&& other) noexcept = delete;
	Texture& operator=(const Texture& other) = delete;
	Texture& operator=(Texture&& other) noexcept = delete;
	~Texture() = default;

	void Bind() const;

	[[nodiscard]] std::string GetPath() const;
	[[nodiscard]] Description GetDescription() const;
	[[nodiscard]] GLuint GetId() const;

private:
	static Description loadTextureInternal(const std::string_view path);
	static GLuint generate(const Description& description);

private:
	const std::string m_path;
	Description m_description;
	GLuint m_id;
};