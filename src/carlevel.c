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

float speed = 200.0;

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
			//printf("redcar selected\n");
		}
		else if (IsCircleClicked(greenCar.Pos.x, greenCar.Pos.y, 70, mouseClickPos.x, mouseClickPos.y) == 1) {
			redCar.Selected = 0;
			greenCar.Selected = 1;
			blueCar.Selected = 0;
			//printf("greencar selected\n");
		}
		else if (IsCircleClicked(blueCar.Pos.x, blueCar.Pos.y, 70, mouseClickPos.x, mouseClickPos.y) == 1) {
			redCar.Selected = 0;
			greenCar.Selected = 0;
			blueCar.Selected = 1;
			//printf("bluecar selected\n");
		}
	}

	// if car is selected, A and D will turn it.
	if (redCar.Selected == 1) {
		if (CP_Input_KeyDown(KEY_A)) {
			if (redCar.Direction > 0) {
				redCar.Direction -= 1.f;
			}
			else {
				redCar.Direction = 359;
			}
			//printf("redcar angle is: %f\n", redCar.Direction);
		}
		else if (CP_Input_KeyDown(KEY_D)) {
			if (redCar.Direction < 359) {
				redCar.Direction += 1.f;
			}
			else {
				redCar.Direction = 0;
			}
			//printf("redcar angle is: %f\n", redCar.Direction);
		}
	}
	else if (greenCar.Selected == 1) {
		if (CP_Input_KeyDown(KEY_A)) {
			if (greenCar.Direction > 0) {
				greenCar.Direction -= 1.f;
			}
			else {
				greenCar.Direction = 359;
			}
			//printf("greencar angle is: %f\n", greenCar.Direction);
		}
		else if (CP_Input_KeyDown(KEY_D)) {
			if (greenCar.Direction < 359) {
				greenCar.Direction += 1.f;
			}
			else {
				greenCar.Direction = 0;
			}
			//printf("greencar angle is: %f\n", greenCar.Direction);
		}
	}
	else if (blueCar.Selected == 1) {
		if (CP_Input_KeyDown(KEY_A)) {
			if (blueCar.Direction > 0) {
				blueCar.Direction -= 1.f;
			}
			else {
				blueCar.Direction = 359;
			}
			//printf("bluecar angle is: %f\n", blueCar.Direction);
		}
		else if (CP_Input_KeyDown(KEY_D)) {
			if (blueCar.Direction < 359) {
				blueCar.Direction += 1.f;
			}
			else {
				blueCar.Direction = 0;
			}
			//printf("bluecar angle is: %f\n", blueCar.Direction);
		}
	}

	// if car is selected, W and S will move it forward or back

	float dtSpeed = speed * CP_System_GetDt(); //x units per second

	if (redCar.Selected == 1) {
		//convert redcar direction (angle) to a vector (radians)
		CP_Vector direction = AngleToVector(redCar.Direction * (PI / 180.0));
		CP_Vector norm = CP_Vector_Normalize(direction);
		if (CP_Input_KeyDown(KEY_W)) {
			redCar.Pos = CP_Vector_Add(redCar.Pos, CP_Vector_Scale(norm, dtSpeed));
		}
		else if (CP_Input_KeyDown(KEY_S)) {
			redCar.Pos = CP_Vector_Subtract(redCar.Pos, CP_Vector_Scale(norm, dtSpeed));
		}
	}
	else if (greenCar.Selected == 1) {
		//convert redcar direction (angle) to a vector (radians)
		CP_Vector direction = AngleToVector(greenCar.Direction * (PI / 180.0));
		CP_Vector norm = CP_Vector_Normalize(direction);
		if (CP_Input_KeyDown(KEY_W)) {
			greenCar.Pos = CP_Vector_Add(greenCar.Pos, CP_Vector_Scale(norm, dtSpeed));
		}
		else if (CP_Input_KeyDown(KEY_S)) {
			greenCar.Pos = CP_Vector_Subtract(greenCar.Pos, CP_Vector_Scale(norm, dtSpeed));
		}
	}
	else if (blueCar.Selected == 1) {
		//convert redcar direction (angle) to a vector (radians)
		CP_Vector direction = AngleToVector(blueCar.Direction * (PI / 180.0));
		CP_Vector norm = CP_Vector_Normalize(direction);
		if (CP_Input_KeyDown(KEY_W)) {
			blueCar.Pos = CP_Vector_Add(blueCar.Pos, CP_Vector_Scale(norm, dtSpeed));
		}
		else if (CP_Input_KeyDown(KEY_S)) {
			blueCar.Pos = CP_Vector_Subtract(blueCar.Pos, CP_Vector_Scale(norm, dtSpeed));
		}
	}
}

void Car_Level_Exit()
{

}