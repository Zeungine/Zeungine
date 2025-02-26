#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <zg/glm.hpp>
#include <zg/interfaces/IFile.hpp>
#include <zg/textures/Texture.hpp>
namespace zg
{
	struct Window;
}
namespace zg::fonts::freetype
{
	struct FreetypeFont;
	struct FreetypeCharacter
	{
		FT_UInt glyphIndex;
		std::shared_ptr<textures::Texture> texturePointer;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance;
		FreetypeCharacter(Window& window, const FreetypeFont& freeTypeFont, float codepoint, float fontSize);
	};
	struct FreetypeFont
	{
		static FT_Library freetypeLibrary;
		static bool freetypeLoaded;
		std::shared_ptr<FT_Face> facePointer;
		std::shared_ptr<int8_t> fontFileBytes;
		std::unordered_map<float, std::unordered_map<float, FreetypeCharacter>> codepointFontSizeCharacters;
		Window& window;
		std::string fontPath;
		/*add member variables in serial order*/
		FreetypeFont(Window& window, interfaces::IFile& fontFile);
		const glm::vec2 stringSize(const std::string_view string, float fontSize, float& lineHeight, glm::vec2 bounds);
		void stringToTexture(const std::string_view string, glm::vec4 color, float fontSize, float& lineHeight,
												 glm::vec2 textureSize, std::shared_ptr<textures::Texture>& texturePointer,
												 const int64_t& cursorIndex, glm::vec3& cursorPosition);
		FreetypeCharacter& getCharacter(float codepoint, float fontSize);
		static void FT_PRINT_AND_THROW_ERROR(const FT_Error& error, const std::string& fontPath);
	};
} // namespace zg::fonts::freetype
