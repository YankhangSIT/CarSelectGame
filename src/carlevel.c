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

	/*
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

	*/
	
}

void Car_Level_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//draw circles
	for (int i = 0; i < 3; i++) {
		CP_Settings_Fill(cars[i].Color);
		CP_Graphics_DrawCircle(cars[i].Pos.x, cars[i].Pos.y, 70.0f);
	}

	/*
	CP_Settings_Fill(cars[0].Color);
	CP_Graphics_DrawCircle(cars[0].Pos.x, cars[0].Pos.y, 70.0f);

	CP_Settings_Fill(cars[1].Color);
	CP_Graphics_DrawCircle(cars[1].Pos.x, cars[1].Pos.y, 70.0f);

	CP_Settings_Fill(cars[2].Color);
	CP_Graphics_DrawCircle(cars[2].Pos.x, cars[2].Pos.y, 70.0f);
	*/

	// draw triangles
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	for (int i = 0; i < 3; i++) {
		CP_Graphics_DrawTriangleAdvanced(cars[i].Pos.x + 35.0f, cars[i].Pos.y,
			cars[i].Pos.x - 20.0f, cars[i].Pos.y + 25.0f,
			cars[i].Pos.x - 20.0f, cars[i].Pos.y - 25.0f,
			cars[i].Direction);
	}

	/*
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
	*/


	//check for isCircleClicked
	if (CP_Input_MouseClicked()) {
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		for (int counter = 0; counter < 3; counter++)
			if (IsCircleClicked(cars[counter].Pos.x, cars[counter].Pos.y, 70, mouseClickPos.x, mouseClickPos.y) == 1) {
				i = counter;
				/*cars[0].Selected = 1;
				cars[1].Selected = 0;
				cars[2].Selected = 0;*/
			}
	}

	/*
	if (CP_Input_MouseClicked()) {
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (IsCircleClicked(cars[0].Pos.x, cars[0].Pos.y, 70, mouseClickPos.x, mouseClickPos.y) == 1) {
			cars[0].Selected = 1;
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
	*/


	// if car is selected, A and D will turn it.
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


	/*
	if (cars[0].Selected == 1) {
		if (CP_Input_KeyDown(KEY_A)) {
			if (cars[0].Direction > 0) {
				cars[0].Direction -= 1.f;
			}
			else {
				cars[0].Direction = 359;
			}
			//printf("redcar angle is: %f\n", redCar.Direction);
		}
		else if (CP_Input_KeyDown(KEY_D)) {
			if (cars[0].Direction < 359) {
				cars[0].Direction += 1.f;
			}
			else {
				cars[0].Direction = 0;
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
	*/
}

void Car_Level_Exit()
{

}