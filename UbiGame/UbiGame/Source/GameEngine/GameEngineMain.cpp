#include "GameEngineMain.h"

#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Util/TextureManager.h"
#include "Util/AnimationManager.h"
#include "Util/CameraManager.h"
#include "Util/ParticleManager.h"
#include "Game/Map.h"
#include "UI/text.h"
#include "UI/UIView.h"
#include "UI/UIWindow.h"
#include "GameEngine\Util\Blockchain.h"

using namespace GameEngine;

const unsigned int GameEngineMain::WINDOW_HEIGHT = 720;
const unsigned int GameEngineMain::WINDOW_WIDTH = 1280;
//Nullptr init for singleton class
GameEngineMain* GameEngineMain::sm_instance = nullptr;
sf::Clock		GameEngineMain::sm_deltaTimeClock;
sf::Clock		GameEngineMain::sm_gameClock;

sf::Sprite sCursor;
sf::Sprite sCursorClicked;

GameEngineMain::GameEngineMain()
	: m_renderTarget(nullptr)	
	, m_windowInitialised(false)
	, m_gameBoard(nullptr)
{
	CreateAndSetUpWindow();
	//Load predefined textures
	TextureManager::GetInstance()->LoadTextures();
	//Create predefined animation definition vector
	AnimationManager::GetInstance()->InitStaticGameAnimations();

	CameraManager::GetInstance()->GetCameraView().setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	CameraManager::GetInstance()->GetCameraView().setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

	Text::init();
}


GameEngineMain::~GameEngineMain()
{
	delete m_renderTarget;
	delete m_view;
}


void GameEngineMain::OnInitialised()
{
	//Engine is initialised, this spot should be used for game object and clocks initialisation
	m_gameBoard = new Game::GameBoard();
	sm_deltaTimeClock.restart();
	sm_gameClock.restart();

	m_view = new UIView();
	m_view->init();
	m_window = new UIWindow();
	m_window->init();
	m_particleManager = new ParticleManager();
	m_particleManager->init();

	sCursor.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Cursor));
	sCursorClicked.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Cursor_clicked));
}


void GameEngineMain::CreateAndSetUpWindow()
{
	m_renderWindow = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Eternity");
	m_renderTarget = m_renderWindow;
}


void GameEngineMain::AddEntity(Entity* entity)
{
	auto found = std::find(m_entities.begin(), m_entities.end(), entity);
	assert(found == m_entities.end()); //Drop an assert if we add duplicate;
	if (found == m_entities.end())
	{
		m_entitiesToAdd.push_back(entity);		
	}	
}


void GameEngineMain::RemoveEntity(Entity* entity)
{
	auto found = std::find(m_entities.begin(), m_entities.end(), entity);
	if (found == m_entities.end())
	{
		found = std::find(m_entitiesToRemove.begin(), m_entitiesToRemove.end(), entity);
		assert(found != m_entitiesToRemove.end()); //Drop an assert if we remove a non existing entity (neither on entity list and on entity to remove list);
	}	

	if (found != m_entities.end())
	{
		m_entitiesToRemove.push_back(entity);
		entity->OnRemoveFromWorld();
	}	
}


