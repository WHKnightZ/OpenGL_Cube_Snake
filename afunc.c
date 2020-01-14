#include "main.h"

// Switch
void Switch_Up() {
    Face_Next = Face_Bottom;
    Face_Save = Face_Front;
    Face_Front = Face_Top;
    Face_Top = Face_Back;
    Face_Back = Face_Bottom;
    Face_Bottom = Face_Save;
    Face_Current = Face_Front;
    Face_Next = Face_Top;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Switch_Right() {
    Face_Next = Face_Left;
    Face_Save = Face_Front;
    Face_Front = Face_Right;
    Face_Right = Face_Back;
    Face_Back = Face_Left;
    Face_Left = Face_Save;
    Face_Current = Face_Front;
    Face_Next = Face_Right;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Switch_Down() {
    Face_Next = Face_Top;
    Face_Save = Face_Front;
    Face_Front = Face_Bottom;
    Face_Bottom = Face_Back;
    Face_Back = Face_Top;
    Face_Top = Face_Save;
    Face_Current = Face_Front;
    Face_Next = Face_Bottom;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Switch_Left() {
    Face_Next = Face_Right;
    Face_Save = Face_Front;
    Face_Front = Face_Left;
    Face_Left = Face_Back;
    Face_Back = Face_Right;
    Face_Right = Face_Save;
    Face_Current = Face_Front;
    Face_Next = Face_Left;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

// Move
void Move_X(int Drt) {
    Snake_Pos[0].x += Snake_Pos[0].Drt;
    if (Time_Rotate == MAX_TIME_ROTATE) {
        if (Drt == -1) {
            if (Snake_Pos[0].x == 0)
                Switch();
        } else {
            if (Snake_Pos[0].x == 19)
                Switch();
        }
    }
}

void Move_Y(int Drt) {
    Snake_Pos[0].y += Snake_Pos[0].Drt;
    if (Time_Rotate == MAX_TIME_ROTATE) {
        if (Drt == -1) {
            if (Snake_Pos[0].y == 0)
                Switch();
        } else {
            if (Snake_Pos[0].y == 19)
                Switch();
        }
    }
}

void Move_Z(int Drt) {
    Snake_Pos[0].z += Snake_Pos[0].Drt;
    if (Time_Rotate == MAX_TIME_ROTATE) {
        if (Drt == -1) {
            if (Snake_Pos[0].z == 0)
                Switch();
        } else {
            if (Snake_Pos[0].z == 19)
                Switch();
        }
    }
}

// Set_Offset
void Set_Offset_x_y() {
    zo = -ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = yo = 0.0f;
    Snake_Pos[0].V = 1;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 0;
    New_Drt = -Face[Face_Current].d;
}

void Set_Offset_x_z() {
    yo = ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = zo = 0.0f;
    Snake_Pos[0].V = 2;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 0;
    New_Drt = -Face[Face_Current].d;
}

void Set_Offset_y_x() {
    zo = ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = yo = 0.0f;
    Snake_Pos[0].V = 0;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 1;
    New_Drt = -Face[Face_Current].d;
}

void Set_Offset_y_z() {
    xo = -ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    yo = zo = 0.0f;
    Snake_Pos[0].V = 2;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 1;
    New_Drt = -Face[Face_Current].d;
}

void Set_Offset_z_x() {
    yo = -ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = zo = 0.0f;
    Snake_Pos[0].V = 0;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 2;
    New_Drt = -Face[Face_Current].d;
}

void Set_Offset_z_y() {
    xo = ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    yo = zo = 0.0f;
    Snake_Pos[0].V = 1;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 2;
    New_Drt = -Face[Face_Current].d;
}

// Arrow
void Arrow_Up() {
    Key_Current = KEY_UP;
    Face_Next = Face_Top;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Arrow_Right() {
    Key_Current = KEY_RIGHT;
    Face_Next = Face_Right;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Arrow_Down() {
    Key_Current = KEY_DOWN;
    Face_Next = Face_Bottom;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

void Arrow_Left() {
    Key_Current = KEY_LEFT;
    Face_Next = Face_Left;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
}

// Game_Display
void Game_Display_Idle() {
    Draw_Game();
    Draw_2D_Begin();
    Map_Texture(&Img_Logo);
    Draw_Rect(&Rct_Logo);
    glColor4f(1.0f, 1.0f, 1.0f, (40.0f - Idle_Stt) / 40);
    Map_Texture(&Img_PressAnyKey);
    Draw_Rect(&Rct_PressAnyKey);
    glColor3f(1.0f, 1.0f, 1.0f);
    Draw_2D_End();
}

void Game_Display_Prepare() {
    Draw_Game();
    Draw_2D_Begin();
    Map_Texture(&Img_Prepare[Prepare_Stt]);
    Draw_Rect(&Rct_Prepare[Prepare_Stt]);
    Draw_2D_End();
}

void Game_Display_Play() {
    Draw_Game();
    Draw_2D_Begin();
    Draw_Score();
    Draw_2D_End();
}

void Game_Display_Dead() {
    Game_Display_Play();
}

void Game_Display_GameOver() {
    Draw_Game();
    Draw_2D_Begin();
    Map_Texture(&Img_GameOver);
    Draw_Rect(&Rct_GameOver);
    glColor4f(1.0f, 1.0f, 1.0f, (40.0f - Idle_Stt) / 40);
    Map_Texture(&Img_PressAnyKey);
    Draw_Rect(&Rct_PressAnyKey);
    glColor3f(1.0f, 1.0f, 1.0f);
    Draw_Score();
    Draw_2D_End();
}

// Game_Process
void Game_Process_Idle() {
    Idle_Stt += Idle_Stt_Offset;
    if (Idle_Stt == 0 || Idle_Stt == 40)
        Idle_Stt_Offset = -Idle_Stt_Offset;
    xo = 0.2f;
    yo = 0.4f;
    zo = 0.0f;
    Reload_View();
}

void Game_Process_Prepare() {
    Game_Timer++;
    if (Game_Timer == 50) {
        Game_Timer = 0;
        Prepare_Stt++;
        if (Prepare_Stt == 3) {
            Game_Stt = GAME_STT_PLAY;
            glutSpecialFunc(Special);
        }
    }
}

void Game_Process_Play() {
    if (Time_Rotate < MAX_TIME_ROTATE) {
        Reload_View();
        Time_Rotate++;
        if (Time_Rotate == MAX_TIME_ROTATE) {
            Offset_Time = OFFSET_TIME;
            Offset_Size = 1.0f / Offset_Time;
            Snake_Offset = Offset_Time - 1;
        }
    }
    Snake_Offset++;
    if (Snake_Offset == Offset_Time) {
        Snake_Offset = 0;
        int i;
        for (i = Snake_Length; i > 0; i--) {
            Snake_Pos[i] = Snake_Pos[i - 1];
        }
        Move_Func[Snake_Pos[0].V](Snake_Pos[0].Drt);
        s_Vec3 *Vec3_Ptr = &Map_Velocity[Snake_Pos[0].V];
        int Next_x = Snake_Pos[0].x + Snake_Pos[0].Drt * Vec3_Ptr->x;
        int Next_y = Snake_Pos[0].y + Snake_Pos[0].Drt * Vec3_Ptr->y;
        int Next_z = Snake_Pos[0].z + Snake_Pos[0].Drt * Vec3_Ptr->z;
        if (Check_Is_Wall(Next_x, Next_y, Next_z) || Check_Is_Snake(Next_x, Next_y, Next_z)) {
            Game_Timer = 0;
            Game_Stt = GAME_STT_DEAD;
        }
        int n = Check_Is_Food(Snake_Pos[0].x, Snake_Pos[0].y, Snake_Pos[0].z);
        if (n >= 0) {
            Update_Score(1);
            Create_Food(n);
            Add_Part();
        }
        if (Pressed_Arrow != -1 && Time_Rotate == MAX_TIME_ROTATE) {
            Arrow_Func[Pressed_Arrow]();
            Pressed_Arrow = -1;
        }
    }
}

void Game_Process_Dead() {
    Game_Timer++;
    if (Game_Timer == 40) {
        Score_Start_Y = POS_SCORE_GAMEOVER;
        Game_Stt = GAME_STT_GAMEOVER;
        glutKeyboardFunc(Keyboard);
    }
}

void Game_Process_GameOver() {
    Game_Process_Idle();
}
