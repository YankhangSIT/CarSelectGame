#include "cprocessing.h"
#include "stdio.h"
#include "utils.h"
#include "mainmenu.h"
#include "math.h"

#define PI (3.141592653589793)

struct Car {
	CP_Vector Pos;
	CP_Color Color;
	int Selected;
	float Direction;
};

float speed = 350.0;

//struct Car redCar, greenCar, blueCar, selectedCar;

struct Car cars[3];

int i;


void Car_Level_Init()
{

	//Set window width and height to variables
	float wWidth = CP_System_GetWindowWidth();
	float wHeight = CP_System_GetWindowHeight();

	//set window size and center it
	CP_System_SetWindowSize(wWidth, wHeight);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	cars[0].Pos = CP_Vector_Set(100.0f, 100.0f);
	cars[0].Color = CP_Color_Create(255, 0, 0, 255);
	cars[0].Selected = 0;
	cars[0].Direction = 0.0f;

	cars[1].Pos = CP_Vector_Set(300.0f, 100.0f);
	cars[1].Color = CP_Color_Create(0, 255, 0, 255);
	cars[1].Selected = 0;
	cars[1].Direction = 0.0f;

	cars[2].Pos = CP_Vector_Set(200.0f, 200.0f);
	cars[2].Color = CP_Color_Create(0, 0, 255, 255);
	cars[2].Selected = 0;
	cars[2].Direction = 0.0f;
}

void Car_Level_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//draw circles
	for (int i = 0; i < 3; i++) {
		CP_Settings_Fill(cars[i].Color);
		CP_Graphics_DrawCircle(cars[i].Pos.x, cars[i].Pos.y, 70.0f);
	}

	// draw triangles
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	for (int i = 0; i < 3; i++) {
		CP_Graphics_DrawTriangleAdvanced(cars[i].Pos.x + 35.0f, cars[i].Pos.y,
			cars[i].Pos.x - 20.0f, cars[i].Pos.y + 25.0f,
			cars[i].Pos.x - 20.0f, cars[i].Pos.y - 25.0f,
			cars[i].Direction);
	}

	//check for isCircleClicked
	if (CP_Input_MouseClicked()) {
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		for (i = 0; i < 3; i++)
			if (IsCircleClicked(cars[i].Pos.x, cars[i].Pos.y, 70, mouseClickPos.x, mouseClickPos.y) == 1) {
				return i;
			}
	}

	// if car is selected, A and D will turn it, W and S will move it forward and backwards respectively
	float dtSpeed = speed * CP_System_GetDt(); //x units per second
	CP_Vector direction = AngleToVector(cars[i].Direction * (PI / 180.0));
	CP_Vector norm = CP_Vector_Normalize(direction);

	if (CP_Input_KeyDown(KEY_A)) {
		if (cars[i].Direction > 0) {
			cars[i].Direction -= 1.f;
		}
		else {
			cars[i].Direction = 359;
		}
		//printf("redcar angle is: %f\n", redCar.Direction);
	}
	else if (CP_Input_KeyDown(KEY_D)) {
		if (cars[i].Direction < 359) {
			cars[i].Direction += 1.f;
		}
		else {
			cars[i].Direction = 0;
		}
	}

	if (CP_Input_KeyDown(KEY_W)) {
		cars[i].Pos = CP_Vector_Add(cars[i].Pos, CP_Vector_Scale(norm, dtSpeed));
	}
	else if (CP_Input_KeyDown(KEY_S)) {
		cars[i].Pos = CP_Vector_Subtract(cars[i].Pos, CP_Vector_Scale(norm, dtSpeed));
	}
}

void Car_Level_Exit()
{

}