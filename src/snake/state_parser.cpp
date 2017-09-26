#include "state_parser.h"
#include "game.h"
#include "texture_manager.h"

#include <string>
#include <vector>
#include <fstream>

bool StateParser::parseState(const char *stateFile, std::string stateID,
                             std::vector<GameObject *> *pObjects, std::vector<std::string> *pTextureIDs)
{
    // create the XML document
    json root;
    // load the state file
    std::ifstream iStateFile(stateFile);

    if (!iStateFile) {
        std::cerr << "file error" << std::endl;
        return false;
    }

    // get the root element
    iStateFile >> root;
    root = root["STATES"];
    // pre declare the states root node
    json stateRoot;

    // get this states root node and assign it to pStateRoot
    if (root[stateID] != nullptr) {
        stateRoot = root[stateID];
    }

    // pre declare the texture root
    json textureRoot;

    // get the root of the texture elements
    if (stateRoot["TEXTURES"] != nullptr) {
        textureRoot = stateRoot["TEXTURES"];
    }

    // now parse the textures
    parseTextures(textureRoot, pTextureIDs);
    // pre declare the object root node
    json objectRoot;

    // get the root node and assign it to pObjectRoot
    if (stateRoot["OBJECTS"] != nullptr) {
        objectRoot = stateRoot["OBJECTS"];
    }

    // now parse the objects
    parseObjects(objectRoot, pObjects);
    return true;
}

void StateParser::parseTextures(json textureRoot,
                                std::vector<std::string> *pTextureIDs)
{
    for (auto i : textureRoot) {
        for (auto j : i) {
            std::string filename = j["filename"];
            std::string id = j["ID"];
            pTextureIDs->push_back(id);
            TextureManager::instance()->load(filename, id, Game::instance()->getRenderer());
        }
    }
}

void StateParser::parseObjects(json objectRoot,
                               std::vector<GameObject *> *pObjects)
{
    for (auto i : objectRoot) {
        for (auto j : i) {
            int x, y, width, height, numFrames, callbackID, animSpeed;
            std::string textureID;
            x = j["x"];
            y = j["y"];
            width = j["width"];
            height = j["height"];
            numFrames = j["numFrames"];
            callbackID = j["callbackID"];
            animSpeed = j["animSpeed"];
            textureID = j["textureID"];
            GameObject* pGameObject = GameObjectFactory::instance()->create(j["type"]);
            pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
            pObjects->push_back(pGameObject);
        }
    }
}
