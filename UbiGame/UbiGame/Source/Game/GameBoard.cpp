#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\CollidablePhysicsComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine\Util\Network.h"

#include "Game\Components\PlayerMovementComponent.h"

using namespace Game;

#include <iostream>
GameBoard::GameBoard()
	: m_player(nullptr)
{
	CreatePlayer();
	CreateObstacle();

	// system("curl \"https://testnet-algorand.api.purestake.io/ps1/v1/account/3ZVAYYEOZRPXD3XDNS3YRHP2CQ4RBPPUVL4HFIAOFVQXZ2TRKYBKLDMK6I\" -H \"Host: testnet-algorand.api.purestake.io\" -H \"X-API-Key: B3SU4KcVKi94Jap2VXkK83xx38bsv95K5UZm2lab\" -o test.txt");
	std::string url = "https://testnet-algorand.api.purestake.io/ps1/v1/account/3ZVAYYEOZRPXD3XDNS3YRHP2CQ4RBPPUVL4HFIAOFVQXZ2TRKYBKLDMK6I";
	std::vector<std::string> headers;
	headers.emplace_back("Host: testnet-algorand.api.purestake.io");
	headers.push_back("X-API-Key: B3SU4KcVKi94Jap2VXkK83xx38bsv95K5UZm2lab");
	std::string result = Network::GetRequest(url, headers);
	std::cout << result << std::endl;
}


GameBoard::~GameBoard()
{

}


void GameBoard::CreatePlayer()
{
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	
	m_player->SetPos(sf::Vector2f(150.f, 150.f));
	m_player->SetSize(sf::Vector2f(50.f, 50.f));
	
	//Render
	GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>
												      (m_player->AddComponent<GameEngine::SpriteRenderComponent>());

	spriteRender->SetFillColor(sf::Color::Transparent);
	spriteRender->SetTexture(GameEngine::eTexture::Player);

	//Movement
	m_player->AddComponent<PlayerMovementComponent>();
	m_player->AddComponent<GameEngine::AnimationComponent>();

	m_player->AddComponent<GameEngine::CollidablePhysicsComponent>();
}


void GameBoard::CreateObstacle()
{
	GameEngine::Entity* obstacle = new GameEngine::Entity();	
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);

	obstacle->SetPos(sf::Vector2f(350.f, 150.f));
	obstacle->SetSize(sf::Vector2f(150.f, 150.f));

	//Render
	GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>
		(obstacle->AddComponent<GameEngine::SpriteRenderComponent>());

	spriteRender->SetFillColor(sf::Color::Transparent);
	spriteRender->SetTexture(GameEngine::eTexture::Obstacle);

	obstacle->AddComponent<GameEngine::CollidableComponent>();
}


void GameBoard::Update()
{	
	
}