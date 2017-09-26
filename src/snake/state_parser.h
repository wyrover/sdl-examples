#ifndef __STATE_PARSER_H__
#define __STATE_PARSER_H__

#include <iostream>
#include <vector>

#include "game_object.h"
#include "json.hpp"

using json = nlohmann::json;

class StateParser
{
public:
    bool parseState(const char* stateFile, std::string stateID,
                    std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);
private:
    void parseObjects(json objectRoot,
                      std::vector<GameObject*> *pObjects);
    void parseTextures(json textureRoot,
                       std::vector<std::string> *pTextureIDs);
};
#endif
