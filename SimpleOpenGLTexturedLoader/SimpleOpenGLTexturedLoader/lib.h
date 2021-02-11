#include "GameObj.h"
#include "GameManager.h"
#include "Obstacle.h"
#include <stdlib.h>
#include "Gl/glut.h"
#include <stdio.h>
#include <math.h>

void recursive_render(const struct aiScene* sc, const struct aiNode* nd, float scale);