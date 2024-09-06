#ifndef __HEADERSYMBOL_H__
#define __HEADERSYMBOL_H__

#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <map>
#include <unordered_map>
#include <deque>
#include <algorithm>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/ext.hpp>
#include "box2d/box2d.h"


//reference on Tetrimino types: https://tinyurl.com/4p9xpkfe
enum ObjectType {
	L, J, O, I, S, Z, T
};

enum GameState { Start, Pause, Play, GameOver };

enum Direction { Left, Right, Down };

// Tetrimino orientation
enum Face { ONE, TWO, THREE, FOUR };

const std::string RES_PATH = "../resources/";
const std::string ROOT_PATH = "../";

const int MAP_DEPTH_X = 9;
const int MAP_DEPTH_Y = 27;

const float BLOCK_WIDTH = 0.25f;
const float BLOCK_HEIGHT = 0.095f;

struct Position
{
	// map position
	int x;
	int y;

	// render position
	float renX;
	float renY;

	Position(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(const Position &p) const
	{
		return p.x == x && p.y == y;
	}
};

#endif /* __HEADERSYMBOL_H__ */
