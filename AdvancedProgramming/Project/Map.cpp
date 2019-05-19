

#include "Map.h"

/*
 * class Map. responsible for the creation of the two dimension map and assign every point
 * in the specific node. also assign vector of neighbors to every node
 */

//constructor
Map::Map(int maxX, int maxY) {
    this->maxX = maxX;
    this->maxY = maxY;
    this->createGrid();
}

//the function gets point and returns the node that in the right place in the grid
PointNode * Map::getNode(Point point) {
    return this->grid[point.getX()][point.getY()];
}

//creating vector of vectors of type Node* which represents the map
void Map::createGrid() {
    vector<PointNode *> temp;
    for (int i = 0; i < this->maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            temp.push_back(new PointNode(Point(i,j),this->maxX*this->maxY));
            temp[j]->setFather(NULL);
        }
        this->grid.push_back(temp);
        temp.clear();
    }
    assignNeighbors();
}

//assign neighbors of every node into the neighbors vector
void Map::assignNeighbors(){
    for (int i = 0; i < this->maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            if (i > 0){
                if (!this->grid[i-1][j]->isIsObstacle()) {
                    this->grid[i][j]->addNeighbor(this->grid[i-1][j]);
                }
            }
            if (j < this->maxY-1){
                if (!this->grid[i][j+1]->isIsObstacle()){
                    this->grid[i][j]->addNeighbor(this->grid[i][j+1]);
                }
            }
            if (i < this->maxX-1){
                if (!this->grid[i+1][j]->isIsObstacle()) {
                    this->grid[i][j]->addNeighbor(this->grid[i+1][j]);
                }
            }
            if (j > 0){
                if (!this->grid[i][j-1]->isIsObstacle()) {
                    this->grid[i][j]->addNeighbor(this->grid[i][j-1]);
                }
            }
        }
    }
}

//destructor. deletes all the node in the grid
Map::~Map() {
    for (int i = 0; i < this->maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            delete  this->grid[i][j];
        }
    }
}

//adds obstacle to the grid
void Map:: addObstacles(Point p){
    this->grid[p.getX()][p.getY()]->setIsObstacle(true);
    this->deleteNeighbors();
    this->assignNeighbors();
}

//removes obstacle from the grid
void Map:: removeObstacles(Point p){
    this->grid[p.getX()][p.getY()]->setIsObstacle(false);
    this->deleteNeighbors();
    this->assignNeighbors();
}

//gets the grid of the map
vector<vector<PointNode*> > Map::getGrid(){
    return this->grid;}

void Map::deleteNeighbors() {
    for (int i = 0; i < maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            this->grid[i][j]->clearNeighbors();
        }
    }
}

PointNode * Map::getNode(Node *node) {
    for (int i = 0; i < this->maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            if (this->grid[i][j] == node) {
                return this->grid[i][j];
            }
        }
    }
}

void Map::resetFathers() {
    for (int i = 0; i < maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            this->grid[i][j]->setFather(NULL);
        }
    }
}

int Map::getMaxX() const {
    return maxX;
}

int Map::getMaxY() const {
    return maxY;
}

void Map::setMaxX(int maxX) {
    Map::maxX = maxX;
    this->createGrid();
}

void Map::setMaxY(int maxY) {
    Map::maxY = maxY;
    this->createGrid();
}

int Map::getNumOfObsticals() const {
    return numOfObsticals;
}

void Map::setNumOfObsticals(int numOfObsticals) {
    Map::numOfObsticals = numOfObsticals;
}
