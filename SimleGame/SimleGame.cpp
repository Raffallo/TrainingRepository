// SimleGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"


sf::Sprite items[3072];

class EQItem
{
public:
	int type;
	int itemNumber = -1;
	int slotNumber;
	sf::String name;
	sf::Sprite itemIcon;
};


void LoadItems()
{
	for (int i = 0; i < 3072; i++)
	{
		int y = i / 64;
		int x = i - y * 64;
		items[i].setTextureRect(sf::IntRect(x * 32, y * 32, 32, 32));
	}
}

void SetItemsTexture(const sf::Texture& itemTexture)
{
	for (int i = 0; i < 3072; i++)
	{
		items[i].setTexture(itemTexture);
	}
}

class Slot
{
public:
	int number = -1;
	int type = 8;
	sf::IntRect rect;
	void SetRect(int left, int top, int width, int height)
	{
		rect.left = left;
		rect.top = top;
		rect.width = width;
		rect.height = height;
	}
	sf::Vector2f GetDrawinPoint()
	{
		sf::Vector2f tempVect;
		tempVect.x = rect.left + 2;
		tempVect.y = rect.top + 2;
		return tempVect;
	}
};

std::vector<Slot> availableItemSlots;

void AddItemSlots() //54 slots
{
	int number = 0;
	int y = 166; int x = 14;
	for (int i = 0; i < 27; i++)
	{
		Slot tempSlot;
		tempSlot.number = number;
		number++;
		int tempY = i / 9;
		int tempX = i - tempY * 9;
		tempSlot.SetRect(tempX * 36 + x, tempY * 36 + y, 36, 36);
		availableItemSlots.push_back(tempSlot);
	}
	y = 282;
	for (int i = 0; i < 9; i++)
	{
		Slot tempSlot;
		tempSlot.number = number;
		number++;
		int tempY = i / 9;
		int tempX = i - tempY * 9;
		tempSlot.SetRect(tempX * 36 + x, tempY * 36 + y, 36, 36);
		availableItemSlots.push_back(tempSlot);
	}
	x = 358; y = 184;
	for (int i = 0; i < 4; i++)
	{
		Slot tempSlot;
		tempSlot.number = number;
		number++;
		int tempY = i / 2;
		int tempX = i - tempY * 2;
		tempSlot.SetRect(tempX * 36 + x, tempY * 36 + y, 36, 36);
		availableItemSlots.push_back(tempSlot);
	}
	y = 262;
	for (int i = 0; i < 2; i++)
	{
		Slot tempSlot;
		tempSlot.number = number;
		number++;
		int tempY = i / 2;
		int tempX = i - tempY * 2;
		tempSlot.SetRect(tempX * 36 + x, tempY * 36 + y, 36, 36);
		availableItemSlots.push_back(tempSlot);
	}
	x = 248; y = 32;
	for (int i = 0; i < 4; i++)
	{
		Slot tempSlot;
		tempSlot.number = number;
		number++;
		int tempY = i / 2;
		int tempX = i - tempY * 2;
		tempSlot.SetRect(tempX * 36 + x, tempY * 36 + y, 36, 36);
		availableItemSlots.push_back(tempSlot);
	}
	x = 14; y = 14;
	for (int i = 0; i < 4; i++)
	{
		Slot tempSlot;
		tempSlot.number = number;
		number++;
		int tempY = i / 1;
		int tempX = i - tempY * 1;
		tempSlot.SetRect(tempX * 36 + x, tempY * 36 + y, 36, 36);
		availableItemSlots.push_back(tempSlot);
	}
	x = 158;
	for (int i = 0; i < 4; i++)
	{
		Slot tempSlot;
		tempSlot.number = number;
		number++;
		int tempY = i / 1;
		int tempX = i - tempY * 1;
		tempSlot.SetRect(tempX * 36 + x, tempY * 36 + y, 36, 36);
		availableItemSlots.push_back(tempSlot);
	}
}

