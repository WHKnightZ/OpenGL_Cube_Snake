#include "main.h"

void Init_Font() {
    char Font_Name[][7] = {"Small", "Medium", "Large"};
    char str[50];
    int k;
    Image Img_Font, Img_Char_Tmp;
    for (k = 0; k < 3; k++) {
        sprintf(str, "Fonts/%s.png", Font_Name[k]);
        Load_Texture(&Img_Font, str);
        sprintf(str, "Fonts/%s.fnt", Font_Name[k]);
        FILE *f = fopen(str, "r");
        int i, n;
        int id, x, y, w, h, xo, yo, wf, hf;
        fscanf(f, "%d %d", &n, &hf);
        for (i = 0; i < n; i++) {
            fscanf(f, "%d %d %d %d %d %d %d %d", &id, &x, &y, &w, &h, &xo, &yo, &wf);
            Crop_Image(&Img_Font, &Img_Char_Tmp, x, y, w, h);
            Create_Image(&Img_Char[k][id], wf, hf);
            Mix_Image_NoBG(&Img_Char[k][id], &Img_Char_Tmp, xo, yo);
            Delete_Image(&Img_Char_Tmp);
        }
        Delete_Image(&Img_Font);
    }
}

void Create_Image_Logo() {
    Image Img_Tmp;
    Rect Rct_Tmp;
    char Logo[] = "Cube Snake";
    int size = LARGE;
    int offset = Font_Offset_Shadow[size];
    int w = offset, h = Img_Char[size][65].h + offset;
    int x;
    char *c = Logo;
    while (*c != '\0') {
        w += Img_Char[size][*c].w;
        c++;
    }
    Create_Image(&Img_Tmp, w, h);
    c = Logo;
    x = 0;
    while (*c != '\0') {
        Mix_Image_Color_NoBG(&Img_Tmp, &Img_Char[size][*c], x + offset, offset, B_Color_Shadow);
        x += Img_Char[size][*c].w;
        c++;
    }
    c = Logo;
    x = 0;
    while (*c != ' ') {
        Mix_Image_Color(&Img_Tmp, &Img_Char[size][*c], x, 0, B_Color_Red);
        x += Img_Char[size][*c].w;
        c++;
    }
    x += Img_Char[size][*c].w;
    c++;
    while (*c != '\0') {
        Mix_Image_Color(&Img_Tmp, &Img_Char[size][*c], x, 0, B_Color_Blue);
        x += Img_Char[size][*c].w;
        c++;
    }
    Rct_Tmp.Left = (WIDTH - w) / 2.0f;
    Rct_Tmp.Right = Rct_Tmp.Left + w;
    Rct_Tmp.Bottom = POS_LOGO;
    Rct_Tmp.Top = Rct_Tmp.Bottom + h;
    Img_Logo = Img_Tmp;
    Rct_Logo = Rct_Tmp;
}

void Create_Image_Font(Image *Img, char Text[], int size, unsigned char Color[]) {
    int offset = Font_Offset_Shadow[size];
    int w = offset, h = Img_Char[size][65].h + offset;
    int x;
    char *c = Text;
    while (*c != '\0') {
        w += Img_Char[size][*c].w;
        c++;
    }
    Create_Image(Img, w, h);
    c = Text;
    x = 0;
    while (*c != '\0') {
        Mix_Image_Color_NoBG(Img, &Img_Char[size][*c], x + offset, offset, B_Color_Shadow);
        x += Img_Char[size][*c].w;
        c++;
    }
    c = Text;
    x = 0;
    while (*c != '\0') {
        Mix_Image_Color(Img, &Img_Char[size][*c], x, 0, Color);
        x += Img_Char[size][*c].w;
        c++;
    }
}

void Create_Rect_Image(Rect *Rct, Image *Img, int x, int y) {
    Rct->Left = x;
    Rct->Right = Rct->Left + Img->w;
    Rct->Bottom = y;
    Rct->Top = Rct->Bottom + Img->h;
}

void Update_Score(int n) {
    Score += n;
    int x = Score;
    Score_Length = 0;
    int Size = 0, Size_s;
    do {
        Score_Array[Score_Length] = x % 10 + 48;
        Size += Img_Char[MEDIUM][Score_Array[Score_Length]].w + 6.0f;
        x /= 10;
        Score_Length++;
    } while (x > 0);
    Score_Start_X = (WIDTH - Size) / 2.0f;
}

void Draw_Score() {
    int i;
    glColor4f(0.0f, 0.0f, 0.0f, 0.75f);
    Rct_Score.Right = Score_Start_X + Font_Offset_Shadow[MEDIUM];
    Rct_Score.Bottom = Score_Start_Y + Font_Offset_Shadow[MEDIUM];
    Rct_Score.Top = Rct_Score.Bottom + Img_Char[MEDIUM][65].h;
    for (i = Score_Length - 1; i >= 0; i--) {
        Rct_Score.Left = Rct_Score.Right + 6.0f;
        Rct_Score.Right = Rct_Score.Left + Img_Char[MEDIUM][Score_Array[i]].w;
        Map_Texture(&Img_Char[MEDIUM][Score_Array[i]]);
        Draw_Rect(&Rct_Score);
    }
    glColor3f(1.0f, 1.0f, 1.0f);
    Rct_Score.Right = Score_Start_X;
    Rct_Score.Bottom = Score_Start_Y;
    Rct_Score.Top = Rct_Score.Bottom + Img_Char[MEDIUM][65].h;
    for (i = Score_Length - 1; i >= 0; i--) {
        Rct_Score.Left = Rct_Score.Right + 6.0f;
        Rct_Score.Right = Rct_Score.Left + Img_Char[MEDIUM][Score_Array[i]].w;
        Map_Texture(&Img_Char[MEDIUM][Score_Array[i]]);
        Draw_Rect(&Rct_Score);
    }
}
