#include "Config.h"

Config::Config() {
    
}

bool Config::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("Config.csb");

	this->addChild(rootNode);

	return true;
}
