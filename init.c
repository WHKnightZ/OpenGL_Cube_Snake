#include "main.h"

void Switch() {
    if (Time_Rotate == MAX_TIME_ROTATE) {
        Mix_PlayChannel(-1, Sound_Switch, 0);
        Time_Rotate = 0;
        Snake_Pos[0].V = New_V;
        Snake_Pos[0].Drt = New_Drt;
        Switch_Func[Key_Current]();
        Offset_Time = OFFSET_TIME_ROTATE;
        Offset_Size = 1.0f / Offset_Time;
    }
}

void Load_Map() {
    FILE *f = fopen("Maps/01.txt", "r");
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            fscanf(f, "%d", &Map[i][j][19]);
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            fscanf(f, "%d", &Map[0][i][j]);
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            fscanf(f, "%d", &Map[19][i][j]);
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            fscanf(f, "%d", &Map[i][19][j]);
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            fscanf(f, "%d", &Map[i][0][j]);
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            fscanf(f, "%d", &Map[i][j][0]);
    fclose(f);
}

int Check_Is_Snake(int x, int y, int z) {
    int i;
    for (i = 0; i <= Snake_Length; i++)
        if (Snake_Pos[i].x == x && Snake_Pos[i].y == y && Snake_Pos[i].z == z)
            return 1;
    return 0;
}

int Check_Is_Wall(int x, int y, int z) {
    if (Map[x][y][z] == 1)
        return 1;
    return 0;
}

int Check_Is_Food(int x, int y, int z) {
    int i;
    for (i = 0; i < MAX_FOOD; i++) {
        if (Food_Pos[i].x == x && Food_Pos[i].y == y && Food_Pos[i].z == z) {
            return i;
        }
    }
    return -1;
}

void Add_Part() {
    int Snake_Length_Old = Snake_Length;
    int V_Old = Snake_Pos[Snake_Length].V;
    int Drt_Old = Snake_Pos[Snake_Length].Drt;
    Snake_Length++;
    Snake_Pos[Snake_Length].x = Snake_Pos[Snake_Length_Old].x - Map_Velocity[V_Old].x * Drt_Old;
    Snake_Pos[Snake_Length].y = Snake_Pos[Snake_Length_Old].y - Map_Velocity[V_Old].y * Drt_Old;
    Snake_Pos[Snake_Length].z = Snake_Pos[Snake_Length_Old].z - Map_Velocity[V_Old].z * Drt_Old;
    Snake_Pos[Snake_Length].V = V_Old;
    Snake_Pos[Snake_Length].Drt = Drt_Old;
}

void Create_Food(int n) {
    int x, y, z;
    do {
        int k = rand() % 3;
        int m = rand() % 2;
        switch (k) {
        case 0:
            x = 19 - 19 * m;
            y = rand() % 18 + 1;
            z = rand() % 18 + 1;
            break;
        case 1:
            x = rand() % 18 + 1;
            y = 19 - 19 * m;
            z = rand() % 18 + 1;
            break;
        case 2:
            x = rand() % 18 + 1;
            y = rand() % 18 + 1;
            z = 19 - 19 * m;
            break;
        }
    } while (Check_Is_Snake(x, y, z) || Check_Is_Wall(x, y, z) || Check_Is_Food(x, y, z) >= 0);
    Food_Pos[n].x = x;
    Food_Pos[n].y = y;
    Food_Pos[n].z = z;
}

void Init_Food() {
    int i;
    for (i = 0; i < MAX_FOOD; i++)
        Create_Food(i);
}

void Reload_Game() {
    Face_Front = FACE_FRONT;
    Face_Left = FACE_LEFT;
    Face_Right = FACE_RIGHT;
    Face_Top = FACE_TOP;
    Face_Bottom = FACE_BOTTOM;
    Face_Back = FACE_BACK;
    Offset_Time = OFFSET_TIME;
    Offset_Size = 1.0f / OFFSET_TIME;
    New_V = 2;
    New_Drt = -1;
    Key_Current = KEY_RIGHT;
    Pressed_Arrow = -1;
    Time_Rotate = MAX_TIME_ROTATE;
    Snake_Offset = 0;
    Snake_Length = 1;
    Snake_Pos[0].x = 10;
    Snake_Pos[1].x = 9;
    int i;
    for (i = 0; i <= Snake_Length; i++) {
        Snake_Pos[i].y = 10;
        Snake_Pos[i].z = 19;
        Snake_Pos[i].V = 0;
        Snake_Pos[i].Drt = 1;
    }
    Face_Current = Face_Front;
    Face_Next = Face_Right;
    Set_Offset_Func[Face[Face_Current].f][Face[Face_Next].f]();
    Init_Food();
    Score_Start_Y = POS_SCORE;
    Score = 0;
    Score_Animate_Stt = 0;
    Score_Is_Animate = 0;
    Update_Score(0);
}

void Init_Game() {
    // GL - 3D
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Dif);
    glLightfv(GL_LIGHT0, GL_POSITION, Light_Pos);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Dif);
    glLightfv(GL_LIGHT1, GL_POSITION, Light_Pos2);
    glEnable(GL_COLOR_MATERIAL);
    //    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
    //    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 90.0f);
    glClearColor(BG_Color[0], BG_Color[1], BG_Color[2], BG_Color[3]);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_POLYGON_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // GL - 2D Texture
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // Game
    Reset_View();
    Face[FACE_FRONT].f = 2;
    Face[FACE_FRONT].d = 1;
    Face[FACE_LEFT].f = 0;
    Face[FACE_LEFT].d = -1;
    Face[FACE_RIGHT].f = 0;
    Face[FACE_RIGHT].d = 1;
    Face[FACE_TOP].f = 1;
    Face[FACE_TOP].d = 1;
    Face[FACE_BOTTOM].f = 1;
    Face[FACE_BOTTOM].d = -1;
    Face[FACE_BACK].f = 2;
    Face[FACE_BACK].d = -1;
    Init_Font();
    Create_Image_Logo();
    Create_Image_Font(&Img_PressAnyKey, "Press Any Key", SMALL, B_Color_White);
    Create_Rect_Image(&Rct_PressAnyKey, &Img_PressAnyKey, (WIDTH - Img_PressAnyKey.w) / 2.0f, POS_PRESSANYKEY);
    Create_Image_Font(&Img_GameOver, "Game Over", LARGE, B_Color_Red);
    Create_Rect_Image(&Rct_GameOver, &Img_GameOver, (WIDTH - Img_GameOver.w) / 2.0f, POS_GAMEOVER);
    Create_Image_Font(&Img_Prepare[0], "3 . . .", MEDIUM, B_Color_White);
    Create_Image_Font(&Img_Prepare[1], "2 . . .", MEDIUM, B_Color_White);
    Create_Image_Font(&Img_Prepare[2], "1 . . .", MEDIUM, B_Color_White);
    int i;
    for (i = 0; i < 3; i++)
        Create_Rect_Image(&Rct_Prepare[i], &Img_Prepare[i], (WIDTH - Img_Prepare[i].w) / 2.0f, POS_PREPARE);
    Load_Map();
    Reload_Game();
    for (i = 0; i < 5; i++)
        Score_Animate_Offset[i] = -i * 8.0f;
    for (i = 5; i < 10; i++)
        Score_Animate_Offset[i] = (i - 10) * 8.0f;
    Init_Sound();
}
