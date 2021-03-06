#include "LevelCell.h"

bool LevelCell::PassableIgnoreObject(const LevelObject* ignoreObj) const
{
	if (PassableIgnoreObject() == false)
	{
		return false;
	}
	for (const auto obj : objects)
	{
		if (obj == ignoreObj)
		{
			continue;
		}
		if (obj->Passable() == false)
		{
			return false;
		}
	}
	return true;
}

bool LevelCell::Passable() const
{
	if (PassableIgnoreObject() == false)
	{
		return false;
	}
	for (const auto obj : objects)
	{
		if (obj->Passable() == false)
		{
			return false;
		}
	}
	return true;
}

LevelObject* LevelCell::back() const
{
	if (objects.empty() == false)
	{
		return objects.back();
	}
	return nullptr;
}

LevelObject* LevelCell::front() const
{
	if (objects.empty() == false)
	{
		return objects.front();
	}
	return nullptr;
}

void LevelCell::addFront(LevelObject* obj)
{
	objects.insert(objects.begin(), obj);
}

void LevelCell::addBack(LevelObject* obj)
{
	objects.push_back(obj);
}

void LevelCell::removeObject(const LevelObject* obj)
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		if (*it == obj)
		{
			objects.erase(it);
			return;
		}
	}
}
