#include "GameObj.h"
#include "GameManager.h"
#include "Obstacle.h"
#include "LoadObj.h"
#include <stdlib.h>
#include "Gl/glut.h"
#include <IL/il.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>

void output(int x, int y, std::string str);

void renderUI(float, float, float);

void renderPressToPlayText();
void renderDeadText();
void renderScoreText();
