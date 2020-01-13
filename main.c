#include "main.h"

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

void Switch() {
    if (Time_Rotate == MAX_TIME_ROTATE) {
        printf("OK ");
        Time_Rotate = 0;
        Snake_Pos[0].V = New_V;
        Snake_Pos[0].Drt = New_Drt;
        Switch_Func[Key_Current]();
        Offset_Time = OFFSET_TIME_ROTATE;
        Offset_Size = 1.0f / Offset_Time;
    }
}

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

void Set_Offset_x_y() {
    zo = -ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = yo = 0.0f;
    Snake_Pos[0].V = 1;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 0;
    New_Drt = -Face[Face_Current].d;
    printf("xy\n");
}

void Set_Offset_x_z() {
    yo = ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = zo = 0.0f;
    Snake_Pos[0].V = 2;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 0;
    New_Drt = -Face[Face_Current].d;
    printf("xz\n");
}

void Set_Offset_y_x() {
    zo = ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = yo = 0.0f;
    Snake_Pos[0].V = 0;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 1;
    New_Drt = -Face[Face_Current].d;
    printf("yx\n");
}

void Set_Offset_y_z() {
    xo = -ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    yo = zo = 0.0f;
    Snake_Pos[0].V = 2;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 1;
    New_Drt = -Face[Face_Current].d;
    printf("yz\n");
}

void Set_Offset_z_x() {
    yo = -ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    xo = zo = 0.0f;
    Snake_Pos[0].V = 0;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 2;
    New_Drt = -Face[Face_Current].d;
    printf("zx\n");
}

void Set_Offset_z_y() {
    xo = ROTATE_OFFSET * Face[Face_Current].d * Face[Face_Next].d;
    yo = zo = 0.0f;
    Snake_Pos[0].V = 1;
    Snake_Pos[0].Drt = Face[Face_Next].d;
    New_V = 2;
    New_Drt = -Face[Face_Current].d;
    printf("zy\n");
}

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

