#include "Texture.h"

#include <stdexcept>

std::unordered_map<std::string, std::shared_ptr<Texture>> Texture::cache;

Texture::Texture(const std::string& fileLocation) : textureID(0) {
	GLint width, height, bitDepth;
	
	textureData = stbi_load(fileLocation.c_str(), &width, &height, &bitDepth, 0);

	// If image fails to load, the `failed` image will appear 
	if (textureData == 0) {
		stbi_image_free(textureData);
		const std::string failedFileLocation = FAILED_TEXTURE_LOCATION;
		textureData = stbi_load(failedFileLocation.c_str(), &width, &height, &bitDepth, 0);
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(textureData);
}

std::shared_ptr<Texture> Texture::get(std::string name) {
	auto it = cache.find(name);

	if (it == cache.end()) {
		it = cache.emplace(name, std::make_shared<Texture>(name)).first;
	}

	return it->second;
}

Texture::Texture(Texture&& tex) noexcept : textureID(tex.textureID) {
	tex.textureID = 0;
}

Texture& Texture::operator=(Texture&& tex) noexcept {
	using std::swap;
	swap(textureID, tex.textureID);
	return *this;
}

void Texture::useTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbindAll() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &textureID);
}