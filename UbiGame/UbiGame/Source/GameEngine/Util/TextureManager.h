#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1,
			Player,
			Cursor,
			Cursor_clicked,
			Grass,
			Water,
			Dirt,
			Icon_wood,
			Icon_ore,
			Icon_wool,
			UI_side_button,
			UI_side_button_clicked,
			UI_background,
			Count
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		switch (texture)
		{
		case eTexture::Player: return "player1.png";
		case eTexture::Cursor: return "icons/cursor.png";
		case eTexture::Cursor_clicked: return "icons/cursor_click.png";
		case eTexture::Icon_wood: return "icons/wood.png";
		case eTexture::Icon_ore: return "icons/ore.png";
		case eTexture::Icon_wool: return "icons/wool.png";
		case eTexture::UI_side_button: return "icons/UI_sidebar.png";
		case eTexture::UI_side_button_clicked: return "icons/UI_sidebar_press.png";
		case eTexture::UI_background: return "icons/UI_background.png";
		}

		return "UnknownTexType";
	}

	class TextureManager
	{
	public:
		static TextureManager* GetInstance() { if (!sm_instance) sm_instance = new TextureManager(); return sm_instance; }
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture* GetTexture(eTexture::type texture) const { return m_textures[(int)texture]; }

	private:
		TextureManager();
		static TextureManager* sm_instance;

		sf::Texture* m_textures[eTexture::Count];
	};
}

namespace TextureHelper
{
	static sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture)
	{
		switch (texture)
		{
			case  GameEngine::eTexture::Player:  return sf::Vector2f(32.f, 32.f);
		}

		return sf::Vector2f(-1.f, -1.f);
	}
}

