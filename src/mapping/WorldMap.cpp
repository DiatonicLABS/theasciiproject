//
//  WorldMap.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 2/28/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "../serialization/Boost_Serialization.h"
#include "WorldMap.h"
#include <memory>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "../mapping/Tile.h"
#include "../mapping/TileMap.h"
#include "../mapping/EntityMap.h"



void WorldMap::init(){
    
    worldTileLength = X * mapX;
    worldTileWidth = Y * mapY;
    worldTileHeight = Z;
    
    initGlobalTileMap();
    //initGlobalEntityMap();
    
}



void WorldMap::initGlobalTileMap(){
    
    for(int x=0; x<X; x++){
        std::vector< std::vector< boost::shared_ptr<TileMap> > > layer;
        for(int y=0; y<Y; y++){
            std::vector< boost::shared_ptr<TileMap> > row;
            for(int z=0; z<Z; z++){
                boost::shared_ptr<TileMap> tileMap(new TileMap(mapX, mapY));
                row.push_back(tileMap);
            }
            layer.push_back(row);
        }
        globalTileMap.push_back(layer);
    }
    
}


void WorldMap::initGlobalEntityMap(){
    
    
    
}


TileMap* WorldMap::getTileMap(int posx, int posy, int posz){
    
    if(posx >= X || posy >= Y || posz >= Z)
        return nullptr;
    
    return globalTileMap.at(posx).at(posy).at(posz).get();
}


Tile* WorldMap::getTileAt(int posx, int posy, int posz){
    
    if( posx >= worldTileLength || posy >= worldTileLength || posz >= worldTileHeight )
        return nullptr;
    
    int realTileMapX = (posx / mapX);
    int realTileMapY = (posy / mapY);
    
    int realTileX = (posx % mapX);
    int realTileY = (posy % mapY);
    
    TileMap *realTileMap = getTileMap(realTileMapX, realTileMapY, posz);
    
    Tile *realTile = realTileMap->getTilePtr(realTileX, realTileY);
    
    return realTile;
    
}


Tile* WorldMap::AltGetTileAt(int posx, int posy, int posz){
    
    if( posx >= worldTileLength || posy >= worldTileLength || posz >= worldTileHeight )
        return nullptr;
    
    int realTileMapX = (posx / mapX);
    int realTileMapY = (posy / mapY);
    
    int realTileX = (posx % mapX);
    int realTileY = (posy % mapY);
    
    // I have no idea why the heightmap generator switches the X and Y positions
    // But this is the fix =shrug=
    TileMap *realTileMap = getTileMap(realTileMapY, realTileMapX, posz);
    
    Tile *realTile = realTileMap->getTilePtr(realTileX, realTileY);
    
    return realTile;
    
}