void GameEngineMain::Update()
{		
	//First update will happen after init for the time being (we will add loading later)
	if (!m_windowInitialised)
	{
		m_windowInitialised = true;
		OnInitialised();
	}
	
	RemovePendingEntities();
	
	// UPDATES
	UpdateWindowEvents();
	if (m_gameBoard)
		m_gameBoard->Update();

	UpdateEntities();
	CameraManager::GetInstance()->update();

	// RENDER FUNCTIONS
	// Map::getInstance().render();
	RenderEntities();
	m_particleManager->render();

	if (m_view) m_view->render(m_renderTarget);
	if (m_window) m_window->render(m_renderTarget);

	// Render cursor based on whether click occurs (Need to take into account camera position)
	sf::Vector2i cam = sf::Vector2i(GameEngine::CameraManager::GetInstance()->GetCameraView().getCenter());
	sf::Vector2i scr = sf::Vector2i(GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->getSize()) / 2;
	sf::Vector2i pos = sf::Mouse::getPosition(*GameEngine::GameEngineMain::GetInstance()->GetRenderWindow());
	sCursor.setPosition(sf::Vector2f(pos + cam - scr));
	sCursorClicked.setPosition(sf::Vector2f(pos + cam - scr));
	m_renderTarget->draw(sf::Mouse::isButtonPressed(sf::Mouse::Left) ? sCursorClicked : sCursor);

	if (m_renderWindow && m_renderWindow->isOpen())
	{
		m_renderWindow->display();
	}

	AddPendingEntities();

	//We pool last delta and will pass it as GetTimeDelta - from game perspective it's more important that DT stays the same the whole frame, rather than be updated halfway through the frame
	m_lastDT = sm_deltaTimeClock.getElapsedTime().asSeconds();
	sm_deltaTimeClock.restart();

	// blockchain update
	if (m_blockclock.getElapsedTime().asSeconds() > 15) {
		m_blockclock.restart();

		sf::Vector2i playerPos = m_gameBoard->GetPlayerPosition();
		TileResource rvals = Map::getInstance().getResourceAt(playerPos.x, playerPos.y);

		Blockchain::TypedData td{ rvals.m_wood, rvals.m_ore, rvals.m_wool,playerPos.x, playerPos.y };
		json result = Blockchain::WriteTransaction(td);
		std::cout << result << std::endl;

		//Blockchain::TypedData fullSum = Blockchain::ReadTransactions();

		//m_view->set_resources(fullSum.wood, fullSum.ore, fullSum.wool);
	}
}


void GameEngineMain::AddPendingEntities()
{
	for (int a = 0; a < m_entitiesToAdd.size(); ++a)
	{
		m_entities.push_back(m_entitiesToAdd[a]);
		m_entitiesToAdd[a]->OnAddToWorld();
	}

	m_entitiesToAdd.clear();
}


void GameEngineMain::RemovePendingEntities()
{
	for (int a = 0; a < m_entitiesToRemove.size(); ++a)
	{
		Entity* entity = m_entitiesToRemove[a];

		auto found = std::find(m_entities.begin(), m_entities.end(), entity);
		assert(found != m_entities.end());

		if (found != m_entities.end())
		{
			m_entities.erase(found);

			delete entity;
		}
	}

	m_entitiesToRemove.clear();
}


void GameEngineMain::UpdateWindowEvents()
{
	if (!m_renderWindow)
		return;

	sf::Event event;
	while (m_renderWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_renderWindow->close();
			m_renderTarget = nullptr;		
			break;
		}
	}
}


void GameEngineMain::UpdateEntities()
{
	//Update que
	for each (auto entity in m_entities)
	{
		entity->Update();
	}
}


void GameEngineMain::RenderEntities()
{
	if (!m_renderTarget)
		return;

	//Here we use a windowRender target - it's more than enough for provided example, but in more complex versions this could end up flickering on the screen
	//If that is the case - one could try to implement doubleBuffer functionality, where the render target is a TEXTURE in memory and objects render there
	//And only at the last bit we render the prepared texture on the window.
	m_renderTarget->clear();

	//The VIEW is the way to control what renders in the window in a very convenient way - view does not modify the local coordinates, but rather than that it defines the rectangle that the window
	//Is supposed to render - by default our camera manager is not doing anything, as it was not needed in bird implementation, but it can be set to follow the player (by modifying the IsFollow enabled static return)
	//If that setting is on, PlayerCamera component will update the camera position to player position - making our camera center on player entity
	//With that test setting on, our bird implementation changes a bunch of rules, just so we can test it easilly
	m_renderTarget->setView(CameraManager::GetInstance()->GetCameraView());

	//Render the map explicitly cause fuck the entity queuing system.
	Map::getInstance().render();

	//Render que
	std::vector<RenderComponent*> renderers;
	//Every entity that has RenderComponent, or a component that extends RenderComponent - should end up in a render que
	for each (auto entity in m_entities)
	{
		if (RenderComponent* render = entity->GetComponent< RenderComponent >())
		{
			renderers.push_back(render);
		}
	}

	// sort using a lambda expression
	// We sort entities according to their Z level, meaning that the ones with that value lower will be draw FIRST (background), and higher LAST (player)
	std::sort(renderers.begin(), renderers.end(), [](RenderComponent* a, RenderComponent* b) 
	{
		return a->GetZLevel() < b->GetZLevel();
	});	

	for each (auto renderer in renderers)
	{		
		renderer->Render(m_renderTarget);
	}
}

