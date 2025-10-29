typedef struct FighterAnim FighterAnim;
typedef struct Entity Entity;

Entity* rightfighterdisplay;
void rightfighterdisplay_init();
void rightfighterdisplay_set_fighter(FighterAnim* fighter);
void rightfighterdisplay_select(int select);