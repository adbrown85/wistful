/*
 * GglConfigFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglConfigFactory.hpp"

/**
 * Creates an OpenGL configuration factory.
 */
GglConfigFactory::GglConfigFactory() {
    ;
}

/**
 * Destroys the factory.
 */
GglConfigFactory::~GglConfigFactory() {
    ;
}

//---------------------------------------------------------
// Helpers
//

/**
 * Adds a configuration to the factory.
 * 
 * @param id Identifier of configuration
 * @param config Pointer to the configuration
 */
void GglConfigFactory::add(int id, GglConfig *config) {
    configs[id] = config;
}

/**
 * Finds a configuration that was already built.
 * 
 * @param id Identifier of configuration
 * @return Pointer to the configuration, or NULL if not found
 */
GglConfig* GglConfigFactory::find(int id) {
    
    map<int,GglConfig*>::iterator it = configs.find(id);
    
    return (it == configs.end()) ? NULL : it->second;
}
