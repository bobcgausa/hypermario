/**
 * @author Lenoa
 */

#include "Mario.h"

#include <SFML/Graphics.hpp>

#include "config.h"
#include "Tile.h"
#include "TileAttributes.h"

/**
 * It updates the Mario
 *
 * @author Lenoa
 */
void Mario::Update()
{
	if(mySprite.GetPosition().x > myPosX * Tile::GetDimensionX())
		mySprite.Move(-2, 0);
	else if(mySprite.GetPosition().x < myPosX * Tile::GetDimensionX())
		mySprite.Move(+2, 0);
	else
		myIsMoving = false;
}

/**
 * @return the view centered on Mario if possible
 * @author Lenoa
 */
sf::View Mario::GetView() const
{
	// Compute the view centred on Mario
	long
		l = mySprite.GetPosition().x + (mySprite.GetSize().x / 2) - (WINDOW_WIDTH / 2),
		r = l + WINDOW_WIDTH,
		t = mySprite.GetPosition().y + (mySprite.GetSize().y / 2) - (WINDOW_HEIGHT / 2),
		b = t + WINDOW_HEIGHT;

	// Re-centrate (if out of the limits of the map)
	if(l < 0)
	{
		l = 0;
		r = WINDOW_WIDTH;
	}
	if(t < 0)
	{
		t = 0;
		b = WINDOW_HEIGHT;
	}
	if(static_cast<unsigned long>(r) > (myMap->GetMaxX() + 1) * Tile::GetDimensionX())
	{
		r = (myMap->GetMaxX() + 1) * Tile::GetDimensionX();
		l = r - WINDOW_WIDTH;
	}
	if(static_cast<unsigned long>(b) > (myMap->GetMaxY() + 1) * Tile::GetDimensionY())
	{
		b = (myMap->GetMaxY() + 1) * Tile::GetDimensionY();
		t = b - WINDOW_HEIGHT;
	}

	// Return the view
	return sf::View(sf::FloatRect(l, t, r, b));
}

/**
 * It renders the mario to the target
 *
 * @param Target the target on which render
 * @author Lenoa
 */
void Mario::Render(sf::RenderTarget &Target) const
{
	Target.Draw(mySprite);
}

/**
 * @return true if Mario can go to the left, false otherwise
 * @author Lenoa
 */
bool Mario::CanGoLeft() const
{
       	return (
		myPosX > 0 && (
			mySize == Little ? (myMap->TileAtPos(myPosX - 1, myPosY).GetAttributes() & TileAttributes::Empty) : (
				(myMap->TileAtPos(myPosX - 1, myPosY + 1).GetAttributes() & TileAttributes::Empty) &&
				(myMap->TileAtPos(myPosX - 1, myPosY    ).GetAttributes() & TileAttributes::Empty)
			)
		)
	);
}
/**
 * @return true if Mario can go to the right, false otherwise
 * @author Lenoa
 */
bool Mario::CanGoRight() const
{
       	return (
		myPosX < myMap->GetMaxX() && (
			mySize == Little ? (myMap->TileAtPos(myPosX + 1, myPosY).GetAttributes() & TileAttributes::Empty) : (
				(myMap->TileAtPos(myPosX + 1, myPosY + 1).GetAttributes() & TileAttributes::Empty) &&
				(myMap->TileAtPos(myPosX + 1, myPosY    ).GetAttributes() & TileAttributes::Empty)
			)
		)
	);
}