class EQInventory : public sf::Drawable
{
public:
	std::vector<EQItem> m_items;
public:
	void AddItem(EQItem& newItem)
	{
		bool isInside = false;
		for (auto item : m_items)
		{
			if (item.slotNumber == newItem.slotNumber)isInside = true;
		}
		if (!isInside)
		{
			sf::Vector2f tempVect = availableItemSlots[newItem.slotNumber].GetDrawinPoint();
			newItem.itemIcon.setPosition(tempVect);
			m_items.push_back(newItem);
		}
	}
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override
	{
		for (auto& item : m_items)
		{
			target.draw(item.itemIcon);
		}
	}
	int IsItemSelected(sf::Vector2i mousePos)
	{
		int i = 0;
		for (auto& item : m_items)
		{
			if (availableItemSlots[item.slotNumber].rect.contains(mousePos))
			{
				return i;
			}
			i++;
		}
		return -1;
	}
	void MoveItem(int itemID, const sf::Vector2f& moveVector)
	{
		if (itemID >= m_items.size()) return;
		m_items[itemID].itemIcon.move(moveVector);
	}
	void SetItemTempPos(int itemID, const sf::Vector2f& posVector)
	{
		if (itemID >= m_items.size()) return;
		m_items[itemID].itemIcon.setPosition(posVector);
	}
	void SetNewItemPos(int itemID, const sf::Vector2i mousePos)
	{
		bool isNewPosOk = false;
		for (auto slot : availableItemSlots)
		{
			if (!slot.rect.contains(mousePos)) continue;
			bool isItemsSwaped = false;
			for (int i = 0; i < m_items.size(); i++)
			{
				if (i == itemID)continue;
				if (m_items[i].slotNumber != slot.number) continue;

				m_items[i].slotNumber = m_items[itemID].slotNumber;
				sf::Vector2f tempVect = availableItemSlots[m_items[i].slotNumber].GetDrawinPoint();
				m_items[i].itemIcon.setPosition(tempVect);
				break;
			}	
				m_items[itemID].slotNumber = slot.number;
				sf::Vector2f tempVect = availableItemSlots[m_items[itemID].slotNumber].GetDrawinPoint();
				m_items[itemID].itemIcon.setPosition(tempVect);
				isNewPosOk = true;
				return;
		}
		if (!isNewPosOk)
		{
			sf::Vector2f tempVect = availableItemSlots[m_items[itemID].slotNumber].GetDrawinPoint();
			m_items[itemID].itemIcon.setPosition(tempVect);
		}
	}
};

