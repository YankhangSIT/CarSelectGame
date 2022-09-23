
#include "cprocessing.h"
#include "stdio.h"
#include "utils.h"
#include "mainmenu.h"

struct Car {
	CP_Vector Pos;
	CP_Color Color;
	int Selected;
	float Direction;
};

int carArray[3];

struct Car redCar, greenCar, blueCar;

void Car_Level_Init()
{
	//Set window width and height to variables
	float wWidth = CP_System_GetWindowWidth();
	float wHeight = CP_System_GetWindowHeight();

	//set window size and center it
	CP_System_SetWindowSize(wWidth, wHeight);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	redCar.Pos = CP_Vector_Set(100.0f, 100.0f);
	redCar.Color = CP_Color_Create(255, 0, 0, 255);
	redCar.Selected = 0;
	redCar.Direction = 0.0f;

	greenCar.Pos = CP_Vector_Set(300.0f, 100.0f);
	greenCar.Color = CP_Color_Create(0, 255, 0, 255);
	greenCar.Selected = 0;
	greenCar.Direction = 0.0f;

	blueCar.Pos = CP_Vector_Set(200.0f, 200.0f);
	blueCar.Color = CP_Color_Create(0, 0, 255, 255);
	blueCar.Selected = 0;
	blueCar.Direction = 0.0f;

	//carArray[0] = redCar;
	//carArray[1] = greenCar;
	//carArray[2] = blueCar;
}

void Car_Level_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	/* 
	if (CP_Input_MouseClicked()) {
		printf("%f, %f\n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	*/

	//draw circles
	CP_Settings_Fill(redCar.Color);
	CP_Graphics_DrawCircle(redCar.Pos.x, redCar.Pos.y, 70.0f);

	CP_Settings_Fill(greenCar.Color);
	CP_Graphics_DrawCircle(greenCar.Pos.x, greenCar.Pos.y, 70.0f);

	CP_Settings_Fill(blueCar.Color);
	CP_Graphics_DrawCircle(blueCar.Pos.x, blueCar.Pos.y, 70.0f);

	// draw triangles
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawTriangleAdvanced(redCar.Pos.x + 35.0f, redCar.Pos.y,
		redCar.Pos.x - 20.0f, redCar.Pos.y + 25.0f,
		redCar.Pos.x - 20.0f, redCar.Pos.y - 25.0f,
		redCar.Direction);

	CP_Graphics_DrawTriangleAdvanced(greenCar.Pos.x + 35.0f, greenCar.Pos.y,
		greenCar.Pos.x - 20.0f, greenCar.Pos.y + 25.0f,
		greenCar.Pos.x - 20.0f, greenCar.Pos.y - 25.0f,
		greenCar.Direction);

	CP_Graphics_DrawTriangleAdvanced(blueCar.Pos.x + 35.0f, blueCar.Pos.y,
		blueCar.Pos.x - 20.0f, blueCar.Pos.y + 25.0f,
		blueCar.Pos.x - 20.0f, blueCar.Pos.y - 25.0f,
		blueCar.Direction);

	//check for isCircleClicked

	if (CP_Input_MouseClicked()) {
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (IsCircleClicked(redCar.Pos.x, redCar.Pos.y, 70, mouseClickPos.x, mouseClickPos.y) == 1) {
			redCar.Selected = 1;
			greenCar.Selected = 0;
			blueCar.Selected = 0;
			printf("redcar selected\n");
		}
		else if (IsCircleClicked(greenCar.Pos.x, greenCar.Pos.y, 70, mouseClickPos.x, mouseClickPos.y) == 1) {
			redCar.Selected = 0;
			greenCar.Selected = 1;
			blueCar.Selected = 0;
			printf("greencar selected\n");
		}
		else if (IsCircleClicked(blueCar.Pos.x, blueCar.Pos.y, 70, mouseClickPos.x, mouseClickPos.y) == 1) {
			redCar.Selected = 0;
			greenCar.Selected = 0;
			blueCar.Selected = 1;
			printf("bluecar selected\n");
		}
	}


	// movement for circle using WASD
	CP_Vector dir = CP_Vector_Set(0.f, 0.f);
	if (CP_Input_KeyTriggered(KEY_W)) {
		dir.y += 1.f;
	}
	else if (CP_Input_KeyTriggered(KEY_A)) {
		dir.x -= 1.f;
	}
	else if (CP_Input_KeyTriggered(KEY_S)) {
		dir.y -= 1.f;
	}
	else if (CP_Input_KeyTriggered(KEY_D)) {
		dir.x += 1.f;
	}
}

void Car_Level_Exit()
{

}