void Reset_View() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, WIDTH, HEIGHT);
    gluPerspective(20.0, 1.0, 1.0, 150.0);
    glTranslatef(0.0f, 0.0f, -94.0f);
    //	glFrustum(-0.4, 0.4, -0.4, 0.4, 1.0, 200.0);
    //	glTranslatef(0.0f, 0.0f, -50.0f);
    glRotatef(x_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(y_angle, 0.0f, 1.0f, 0.0f);
    glRotatef(z_angle, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void Reload_View() {
    glMatrixMode(GL_PROJECTION);
    glRotatef(xo, 1.0f, 0.0f, 0.0f);
    glRotatef(yo, 0.0f, 1.0f, 0.0f);
    glRotatef(zo, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
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

void Draw_Game() {
    int i, j;
    //        for (i = 1; i < 19; i++) {
    //            glBegin(GL_LINES);
    //            glVertex3f(-9.0f, i - 9.0f, 9.1f);
    //            glVertex3f(9.0f, i - 9.0f, 9.1f);
    //            glVertex3f(i - 9.0f, -9.0f, 9.1f);
    //            glVertex3f(i - 9.0f, 9.0f, 9.1f);
    //            glEnd();
    //        }
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Cube);
    glutSolidCube(18.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Wall);
    Draw_Face_Front();
    Draw_Face_Left();
    Draw_Face_Right();
    Draw_Face_Top();
    Draw_Face_Bottom();
    Draw_Face_Back();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Food);
    for (i = 0; i < MAX_FOOD; i++) {
        glLoadIdentity();
        glTranslatef(Food_Pos[i].x - 9.5f, Food_Pos[i].y - 9.5f, Food_Pos[i].z - 9.5f);
        glutSolidCube(1.0);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Snake);
    for (i = 0; i < Snake_Length; i++) {
        glLoadIdentity();
        glTranslatef(Snake_Pos[i].x - 9.5f, Snake_Pos[i].y - 9.5f, Snake_Pos[i].z - 9.5f);
        glutSolidCube(1.0);
    }
    if (Snake_Length > 0) {
        Translate_Offset(&Snake_Pos[Snake_Length]);
        glutSolidCube(1.0);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse_Snake_Head);
    Translate_Offset(&Snake_Pos[0]);
    glutSolidCube(1.2);
}

void Draw_2D_Begin() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
}

void Draw_2D_End() {
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void Game_Display_Idle() {
    Draw_Game();
    Draw_2D_Begin();
    Map_Texture(&Img_Logo);
    Draw_Rect(&Rct_Logo);
    glColor4f(1.0f,1.0f,1.0f, (40.0f-Idle_Stt)/40);
    Map_Texture(&Img_PressAnyKey);
    Draw_Rect(&Rct_PressAnyKey);
    glColor3f(1.0f,1.0f,1.0f);
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
}

void Game_Display_GameOver() {
    Draw_Game();
}

void Game_Process_Idle() {
	Idle_Stt+=Idle_Stt_Offset;
	if (Idle_Stt==0||Idle_Stt==40)
		Idle_Stt_Offset=-Idle_Stt_Offset;
    xo = 0.2f;
    yo = 0.4f;
    zo = 0.0f;
    Reload_View();
}

void Game_Process_Prepare() {
    Game_Timer++;
    if (Game_Timer == 50) {
    	Game_Timer=0;
    	Prepare_Stt++;
    	if (Prepare_Stt==3){
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
            Game_Stt = GAME_STT_GAMEOVER;
        }
        int n = Check_Is_Food(Snake_Pos[0].x, Snake_Pos[0].y, Snake_Pos[0].z);
        if (n >= 0) {
            Create_Food(n);
            Add_Part();
        }
        if (Pressed_Arrow != -1 && Time_Rotate == MAX_TIME_ROTATE) {
            Arrow_Func[Pressed_Arrow]();
            Pressed_Arrow = -1;
        }
    }
}

void Game_Process_GameOver() {
    Game_Timer++;
    if (Game_Timer == 40) {
        Game_Stt = GAME_STT_IDLE;
        glutKeyboardFunc(Keyboard);
    }
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
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
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
    glEnable(GL_DEPTH_TEST);
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
    Create_Image_Font(&Img_PressAnyKey, "Press Any Key", SMALL, Color_White);
    Create_Rect_Image(&Rct_PressAnyKey, &Img_PressAnyKey, (WIDTH - Img_PressAnyKey.w) / 2.0f, 400.0f);
    Create_Image_Font(&Img_GameOver, "Game Over", LARGE, Color_Red);
    Create_Rect_Image(&Rct_GameOver, &Img_GameOver, (WIDTH - Img_GameOver.w) / 2.0f, 300.0f);
    Create_Image_Font(&Img_Prepare[0], "3 . . .", MEDIUM, Color_White);
    Create_Image_Font(&Img_Prepare[1], "2 . . .", MEDIUM, Color_White);
    Create_Image_Font(&Img_Prepare[2], "1 . . .", MEDIUM, Color_White);
    int i;
    for (i=0;i<3;i++)
    	Create_Rect_Image(&Rct_Prepare[i], &Img_Prepare[i], (WIDTH - Img_Prepare[i].w) / 2.0f, 200.0f);
    Load_Map();
    Reload_Game();
}

void Draw_Face_Front() {
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            if (Map[i][j][19] > 0) {
                glLoadIdentity();
                glTranslatef(i - 9.5f, j - 9.5f, 9.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Left() {
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            if (Map[0][i][j] > 0) {
                glLoadIdentity();
                glTranslatef(-9.5f, i - 9.5f, j - 9.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Right() {
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            if (Map[19][i][j] > 0) {
                glLoadIdentity();
                glTranslatef(9.5f, i - 9.5f, j - 9.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Top() {
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            if (Map[i][19][j] > 0) {
                glLoadIdentity();
                glTranslatef(i - 9.5f, 9.5f, j - 9.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Bottom() {
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            if (Map[i][0][j] > 0) {
                glLoadIdentity();
                glTranslatef(i - 9.5f, -9.5f, j - 9.5f);
                glutSolidCube(1.0);
            }
}

void Draw_Face_Back() {
    int i, j;
    for (i = 1; i < 19; i++)
        for (j = 1; j < 19; j++)
            if (Map[i][j][0] > 0) {
                glLoadIdentity();
                glTranslatef(i - 9.5f, j - 9.5f, -9.5f);
                glutSolidCube(1.0);
            }
}

void Translate_Offset(s_Snake_Pos *s) {
    glLoadIdentity();
    switch (s->V) {
    case 0:
        glTranslatef(s->x + s->Drt * Offset_Size * Snake_Offset - 9.5f, s->y - 9.5f, s->z - 9.5f);
        break;
    case 1:
        glTranslatef(s->x - 9.5f, s->y + s->Drt * Offset_Size * Snake_Offset - 9.5f, s->z - 9.5f);
        break;
    case 2:
        glTranslatef(s->x - 9.5f, s->y - 9.5f, s->z + s->Drt * Offset_Size * Snake_Offset - 9.5f);
        break;
    }
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Game_Display_Func[Game_Stt]();
    glLoadIdentity();
    glutSwapBuffers();
}

void Resize(int x, int y) {
    glutPositionWindow(POS_X, POS_Y);
    glutReshapeWindow(WIDTH, HEIGHT);
}

void Keyboard(GLubyte key, int x, int y) {
    if (Is_First_Time)
        Is_First_Time = 0;
    else
        Reload_Game();
    Reset_View();
    Game_Timer = 0;
    glutKeyboardFunc(NULL);
    Game_Stt = GAME_STT_PREPARE;
    Prepare_Stt=0;
}

void Special(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        Pressed_Arrow = KEY_UP;
        break;
    case GLUT_KEY_RIGHT:
        Pressed_Arrow = KEY_RIGHT;
        break;
    case GLUT_KEY_DOWN:
        Pressed_Arrow = KEY_DOWN;
        break;
    case GLUT_KEY_LEFT:
        Pressed_Arrow = KEY_LEFT;
        break;
    }
}

void Timer(int value) {
    Game_Process_Func[Game_Stt]();
    glutPostRedisplay();
    glutTimerFunc(INTERVAL, Timer, 0);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
    POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
    glutInitWindowPosition(POS_X, POS_Y);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Snake Cube");
    Init_Game();
    glutKeyboardFunc(Keyboard);
    glutTimerFunc(0, Timer, 0);
    glutDisplayFunc(Display);
    //    glutReshapeFunc(Resize);
    glutMainLoop();
    return 0;
}
