//
// Created by yehoshua on 26/11/16.
//

#ifndef MISSION2_MAP_H
#define MISSION2_MAP_H

#include <vector>
#include "PointNode.h"

/*
 * class Map. responsible for the creation of the two dimension map and assign every point
 * in the specific node. also assign vector of neighbors to every node
 */
class Map {
private:
    //members
    vector<vector<PointNode*> > grid;
    int maxX;
    int maxY;
    int numOfObsticals;
    vector<Point*>* listofobstacles;
    //creating vector of vectors of type Node* which represents the map
    void createGrid();
    //assign neighbors of every node into the neighbors vector
    void assignNeighbors();
    //delete neighbors for updating the list after adding obstacle
    void deleteNeighbors();
public:
    //destructor. deletes all the node in the grid
    ~Map();
    //constructor
    Map(int maxX, int maxY);
    //the function gets point and returns the node that in the right place in the grid
    PointNode * getNode(Point point);
    PointNode * getNode(Node * node);
    //get all the obstacles on the map
    vector<Point*>* getListOfObstacles(){return listofobstacles;}

    //adds obstacles to the map
    void addObstacles(Point p);

    //removes obstacles from the map
    void removeObstacles(Point p);

// gets the grid of the map
    vector<vector<PointNode*> > getGrid();

    void resetFathers();

    void setMaxX(int maxX);

    void setMaxY(int maxY);

    int getMaxX() const;

    int getMaxY() const;

    int getNumOfObsticals() const;

    void setNumOfObsticals(int numOfObsticals);
};



#endif //MISSION2_MAP_H
