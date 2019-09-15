#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\CollidablePhysicsComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine\Util\Blockchain.h"

#include "Game\Components\PlayerMovementComponent.h"
#include "Map.h"

using namespace Game;

#include <iostream>
GameBoard::GameBoard()
	: m_player(nullptr)
{
	CreatePlayer();

	//string playerAddress = Blockchain::NewUserKey();

	json result = Blockchain::GetVersion();
	std::cout << result << std::endl;

	Blockchain::TypedData td{ 1,1,1,0,0 };

	result = Blockchain::WriteTransaction(td);
	std::cout << result << std::endl;

	Blockchain::ReadTransactions();
	

	//std::string url = "https://postman-echo.com/post";
	//std::vector<std::string> headers;
	//headers.emplace_back("Host: testnet-algorand.api.purestake.io");
	//headers.push_back("X-API-Key: B3SU4KcVKi94Jap2VXkK83xx38bsv95K5UZm2lab");
	//json data;
	//data["test"] = 3;
	//data["test2"] = "stringggg";
	//json result = Network::PostRequest(url, headers, data);
	//std::cout << result << std::endl;
}


GameBoard::~GameBoard()
{

}


void GameBoard::CreatePlayer()
{
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	
	m_player->SetPos(sf::Vector2f(150.f, 150.f));
	m_player->SetSize(sf::Vector2f(20.f, 50.f));
	
	//Render
	GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>
												      (m_player->AddComponent<GameEngine::SpriteRenderComponent>());

	spriteRender->SetFillColor(sf::Color::Blue);
	spriteRender->SetTexture(GameEngine::eTexture::Player);

	//Movement
	m_player->AddComponent<PlayerMovementComponent>();
	m_player->AddComponent<GameEngine::AnimationComponent>();

	m_player->AddComponent<GameEngine::CollidablePhysicsComponent>();
}


void GameBoard::Update()
{	

}
