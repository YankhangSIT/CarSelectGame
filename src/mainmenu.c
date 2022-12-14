#include "cprocessing.h"
#include "utils.h"
#include "carlevel.h"
#include "stdio.h"

void Main_Menu_Init()
{
	//Set window width and height to variables
	float wWidth = CP_System_GetWindowWidth();
	float wHeight = CP_System_GetWindowHeight();

	//set window size and center it
	CP_System_SetWindowSize(wWidth * 2.5, wWidth * 2);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	//align texts to center and set font size 35
	CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
	CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
	CP_Settings_TextAlignment(horizontal, vertical);
	CP_Settings_TextSize(35.0f);
}

void Main_Menu_Update()
{
	//Set window width and height to variables
	float wWidth = CP_System_GetWindowWidth();
	float wHeight = CP_System_GetWindowHeight();

	//Play Button
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f - 100, 180, 80);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Play", wWidth / 2.0f, wHeight / 2.0f - 100);

	//Exit Button
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawRect(wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Exit", wWidth / 2.0f, wHeight / 2.0f + 100);

	//If click "Play" Button
	if (CP_Input_MouseClicked()) {
		CP_Vector mouseClickPos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f - 100, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1) {
			CP_Engine_SetNextGameState(Car_Level_Init, Car_Level_Update, Car_Level_Exit);
		} 
		//else if click "Exit" button
		else if (IsAreaClicked(wWidth / 2.0f, wHeight / 2.0f + 100, 180, 80, mouseClickPos.x, mouseClickPos.y) == 1) {
			CP_Engine_Terminate();
		}

	}
}

void Main_Menu_Exit()
{

}
