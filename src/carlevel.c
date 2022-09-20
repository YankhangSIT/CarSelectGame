
#include "cprocessing.h"
#include "stdio.h"
#include "utils.h"
#include "mainmenu.h"

struct Car {
	CP_Vector Pos;
	CP_Color Color;
};

struct Car redCar, greenCar, blueCar;

void Car_Level_Init()
{
	//Set window width and height to variables
	float wWidth = CP_System_GetWindowWidth();
	float wHeight = CP_System_GetWindowHeight();
	CP_System_SetWindowSize(wWidth * 3.5, wWidth * 2);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	redCar.Pos = CP_Vector_Set(wWidth / 2.0f, wHeight / 2.0f - 100);
	redCar.Color = CP_Color_Create(255, 0, 0, 255);

	greenCar.Pos = CP_Vector_Set(wWidth / 3.0f, wHeight / 2.0f + 100);
	greenCar.Color = CP_Color_Create(0, 255, 0, 255);

	blueCar.Pos = CP_Vector_Set(wWidth / 1.5f, wHeight / 2.0f + 100);
	blueCar.Color = CP_Color_Create(0, 0, 255, 255);


}

void Car_Level_Update()
{
	//doesnt work?
	CP_Settings_Fill(redCar.Color);
	CP_Graphics_DrawCircle(redCar.Pos.x, redCar.Pos.y, 50.0f);

	CP_Settings_Fill(greenCar.Color);
	CP_Graphics_DrawCircle(greenCar.Pos.x, greenCar.Pos.y, 50.0f);

	CP_Settings_Fill(blueCar.Color);
	CP_Graphics_DrawCircle(blueCar.Pos.x, blueCar.Pos.y, 50.0f);

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