#include "Game.h"
#include <iostream>
#include <string>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() 
	: mWindow(sf::VideoMode(640, 480), "Shoot'em up !")
	, mWorld(mWindow)
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	//TODO utiliser RessourceHolder
	mFont.loadFromFile("Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}
		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time dt)
{
	mWorld.update(dt);
}

void Game::render()
{
	mWindow.clear();

	sf::Text text;
	text.setString("Hello world");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	mWindow.draw(text);

	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);

	
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	//  Echap
	if (key == sf::Keyboard::Escape)
		mWindow.close();
}
