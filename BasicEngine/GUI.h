#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <string>
#include <glm/glm.hpp>
#include <SDL/SDL_events.h>
namespace BasicEngine {
	class GUI
	{
	public:
		void init(const std::string& resourceDirectory);
		void destroy();

		void draw();
		void update();

		void onSDLEvent(SDL_Event& evnt);

		void loadScheme(const std::string& schemeFile);
		void setFont(const std::string& fontFile);
		CEGUI::Window* createWidget(const std::string& type,const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
		CEGUI::Window* createWidget(CEGUI::Window* parent,const std::string& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string& name = "");
		static void setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);

		//Mouse cursor stuff
		void setMouseCursor(const std::string& imgFile);
		void showMouseCursor();
		void hideMouseCursor();

		//getters
		static CEGUI::OpenGL3Renderer* getRenderer() { return _renderer; }
		const CEGUI::GUIContext* getContext() const { return _context; }
	private:
		static CEGUI::OpenGL3Renderer* _renderer;
		CEGUI::GUIContext* _context = nullptr;
		CEGUI::Window* _root = nullptr;
		unsigned int _lastTime = 0;
	};
}