int main()
{
	AddItemSlots();
	//load items \/
	sf::Texture itemTexture;
	if (!itemTexture.loadFromFile("EQItems.png"))
	{
		sf::String c = "dsd";
	}
	SetItemsTexture(itemTexture);
	LoadItems();
	//load items /\
	//load EQ slots\/
	sf::Texture eqSlotsTexture;
	if (!eqSlotsTexture.loadFromFile("EQSlots.png"))
	{
		sf::String c = "dsd";
	}
	sf::Sprite EQSlots(eqSlotsTexture);
	//load EQ slots/\
	//load Character \/
	sf::Texture characterTexture;
	if (!characterTexture.loadFromFile("Char1.png"))
	{
		sf::String c = "dsd";
	}
	sf::Sprite Character(characterTexture);
	Character.setPosition(52, 16);
	//load Character /\
	//load trees \/
	sf::Texture treesTexture;
	if (!treesTexture.loadFromFile("trees.png"))
	{
		sf::String c = "dsd";
	}
	sf::Sprite Trees(treesTexture);
	Trees.setPosition(52, 16);
	//load Character /\
	//load Cursor \/
	sf::Texture CursorTexture;
	if (CursorTexture.loadFromFile("cursor.png"))
	{
		sf::String c = "dsd";
	}
	sf::Sprite Cursor(CursorTexture);
	//load Cursor /\
	//load Item Info Texture \/
	sf::Texture ItemInfoTexture;
	if (ItemInfoTexture.loadFromFile("ItemInfoFrame.png"))
	{
		sf::String c = "dsd";
	}
	sf::Sprite ItemInfoFrame(ItemInfoTexture);
	//load Cursor /\

	EQInventory eqInventory;
	for (int i = 0; i < 10; i++) //54
	{
		EQItem tempItem;
		tempItem.itemIcon = items[1722 + i];
		tempItem.slotNumber = i;
		tempItem.type = 1;
		tempItem.itemNumber = 1722 + i;
		eqInventory.AddItem(tempItem);
	}

	//sf::VideoMode::getFullscreenModes()[5]  \/
	sf::RenderWindow window{ sf::VideoMode{800,600}, "Main window" }; // , sf::Style::Fullscreen};
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);

	sf::Font TextFont;
	TextFont.loadFromFile("Amiko.ttf");

	bool isMoved = false;
	bool isItemInfoMenu = false;
	float dx = 0, dy = 0;
	int n = -1;
	sf::Vector2f oldPos;

	sf::Text tekst("", TextFont, 15);

	while (window.isOpen())
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);

		sf::Event windowEvent;
		while (window.pollEvent(windowEvent))
		{
			if (windowEvent.type == sf::Event::Closed)
			{
				window.close();
				return 0;
			}
			if (windowEvent.type == sf::Event::KeyPressed)
			{
				if (windowEvent.key.code == sf::Keyboard::Escape)
				{
					window.close();
					return 0;
				}
			}
			//drag&drop
			if (windowEvent.type == sf::Event::MouseButtonPressed)
				if (windowEvent.key.code == sf::Mouse::Left)
				{
					n = eqInventory.IsItemSelected(pos);
					if (n != -1)
					{
						dx = pos.x - eqInventory.m_items[n].itemIcon.getPosition().x;
						dy = pos.y - eqInventory.m_items[n].itemIcon.getPosition().y;
						isMoved = true;
					}
				}
			if (windowEvent.type == sf::Event::MouseButtonReleased)
				if (windowEvent.key.code == sf::Mouse::Left)
				{
					if (n == -1) continue;
					isMoved = false;
					eqInventory.SetNewItemPos(n, pos);
					n = -1;
				}
			//~drag&drop
			//item info frame
			if (!isMoved)
			{
				n = eqInventory.IsItemSelected(pos);
				if (n != -1)
				{
					ItemInfoFrame.setPosition(pos.x + 15, pos.y + 15);

					//sf::String tekst(L"abcd ąłĆ");
					
					sf::String str;
					str += "Item slot: ";
					str += std::to_string(eqInventory.m_items[n].slotNumber);
					str += "\nIEQ item number: ";
					str += std::to_string(n);
					str += "\nItem number: ";
					str += std::to_string(eqInventory.m_items[n].itemNumber);
					tekst.setString(str);
					tekst.setPosition(ItemInfoFrame.getPosition() + sf::Vector2f(10, 45));
					isItemInfoMenu = true;
				}
				else isItemInfoMenu = false;
			}
			//~item info frame
		}
		auto mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		if (mousePos.x <= 0 || mousePos.y <= 0)
		{
			mousePos.x = -100;
			mousePos.y = -100;
		}
		Cursor.setPosition(mousePos);
		if (isMoved && n > -1)
		{
			sf::Vector2f tempVect;
			tempVect.x = pos.x - dx;
			tempVect.y = pos.y - dy;
			eqInventory.SetItemTempPos(n, tempVect);
		}
		
		window.clear(sf::Color::Blue);
		window.draw(EQSlots);
		window.draw(Trees);
		window.draw(Character);
		window.draw(eqInventory);
		if (isItemInfoMenu && !isMoved)
		{
			window.draw(ItemInfoFrame);
			window.draw(tekst);
		}
		//it need to be last
		window.draw(Cursor);
		window.display();		
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
