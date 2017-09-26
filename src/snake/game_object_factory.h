#ifndef __GAME_OBJECT_FACTORY_H__
#define __GAME_OBJECT_FACTORY_H__


#include <string>
#include <map>
#include <iostream>

#include "game_object.h"

class BaseCreator
{
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:
    bool registerType(std::string typeID, BaseCreator* pCreator);

    GameObject* create(std::string typeID);

    static GameObjectFactory* instance();

private:
    std::map<std::string, BaseCreator*> m_creators;
    static GameObjectFactory* s_pInstance;
};

#endif
