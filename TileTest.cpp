#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <ctime>

int main()
{
	//Create the rendering window
	sf::RenderWindow TileTest(sf::VideoMode(800, 600, 32), "Tile Test");
	
	// Load the images from files
  std::vector<sf::Image> images(2); // Preset the vector to 2 images
  if (!images[0].LoadFromFile("TestTile.png")) 
	  return EXIT_FAILURE;
  	
  if (!images[1].LoadFromFile("TestTile2.png")) 
	  return EXIT_FAILURE;
	
	sf::Image TestPlayerImage;
	if (!TestPlayerImage.LoadFromFile("circle.png"))
		return EXIT_FAILURE;
	
	// Create the sprites
  std::vector<sf::Sprite> tiles(2); // Preset the vector to 2 sprites
  tiles[0] = sf::Sprite(images[0]); // green
  tiles[1] = sf::Sprite(images[1]); // blue
	
	sf::Sprite TestPlayer(TestPlayerImage);	
	TestPlayer.SetPosition(90.f, 40.f);
		  
	//set up the map
	std::vector< std::vector<int> > map(11, std::vector<int>(35));
  
	//random seed  
	srand(time(0));	
	
	//randomly generate blue tiles
	for (int count = 0; count < 10; count++)
	{
	int RandomTileX = rand() %11;
	int RandomTileY = rand() %35;
	map[RandomTileX][RandomTileY] = 1;
	}	
		
	//running loop
	while (TileTest.IsOpened())
	{
		sf::Event Event;
		while (TileTest.GetEvent(Event))
		{
		  //Close window : exit
			if (Event.Type == sf::Event::Closed)
				TileTest.Close();
			
			//Escape key : exit	
			if ((Event.Type == sf::Event::KeyPressed) 
			&& (Event.Key.Code == sf::Key::Escape))
				TileTest.Close();
		}
	
	//Get elapsed time	
	float ElapsedTime = TileTest.GetFrameTime();
		
	//Move the player
	if (TileTest.GetInput().IsKeyDown(sf::Key::W))
	  if (TestPlayer.GetPosition().y > 16)
  		TestPlayer.Move(0, -16);	
			
	if (TileTest.GetInput().IsKeyDown(sf::Key::S))
	  if (TestPlayer.GetPosition().y < 550)
  		TestPlayer.Move(0, 16);	
	
	if (TileTest.GetInput().IsKeyDown(sf::Key::A))
	  if (TestPlayer.GetPosition().x > 64)
  		TestPlayer.Move(-32, 0);	
			
	if (TileTest.GetInput().IsKeyDown(sf::Key::D))
	  if (TestPlayer.GetPosition().x < 730)
  		TestPlayer.Move(32, 0);
	
	//clear the screen
	TileTest.Clear();
	
	//draw the map	
	for (int x = 0; x < map.size (); x++) 
	{	    
	  for (int y = 0; y < map[x].size (); y++) 
		{
		  int tileId = map[x][y];
      // Get the tile's image
      const sf::Image* image = tiles[tileId].GetImage();
      // Get the width and height of the image
      int width = image->GetWidth();
      int height = image->GetHeight();
			if ((y % 2) == 1)
			{
				// Adjust the offset by using the width
        tiles[tileId].SetPosition(x * width + width / 2 + 32, y * height / 2); 
			}
			else
			{
        // Adjust the offset by using the width
        tiles[tileId].SetPosition(x * width + 32, y * height / 2);        
      }
			TileTest.Draw(tiles[tileId]);
    }
	}	
	TileTest.Draw(TestPlayer);
	TileTest.Display();
	}
}
