#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include <SDL_image.h>
#include "TextureManager.h"
#include <iostream>

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);

		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		}

		m_bRunning = true;

		if (!TheTextureManager::Instance()->load("assets/animate-alpha.png", "player", m_pRenderer))
		{
			return false;
		}
		if (!TheTextureManager::Instance()->load("assets/animate-enemy.png", "enemy", m_pRenderer))
		{
			return false;
		}
		
		m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "player")));
		m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "enemy")));

	}
	else 
	{
		return false; 
	}
	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer); 
	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	TheInputHandler::Instance()->clean();
	SDL_Quit();
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
}

void Game::update()
{
	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void Game::quit()
{

}